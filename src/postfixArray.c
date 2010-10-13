/*
* Tiedosto: postfixArray.c
* Tyyppi: Source
* Kirjoittaja: Kimmo Heikkinen
* Kuvaus:
* Lähdekoodi, joka implementoi postfixArray.h:ssa kuvatun toiminnallisuuden, sekä yhden apufunktion.
* Käyttää hyväkseen stackCalculator.h:ssa kuvattuja funktiota.
*
*/



#include <stdio.h>
#include <stdlib.h>
#include "postfixArray.h"
#include "stackCalculator.h"

/*
* Funktio : isOperator
* Parametrit: yksi char-merkki
* Palautusarvo: != 0 jos annettu char on operaattori, muuten 0.
* Muuttaa. Ei mitään.
* Kuvaus:
* Tarkistaa onko annettu merkki operaattori. Käyttää hyväkseen stackCalculator.h:ssa esiteltyjä funktioita.
*/
int isOperator(char);

postfixArray* createPostfixArray(char* inputString){

	char** returnArray = calloc(MAX_TOKENS, sizeof(char*));
	char* tempString;
	char c;
	int returnArrayLength = 0;
	int index = 0;
	int tempIndex, tempIndex1, i;
	postfixArray* newPostfixArray;
	i = 0;
	
	while(i < MAX_TOKENS){
		returnArray[i] = NULL;
		i++;
	}
	
	#ifdef DEBUG
		fprintf(stderr, "Creating postfixArray\n");
	#endif
	
	/* Käydään läpi inputString yksi merkki kerrallaan */
	while((c = inputString[index])){
	
		/* 
		* Tämä kohta vaatinee hieman selittämistä: Jos vastaan tulee literal, eli numero,
		* algoritmi tämän jälkeen kelaa inputStringiä eteenpäin, kunnes löytää numeron lopun. Tämän jälkeen varataan tarvittavasti
		* tilaa numerolle ja kopioidaan se tempStringiin. Sitten tempString kopioidaan returnArray:hyn ja jatketaan inputStringin
		* lukemista numeron jälkeen.
		*/
		if(isLiteral(c)){
		
			#ifdef DEBUG
				fprintf(stderr, "Found Literal\n");
			#endif
			
			tempIndex = index;
			
			while(isLiteral(inputString[tempIndex]))
				tempIndex++;
			
			#ifdef DEBUG
				fprintf(stderr, "Literal start index: %d\nLiteral end index: %d\nAllocating memory\n", index, tempIndex);
			#endif
			
			tempString = calloc(tempIndex-index+1, sizeof(char));
			
			#ifdef DEBUG
				fprintf(stderr, "Memory allocated\n");
			#endif
			
			for(i = 0, tempIndex1 = index; tempIndex1 < tempIndex; i++, tempIndex1++){
			
				#ifdef DEBUG
					fprintf(stderr, "i = %d\ntempIndex1 = %d\n", i, tempIndex1);
				#endif
				
				tempString[i] = inputString[tempIndex1];
			}
			
			#ifdef DEBUG
				fprintf(stderr, "Literal: %s\n", tempString);
			#endif
			
			index = tempIndex-1;
			returnArray[returnArrayLength] = tempString;
			returnArrayLength++;
		}
		/*
		* Vastaava operaatio kuin numeron kanssa, mutta koska operaattorit (+, -, /, *) ovat vain yhden merkin
		* mittaisia, ei pituuden mittausta tarvitse tehdä.
		*/
		else if (isOperator(c)){
		
			#ifdef DEBUG
				fprintf(stderr, "Found operator\n");
			#endif
			
			tempString = calloc(2, sizeof(char));
			
			#ifdef DEBUG
				fprintf(stderr, "Memory allocated\n");
			#endif
			
			tempString[0] = c;
			
			#ifdef DEBUG
				fprintf(stderr, "Operator: %s\n", tempString);
			#endif
			
			returnArray[returnArrayLength] = tempString;
			returnArrayLength++;
		}
		
		index++;
		
	}
	
	/* luodaan uusi postfixArray-strukti ja talletetaan siihen osoitin luotuun returnArrayhyn*/
	
	newPostfixArray = malloc(sizeof(postfixArray));
	newPostfixArray->array = returnArray;
	newPostfixArray->size = returnArrayLength;
	
	#ifdef DEBUG
		fprintf(stderr, "Returning postfixArray, size: %d\n\n", returnArrayLength);
	#endif
	
	return newPostfixArray;
}
void printPostfixArrayContents(postfixArray* a){
	int i = 0;
	fprintf(stderr, "PostfixContents\n");
	
	while(i < a->size){
		fprintf(stderr, "Index %d: .%s.\n", i, a->array[i]);
		i++;
	}
}
int isOperator(char c){
	return(isPlus(c) || isMinus(c) || isMultiplying(c) || isDivision(c));
}
void destructPostfixArray(postfixArray* p){
	int i;
	
	if(p == NULL)
		return;
		
	for(i = 0; i < p->size; i++)
		free(p->array[i]);
	
	free(p->array);
	free(p);
}
