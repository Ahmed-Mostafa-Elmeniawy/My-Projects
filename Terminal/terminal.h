

#ifndef TERMINAL_H
#define TERMINAL_H

#include"../Project_Payment_Application/Types.h"
#include"../Card/card.h"

typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[15];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
    /**************** TERMINAL_OK = 1 to distinuish it from NULL ********************/
    TERMINAL_OK = 1, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, f32_t maxAmount);

void printErrorStateTerminal(EN_terminalError_t ErrorState);

void getTransactionDateTest(void);
void isCardExpriedTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);

#endif