/*
 * RTC.h
 *
 *  Created on: 6 oct. 2022
 *      Author: crist
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

//#include "stm32f1xx_hal.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define POS_HS 4
#define POS_MIN 7
#define POS_SEG 10
#define POS_DIA 4
#define POS_MES 7
#define POS_ANIO 12

void Inicializar_RTC (void);
void RTC_SetFecha(void);
void RTC_GetFecha (void);
void RTC_SetHora (void);
void RTC_GetHora (void);
void Actualizar_FechaHora(void);

//uint8_t time[30];
//uint8_t date[30];

#endif /* INC_RTC_H_ */
