/*
 * can.h
 *
 *  Created on: Oct 27, 2022
 *      Author: Luca le meilleur
 */

#ifndef INC_CAN_H_
#define INC_CAN_H_

#include <stdio.h>


typedef struct{
	uint32_t ID;
	uint32_t RDT;
	uint32_t dataL;
	uint32_t dataH;
}CAN_data;


void CAN_init(void);
void CAN_sendData_mailbox0(uint32_t dataH, uint32_t dataL);
CAN_data CAN_receiveData(void);

#endif /* INC_CAN_H_ */

