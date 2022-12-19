/*
 * fatfs_app.h
 *
 *  Created on: 2 nov. 2022
 *      Author: Jonathan
 */

#ifndef INC_FATFS_APP_H_
#define INC_FATFS_APP_H_



#endif /* INC_FATFS_APP_H_ */


#include "stm32f4xx.h"

#include "main.h"
#include "ff.h"
#include "diskio.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define INIT 0
#define NO_INIT 1
#define STR_MAX_SD 30 /* dataSD[40]*/
#define TICK_MSG 60000 /*1 min */
#define MODO_SD 1

uint8_t InicializarSd(void);
uint8_t LeerDatos(char* dataSD);
uint8_t DetectarSd(void); /* card detect */
