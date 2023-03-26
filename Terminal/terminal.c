#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "../Project_Payment_Application/Types.h"
#include "../Card/card.h"
#include"terminal.h"


void printErrorStateTerminal(EN_terminalError_t ErrorState)
{
	switch (ErrorState)
	{
	case TERMINAL_OK:
		printf("TERMINAL_OK\n");
		break;
	case WRONG_DATE:
		printf("WRONG_DATE\n");
		break;
	case EXPIRED_CARD:
		printf("EXPIRED_CARD\n");
		break;
	case INVALID_CARD:
		printf("INVALID_CARD\n");
		break;
	case INVALID_AMOUNT:
		printf("INVALID_AMOUNT\n");
		break;
	case EXCEED_MAX_AMOUNT:
		printf("EXCEED_MAX_AMOUNT\n");
		break;
	case INVALID_MAX_AMOUNT:
		printf("INVALID_MAX_AMOUNT\n");
		break;
	case 0:
		printf("NULL\n");
		break;
	}
}


/****************************** Code of the test functions *****************************/

void getTransactionDateTest(void)
{
	EN_terminalError_t ErrorState;
	ST_terminalData_t termData;

	printf("Tester name: Ahmed Mostafa Elmeniawy\n");
	printf("Function Name: getTransactionDateTest\n\n");

	printf("Test case 1: The transaction date is accepted\n");
	printf("Input Data: 12/01/2003\n");
	printf("Expected Result: TERMINAL_OK\n");
	strcpy_s( termData.transactionDate, 11, "12/01/2003");
	ErrorState = getTransactionDate(&termData);
	printf("Actual Result: ");
	printErrorStateTerminal(ErrorState);
	printf("\n\n");

	printf("Test case 2: The transaction date is rejected as it contains a charcter \n");
	printf("Input Data: 1A/01/2003\n");
	printf("Expected Result: WRONG_DATE\n");
	strcpy_s(termData.transactionDate, 11, "1A/01/2003");
	ErrorState = getTransactionDate(&termData);
	printf("Actual Result: ");
	printErrorStateTerminal(ErrorState);
	printf("\n\n");

	printf("Test case 3: The transaction date is rejected as it is less than 10 characters \n");
	printf("Input Data: 12/1/2003\n");
	printf("Expected Result: WRONG_DATE\n");
	strcpy_s(termData.transactionDate, 11, "12/1/2003");
	ErrorState = getTransactionDate(&termData);
	printf("Actual Result: ");
	printErrorStateTerminal(ErrorState);
	printf("\n\n");

	printf("Test case 4: The transaction date is rejected as it has a wrong format \n");
	printf("Input Data: 121/20/03\n");
	printf("Expected Result: WRONG_DATE\n");
	strcpy_s(termData.transactionDate, 11, "121/20/03");
	ErrorState = getTransactionDate(&termData);
	printf("Actual Result: ");
	printErrorStateTerminal(ErrorState);
	printf("\n\n");

	printf("Test case 5: The transaction date is rejected as it is NULL \n");
	printf("Input Data: 0\n");
	printf("Expected Result: WRONG_DATE\n");
	strcpy_s(termData.transactionDate, 11, "0");
	ErrorState = getTransactionDate(&termData);
	printf("Actual Result: ");
	printErrorStateTerminal(ErrorState);
	printf("\n\n");

}


void isCardExpriedTest(void)
{
	EN_terminalError_t ErrorState;
	ST_terminalData_t termData ;
	ST_cardData_t     cardData ;

	printf("Tester name: Ahmed Mostafa Elmeniawy\n");
	printf("Function Name: isCardExpriedTest\n\n");

	printf("Test case 1: Card is not expired\n");
	printf("Input Data: Expiration date = 05/25, Transaction date = 21/01/2023\n");
	printf("Expected Result: TERMINAL_OK\n");
	strcpy_s(termData.transactionDate, 11, "21/01/2023");
	strcpy_s(cardData.cardExpirationDate, 6, "05/25");
	ErrorState = isCardExpired(&cardData, &termData);
	printf("Actual Result: ");
	printErrorStateTerminal(ErrorState);
	printf("\n\n");

	printf("Test case 2: Card is expired\n");
	printf("Input Data: Expiration date = 05/20, Transaction date = 21/01/2023\n");
	printf("Expected Result: EXPIRED_CARD\n");
	strcpy_s(termData.transactionDate, 11, "21/01/2023");
	strcpy_s(cardData.cardExpirationDate, 6, "05/20");
	ErrorState = isCardExpired(&cardData, &termData);
	printf("Actual Result: ");
	printErrorStateTerminal(ErrorState);
	printf("\n\n");

	printf("Test case 3: Card is expired\n");
	printf("Input Data: Expiration date = 05/22, Transaction date = 21/07/2022\n");
	printf("Expected Result: EXPIRED_CARD\n");
	strcpy_s(termData.transactionDate, 11, "21/07/2022");
	strcpy_s(cardData.cardExpirationDate, 6, "05/22");
	ErrorState = isCardExpired(&cardData, &termData);
	printf("Actual Result: ");
	printErrorStateTerminal(ErrorState);
	printf("\n\n");

}


void getTransactionAmountTest(void)
{
	EN_terminalError_t ErrorState;
	ST_terminalData_t termData ;

	printf("Tester name: Ahmed Mostafa Elmeniawy\n");
	printf("Function Name: getTransactionAmountTest\n\n");

	printf("Test case 1:\n");
	printf("Input Data: \n");
	printf("	Transaction Amount: ");
	ErrorState = getTransactionAmount(&termData);
	printf("Expected Result: TERMINAL_OK\n");
	printf("Actual Result: ");
	printErrorStateTerminal(ErrorState);
	printf("\n\n");

	printf("Test case 2:\n");
	printf("Input Data: \n");
	printf("	Transaction Amount: ");
	ErrorState = getTransactionAmount(&termData);
	printf("Expected Result: INVALID_AMOUNT\n");
	printf("Actual Result: ");
	printErrorStateTerminal(ErrorState);
	printf("\n\n");

}


void isBelowMaxAmountTest(void)
{
	EN_terminalError_t ErrorState;
	ST_terminalData_t termData;

	printf("Tester name: Ahmed Mostafa Elmeniawy\n");
	printf("Function Name: isBelowMaxAmountTest\n\n");

	printf("Test case 1:\n");
	printf("Input Data:\n");
	printf("	Transaction Amount: ");
	ErrorState = getTransactionAmount(&termData);
	if (ErrorState == TERMINAL_OK)
	{
		printf("	Maximum Transaction Amount: ");
		ErrorState = isBelowMaxAmount(&termData);
		if (ErrorState == TERMINAL_OK)
		{
			printf("Expected Result: TERMINAL_OK\n");
			printf("Actual Result: ");
			printErrorStateTerminal(ErrorState);
			printf("\n\n");
		}
		else
		{
			printf("Expected Result: EXCEED_MAX_AMOUNT\n");
			printf("Actual Result: ");
			printErrorStateTerminal(ErrorState);
			printf("\n\n");
		}
		
	}
	else
	{
		printf("Actual Result: ");
		printErrorStateTerminal(ErrorState);
		printf("\n\n");
	}

	printf("Test case 2:\n");
	printf("Input Data:\n");
	printf("	Transaction Amount: ");
	ErrorState = getTransactionAmount(&termData);
	if (ErrorState == TERMINAL_OK)
	{
		printf("	Maximum Transaction Amount: ");
		ErrorState = isBelowMaxAmount(&termData);
		if (ErrorState == TERMINAL_OK)
		{
			printf("Expected Result: TERMINAL_OK\n");
			printf("Actual Result: ");
			printErrorStateTerminal(ErrorState);
			printf("\n\n");
		}
		else
		{
			printf("Expected Result: EXCEED_MAX_AMOUNT\n");
			printf("Actual Result: ");
			printErrorStateTerminal(ErrorState);
			printf("\n\n");
		}

	}
	else
	{
		printf("Actual Result: ");
		printErrorStateTerminal(ErrorState);
		printf("\n\n");
	}
	
}


void setMaxAmountTest(void)
{
	EN_terminalError_t ErrorState;
	uint8_t index;
	f32_t maxAmount;

	ST_terminalData_t termData;

	printf("Tester name: Ahmed Mostafa Elmeniawy\n");
	printf("Function Name: setMaxAmountTest\n\n");

	/***** This loop is for test cases *****/
	for (index = 0; index < 2; index++)
	{
		printf("Test case %d:\n", (index+1));
		printf("Input Data: ");
		scanf_s("%f", &maxAmount);
		ErrorState = setMaxAmount(&termData, maxAmount);

		if (ErrorState == INVALID_MAX_AMOUNT)
		{
			printf("Expected Result: INVALID_MAX_AMOUNT\n");
			printf("Actual Result: ");
			printErrorStateTerminal(ErrorState);
			printf("\n\n");
		}
		else
		{
			printf("Expected Result: TERMINAL_OK\n");
			printf("Actual Result: ");
			printErrorStateTerminal(ErrorState);
			printf("\n\n");
		}
	}

}

/***************************** Code of the 5 functions ******************************/

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) /* Do not forget to make this function ask for data */
{
	EN_terminalError_t ErrorState;
	uint8_t index = 0, size = 0;

	gets_s(termData->transactionDate, 11);		// Used when testing the whole program

	if (termData->transactionDate != NULL)
	{
		while (termData->transactionDate[index] != '\0')
		{
			if ((termData->transactionDate[index] == '0') || (termData->transactionDate[index] == '1') ||
				(termData->transactionDate[index] == '2') || (termData->transactionDate[index] == '3') ||
				(termData->transactionDate[index] == '4') || (termData->transactionDate[index] == '5') ||
				(termData->transactionDate[index] == '6') || (termData->transactionDate[index] == '7') ||
				(termData->transactionDate[index] == '8') || (termData->transactionDate[index] == '9'))
				{
				index++;
			   }
			else if (termData->transactionDate[index] == '/')
			{
				index++;
			}
			else
			{
				ErrorState = WRONG_DATE;
				index++;
				goto EndFunction;
			}
		}

		size = index;

		if ((termData->transactionDate == NULL) || (size < 10) || (size > 10))
		{
			ErrorState = WRONG_DATE;
		}
		else
		{
			ErrorState = TERMINAL_OK;
			
		}
	}
	else
	{
		ErrorState = WRONG_DATE;
	}

EndFunction:
	return ErrorState;
} 

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) /* Do not forget to make this function ask for data */
{
	uint8_t monthCard = 0, monthTerm = 0, yearCard = 0, yearTerm = 0;
	EN_terminalError_t ErrorState;

	/* Convert the date from string to digits */
	monthCard = (cardData->cardExpirationDate[0] - 48) * 10 + (cardData->cardExpirationDate[1] - 48);
	yearCard  = (cardData->cardExpirationDate[3] - 48) * 10 + (cardData->cardExpirationDate[4] - 48);

	monthTerm = (termData->transactionDate[3] - 48) * 10 + (termData->transactionDate[4] - 48);
	yearTerm  = (termData->transactionDate[8] - 48) * 10 + (termData->transactionDate[9] - 48);

	/* Check the validation of the date */
	if (yearCard < yearTerm)
	{
		ErrorState = EXPIRED_CARD;
	}
	else if (yearCard == yearTerm)
	{
		if (monthCard < monthTerm)
		{
			ErrorState = EXPIRED_CARD;
		}
		else
		{
			ErrorState = TERMINAL_OK;
		}
	}
	else
	{
		ErrorState = TERMINAL_OK;
	}


	return ErrorState;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t ErrorState;

	scanf_s("%f", &termData->transAmount);

	if (termData->transAmount <= 0)
	{
		ErrorState = INVALID_AMOUNT;
	}
	else
	{
		ErrorState = TERMINAL_OK;
	}

	return ErrorState;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t ErrorState;

	scanf_s("%f", &termData->maxTransAmount);		// Used when testing the function itself

	if (termData->transAmount > termData->maxTransAmount)
	{
		ErrorState = EXCEED_MAX_AMOUNT;
	}
	else
	{
		ErrorState = TERMINAL_OK;
	}

	return ErrorState;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, f32_t maxAmount)
{
	EN_terminalError_t ErrorState;

	termData->maxTransAmount = maxAmount;

	if (termData->maxTransAmount <= 0)
	{
		ErrorState = INVALID_MAX_AMOUNT;
	}
	else
	{
		ErrorState = TERMINAL_OK;
	}

	return ErrorState;
}

