///*
// * App.c
// *
// *  Created on: Aug 19, 2022
// *      Author: moazo
// */
//
//
#include"../Card/Card.h"
#include"../Terminal/Terminal.h"
#include"../Server/Server.h"

void appStart(void){
	printf("stating....\n");
}

int main(){
	appStart();
	accountsBD[0].balance=(float)20000;
	accountsBD[0].primaryAccountNumber[20]=(int)"123456789123456789";
	accountsBD[1].balance=(float)25000;
	accountsBD[1].primaryAccountNumber[20]=(char)"123456789987654321";
	accountsBD[2].balance=(float)15000;
	accountsBD[2].primaryAccountNumber[20]=(char)"112233445566778899";
	ST_cardData_t cardData;
	ST_terminalData_t termData;
	int status;
	ST_transaction_t transactiondata;
	transactiondata.cardHolderData=cardData;
	transactiondata.terminalData=termData;
	transactiondata.transactionSequenceNumber=1000000;

	status=getCardHolderName(&cardData);
	if(status!= Card_OK)
		printf("Wrong name\n");
	fflush(stdout); fflush(stdin);
	status=getCardExpiryDate(&cardData);
	if(status!= Card_OK)
		printf("Wrong date\n");
	fflush(stdout); fflush(stdin);
	status=getCardPAN(&cardData);
	if(status!= Card_OK)
		printf("Wrong PAN\n");
	fflush(stdout); fflush(stdin);
	status=getTransactionDate(&termData);
	if(status!= Terminal_OK){
		printf("can not obtain date from system\n");
		fflush(stdout); fflush(stdin);
	}
	else
	{
		printf("\n Date obtained");
		fflush(stdout); fflush(stdin);
	}
	status=isCardExpired(&cardData, &termData);
	if(status!= Terminal_OK){
		printf("Expired card\n ending!!!");
		fflush(stdout); fflush(stdin);
		exit(0);
	}
//	else
//	{
//		printf("\n card is not expired");
//		fflush(stdout); fflush(stdin);
//	}
	status=getTransactionAmount(&termData);
	if(status!= Terminal_OK){
		printf("\n invalid amount");
		fflush(stdout); fflush(stdin);
	}
	else{
		printf(" Amount entered");
		fflush(stdout); fflush(stdin);
	}
	status=setMaxAmount(&termData);
	if(status!= Terminal_OK){
		printf("\n invalid max amount");
		fflush(stdout); fflush(stdin);
	}
	else{
		printf(" max amount entered");
		fflush(stdout); fflush(stdin);
	}
	status=isBelowMaxAmount(&termData);
	if(status!= Terminal_OK){
		printf("\n exceeded max amount\n ending!!!");
		fflush(stdout); fflush(stdin);
		exit(0);
	}
//	else
//	{
//		printf("\n below max");
//		fflush(stdout); fflush(stdin);
//	}
	status=isValidAccount(&cardData);
	if(status!= Server_OK){
		printf("\n declined stolen card\n ending!!!");
		fflush(stdout); fflush(stdin);
		exit(0);
	}
//	else
//	{
//		printf("\n valid card");
//		fflush(stdout); fflush(stdin);
//	}
	status=isAmountAvailable(&termData);
	if(status!= Server_OK){
		printf("\n low balance\n ending!!!");
		fflush(stdout); fflush(stdin);
		exit(0);
	}
//	else
//	{
//		printf("\n done");
//		fflush(stdout); fflush(stdin);
//	}
	status=recieveTransactionData(&transactiondata);
	if(status!= Server_OK){
		printf("\n failed");
		fflush(stdout); fflush(stdin);
	}
	else
	{
		printf("\n done");
		fflush(stdout); fflush(stdin);
	}
	return 0;
}
