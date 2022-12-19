/*
 * RTC.c
 *
 *  Created on: 6 oct. 2022
 *      Author: crist
 */


#include "RTC.h"
#include "Bluetooth.h"

RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

extern uint8_t dataRx[];
extern RTC_HandleTypeDef hrtc;
extern CartelLed_TypeDef Cartel_Led;


void Inicializar_RTC (void)
{
	sDate.Date = 25;
	sDate.Month = 9;
	sDate.Year = 22;
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

	sTime.Hours = 23;
	sTime.Minutes = 54;
	sTime.Seconds = 20;
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
}

void Actualizar_FechaHora(void)
{
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

	sprintf((char *)Cartel_Led.hora,"%02d:%02d",sTime.Hours,sTime.Minutes);
	sprintf((char*)Cartel_Led.segs,":%02d",sTime.Seconds);

	sprintf((char *)Cartel_Led.fecha,"%02d-%02d-%04d",sDate.Date,sDate.Month,sDate.Year+2000);
}
void RTC_SetFecha(void)
{
	char y[3],m[3],d[3];

	memcpy(d,&dataRx[POS_DIA],2);
	memcpy(m,&dataRx[POS_MES],2);
	memcpy(y,&dataRx[POS_ANIO],2);

	sDate.Date = atoi(d);
	sDate.Month = atoi(m);
	sDate.Year = atoi(y);
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}

void RTC_SetHora (void)
{
	char hrs[3],mins[3],segs[3];

	memcpy(hrs,&dataRx[POS_HS],2);
	memcpy(mins,&dataRx[POS_MIN],2);
	memcpy(segs,&dataRx[POS_SEG],2);

	sTime.Hours = atoi(hrs);
	sTime.Minutes = atoi(mins);
	sTime.Seconds = atoi(segs);

	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
}

void RTC_GetHora (void)
{
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
}

void RTC_GetFecha(void)
{
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}
