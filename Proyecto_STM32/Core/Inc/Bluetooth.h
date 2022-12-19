/*
 * Bluetooth.h
 *
 *  Created on: 6 oct. 2022
 *      Author: crist
 */

#ifndef INC_BLUETOOTH_H_
#define INC_BLUETOOTH_H_

//#include "stm32f1xx_hal.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LONG_DATOS_BT 30

#define STR_MAX_LEN 30
#define OFF 0
#define ON 1

/* Posicion de los valores en la lista de comandos */
//Posicion para establecer fecha
//dd/mm/yyyy
#define POS_FECHA 4
#define CANT_FECHA 10
//Posicion para establecer la Hora
//hh:mm:ss
#define POS_HORA 4
#define CANT_HORA 5
#define CANT_SEG 2

#define POS_TEMP 5
#define CANT_TEMP 2

typedef struct {
	uint8_t fecha[13];
	uint8_t hora[8],segs[6];
	uint8_t temp[25];
	uint8_t mensaje[STR_MAX_LEN];
	uint8_t mensaje_sd[STR_MAX_LEN];

}CartelLed_TypeDef;


void f_comandos(uint8_t );



#endif /* INC_BLUETOOTH_H_ */
