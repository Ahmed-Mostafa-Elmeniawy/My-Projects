
#ifndef SERVER_H
#define SERVER_H

#include"../Card/card.h"
#include"../Project_Payment_Application/Types.h"
#include"../Terminal/terminal.h"

typedef enum EN_transState_t
{
    APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef enum EN_serverError_t
{
    SERVER_OK = 1, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t;

typedef enum EN_accountState_t
{
    RUNNING,
    BLOCKED
}EN_accountState_t;

typedef struct ST_accountsDB_t
{
    f32_t balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[25];
}ST_accountsDB_t;


EN_transState_t recieveTransactionData(ST_transaction_t* transData);
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence);
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence);
void saveTransaction(ST_transaction_t* transData);

void printErrorStateServer(EN_serverError_t ErrorState);

void listSavedTransactions(void);

void StringCopy(uint8_t* Distination, uint8_t* Source);

/*********************** Test functions' prototype *************************/
void recieveTransactionDataTest(void);
void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);
void saveTransactionTest(void);
void printTransaction(ST_transaction_t* transData);
void printErrorState_TransState(EN_transState_t transState);
void listSavedTransactionsTest(void);

#endif