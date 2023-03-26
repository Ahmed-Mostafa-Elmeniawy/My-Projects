#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "../Card/card.h"
#include"../Terminal/terminal.h"
#include"../Server/server.h"
#include"app.h"





void appStart(void)
{
	ST_transaction_t transData;
	EN_transState_t transState;

	transState = recieveTransactionData(&transData);
}