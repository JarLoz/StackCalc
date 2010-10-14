/*
* Tiedosto: stackCalculator.h
* Tyyppi: Header
* Kirjoittaja: Kimmo Heikkinen.
* Kuvaus:
* stackCalculator.h:ssa esitellyt funktiot toteuttavat pinolaskurin toiminnallisuuden käyttäen
* hyväkseen stack:h:ssa määriteltyä pinototeutusta. 
*/




#define STARTING_STACK_SIZE 10
#define MAX_STRING_LENGTH 80
int calculatorAlgo(char**, int, double*);
int isPlus(char);
int isMinus(char);
int isMultiplying(char);
int isDivision(char);
int isWhiteSpace(char);
int isLiteral(char);

