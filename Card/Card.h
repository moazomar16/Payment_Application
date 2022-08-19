/*
 * Card.h
 *
 *  Created on: Aug 19, 2022
 *      Author: moaz omar
 */

#ifndef CARD_CARD_H_
#define CARD_CARD_H_

#include <stdint.h>
// creating structure to hold the card data
typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;

// creating different status
typedef enum EN_cardError_t
{
	Card_OK,
	WRONG_NAME,
	WRONG_EXP_DATE,
	WRONG_PAN
}EN_cardError_t;

// APIs
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);




#endif /* CARD_CARD_H_ */
