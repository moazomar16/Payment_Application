/*
 * Server.h
 *
 *  Created on: Aug 19, 2022
 *      Author: moaz omar
 */

#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include<stdint.h>
#include<stdio.h>
#include<string.h>

// transaction status
typedef enum EN_transState_t
{
APPROVED,
DECLINED_INSUFFECIENT_FUND,
DECLINED_STOLEN_CARD,
INTERNAL_SERVER_ERROR
}EN_transStat_t;

// structure to hold transaction data
typedef struct ST_transaction_t
{
ST_cardData_t cardHolderData;
ST_terminalData_t terminalData;
EN_transStat_t transState;
uint32_t transactionSequenceNumber;
}ST_transaction_t;



// server status
typedef enum EN_serverError_t
{
Server_OK,
SAVING_FAILED,
TRANSACTION_NOT_FOUND,
ACCOUNT_NOT_FOUND,
LOW_BALANCE
}EN_serverError_t ;

// account database
typedef struct ST_accountsDB_t
{
float balance;
uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;


ST_transaction_t transaction_DB[255];

ST_accountsDB_t accounts_DB[255];
//APIs
EN_transStat_t recieveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData);




#endif /* SERVER_SERVER_H_ */
