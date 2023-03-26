#include <stdio.h>
#include "../Project_Payment_Application/Types.h"
#include "card.h"
#include<string.h>
#include<stdlib.h>


void printErrorState(EN_cardError_t ErrorState)
{
	switch (ErrorState)
	{
	case CARD_OK:
		printf("CARK_OK\n");
		break;
	case WRONG_NAME: 
		printf("WRONG_NAME\n");
		break;
	case WRONG_EXP_DATE:
		printf("WRONG_EXP_DATE\n");
		break;
	case WRONG_PAN:
		printf("WRONG_PAN\n");
		break;
	case 0:
		printf("NULL\n");
		break;
	}
}

/************************************** Test Functions ***************************************/

void getCardHolderNameTest(void)
{
	EN_cardError_t ErrorState;
	ST_cardData_t cardData;
		
		printf("Tester name: Ahmed Mostafa Elmeniawy\n");
		printf("Function Name: getCardHolderName\n\n");

		printf("Test case 1: The name is accepted\n");
		printf("Input Data: Ahmed Mostafa Elmeniawy\n");
		printf("Expected Result: CARD_OK\n");
		strcpy_s(&cardData.cardHolderName, 30, "Ahmed Mostafa Elmeniawy");
		ErrorState = getCardHolderName(&cardData);
		printf("Actual Result: ");
		printErrorState(ErrorState);
		printf("\n\n");

		printf("Test case 2: The name is rejected as it includes a special character\n");
		printf("Input Data: Ahmed $ostafa Elmeniawy\n");
		printf("Expected Result: WRONG_NAME\n");
		strcpy_s(cardData.cardHolderName, 25, (uint8_t)"Ahmed $ostafa Elmeniawy");
		ErrorState = getCardHolderName(&cardData);
		printf("Actual Result: ");
		printErrorState(ErrorState);
		printf("\n\n");
		
		printf("Test case 3: The name is rejected as it includes a number\n");
		printf("Input Data: Ahmed Mostafa E8meniawy\n");
		printf("Expected Result: WRONG_NAME\n");
		strcpy_s(cardData.cardHolderName, 25, (uint8_t)"Ahmed Mostafa E8meniawy");
		ErrorState = getCardHolderName(&cardData);
		printf("Actual Result: ");
		printErrorState(ErrorState);
		printf("\n\n");

		printf("Test case 4: The name is rejected as it is less than 20\n");
		printf("Input Data: Ahmed\n");
		printf("Expected Result: WRONG_NAME\n");
		strcpy_s(cardData.cardHolderName, 25, (uint8_t)"Ahmed");
		ErrorState = getCardHolderName(&cardData);
		printf("Actual Result: ");
		printErrorState(ErrorState);
		printf("\n\n");
		
		printf("Test case 5: The name is rejected as it is greater than 24\n");
		printf("Input Data: Ahmed Mostafa Abdo Elmeniawy\n");
		printf("Expected Result: WRONG_NAME\n");
		cardData.cardHolderName[0] = (uint8_t) 'A';		cardData.cardHolderName[1] = (uint8_t) 'h';
		cardData.cardHolderName[2] = (uint8_t) 'm';		cardData.cardHolderName[3] = (uint8_t) 'e';
		cardData.cardHolderName[4] = (uint8_t) 'd';		cardData.cardHolderName[5] = (uint8_t) ' ';
		cardData.cardHolderName[6] = (uint8_t) 'M';		cardData.cardHolderName[7] = (uint8_t) 'o';
		cardData.cardHolderName[8] = (uint8_t) 's';		cardData.cardHolderName[9] = (uint8_t) 't';
		cardData.cardHolderName[10] =(uint8_t) 'a';		cardData.cardHolderName[11] =(uint8_t) 'f';
		cardData.cardHolderName[12] =(uint8_t) 'a';		cardData.cardHolderName[13] =(uint8_t) ' ';
		cardData.cardHolderName[14] =(uint8_t) 'A';		cardData.cardHolderName[15] =(uint8_t) ' ';
		cardData.cardHolderName[16] =(uint8_t) 'E';		cardData.cardHolderName[17] =(uint8_t) 'l';
		cardData.cardHolderName[18] =(uint8_t) 'm';		cardData.cardHolderName[19] =(uint8_t) 'e';
		cardData.cardHolderName[20] =(uint8_t) 'n';		cardData.cardHolderName[21] =(uint8_t) 'i';
		cardData.cardHolderName[22] =(uint8_t) 'a';		cardData.cardHolderName[23] =(uint8_t) 'w';
		cardData.cardHolderName[24] =(uint8_t) 'y';		cardData.cardHolderName[25] =(uint8_t) 'A';
		cardData.cardHolderName[26] =(uint8_t) '\0';
		ErrorState = getCardHolderName(&cardData);
		printf("Actual Result: ");
		printErrorState(ErrorState);
		printf("\n\n");
		
		printf("Test case 6: The name is rejected as it is NULL(0)\n");
		printf("Input Data: 0\n");
		printf("Expected Result: WRONG_NAME\n");
		strcpy_s(cardData.cardHolderName, 25, (uint8_t)'0');
		ErrorState = getCardHolderName(&cardData);
		printf("Actual Result: ");
		printErrorState(ErrorState);
		printf("\n\n");
	
}



void getCardExpiryDateTest(void)
{
	EN_cardError_t ErrorState;
	ST_cardData_t cardData ;

	printf("Tester name: Ahmed Mostafa Elmeniawy\n");
	printf("Function Name: getCardExpiryDateTest\n\n");

	printf("Test case 1: The expiration date is accepted\n");
	printf("Input Data: 05/25\n");
	printf("Expected Result: CARD_OK\n");
	strcpy_s(cardData.cardExpirationDate,6 , (uint8_t)"05/25");
	ErrorState = getCardExpiryDate(&cardData);
	printf("Actual Result: ");
	printErrorState(ErrorState);
	printf("\n\n");

	printf("Test case 2: The expiration date is rejected as it contains a character\n");
	printf("Input Data: 05/A5\n");
	printf("Expected Result: WRONG_EXP_DATE\n");
	strcpy_s(cardData.cardExpirationDate,6 , (uint8_t)"05/A5");
	ErrorState = getCardExpiryDate(&cardData);
	printf("Actual Result: ");
	printErrorState(ErrorState);
	printf("\n\n");
	

	printf("Test case 3: The expiration date is rejected as it contains a special character\n");
	printf("Input Data: 05/2@\n");
	printf("Expected Result: WRONG_EXP_DATE\n");
	strcpy_s(cardData.cardExpirationDate,6 , (uint8_t)"05/2@");
	ErrorState = getCardExpiryDate(&cardData);
	printf("Actual Result: ");
	printErrorState(ErrorState);
	printf("\n\n");
	

	printf("Test case 4: The expiration date is rejected as it is a wrong format\n");
	printf("Input Data: 05A5/\n");
	printf("Expected Result: WRONG_EXP_DATE\n");
	strcpy_s(cardData.cardExpirationDate,6 , (uint8_t)"05A5/");
	ErrorState = getCardExpiryDate(&cardData);
	printf("Actual Result: ");
	printErrorState(ErrorState);
	printf("\n\n");
	

	printf("Test case 5: The expiration date is rejected as it is less than 5 characters\n");
	printf("Input Data: 5/6\n");
	printf("Expected Result: WRONG_EXP_DATE\n");
	strcpy_s(cardData.cardExpirationDate,6 , (uint8_t)"5/6");
	ErrorState = getCardExpiryDate(&cardData);
	printf("Actual Result: ");
	printErrorState(ErrorState);
	printf("\n\n");
	

	printf("Test case 6: The expiration date is rejected as it is greater than 5 characters\n");
	printf("Input Data: 025/09\n");
	printf("Expected Result: WRONG_EXP_DATE\n");
	strcpy_s(cardData.cardExpirationDate,6 , (uint8_t) "025/9");
	ErrorState = getCardExpiryDate(&cardData);
	printf("Actual Result: ");
	printErrorState(ErrorState);
	printf("\n\n");
	

	printf("Test case 7: The expiration date is rejected as it equals to NULL(0)\n");
	printf("Input Data: 0\n");
	printf("Expected Result: WRONG_EXP_DATE\n");
	strcpy_s(cardData.cardExpirationDate,6 , (uint8_t)'0');
	ErrorState = getCardExpiryDate(&cardData);
	printf("Actual Result: ");
	printErrorState(ErrorState);
	printf("\n\n");

}




void getCardPANTest(void)
{
	EN_cardError_t ErrorState;
	ST_cardData_t cardData;

	printf("Tester name: Ahmed Mostafa Elmeniawy\n");
	printf("Function Name: getCardPANTest\n\n");

	printf("Test case 1: The PAN is accepted\n");
	printf("Input Data: 053646974315689642\n");
	printf("Expected Result: CARD_OK\n");
	strcpy_s(  cardData.primaryAccountNumber, 20, (uint8_t)"053646974315689642");
	ErrorState = getCardPAN(&cardData);
	printf("Actual Result: ");
	printErrorState(ErrorState);
	printf("\n\n");

	printf("Test case 2: The PAN is rejected as it is greater than 19 characters\n");
	printf("Input Data: 111111111111111111111\n");
	printf("Expected Result: WRONG_PAN\n");
	cardData.primaryAccountNumber[0]  = (uint8_t) '1';		cardData.primaryAccountNumber[1]  = (uint8_t) '1';
	cardData.primaryAccountNumber[2]  = (uint8_t) '1';		cardData.primaryAccountNumber[3]  = (uint8_t) '1';
	cardData.primaryAccountNumber[4]  = (uint8_t) '1';		cardData.primaryAccountNumber[5]  = (uint8_t) '1';
	cardData.primaryAccountNumber[6]  = (uint8_t) '1';		cardData.primaryAccountNumber[7]  = (uint8_t) '1';
	cardData.primaryAccountNumber[8]  = (uint8_t) '1';		cardData.primaryAccountNumber[9]  = (uint8_t) '1';
	cardData.primaryAccountNumber[10] = (uint8_t) '1';		cardData.primaryAccountNumber[11] = (uint8_t) '1';
	cardData.primaryAccountNumber[12] = (uint8_t) '1';		cardData.primaryAccountNumber[13] = (uint8_t) '1';
	cardData.primaryAccountNumber[14] = (uint8_t) '1';		cardData.primaryAccountNumber[15] = (uint8_t) '1';
	cardData.primaryAccountNumber[16] = (uint8_t) '1';		cardData.primaryAccountNumber[17] = (uint8_t) '1';
	cardData.primaryAccountNumber[18] = (uint8_t) '1';		cardData.primaryAccountNumber[19] = (uint8_t) '1';
	cardData.primaryAccountNumber[20] = (uint8_t) '1';		cardData.primaryAccountNumber[21] = (uint8_t) '1';
	ErrorState = getCardPAN(&cardData);
	printf("Actual Result: ");
	printErrorState(ErrorState);
	printf("\n\n");

	printf("Test case 3: The PAN is rejected as it is less than 16 characters\n");
	printf("Input Data: 0536469\n");
	printf("Expected Result: WRONG_PAN\n");
	strcpy_s(cardData.primaryAccountNumber, 20, (uint8_t)"0536469");
	ErrorState = getCardPAN(&cardData);
	printf("Actual Result: ");
	printErrorState(ErrorState);
	printf("\n\n");

	printf("Test case 4: The PAN is rejected as it is NULL\n");
	printf("Input Data: 0\n");
	printf("Expected Result: WRONG_PAN\n");
	strcpy_s(cardData.primaryAccountNumber, 20, (uint8_t)'0');
	ErrorState = getCardPAN(&cardData);
	printf("Actual Result: ");
	printErrorState(ErrorState);
	printf("\n\n");

	printf("Test case 5: The PAN is rejected as it contains characters\n");
	printf("Input Data: 05364697LD15689642\n");
	printf("Expected Result: WRONG_PAN\n");
	strcpy_s(cardData.primaryAccountNumber, 20, (uint8_t)"05364697LD15689642");
	ErrorState = getCardPAN(&cardData);
	printf("Actual Result: ");
	printErrorState(ErrorState);
	printf("\n\n");

	printf("Test case 6: The PAN is rejected as it contains special characters\n");
	printf("Input Data: 05364697@15#689642\n");
	printf("Expected Result: WRONG_PAN\n");
	strcpy_s(cardData.primaryAccountNumber, 20, (uint8_t)"05364697@15#689642");
	ErrorState = getCardPAN(&cardData);
	printf("Actual Result: ");
	printErrorState(ErrorState);
	printf("\n\n");

}

/***************************************** Code of the three functions ***********************************************/

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	EN_cardError_t ErrorState;
	uint8_t size=0, index = 0;

	gets_s(cardData->cardHolderName, 30);			//Used when testing the whole program

	
		while (cardData->cardHolderName[index] != (uint8_t)'\0')
		{
			if (((cardData->cardHolderName[index] >= (uint8_t)'a') && (cardData->cardHolderName[index] <= (uint8_t)'z')) || 
				((cardData->cardHolderName[index] >= (uint8_t)'A') && (cardData->cardHolderName[index] <= (uint8_t)'Z')))
			{
				index++;
			}
			else if (cardData->cardHolderName[index] == (uint8_t)' ')
			{
				index++;
			}
			else
			{
				ErrorState = WRONG_NAME;
				index++;
				goto EndFunction;
			}
		}
		size = index;
	

	if ((cardData == NULL) || (size < 20) || (size > 24))
	{
		ErrorState = WRONG_NAME;
	}
	else
	{
		ErrorState = CARD_OK;
	}

EndFunction:
	return ErrorState;
}



EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	EN_cardError_t ErrorState;
	uint8_t size = 0, index = 0;
	ST_cardData_t* CARD_EXPIRATION_DATE = &cardData->cardExpirationDate;

	gets_s(cardData->cardExpirationDate, 6);		// Used when testing the whole program

	if (*cardData->cardExpirationDate != (uint8_t) NULL)
	{
		while (cardData->cardExpirationDate[index] != (uint8_t)'\0')
		{
			if ((cardData->cardExpirationDate[index] == (uint8_t)'0') || (cardData->cardExpirationDate[index] == (uint8_t)'1') || 
				(cardData->cardExpirationDate[index] == (uint8_t)'2') || (cardData->cardExpirationDate[index] == (uint8_t)'3') || 
				(cardData->cardExpirationDate[index] == (uint8_t)'4') || (cardData->cardExpirationDate[index] == (uint8_t)'5') || 
				(cardData->cardExpirationDate[index] == (uint8_t)'6') || (cardData->cardExpirationDate[index] == (uint8_t)'7') || 
				(cardData->cardExpirationDate[index] == (uint8_t)'8') || (cardData->cardExpirationDate[index] == (uint8_t)'9')) 
			{
				index++;
			}
			else if (cardData->cardExpirationDate[index] == (uint8_t)'/')
			{
				index++;
			}
			else
			{
				ErrorState = WRONG_EXP_DATE;
				index++;
				goto EndFunction;
			}
		}
		size = index;
	}


	if ((cardData == NULL) ||  (size < 5) || (size > 5) || (cardData->cardExpirationDate[2] != (uint8_t)'/'))
	{
		ErrorState = WRONG_EXP_DATE;
	}
	else
	{
		ErrorState = CARD_OK;
	}


EndFunction:
	return ErrorState;
}



EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	EN_cardError_t ErrorState;
	uint8_t index = 0, size = 0;

	gets_s(cardData->primaryAccountNumber, 20);			// Used when testing the whole program

		while (cardData->primaryAccountNumber[index] != (uint8_t)'\0')
		{
			if (((cardData->primaryAccountNumber[index] >= (uint8_t)'a') && (cardData->primaryAccountNumber[index] <= (uint8_t)'z')) ||
				((cardData->primaryAccountNumber[index] >= (uint8_t)'A') && (cardData->primaryAccountNumber[index] <= (uint8_t)'Z')))
			{
				ErrorState = WRONG_PAN;
				index++;
				goto EndFunction;
			}
			else if ((cardData->primaryAccountNumber[index] == (uint8_t)'0') || (cardData->primaryAccountNumber[index] == (uint8_t)'1') ||
					 (cardData->primaryAccountNumber[index] == (uint8_t)'2') || (cardData->primaryAccountNumber[index] == (uint8_t)'3') ||
					 (cardData->primaryAccountNumber[index] == (uint8_t)'4') || (cardData->primaryAccountNumber[index] == (uint8_t)'5') ||
					 (cardData->primaryAccountNumber[index] == (uint8_t)'6') || (cardData->primaryAccountNumber[index] == (uint8_t)'7') ||
					 (cardData->primaryAccountNumber[index] == (uint8_t)'8') || (cardData->primaryAccountNumber[index] == (uint8_t)'9'))
			{
				index++;
			}
			else
			{
				ErrorState = WRONG_PAN;
				index++;
				goto EndFunction;
			}
		}
	if(cardData->primaryAccountNumber == NULL)
	{
		ErrorState = WRONG_PAN;
		index++;
		goto EndFunction;
	}

	size = index;

	if ((size < 16) || (size > 19))
	{
		ErrorState = WRONG_PAN;
	}
	else
	{
		ErrorState = CARD_OK;
	}

EndFunction:
	return ErrorState;
}


