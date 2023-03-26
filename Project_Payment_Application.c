#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "Types.h"
#include "../Card/card.h"
#include"../Terminal/terminal.h"
#include"../Server/server.h"
#include"../Application/app.h"

int main()
{
    //getCardHolderNameTest();
    //getCardExpiryDateTest();
    //getCardPANTest();
    //getTransactionDateTest();
    //isCardExpriedTest();
    //getTransactionAmountTest();
    isBelowMaxAmountTest();
    //setMaxAmountTest();
    //isValidAccountTest();
    //isBlockedAccountTest();
    //isAmountAvailableTest();
    //recieveTransactionDataTest();
    //saveTransactionTest();
    //listSavedTransactionsTest();

    /* ============================ Testing the whole application =============================== */
#if 0

    uint32_t EndProgram;

    while (1)
    {
        appStart();

        printf("If you want to exit write \" 1 \" \n");
        scanf_s("%d", &EndProgram);

        printf("\n\n");
        if (EndProgram == 1)
        {
            printf("Thank you for your time\n");
            listSavedTransactions();
            break;
        }
    }
    
#endif

}
