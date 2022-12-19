/*
 * inicializaciones.c
 *
 *  Created on: 13 nov. 2022
 *      Author: crist
 */


#include "main.h"
#include "cmsis_os.h"

extern I2C_HandleTypeDef hi2c1;
extern SPI_HandleTypeDef hspi1;
extern TIM_HandleTypeDef htim4;

extern CartelLed_TypeDef Cartel_Led;

extern xSemaphoreHandle sem_rx;
extern xSemaphoreHandle sem_push1;
extern xSemaphoreHandle sem_push2;
extern xSemaphoreHandle sem_push3;
extern xSemaphoreHandle sem_rutina_normal;
extern xSemaphoreHandle sem_rutina_alt;

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim2;
extern BH1750_device_t* test_dev;
extern char MSG[]; // 33 lenght

void inicializar_semaforos (void)
{
	sem_rx = xSemaphoreCreateBinary();
	sem_push1 = xSemaphoreCreateBinary();
	sem_push2 = xSemaphoreCreateBinary();
	sem_push3 = xSemaphoreCreateBinary();
	sem_rutina_normal = xSemaphoreCreateBinary();
	sem_rutina_alt = xSemaphoreCreateBinary();

	xSemaphoreTake(sem_rx,0);
	xSemaphoreTake(sem_push1,0);
	xSemaphoreTake(sem_push2,0);
	xSemaphoreTake(sem_push3,0);
	xSemaphoreTake(sem_rutina_normal,0);
	xSemaphoreTake(sem_rutina_alt,0);
}

void inicializar_cartel(void)
{
	Actualizar_FechaHora();
	sprintf((char *)Cartel_Led.temp,"TEMP:20,2 C  HUM:50%%");
	sprintf((char *)Cartel_Led.mensaje,"MSJ BT VACIO");
	sprintf((char *)Cartel_Led.mensaje_sd,"MSJ SD VACIO");
}

void inicializar_BH1750 (void)
{
	test_dev = BH1750_init_dev_struct(&hi2c1, "test device", true);
	BH1750_init_dev(test_dev);
}

void inicializar_Matrix (void)
{
	DOT_MATRIX_Init_TMR(&hspi1, &htim4);
}

void inicializar_perifericos(void)
{
	inicializar_semaforos ();
	inicializar_cartel();
	inicializar_BH1750();
	inicializar_Matrix();
	HAL_TIM_Base_Start(&htim3);
	//HAL_TIM_Base_Start_IT(&htim2);


}

void inicializar_tareas (void)
{
	xTaskCreate(tarea_uart,"uart2",configMINIMAL_STACK_SIZE,NULL,3,NULL);
	xTaskCreate(tarea_actualizarRTC,"actualizarRTC",configMINIMAL_STACK_SIZE,NULL,3,NULL);
	xTaskCreate(tarea_acciones_pulsador,"AccionesPulsador",configMINIMAL_STACK_SIZE,NULL,3,NULL);
	xTaskCreate( tarea_cartel, "tarea_cartel", configMINIMAL_STACK_SIZE, NULL, 3, NULL );
	xTaskCreate(tarea_pulsador1,"Pulsador1",configMINIMAL_STACK_SIZE,NULL,2,NULL);
	xTaskCreate(tarea_pulsador2,"Pulsador2",configMINIMAL_STACK_SIZE,NULL,2,NULL);
	xTaskCreate(tarea_pulsador3,"Pulsador3",configMINIMAL_STACK_SIZE,NULL,2,NULL);
	xTaskCreate(tarea_sd,"SD",configMINIMAL_STACK_SIZE,NULL,2,NULL);
	xTaskCreate( tarea_bh1750, "tarea_bh1750", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( tarea_DHT11, "tarea_DHT11", configMINIMAL_STACK_SIZE, NULL, 1, NULL );

}
