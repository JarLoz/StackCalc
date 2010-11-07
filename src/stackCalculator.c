/*
* Tiedosto: stackCalculator.c
* Tyyppi: Source
* Kirjoittaja: Kimmo Heikkinen
* Kuvaus:
* Lähdekoodi, joka implementoi stackCalculator.h:ssa määritellyn toiminnallisuuden. Käyttää hyväkseen
* stack.h:ssa määriteltyä toiminnallisuutta
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"
#include "stackCalculator.h"

#ifdef TESTMODE
	#ifndef DEBUG
		#define DEBUG
	#endif
#endif

int calculatorAlgo(char** postfix, int size, double* returnValue){

	char* string;
	double pushValue, tempValue1, tempValue2;
	int postfixIndex = 0;
	int validPostfix = 1;
	doubleStack* operationStack = NULL;
	
	#ifdef DEBUG
		fprintf(stderr, "Starting calculation, size: %d\n", size);
	#endif
	
	/* Luuppia pyöritetään vain jos validPostfix-lippu osoittaa laskutoimituksen muodon olevan edelleen oikea*/
	while(postfixIndex < size && validPostfix){
	
		string = postfix[postfixIndex];
		
		/*Tarkasteluissa tutkitaan vain tokenin ensimmäistä merkkiä, koska se määrää itse tokenin tyypin*/
		
		if( isLiteral(string[0]) ){
			pushValue = atof(string);
			operationStack = push(pushValue, operationStack);
			
			#ifdef DEBUG
				fprintf(stderr, "Pushing value %f to stack from string %s\n", pushValue, string);
			#endif
			
		}
		
		else{
		
			if( isPlus(string[0]) ){
			
				tempValue2 = pop(&operationStack, &validPostfix);
				tempValue1 = pop(&operationStack, &validPostfix);
				pushValue = tempValue1 + tempValue2;
				operationStack = push(pushValue, operationStack);
				
				#ifdef DEBUG
					fprintf(stderr, "Pushing value %f to stack(plus Operation)\n", pushValue);
				#endif
			}
			
			else if ( isMinus(string[0]) ){
			
				tempValue2 = pop(&operationStack, &validPostfix);
				tempValue1 = pop(&operationStack, &validPostfix);
				pushValue = tempValue1 - tempValue2;
				operationStack = push(pushValue, operationStack);
				
				#ifdef DEBUG
					fprintf(stderr, "Pushing value %f to stack(minus Operation)\n", pushValue);
				#endif
			}
			
			else if ( isMultiplying(string[0]) ){
			
				tempValue2 = pop(&operationStack, &validPostfix);
				tempValue1 = pop(&operationStack, &validPostfix);
				pushValue = tempValue1 * tempValue2;
				operationStack = push(pushValue, operationStack);
				
				#ifdef DEBUG
					fprintf(stderr, "Pushing value %f to stack(multiplying operation)\n", pushValue);
				#endif
			}
			
			else if ( isDivision(string[0]) ){
			
				tempValue2 = pop(&operationStack, &validPostfix);
				tempValue1 = pop(&operationStack, &validPostfix);
				pushValue = tempValue1 / tempValue2;
				operationStack = push(pushValue, operationStack);
				
				#ifdef DEBUG
					fprintf(stderr, "Pushing value %f to stack(division operation)\n", pushValue);
				#endif
			}
		}
		
		#ifdef DEBUG
			printStackContent(operationStack);
			if(!validPostfix)
				fprintf(stderr, "Invalid postfix (empty stack), aborting calculation\n");
		#endif
		
		postfixIndex++;
	}
	
	*returnValue =  pop(&operationStack, &validPostfix);
	
	/* Jos pino ei ole tyhjä, ei laskutoimitus voinut olla validi */
	if(operationStack != NULL && validPostfix){
		validPostfix = 0;
		#ifdef DEBUG
			fprintf(stderr, "Invalid postfix (values remain in stack after calculation), aborting calculation\n");
		#endif
	}
	destructStack(operationStack);
	return validPostfix;
}

int isPlus(char c){
	if(c == '+')
		return 1;
	else
		return 0;
}

int isMinus(char c){
	if(c == '-')
		return 1;
	else
		return 0;
}

int isMultiplying(char c){
	if(c == '*')
		return 1;
	else
		return 0;
}

int isDivision(char c){
	if(c == '/')
		return 1;
	else
		return 0;
}

int isWhiteSpace(char c){
	if(c == ' ' || c == '\t' || c == '\0' || c == '\n')
		return 1;
	else
		return 0;
}


int isLiteral(char c){
	if((c >= '0' && c <= '9') || c == '.')
		return 1;
	else
		return 0;
}
