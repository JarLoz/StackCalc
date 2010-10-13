#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "postfixArray.h"
#include "stackCalculator.h"

#define CALC_MAX_LENGTH 200
#define MAX_FILENAME_LENGTH 200

void printHelp(char*);
void closeEverything(postfixArray*, FILE*);

static int usingInFile;


int main(int argc, char** argv){
	FILE* inFile = stdin;
	double result;
	char calculation[CALC_MAX_LENGTH];
	postfixArray* currentPostfix;
	if(argc > 1){
	
		if(strcmp(argv[1], "-h") == 0)
			printHelp(argv[0]);

		else if (strcmp(argv[1], "-f") == 0){
			if((inFile = fopen(argv[2], "r")) == NULL){
				fprintf(stderr, "File %s not found\n", argv[2]);
				exit(EXIT_FAILURE);
			}
			usingInFile = 1;
		}
		
		else{
			fprintf(stderr, "Incorrect arguments\n");
			printHelp(argv[0]);
		}
		
	}
	else
		usingInFile = 0;
	
	
	while(fgets(calculation, CALC_MAX_LENGTH, inFile) != NULL){
		
		if(calculation[0] == '\n' || calculation[0] == '\0'){
			closeEverything(currentPostfix, inFile);
			return(EXIT_SUCCESS);
		}
		
		currentPostfix = createPostfixArray(calculation);
		
		if(calculatorAlgo(currentPostfix->array, currentPostfix->size, &result) == 0){			
			fprintf(stderr, "INVALID FORM, STOP DOING THAT, SHUTTING DOWN EVERYTHING\n");
			closeEverything(currentPostfix, inFile);
			return(EXIT_FAILURE);
		}	
		
		fprintf(stdout, "%s = %f\n", calculation, result);	
			
		destructPostfixArray(currentPostfix);
		currentPostfix = NULL;
	}
	
	fclose(inFile);
	return(EXIT_SUCCESS);
}

void printHelp(char* progName){
	fprintf(stderr, "A small program for calculating mathematical forms in reverse polish notation\n");
	fprintf(stderr, "The forms are read either from keyboard in interactive mode, or from a specified file\n");
	fprintf(stderr, "The output is written to stdout\n");
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "%s\n", progName);
	fprintf(stderr, "%s -h\n", progName);
	fprintf(stderr, "%s -f filename\n", progName);
	fprintf(stderr, "No arguments: Interactive mode, input calculations by hand, empty input ends the process.\n");
	fprintf(stderr, "-h : Prints this help and exits\n");
	fprintf(stderr, "-f filename : reads the calculations from specified filename\n");
	exit(EXIT_SUCCESS);
}

void closeEverything(postfixArray* array, FILE* inFile){
	destructPostfixArray(array);
	if(usingInFile)
		fclose(inFile);
}
