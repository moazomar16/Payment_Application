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
#include "App.h"
extern foundit;

void appStart(void){
	printf("\n");
	printf("\t welcome \nconnecting to server.........\n------------------------------");
	printf(" \n");
}

int main(){
	ST_cardData_t cardData;
	ST_terminalData_t termData;
	int status;
	ST_transaction_t transactiondata;

	appStart();
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
		printf("Obtaining Date...");
		fflush(stdout); fflush(stdin);
	}
	status=isCardExpired(&cardData, &termData);
	if(status!= Terminal_OK){
		printf("\nExpired card\n ending!!!");
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
		printf("\ninvalid amount");
		fflush(stdout); fflush(stdin);
	}
//	else{
//		printf(" Amount entered");
//		fflush(stdout); fflush(stdin);
//	}
	status=setMaxAmount(&termData);
	if(status!= Terminal_OK){
		printf("\ninvalid max amount");
		fflush(stdout); fflush(stdin);
	}
//	else{
//		printf(" max amount entered");
//		fflush(stdout); fflush(stdin);
//	}
	status=isBelowMaxAmount(&termData);
	if(status!= Terminal_OK){
		printf("\nExceeded max amount\n ending!!!");
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
		printf("\nDeclined stolen card\n ending!!!");
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
		printf("\nLow balance\n ending!!!");
		fflush(stdout); fflush(stdin);
		exit(0);
	}
//	else
//	{
//		printf("\n Amount available");
//		fflush(stdout); fflush(stdin);
//	}
	transactiondata.cardHolderData=cardData;
	transactiondata.terminalData=termData;


	status=recieveTransactionData(&transactiondata);
	if(status!= Server_OK){
		printf("\nFailed");
		fflush(stdout); fflush(stdin);
		exit(0);
	}
//	else
//	{
//		printf("\n done");
//		fflush(stdout); fflush(stdin);
//	}
	printf("\n--------------- Printing Saved Transaction ---------------\n");
	printf("Transaction Number: %d\nCard Holder Name: %s\nAccount Number: %s \ntransaction amount: %.2f \navailable balance: %.2f  ",
			transaction_DB[foundit].transactionSequenceNumber,
			transaction_DB[foundit].cardHolderData.cardHolderName,
			transaction_DB[foundit].cardHolderData.primaryAccountNumber,
			transaction_DB[foundit].terminalData.transAmount,
			accounts_DB[foundit].balance) ;
	printf("\n----------------------------------------------------------\n");
	printf("Do You Want To Do Another Transaction Y/N ");
	fflush(stdout); fflush(stdin);
	if(getchar()=='Y')
		main();
	else
		exit(0);
	return 0;
}



