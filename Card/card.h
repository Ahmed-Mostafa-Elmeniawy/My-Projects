#ifndef CARD_H
#define CARD_H

#include"../Project_Payment_Application/Types.h"

typedef struct ST_cardData_t
{
    uint8_t cardHolderName[30];
    uint8_t primaryAccountNumber[25];
    uint8_t cardExpirationDate[12];
}ST_cardData_t;

typedef enum EN_cardError_t
{
    /*CARD_OK is equaled to 1 to distinguish it from NULL*/
    CARD_OK = 1, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN 
}EN_cardError_t;

void printErrorState(EN_cardError_t ErrorState); /*Prints the EN_cardError_t string representation instead of numbers*/

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);

#endif
