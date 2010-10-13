#include <stdio.h>
#include <stdlib.h>
#include "stack.h"





doubleStack* createStackNode(double value) {
	doubleStack* newStack = malloc(sizeof(doubleStack));
	newStack->value = value;
	return newStack;
}

doubleStack* push(double value, doubleStack* head){
	doubleStack* newStackNode = createStackNode(value);
	newStackNode->next = head;
	return newStackNode;
	
}
double pop(doubleStack** headPointer, int *valid){
	double value;
	doubleStack* head = *headPointer;
	
	if(*valid == 0)
		return 0;
		
	if(head == NULL){
		*valid = 0;
		return 0;
	}
	
	value = head->value;
	*headPointer = head->next;
	free(head);
	
	return value;
}
void printStackContent(doubleStack* head){

	doubleStack* currentNode = head;
	fprintf(stderr, "Stack contents:\n");
	
	while (currentNode != NULL){
		fprintf(stderr, "%f\n", currentNode->value);
		currentNode = currentNode->next;
	}
}

void* destructStack(doubleStack* head){
	doubleStack *currentNode, *nextNode;
	
	if(head == NULL)
		return NULL;
		
	currentNode = head;
	
	while(currentNode != NULL){
		nextNode = currentNode->next;
		free(currentNode);
		currentNode = nextNode;
	}
	
	return NULL;
}
