/*
 * Card.c
 *
 *  Created on: Aug 19, 2022
 *      Author: moaz omar
 */
#include"Card.h"
#include <stdio.h>
#include<string.h>
// get the card holder name
EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
	printf("Enter Card Holder Name\n");
	gets(cardData->cardHolderName);
	// check for the length of entered string to confirm that data entered is correct
	int length;
	length=strlen(cardData->cardHolderName);
	if(length<20 || length>24 || length==0 )
		return WRONG_NAME;
	else
		return Card_OK;
}

// getting card expiration date
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
	printf("Enter Card Expiry Date MM/YY e.g \"08/22\"\n");
	gets(cardData->cardExpirationDate);
	// check for the length of entered string to confirm that data entered is correct
	int length;
	length=strlen(cardData->cardExpirationDate);
	if(length<5 || length>5 || length==0 )
		return WRONG_EXP_DATE;
	// check if data entered in the correct format
	else if(cardData->cardExpirationDate[2]!='/')
		return WRONG_EXP_DATE;
	else
		return Card_OK;
}

// getting card primary account number
EN_cardError_t getCardPAN(ST_cardData_t *cardData){
	printf("Enter Card Primary Account Number\n");
	scanf("%[0-9]",cardData->primaryAccountNumber);
	// check for the length of entered string to confirm that data entered is correct
	int length;
	length=strlen(cardData->primaryAccountNumber);
	if(length<16 || length>19 || length==0 )
		return WRONG_PAN;
	else
		return Card_OK;
}
int main(){
	ST_cardData_t cardData;
	int status;
	status=getCardHolderName(&cardData);
	if(status!= Card_OK)
		printf("Wrong name");
	status=getCardExpiryDate(&cardData);
	if(status!= Card_OK)
		printf("Wrong date");
	return 0;

}
