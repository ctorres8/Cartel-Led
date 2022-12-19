/*
 * fatfs_app.c
 *
 *  Created on: 2 nov. 2022
 *      Author: Jonathan
 */
#include "fatfs_app.h"



extern FATFS USERFatFS;
FIL userFILE;
#define MSG_FILE "TDII.txt"

uint8_t LeerDatos(char* dataSD)
{
	uint8_t i;
	uint8_t retUSER = FR_OK;
	static uint8_t msg_pos = 0; /* para recordar la posición del msg en el file */
	char msg_read[40];
	static TCHAR* by_read = NULL;		/* bytes leidos */

	memset(msg_read,'\0',40);
	//f_mount(&USERFatFS, "", 0);
	/* Abro un archivo y verifico */
	retUSER =f_open(&userFILE, MSG_FILE, FA_READ);
	if(retUSER != FR_OK){
		strcpy(dataSD,"Archivo no existente!");
		return retUSER;
	}

	//f_lseek(&userFILE, by_read); Se puede implementar moviendome dentro del file

	/* los mensajes se leerán de forma ciclica, recordando donde estaba */
	for( i = 0; i <= msg_pos; i++)
	{
		by_read = f_gets(msg_read,sizeof(msg_read),&userFILE);
	}
	if( by_read == 0)/* tengo EOF o archivo vacio */
	{
		strcpy(dataSD,"Archivo vacio!");/* me anticipo ante un posible archivo vacio*/
		by_read = f_gets(msg_read,sizeof(msg_read),&userFILE);
		msg_pos = 0;
		/* si fue EOF, leerá el primer msg y resetea el contador */
	}
	if(by_read != 0){
		strcpy(dataSD,msg_read);
	}

	f_close(&userFILE);
	return retUSER;
}

uint8_t InicializarSd(void)
{
	return f_mount(&USERFatFS, "", 0);
}
uint8_t DetectarSd(void)
{
	return 0;// HAL_GPIO_ReadPin(SD_CD_GPIO_Port,SD_CD_Pin);
	/*pregunto por el pin card detect */
}

