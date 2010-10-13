#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"
#include "stackCalculator.h"


int calculatorAlgo(char** postfix, int size, double* returnValue){

	char* string;
	double pushValue, tempValue1, tempValue2;
	int postfixIndex = 0;
	int validPostfix = 1;
	doubleStack* operationStack = NULL;
	
	#ifdef DEBUG
		fprintf(stderr, "Starting calculation, size: %d\n", size);
	#endif
	
	while(postfixIndex < size && validPostfix){
	
		string = postfix[postfixIndex];
		
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
		#endif
		
		postfixIndex++;
	}
	
	*returnValue =  pop(&operationStack, &validPostfix);
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
