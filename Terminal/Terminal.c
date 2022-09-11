/*
 * Terminal.c
 *
 *  Created on: Aug 19, 2022
 *      Author: moaz omar
 */
#include"../card/card.h"
#include"Terminal.h"


// this function is going to get the current date @ runtime
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
	time_t Time;
	time(&Time);
	struct tm *tm=localtime(&Time);
	// strftime if going to store the wanted data from date info into required array
	// %d == day of the month **** %m month as a deciml e.g 01-12 ... **** %Y year e.g 2018
	strftime(termData->transactionDate,sizeof(termData->transactionDate),"%d/%m/%Y",tm);
	return Terminal_OK;
}

// this func compare transacion date with expiration date
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){
	char temp[5];
	int i;
	// i used a loop to get the date from the array
	for(i=8;i<11;i++)
		temp[i-8]=termData->transactionDate[i];
	int year1=atoi(temp);

	for(i=3;i<6;i++)
		temp[i-3]=cardData->cardExpirationDate[i];
	int year2=atoi(temp);

	for(i=3;i<5;i++){
		temp[i-3]=termData->transactionDate[i];
		temp[2]='\0';
	}
	int mon1=atoi(temp);
	for(i=0;i<2;i++){
		temp[i]=cardData->cardExpirationDate[i];
		temp[2]='\0';
	}
	int mon2=atoi(temp);
	if((year2==year1 && mon2==mon1)|| (year2==year1 && mon2>mon1)){
		return Terminal_OK;

	}
	else if(year2>year1)
		return Terminal_OK;
	else
		return EXPIRED_CARD;

}
// this function asks the user to enter the amount of transaction
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
	printf("\nEnter Transaction Amount: ");
	fflush(stdout); fflush(stdin);
	scanf("%f",&termData->transAmount);
	fflush(stdout); fflush(stdin);
	if (termData->transAmount<=0)
		return INVALID_AMOUNT;
	else
		return Terminal_OK;
}

//this function compare the transaction amount with max Amount
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
	if(termData->transAmount > termData->maxTransAmount)
		return EXCEED_MAX_AMOUNT;
	else
		return Terminal_OK;
}

// this function asks the user to enter the max amount of transaction allowed
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData){
	printf("Enter transaction Max Amount: ");
	fflush(stdout); fflush(stdin);
	scanf("%f",&termData->maxTransAmount);
	fflush(stdout); fflush(stdin);
	if(termData->maxTransAmount <= 0)
		return INVALID_MAX_AMOUNT;
	else
		return Terminal_OK;
}
//EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){
//
//
//}

//int main(){
//	ST_cardData_t cardData;
//	ST_terminalData_t termData;
//	int status;
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
//		printf("\n can not obtain date from system");
//		fflush(stdout); fflush(stdin);
//	}
//	else
//	{
//		printf("\n Date obtained");
//		fflush(stdout); fflush(stdin);
//	}
//	status=isCardExpired(&cardData, &termData);
//	if(status!= Terminal_OK){
//		printf("\n Expired card");
//		fflush(stdout); fflush(stdin);
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
//		printf("\n exceeded max amount");
//		fflush(stdout); fflush(stdin);
//	}
//	else
//	{
//		printf("\n below max");
//		fflush(stdout); fflush(stdin);
//	}
//
//
//
//	return 0;
//}
