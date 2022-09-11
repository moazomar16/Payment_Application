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

// Creating array of structure to use it as a transaction database
ST_transaction_t transaction_DB[255]={{0}};

// Creating array of structure to use it as a accounts database
ST_accountsDB_t accounts_DB[255] = {
		{15000,"123456789123456789"},
		{10000,"987654321987654321"},
		{25000,"112233445566778899"} };

EN_transStat_t recieveTransactionData(ST_transaction_t *transData){
	int result;
	ST_cardData_t cardData;
	cardData=transData->cardHolderData;
	ST_terminalData_t termData;
	termData.transAmount=transData->terminalData.transAmount;
	result=isValidAccount(&cardData);
	if(result==Server_OK){
		result=isAmountAvailable(&termData);
		if(result==Server_OK){
			transData->transState=APPROVED;
			accounts_DB[foundit].balance = (accounts_DB[foundit].balance) - (transData->terminalData.transAmount);
			saveTransaction(transData);
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
	int i;
	for (i=0; i<255; i++){
	if(strcmp(cardData->primaryAccountNumber,accounts_DB[i].primaryAccountNumber)==0){
		foundit=i;
		return Server_OK;
	}
	else
		return DECLINED_STOLEN_CARD;

}
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){
	if(accounts_DB[foundit].balance > termData->transAmount)
		return Server_OK;
	else
		return LOW_BALANCE;
}
EN_serverError_t saveTransaction(ST_transaction_t *transData){
	static int i=0;
	transaction_DB[i].cardHolderData=transData->cardHolderData;
	transaction_DB[i].terminalData=transData->terminalData;
	transaction_DB[i].transState=transData->transState;
	transaction_DB[i].transactionSequenceNumber=202210000+i;
}
//EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData);

//int main(){
//	ST_cardData_t cardData;
//	ST_terminalData_t termData;
//	int status;
//	ST_transaction_t transactiondata;
//
//
//	status=getCardHolderName(&cardData);
//	if(status!= Card_OK)
//		printf("Wrong name\n");
//	fflush(stdout); fflush(stdin);
//	status=getCardExpiryDate(&cardData);
//	if(status!= Card_OK)
//		printf("Wrong date\n");
//	fflush(stdout); fflush(stdin);
//	status=getCardPAN(&cardData);
//	if(status!= Card_OK)
//		printf("Wrong PAN\n");
//	fflush(stdout); fflush(stdin);
//	status=getTransactionDate(&termData);
//	if(status!= Terminal_OK){
//		printf("can not obtain date from system\n");
//		fflush(stdout); fflush(stdin);
//	}
//	else
//	{
//		printf("\n Date obtained");
//		fflush(stdout); fflush(stdin);
//	}
//	status=isCardExpired(&cardData, &termData);
//	if(status!= Terminal_OK){
//		printf("Expired card\n ending!!!");
//		fflush(stdout); fflush(stdin);
//		exit(0);
//	}
//	else
//	{
//		printf("\n card is not expired");
//		fflush(stdout); fflush(stdin);
//	}
//	status=getTransactionAmount(&termData);
//	if(status!= Terminal_OK){
//		printf("\n invalid amount");
//		fflush(stdout); fflush(stdin);
//	}
//	else{
//		printf(" Amount entered");
//		fflush(stdout); fflush(stdin);
//	}
//	status=setMaxAmount(&termData);
//	if(status!= Terminal_OK){
//		printf("\n invalid max amount");
//		fflush(stdout); fflush(stdin);
//	}
//	else{
//		printf(" max amount entered");
//		fflush(stdout); fflush(stdin);
//	}
//	status=isBelowMaxAmount(&termData);
//	if(status!= Terminal_OK){
//		printf("\n exceeded max amount\n ending!!!");
//		fflush(stdout); fflush(stdin);
//		exit(0);
//	}
//	else
//	{
//		printf("\n below max");
//		fflush(stdout); fflush(stdin);
//	}
//	status=isValidAccount(&cardData);
//	if(status!= Server_OK){
//		printf("\n declined stolen card\n ending!!!");
//		fflush(stdout); fflush(stdin);
//		exit(0);
//	}
//	else
//	{
//		printf("\n valid card");
//		fflush(stdout); fflush(stdin);
//	}
//	status=isAmountAvailable(&termData);
//	if(status!= Server_OK){
//		printf("\n low balance\n ending!!!");
//		fflush(stdout); fflush(stdin);
//		exit(0);
//	}
//	else
//	{
//		printf("\n Amount available");
//		fflush(stdout); fflush(stdin);
//	}
//	transactiondata.cardHolderData=cardData;
//	transactiondata.terminalData=termData;
//
//
//	status=recieveTransactionData(&transactiondata);
//	if(status!= Server_OK){
//		printf("\n failed");
//		fflush(stdout); fflush(stdin);
//	}
//	else
//	{
//		printf("\n done");
//		fflush(stdout); fflush(stdin);
//	}
//	printf("\n--------------- Printing Saved Transaction ---------------\n");
//	printf("Card Holder Name:%s\nAccount Number: %s \ntransaction amount:%.2f \navailable balance:%.2f ",
//			transaction_DB[foundit].cardHolderData.cardHolderName,
//			transaction_DB[foundit].cardHolderData.primaryAccountNumber,
//			transaction_DB[foundit].terminalData.transAmount,
//			accounts_DB[foundit].balance);
//	return 0;
//}
//
//
//
