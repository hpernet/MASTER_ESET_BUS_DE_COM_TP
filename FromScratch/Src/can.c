/*
 * can.c
 *
 *  Created on: Oct 27, 2022
 *      Author: Luca le meilleur
 */
#include "can.h"
#include <stm32f446xx.h>

void CAN_init(void){

	// GPIO CONFIG
	GPIOB->MODER  |= (2<<16) | (2<<18);
	GPIOB->AFR[1] |= (9) | (9<<4);
	//Enable and conf CAN module
	RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;
	CAN1->MCR |= 0x1; // INRQ=1

	while(!(CAN1->MSR & 0x1))
	{
	}; // Wait INAK==1

	CAN1->BTR = 0x001c0007;

	CAN1->MCR &= ~0x1; // INRQ=0
	while((CAN1->MSR & 0x1))
	{
	}; // Wait INAK==0

	CAN1->MCR &= ~0x2; // SLEEP=0
}

void CAN_sendData_mailbox0(uint32_t dataH, uint32_t dataL){
	if(CAN1->TSR & (1<<26)){
//		printf("Mailbox0 empty\r\n");
		CAN1->sTxMailBox[0].TIR = 0x0; // ID = 0
		CAN1->sTxMailBox[0].TDTR |= 0x8; // DLC = 8
		CAN1->sTxMailBox[0].TDLR = dataL;
		CAN1->sTxMailBox[0].TDHR = dataH;
		CAN1->sTxMailBox[0].TIR |= 1; // Tx Request

//		while(!(CAN1->TSR & (1<<0)));//{ // Check error
//			if((CAN1->TSR & (1<<2))) printf("Arbitration lost\r\n");
//			if((CAN1->TSR & (1<<3))) printf("Error\r\n");
//		};
//		printf("Data successfully sent\r\n");
	}
//	else printf("Mailbox0 not empty\r\n");
}

CAN_data CAN_receiveData(void){
	CAN_data data = {0};

	if((CAN1->RF0R & 0x3)){
		data.ID 	= CAN1->sFIFOMailBox[0].RIR;
		data.RDT 	= CAN1->sFIFOMailBox[0].RDTR;
		data.dataL 	= CAN1->sFIFOMailBox[0].RDLR;
		data.dataH 	= CAN1->sFIFOMailBox[0].RDHR;
	}

	if(CAN1->RF1R & 0x3){
		data.ID 	= CAN1->sFIFOMailBox[1].RIR;
		data.RDT 	= CAN1->sFIFOMailBox[1].RDTR;
		data.dataL 	= CAN1->sFIFOMailBox[1].RDLR;
		data.dataH 	= CAN1->sFIFOMailBox[1].RDHR;
	}

	return data;
}
