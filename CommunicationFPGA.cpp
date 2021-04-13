/*
*
*   Author: jara2502, pera3307, rouy2404, veic1101
*   Date: 2021-04-13 (mar., 13 avril. 2021)
*
*/
#include "CommunicationFPGA.h"

int* CommunicationFPGA::read4Channel() 
{
	int* echconv = new int[4];
	this->lireRegistre(nreg_lect_can0, echconv[0]);       // lecture canal 0
	this->lireRegistre(nreg_lect_can1, echconv[1]);       // lecture canal 1
	this->lireRegistre(nreg_lect_can2, echconv[2]);       // lecture canal 2
	this->lireRegistre(nreg_lect_can3, echconv[3]);       // lecture canal 3
	return echconv;
}