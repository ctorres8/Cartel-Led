/*
 * Bluetooth.c
 *
 *  Created on: 7 oct. 2022
 *      Author: crist
 */

#include "main.h"
#include "cmsis_os.h"

extern UART_HandleTypeDef huart1;
extern CartelLed_TypeDef Cartel_Led;
extern uint8_t dataRx[];

extern xSemaphoreHandle sem_rx;

extern char *MSG;

void f_comandos(uint8_t Comando)
{
	uint8_t hora_tx[16];
	uint8_t fecha_tx[16];
	uint8_t temp_tx[28];
	uint8_t msj_tx[32];
	uint8_t SensorLuz = OFF;

	switch (Comando)
	{
		case 'F' :  // Configuro la fecha
					if(dataRx[POS_FECHA]>47&&dataRx[POS_FECHA+CANT_FECHA-1]<58)
					{
						RTC_SetFecha();
					}

					break;

		case 'H' :  // Configuro la hora
					if(dataRx[POS_HORA]>47&&dataRx[POS_SEG+CANT_SEG-1]<58) RTC_SetHora();

					break;

		case 'T' :  // Devuelvo el valor de la temperatura y muestro en pantalla
					sprintf((char *)temp_tx,"%s\r\n",(char*)Cartel_Led.temp);

					HAL_UART_Transmit(&huart1, temp_tx, strlen((char*)temp_tx), HAL_MAX_DELAY);

					break;

		case 'L' :  // APAGO/ ENCIENDO EL SENSOR DE LUZ
					if(!SensorLuz) SensorLuz = ON;
					else SensorLuz = OFF;
					break;

		case 'M' :	//Devuelvo el mensaje guardado
					sprintf((char *)msj_tx,"%s\r\n",(char*)Cartel_Led.mensaje);
					HAL_UART_Transmit(&huart1,msj_tx, strlen((char*)msj_tx), HAL_MAX_DELAY);

					break;

		case 'O' :  //devuelvo un OK
					HAL_UART_Transmit(&huart1, (uint8_t *)"OK\r\n", 4, HAL_MAX_DELAY);

					break;

		case 'f' :  // Devuelvo y muestro la fecha
					sprintf((char *)fecha_tx,"%s\r\n",(char *)Cartel_Led.fecha);
					HAL_UART_Transmit(&huart1, fecha_tx, strlen((char *) fecha_tx), HAL_MAX_DELAY);
					break;

		case 'h' :  // Devuelvo y muestro la hora
					sprintf((char *)hora_tx,"%s%s\r\n",(char *)Cartel_Led.hora,(char *)Cartel_Led.segs);
					HAL_UART_Transmit(&huart1, hora_tx, strlen((char *) hora_tx), HAL_MAX_DELAY);
					break;
	}

}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	UNUSED(huart);
	UNUSED(Size);

	BaseType_t p;
	xSemaphoreGiveFromISR(sem_rx,&p);//libero el semaforo de la tarea cuando terminé de recibir datos
	portEND_SWITCHING_ISR(p)
}

