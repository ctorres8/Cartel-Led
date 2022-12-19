/*
 * tareas_rutina.c
 *
 *  Created on: Dec 5, 2022
 *      Author: crist
 */
#include "main.h"
#include "cmsis_os.h"

extern I2C_HandleTypeDef hi2c1;
extern SPI_HandleTypeDef hspi1;
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart1;

extern CartelLed_TypeDef Cartel_Led;

extern xSemaphoreHandle sem_rx;
extern xSemaphoreHandle sem_push1;
extern xSemaphoreHandle sem_push2;
extern xSemaphoreHandle sem_push3;
extern xSemaphoreHandle sem_rutina_normal;
extern xSemaphoreHandle sem_rutina_alt;


extern BH1750_device_t* test_dev;
extern char MSG[]; // 33 lenght

uint8_t dataRx[LONG_DATOS_BT];
uint8_t flag_rutina=0;

extern char mensaje_sd[];
extern uint32_t timer_msg_sd;


void tarea_bh1750( void *pvParameters )
{
	uint8_t i =0;
	for (;;){
		BH1750_get_lumen(test_dev);
		if (test_dev->value>1000){
			  i = 10;
		  }
		  else if (test_dev->value>200){
			  i = 5;
		  }
		  else if (test_dev->value>100){
				  i = 3;
			  }
		  else if (test_dev->value>50){
			  i = 2;
		  }
		  else if (test_dev->value>20){
			  i = 1;
		  }
		  else {
			  i = 0;
		  }
		DOT_MATRIX_Brightness(i);
		vTaskDelay(2000);
		}

}

void tarea_cartel( void *pvParameters )
{
	uint8_t i =0;

	MATRIX_DisplayMessage(MATRIX_DISPLAY_UNIT1, MSG, strlen(MSG)+2);
	vTaskDelay(10000);

	for (;;){
		if (flag_rutina!=0) xSemaphoreTake(sem_rutina_normal,HAL_MAX_DELAY);

		memset(MSG,'\0',strlen(MSG));
		DOT_MATRIX_Clear(&hspi1);

		//if(i==-1)

		if (i==0)
			sprintf(MSG,"%s ",(char *)Cartel_Led.fecha);

		else if (i==1)
			sprintf(MSG,"%s ",(char *)Cartel_Led.hora);

		else if (i==2)
			sprintf(MSG,"%s ",(char *)Cartel_Led.temp);

		MATRIX_DisplayMessage(MATRIX_DISPLAY_UNIT1, MSG, strlen(MSG)+2);
		i++;
		i%=3;
		if(i!=0) vTaskDelay(20000);
		else vTaskDelay(24000);

		}

}

void tarea_acciones_pulsador (void *p)
{
	uint8_t fecha_ant[13]="00-00-0000";
	uint8_t hora_ant[8]="11:11";
	uint8_t temp_ant[13]="TEMP: 12 C";
	uint8_t msj_ant[32],msj_ant_sd[32];
	while(1)
	{
		if (!flag_rutina) xSemaphoreTake(sem_rutina_alt,HAL_MAX_DELAY);

		if(flag_rutina==1)
		{
			if(strcmp((char*)fecha_ant,(char *)Cartel_Led.fecha)!=0)
			{
				memset(MSG,'\0',strlen(MSG));
				DOT_MATRIX_Clear(&hspi1);
				sprintf(MSG,"%s ",(char *)Cartel_Led.fecha);
				strcpy((char*)fecha_ant,(char *)Cartel_Led.fecha);
				MATRIX_DisplayMessage(MATRIX_DISPLAY_UNIT1, MSG, strlen(MSG)+2);
			}
		}
		else if(flag_rutina==2)
		{
			if(strcmp((char*)hora_ant,(char *)Cartel_Led.hora)!=0)
			{
				memset(MSG,'\0',strlen(MSG));
				DOT_MATRIX_Clear(&hspi1);
				sprintf(MSG,"%s ",(char *)Cartel_Led.hora);
				strcpy((char*)hora_ant,(char *)Cartel_Led.hora);
				MATRIX_DisplayMessage(MATRIX_DISPLAY_UNIT1, MSG, strlen(MSG)+2);
			}
		}
		else if(flag_rutina==3)
		{
			if(strcmp((char*)temp_ant,(char *)Cartel_Led.temp)!=0)
			{
				memset(MSG,'\0',strlen(MSG));
				DOT_MATRIX_Clear(&hspi1);
				sprintf(MSG,"%s ",(char *)Cartel_Led.temp);
				strcpy((char*)temp_ant,(char *)Cartel_Led.temp);
				MATRIX_DisplayMessage(MATRIX_DISPLAY_UNIT1, MSG, strlen(MSG)+2);
			}
		}
		else if(flag_rutina==4)
		{
			if(strcmp((char*)msj_ant,(char *)Cartel_Led.mensaje)!=0)
			{
				memset(MSG,'\0',strlen(MSG));
				memset((char*) msj_ant, '\0',strlen((char *)msj_ant));
				DOT_MATRIX_Clear(&hspi1);
				sprintf(MSG,"%s ",(char *)Cartel_Led.mensaje);
				sprintf((char*)msj_ant,"%s ",(char *)Cartel_Led.mensaje);
				//strcpy((char*)msj_ant,(char *)Cartel_Led.mensaje);
				MATRIX_DisplayMessage(MATRIX_DISPLAY_UNIT1, MSG, strlen(MSG)+2);
			}
		}
		else if(flag_rutina==5)
		{
			if(strcmp((char*)msj_ant_sd,(char*)Cartel_Led.mensaje_sd)!=0)
			{
				memset(MSG,'\0',strlen(MSG));
				memset((char*) msj_ant_sd,'\0',strlen((char*)msj_ant_sd));
				DOT_MATRIX_Clear(&hspi1);
				sprintf(MSG,"%s ",(char*)Cartel_Led.mensaje_sd);
				sprintf((char*)msj_ant_sd,"%s ",(char*)Cartel_Led.mensaje_sd);
				MATRIX_DisplayMessage(MATRIX_DISPLAY_UNIT1, MSG, strlen(MSG)+2);
			}
		}
		vTaskDelay(500);
	}
}

void tarea_uart (void *p)
{
	//Recibo en forma de interrupcion una cantidad estimada de datos o hasta que llega a un estado idle (hay '\0' - corta antes)
	HAL_UARTEx_ReceiveToIdle_IT(&huart1, dataRx, sizeof(dataRx));
	while(1)
	{
		xSemaphoreTake(sem_rx,portMAX_DELAY);

		if(!strncmp((char*)dataRx,"ATY",3))
		{
				f_comandos(dataRx[3]);//Acá podemos enviar unos comandos que puede servir como mantenimiento (sincronización, chequear retorno)
		}

			else
			{
				memset((char*)Cartel_Led.mensaje,'\0',LONG_DATOS_BT); //borro el mensaje guardado en el struct del cartel
				strncpy((char*)Cartel_Led.mensaje,(char*)dataRx,strlen((char*)dataRx)-2); //cargo un nuevo mensaje y le quito el \r y \n
			}
		memset((char*)dataRx,'\0',LONG_DATOS_BT); //borro el buffer de recepcion
		HAL_UARTEx_ReceiveToIdle_IT(&huart1, dataRx, sizeof(dataRx)); //habilito la uart para recibir de nuevo
	}
}

void tarea_actualizarRTC (void *p)
{
	while(1)
	{
		Actualizar_FechaHora();
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void tarea_pulsador1 (void *p)
{
	uint8_t veces_push1=0;
	uint8_t flag_rutina_ant=0;
	while(1)
	{
		xSemaphoreTake(sem_push1,portMAX_DELAY);
		//memset(MSG,'\0',strlen(MSG));
		//DOT_MATRIX_Clear(&hspi1);
		if(flag_rutina_ant!=flag_rutina) veces_push1=0;
		else veces_push1++;

		switch(veces_push1)
		{
			case 1 :
					flag_rutina=1;
					break;
			case 2 :
					flag_rutina=2;
					break;
			case 3 :
					flag_rutina=3;
					break;
			default:
					veces_push1 %= 4;
					flag_rutina=0;
					break;
		}
		flag_rutina_ant=flag_rutina;
		if (!flag_rutina) xSemaphoreGive(sem_rutina_normal);
		else xSemaphoreGive(sem_rutina_alt);
	}
}

void tarea_pulsador2 (void *p)
{
	uint8_t veces_push2=0;
	uint8_t flag_rutina_ant=0;
	while(1)
	{
		xSemaphoreTake(sem_push2,portMAX_DELAY);
		if(flag_rutina_ant!=flag_rutina) veces_push2=0;
		else veces_push2++;
		switch(veces_push2)
		{
			case 1 :
					flag_rutina=4;
					break;
			case 2 :
					flag_rutina=5;
					break;

			default:
					//veces_push2 %= 4;
					veces_push2 =0;
					flag_rutina=0;
					break;
		}
		flag_rutina_ant=flag_rutina;
		if (!flag_rutina) xSemaphoreGive(sem_rutina_normal);
		else xSemaphoreGive(sem_rutina_alt);
	}
}

void tarea_pulsador3 (void *p)
{
	uint8_t veces_push3=0;
	while(1)
	{
		xSemaphoreTake(sem_push3,portMAX_DELAY);
		veces_push3++;
		switch(veces_push3)
		{
			case 1 :
					MATRIX_SCROLL_SetSpeed(0,100);
					break;
			case 2 :
					MATRIX_SCROLL_SetSpeed(0,500);
					break;
			case 3 :
					MATRIX_SCROLL_SetSpeed(0,1000);
					break;
		}
		veces_push3 %= 4;
	}
}

void tarea_DHT11(void *p)
{
	uint8_t RHI, RHD, TCI, TCD, SUM;
	//uint8_t tCelsius = 0;

	while(1)
	{

			DHT11_Start(); //Siempre que solicite datos
			 RHI = DHT11_Read(); // Relative humidity integral
			 RHD = DHT11_Read(); // Relative humidity decimal
			 TCI = DHT11_Read(); // Celsius integral
			 TCD = DHT11_Read(); // Celsius decimal
			 SUM = DHT11_Read(); // Check sum

			 if (RHI + RHD + TCI + TCD == SUM)
			 {
				 sprintf((char *)Cartel_Led.temp,"TEMP:%d.%1d C  HUM:%d%%",TCI,TCD,RHI);
				 //tCelsius = TCI;//(float)TCI + (float)(TCD/10.0);
			 }
			vTaskDelay(5*60000);

	}
}

void tarea_sd(void *p)
{
	char bufferSd[STR_MAX_SD];
	static uint8_t estadoSd = NO_INIT;


	vTaskDelay(1000);
	for (;;){

				if(!DetectarSd() && estadoSd !=INIT) /* sd conectada? */
				{
					estadoSd = InicializarSd();
				}
				else if(estadoSd != INIT){
					//actualizo cartel "inserte tarjeta sd"
					memset((char*)Cartel_Led.mensaje_sd, '\0',STR_MAX_SD);
					strcpy((char*)Cartel_Led.mensaje_sd, "Inserte tarjeta Sd");
					//memset(mensaje_sd, '\0',STR_MAX_SD);
					//strcpy(mensaje_sd, "Inserte tarjeta Sd");
				}

				if(estadoSd==INIT){
				memset(bufferSd,'\0',STR_MAX_SD);
				estadoSd = LeerDatos(bufferSd);
				memset((char*)Cartel_Led.mensaje_sd, '\0',STR_MAX_SD);
				strncpy((char*)Cartel_Led.mensaje_sd, bufferSd,strlen(bufferSd)-1);
				}


			HAL_Delay(100);

			vTaskDelay(30000);
		}
}
