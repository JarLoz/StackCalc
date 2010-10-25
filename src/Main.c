/*
* Tiedosto: Main.c
* Tyyppi: Source
* Kirjoittaja: Kimmo Heikkinen
* Kuvaus:
* Lähdekoodi, joka implementoi pinolaskurin käyttöliittymän ja testiajon.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "postfixArray.h"
#include "stackCalculator.h"

/* Laskutoimituksen maksimipituus merkkeinä*/
#define CALC_MAX_LENGTH 200
/* Tiedostonimen maksimipituus merkkeinä*/
#define MAX_FILENAME_LENGTH 200

/*
* Funktio: printHelp
* Parametrit: char-pointteri merkkijonoon
* Muuttaa: Ei mitään
* Esittely:
* Funktio printtaa ohjelman käyttöohjeet standardivirhetulostusvirtaan. Parametrina annettu merkkijono tulkitaan ohjelman
* nimeksi (argv[0]).
*/
void printHelp(char*);

/*
* Funktio: closeEverything
* Parametrit: pointteri postfixArray-struktiin, FILE-pointteri
* Muuttaa: molempien pointterien arvoja
* Esittely:
* Funktio vapauttaa postfixArray:lle varatun tilan ja sulkee avatun tiedoston, jos
* sisääntulotiedosto on käytössä. Käyttää hyväkseen postixArray.h:ssa määriteltyä toiminnallisuutta.
*/
void closeEverything(postfixArray*, FILE*);

/* Lippu, joka osoittaa onko lukutiedosto käytössä*/
static int usingInFile;

/*
* Funktio: main
* Parametrit: ohjelman komentoriviparametrit
* Palautusarvo: EXIT_SUCCESS jos ohjelma suoriutui oikein, muuten EXIT_FAILURE
* Muuttaa: Ei mitään
* Esittely:
* Ohjelman pääfunktio. Toteuttaa sekä käyttöliittymän, että ohjelman korkean tason toiminnan, mukaanlukien tiedostonlukemisen
* ja kirjoittamisen, käyttäen postfixArray.h:ssa ja stackCalculator.h:ssa määriteltyä toiminnallisuutta. Jos TESTMODE on 
* määritelty esiprosessointivaiheessa, funktio suorittaa testiajon virheentarkistusmoodissa, jossa ohjelman oikeellisuutta 
* testataan joukolla testitapauksia.
*
*/
int main(int argc, char** argv){

	postfixArray* currentPostfix;
	double result;
	
	/* Normaalin toiminnallisuuden määrittely*/
	#ifndef TESTMODE
	
	FILE* inFile = stdin;
	char calculation[CALC_MAX_LENGTH];

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
	
	#endif
	
	/* Testitilan määrittely */
	#ifdef TESTMODE

	int errors = 0;
	usingInFile = 0;
	fprintf(stdout, "Test mode activated\n**************\n\n");
	
	fprintf(stdout, "Testing simple valid calculation: 1 1 +, expected result 2\n\n");
	currentPostfix = createPostfixArray("1 1 +");
	if(calculatorAlgo(currentPostfix->array, currentPostfix->size, &result) == 0){
		fprintf(stdout, "************\nSomething has gone terribly wrong, 1 1 + is not valid\n");
		errors++;
	}
	else{
		fprintf(stdout, "************\nResult: %f\n\n", result);
	}
	destructPostfixArray(currentPostfix);
	
	
	fprintf(stdout, "Testing simple invalid calculation: 1 + 1, expected result none\n");
	currentPostfix = createPostfixArray("1 + +");
	if(calculatorAlgo(currentPostfix->array, currentPostfix->size, &result) == 0){
		fprintf(stdout, "************\nEverything alright, 1 + 1 is not valid\n\n");
	}
	else{
		fprintf(stdout, "************\nWhat the hell it was valid, this is the result: %f\n\n", result);
		errors++;
	}
	destructPostfixArray(currentPostfix);
	
	
	fprintf(stdout, "Testing valid calculation: 2 46 33 + 32 - 5 / *, expected result 18.8\n");
	currentPostfix = createPostfixArray("2 46 33 + 32 - 5 / *");
	if(calculatorAlgo(currentPostfix->array, currentPostfix->size, &result) == 0){
		fprintf(stdout, "************\nSomething has gone terribly wrong, 46 33 + 32 - 5 / is not valid\n\n");
		errors++;
	}
	else{
		fprintf(stdout, "************\nResult: %f\n\n", result);
	}
	destructPostfixArray(currentPostfix);
	
	
	fprintf(stdout, "Testing invalid calculation: 765 33 654 234 + / * / 3456, expected result none\n");
	currentPostfix = createPostfixArray("765 33 654 234 + / * / 3456");
	if(calculatorAlgo(currentPostfix->array, currentPostfix->size, &result) == 0){
		fprintf(stdout, "************\nEverything alright, 765 33 654 234 + / * / 3456 is not valid\n\n");
	}
	else{
		fprintf(stdout, "************\nWhat the hell, it was valid, this is the result: %f\n\n", result);
		errors++;
	}
	destructPostfixArray(currentPostfix);
	
	
	fprintf(stdout, "Testing invalid calculation: 66 44 + 44, expected result none\n");
	currentPostfix = createPostfixArray("66 44 + 44");
	if(calculatorAlgo(currentPostfix->array, currentPostfix->size, &result) == 0){
		fprintf(stdout, "************\nEverything alright, 66 44 + 44 is not valid\n\n");
	}
	else{
		fprintf(stdout, "************\nWhat the hell, it was valid, this is the result: %f\n\n", result);
		errors++;
	}
	destructPostfixArray(currentPostfix);
	fprintf(stdout, "End of test, total errors: %d\n", errors);
	
	#endif
	
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
