/*
 * Server.c
 *
 *  Created on: Aug 19, 2022
 *      Author: moaz omar
 */
#include"../Card/Card.h"
#include"../Terminal/Terminal.h"
#include"Server.h"
int foundit=-1;

EN_transStat_t recieveTransactionData(ST_transaction_t *transData){
	int result;
	ST_cardData_t cardData;
	cardData.primaryAccountNumber[20]=transData->cardHolderData.primaryAccountNumber[20];
	ST_terminalData_t termData;
	termData.transAmount=transData->terminalData.transAmount;
	termData.transAmount=transData->terminalData.maxTransAmount;
	result=isValidAccount(&cardData);
	if(result==Server_OK){
		result=isAmountAvailable(&termData);
		if(result==Server_OK){
			transData->transState=APPROVED;
			return APPROVED;
		}
		else
		{
			transData->transState=DECLINED_INSUFFECIENT_FUND;
			return DECLINED_INSUFFECIENT_FUND;
		}
	}
	else{
		transData->transState=DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}
}
EN_serverError_t isValidAccount(ST_cardData_t *cardData){
	int i,j;
	for (i=0; i<255; i++){
		//if(strcmp(cardData->primaryAccountNumber,accountsBD[i].primaryAccountNumber)==0)
		for(j=0; j!='\0';j++){
				if((cardData->primaryAccountNumber[j]) == (accountsBD[i].primaryAccountNumber[j])){
					foundit=i;
					j++;
		}
				else {
					foundit=-1;
					break;
		}
		}
	}

	if(foundit!=-1)
		return Server_OK;
	else
		return DECLINED_STOLEN_CARD;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){
	if(accountsBD[foundit].balance>termData->transAmount)
		return LOW_BALANCE;
	else
		return Server_OK;
}
//EN_serverError_t saveTransaction(ST_transaction_t *transData);
//EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData);




