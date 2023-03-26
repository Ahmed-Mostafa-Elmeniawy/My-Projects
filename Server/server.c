#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"../Project_Payment_Application/Types.h"
#include "../Card/card.h"
#include"../Terminal/terminal.h"
#include"../Application/app.h"
#include"server.h"

/****************************** Server Database ******************************/
ST_accountsDB_t accountsDB[255] = { {2000.0		, RUNNING, "8989374615436851"},
									{100000.0		, RUNNING, "5807007076043875"},
									{4000.0		, RUNNING, "454421154832315649"},
									{6000000.0	, BLOCKED, "4557788514851445"},
									{800.0		, RUNNING, "5976518719895584"}};


/************************* Transaction records *************************/
ST_transaction_t transaction[255] = { 0 };

uint32_t TransactionCount = 0;

/********************************** All test functions ************************************/

void printErrorStateServer(EN_serverError_t ErrorState)
{
	switch (ErrorState)
	{
	case SERVER_OK:
		printf("SERVER_OK\n");
		break;
	case SAVING_FAILED:
		printf("SAVING_FAILED\n");
		break;
	case TRANSACTION_NOT_FOUND:
		printf("TRANSACTION_NOT_FOUND\n");
		break;
	case ACCOUNT_NOT_FOUND:
		printf("ACCOUNT_NOT_FOUND\n");
		break;
	case LOW_BALANCE:
		printf("LOW_BALANCE\n");
		break;
	case BLOCKED_ACCOUNT:
		printf("BLOCKED_ACCOUNT\n");
		break;
	}
}


void printErrorState_TransState(EN_transState_t transState)
{
	switch (transState)
	{
	case APPROVED:
		printf("APPROVED\n");
		break;
	case DECLINED_INSUFFECIENT_FUND:
		printf("DECLINED_INSUFFECIENT_FUND\n");
		break;
	case DECLINED_STOLEN_CARD:
		printf("DECLINED_STOLEN_CARD\n");
		break;
	case FRAUD_CARD:
		printf("FRAUD_CARD\n");
		break;
	case INTERNAL_SERVER_ERROR:
		printf("INTERNAL_SERVER_ERROR\n");
		break;
	default:
		printf("Enough Is Enough\n");
		break;
	}
}


void isValidAccountTest(void) {
	EN_serverError_t ErrorState;
	ST_accountsDB_t* accountRefrence = accountsDB;
	ST_cardData_t cardData ;
	uint8_t index;

	printf("Tester name: Ahmed Mostafa Elmeniawy\n");
	printf("Function Name: isValidAccountTest\n\n");

	for (index = 0; index < 2; index++)
	{
		printf("Test case %d:\n", (index+1));
		printf("Input Data: ");
		gets_s(cardData.primaryAccountNumber, 25);
		ErrorState = isValidAccount(&cardData, accountRefrence);


		/************************ Testing the validation of the account **************************/

		if (ErrorState == SERVER_OK)
		{
			printf("Expected Result: SERVER_OK\n");
			printf("Actual Result: ");
			printErrorStateServer(ErrorState);
			printf("\n\n");
		}
		else
		{
			printf("Expected Result: ACCOUNT_NOT_FOUND\n");
			printf("Actual Result: ");
			printErrorStateServer(ErrorState);
			printf("\n\n");
		}
	}


}

void isBlockedAccountTest(void)
{
	EN_serverError_t ErrorState;
	ST_accountsDB_t* accountRefrence;

	printf("Tester name: Ahmed Mostafa Elmeniawy\n");
	printf("Function Name: isBlockedAccountTest\n\n");

    /******************** First Test ***************/
	printf("Test case 1: Running account\n");
	printf("Input Data: 8989374615436851\n");
	accountRefrence = &accountsDB[0];
	ErrorState = isBlockedAccount(accountRefrence);
	printf("Expected Result: SERVER_OK\n");
	printf("Actual Result: ");
	printErrorStateServer(ErrorState);
	printf("\n\n");


	/******************* Second Test ***************/
	printf("Test case 2: Blocked account\n");
	printf("Input Data: 4557788514851445\n");
	accountRefrence = &accountsDB[3];
	ErrorState = isBlockedAccount(accountRefrence);
	printf("Expected Result: BLOCKED_ACCOUNT\n");
	printf("Actual Result: ");
	printErrorStateServer(ErrorState);
	printf("\n\n");


}

void isAmountAvailableTest(void)
{
	EN_serverError_t ErrorState;
	ST_accountsDB_t* accountRefrence;
	ST_terminalData_t termData ;

	printf("Tester name: Ahmed Mostafa Elmeniawy\n");
	printf("Function Name: isAmountAvailableTest\n\n");

	printf("Test case 1:\n");
	printf("Input Data: Amount = 2000.0, Balance = 2000.0\n");
	termData.transAmount = accountsDB[0].balance;
	accountRefrence = &accountsDB[0];
	ErrorState = isAmountAvailable(&termData, accountRefrence);
	printf("Expected Result: SERVER_OK\n");
	printf("Actual Result: ");
	printErrorStateServer(ErrorState);
	printf("\n\n");

	printf("Test case 2:\n");
	printf("Input Data: Amount = 20000.0, Balance = 5000.0\n");
	termData.transAmount = 20000.0;
	accountRefrence = &accountsDB[2];
	ErrorState = isAmountAvailable(&termData, accountRefrence);
	printf("Expected Result: LOW_BALANCE\n");
	printf("Actual Result: ");
	printErrorStateServer(ErrorState);
	printf("\n\n");

}

void recieveTransactionDataTest(void)
{
	EN_transState_t transState;
	ST_transaction_t transData;

	printf("Tester name: Ahmed Mostafa Elmeniawy\n");
	printf("Function Name: recieveTransactionDataTest\n\n");

	/**************	Testing happy and worst cases **************/
	transState = recieveTransactionData(&transData);
	printErrorState_TransState(transState);

}

void saveTransactionTest(void)
{
	ST_transaction_t transData;

	printf("Tester name: Ahmed Mostafa Elmeniawy\n");
	printf("Function Name: saveTransactionTest\n\n");

	/**********************	Happy Case **********************/
	printf("TransactionCount is less than 255\n");
	strcpy_s(transData.cardHolderData.cardHolderName		, 25, "Ahmed Mostafa Elmeniawy");
	strcpy_s(transData.cardHolderData.cardExpirationDate	, 6 , "05/25");
	strcpy_s(transData.cardHolderData.primaryAccountNumber	, 20, "5976518719895584");
	strcpy_s(transData.terminalData.transactionDate			, 11, "22/01/2023");

	 transData.terminalData.transAmount		=	200.0;
	 transData.terminalData.maxTransAmount	=	300.0;
	 transData.transState					= APPROVED;

	 saveTransaction(&transData);

	 printTransaction(&transData);


	 /********************** Worst Case **********************/
	 printf("\n\nTransactionCount is more than 255\n");
	 TransactionCount = 348;
	 strcpy_s(transData.cardHolderData.cardHolderName, 25, "Ahmed Mostafa Elmeniawy");
	 strcpy_s(transData.cardHolderData.cardExpirationDate, 6, "05/25");
	 strcpy_s(transData.cardHolderData.primaryAccountNumber, 20, "5976518719895584");
	 strcpy_s(transData.terminalData.transactionDate, 11, "22/01/2023");

	 transData.terminalData.transAmount = 200.0;
	 transData.terminalData.maxTransAmount = 300.0;
	 transData.transState = APPROVED;

	 saveTransaction(&transData);

}

void printTransaction(ST_transaction_t* transData)
{
	printf("Holder Name: %s\n"				,transaction[TransactionCount-1].cardHolderData.cardHolderName			);
	printf("PAN: %s\n"						,transaction[TransactionCount-1].cardHolderData.primaryAccountNumber	);
	printf("Expiration Date: %s\n"			,transaction[TransactionCount-1].cardHolderData.cardExpirationDate		);
	printf("Transfer Amount: %f\n"			,transaction[TransactionCount-1].terminalData.transAmount				);
	printf("Maximum Transfer Amount: %f\n"	,transaction[TransactionCount-1].terminalData.maxTransAmount			);
	printf("Transaction Date: %s\n"		    ,transaction[TransactionCount-1].terminalData.transactionDate			);
	printf("Transaction State: ");
	printErrorState_TransState(transaction[TransactionCount - 1].transState);
	printf("Transaction Sequence Number: %d", transaction[TransactionCount - 1].transactionSequenceNumber);
}

void listSavedTransactionsTest(void)
{
	ST_transaction_t transData;

	strcpy_s(transData.cardHolderData.cardHolderName, 25, "Ahmed Mostafa Elmeniawy");
	strcpy_s(transData.cardHolderData.cardExpirationDate, 6, "05/25");
	strcpy_s(transData.cardHolderData.primaryAccountNumber, 20, "5976518719895584");
	strcpy_s(transData.terminalData.transactionDate, 11, "22/01/2023");

	transData.terminalData.transAmount = 200.0;
	transData.terminalData.maxTransAmount = 300.0;
	transData.transState = APPROVED;

	saveTransaction(&transData);


	strcpy_s(transData.cardHolderData.cardHolderName, 25, "Mohammed Mostafa Ali");
	strcpy_s(transData.cardHolderData.cardExpirationDate, 6, "07/15");
	strcpy_s(transData.cardHolderData.primaryAccountNumber, 20, "4557788514851445");
	strcpy_s(transData.terminalData.transactionDate, 11, "22/02/2022");

	transData.terminalData.transAmount = 500.0;
	transData.terminalData.maxTransAmount = 900.0;
	transData.transState = DECLINED_STOLEN_CARD;

	saveTransaction(&transData);

	listSavedTransactions();
}



/************************************* Implementation of these functions **************************************/

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	EN_cardError_t ErrorState_card;
	EN_terminalError_t ErrorState_terminal;
	EN_serverError_t ErrorState_server;
	EN_transState_t transState = APPROVED;
	ST_cardData_t cardData;
	ST_terminalData_t termData;
	ST_accountsDB_t* accountRefrence = accountsDB;
	f32_t maxAmount;

	/*************************** Reading the card data ******************************/
	printf("Enter the holder name: ");
	ErrorState_card = getCardHolderName(&cardData);
	if (ErrorState_card == WRONG_NAME)
	{
		transState = FRAUD_CARD;
		printErrorState(ErrorState_card);
		goto EndFunction;
	}
	printf("Enter the pinary account number(PAN): ");
	ErrorState_card = getCardPAN(&cardData);
	if (ErrorState_card == WRONG_PAN)
	{
		transState = FRAUD_CARD;
		printErrorState(ErrorState_card);
		goto EndFunction;
	}

	printf("Enter the card expiry date: ");
	ErrorState_card = getCardExpiryDate(&cardData);
	if (ErrorState_card == WRONG_EXP_DATE)
	{
		transState = FRAUD_CARD;
		printErrorState(ErrorState_card);
		goto EndFunction;
	}


	/**************************** Reading the transaction date *****************************/
	printf("Enter the transaction date: ");
	ErrorState_terminal = getTransactionDate(&termData);
	if (ErrorState_terminal == WRONG_DATE)
	{
		transState = FRAUD_CARD;
		printErrorStateTerminal(ErrorState_terminal);
		goto EndFunction;
	}
	else if (isCardExpired(&cardData, &termData) == EXPIRED_CARD)
	{
		ErrorState_terminal = EXPIRED_CARD;
		transState = FRAUD_CARD;
		printErrorStateTerminal(ErrorState_terminal);
		goto EndFunction;
	}
	printf("Enter transaction amount: ");
	ErrorState_terminal = getTransactionAmount(&termData);
	if (ErrorState_terminal == INVALID_AMOUNT)
	{
		transState = FRAUD_CARD;
		printErrorStateTerminal(ErrorState_terminal);
		goto EndFunction;
	}

	printf("Enter maximum amount: ");
	scanf_s("%f", &maxAmount);

	ErrorState_terminal = setMaxAmount(&termData, maxAmount);

	if (ErrorState_terminal == INVALID_MAX_AMOUNT)
	{
		transState = DECLINED_INSUFFECIENT_FUND;
		printErrorStateTerminal(ErrorState_terminal);
		goto EndFunction;
	}

	/**************************** Checking if the entered amount exceeds the max amount or not ******************************/
	ErrorState_terminal = isBelowMaxAmount(&termData);
	if (ErrorState_terminal == EXCEED_MAX_AMOUNT)
	{
		transState = DECLINED_INSUFFECIENT_FUND;
		printErrorStateTerminal(ErrorState_terminal);
		goto EndFunction;
	}

	/********************* Checking the account in the database ********************/
	ErrorState_server = isValidAccount(&cardData, accountRefrence);
	if (ErrorState_server == ACCOUNT_NOT_FOUND)
	{
		transState = FRAUD_CARD;
		printErrorStateServer(ErrorState_server);
		goto EndFunction;
	}


	/********************* Checking if the account is blocked or not *********************/
	ErrorState_server = isBlockedAccount(accountRefrence);
	if (ErrorState_server == BLOCKED_ACCOUNT)
	{
		transState = DECLINED_STOLEN_CARD;
		printErrorStateServer(ErrorState_server);
		goto EndFunction;
	}

	/********************** Checking the availability of the amount entered *********************/
	ErrorState_server = isAmountAvailable(&termData, accountRefrence);
	if (ErrorState_server == LOW_BALANCE)
	{
		transState = DECLINED_INSUFFECIENT_FUND;
		printErrorStateServer(ErrorState_server);
		goto EndFunction;
	}


	if (TransactionCount >= 255)
	{
		transData->transState = INTERNAL_SERVER_ERROR;
		saveTransaction(transData);
		printf("Transaction State is ");
		printErrorState_TransState(transData->transState);
		listSavedTransactions();
		goto EndFunction;
	}
	else
	{
		/******************* Transaction is approved and updating the balance in the account *******************/
		transData->transState = APPROVED;
	}

EndFunction:

	strcpy_s(transData->cardHolderData.cardHolderName, 25, cardData.cardHolderName);
	strcpy_s(transData->cardHolderData.cardExpirationDate, 6, cardData.cardExpirationDate);
	strcpy_s(transData->cardHolderData.primaryAccountNumber, 20, cardData.primaryAccountNumber);
	strcpy_s(transData->terminalData.transactionDate, 11, termData.transactionDate);
	transData->terminalData.transAmount = termData.transAmount;
	transData->terminalData.maxTransAmount = termData.maxTransAmount;
	transData->transState = transState;

	saveTransaction(transData);
	printf("\n\n**************\n");
	printf("Transaction State is ");
	printErrorState_TransState(transData->transState);
	printf("**************\n\n");

	if (transData->transState == APPROVED)
	{
		accountRefrence->balance -= termData.transAmount;
		printf("\n\n**************\n");
		printf("Account Balance:	%f\n", accountRefrence->balance);
		printf("**************\n\n");
	}

	return transState;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	EN_serverError_t ErrorState;
	uint8_t index;

	for (index = 0; index < 5; index++)
	{
		if (strcmp(cardData->primaryAccountNumber, accountRefrence[index].primaryAccountNumber) == 0)
		{
			ErrorState = SERVER_OK;
			*accountRefrence = accountsDB[index];

			break;
		}
		else
		{
			ErrorState = ACCOUNT_NOT_FOUND;
		}
	}

	if (ErrorState == ACCOUNT_NOT_FOUND)
	{
		accountRefrence = (ST_accountsDB_t*)NULL;
	}

	return ErrorState;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	EN_serverError_t ErrorState;

	if (accountRefrence->state == BLOCKED)
	{
		ErrorState = BLOCKED_ACCOUNT;
	}
	else
	{
		ErrorState = SERVER_OK;
	}

	return ErrorState;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	EN_serverError_t ErrorState;

	if ( ( (f32_t) termData->transAmount ) > ( (f32_t) accountRefrence->balance ) )
	{
		ErrorState = LOW_BALANCE;
	}
	else
	{
		ErrorState = SERVER_OK;
	}

	return ErrorState;
}

void saveTransaction(ST_transaction_t* transData)
{	
	if (TransactionCount < 255)
	{
		/************************* Moving the string data from transData to transaction database ***********************/
		StringCopy(transaction[TransactionCount].cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName);
		StringCopy(transaction[TransactionCount].cardHolderData.cardExpirationDate, transData->cardHolderData.cardExpirationDate);
		StringCopy(transaction[TransactionCount].cardHolderData.primaryAccountNumber, transData->cardHolderData.primaryAccountNumber);
		StringCopy(transaction[TransactionCount].terminalData.transactionDate, transData->terminalData.transactionDate);

		/*************************************** Moving non-string data ****************************/
		transaction[TransactionCount].terminalData.transAmount = transData->terminalData.transAmount;
		transaction[TransactionCount].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
		transaction[TransactionCount].transState = transData->transState;
		transaction[TransactionCount].transactionSequenceNumber = TransactionCount + 1;

		TransactionCount++;
	}
	else
	{
		transData->transState = INTERNAL_SERVER_ERROR;
		printErrorState_TransState(transData->transState);
	}
		
}

void StringCopy(uint8_t* Distination, uint8_t* Source)
{
	uint8_t index = 0;

	while (Source[index] != '\0')
	{
		Distination[index] = Source[index];
		index++;
	}
}



void listSavedTransactions(void)
{
	uint8_t index;

	for (index = 0; index < TransactionCount; index++)
	{
		printf("#########################\n");
		printf("Transaction Sequence Number:		%d\n"	, transaction[index].transactionSequenceNumber);
		printf("Transaction Date:			%s\n"			, transaction[index].terminalData.transactionDate);
		printf("Transaction Amount:			%f\n"			, transaction[index].terminalData.transAmount);
		printf("Transaction State:			");
		printErrorState_TransState(transaction[index].transState);
		printf("Terminal Max Amount:			%f\n"		, transaction[index].terminalData.maxTransAmount);
		printf("Cardholder Name:			%s\n"			, transaction[index].cardHolderData.cardHolderName);
		printf("PAN:					%s\n"				, transaction[index].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date:			%s\n"		, transaction[index].cardHolderData.cardExpirationDate);
		printf("#########################\n");
	}
}




