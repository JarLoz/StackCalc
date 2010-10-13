/*
* Tiedosto: postfixArray.h
* Tyyppi: Header
* Kirjoittaja: Kimmo Heikkinen.
* Kuvaus:
* PostfixArrayssa sijaitsevat funktiot pilkkovat annetun RPN-muotoisen merkkijonon
* tokeneiksi, jotka kukin talletetaan dynaamisesti omaan mustilohkoonsa. Esimerkiksi
* merkkijono "345 64 +" tulkitaan kolmeksi tokeniksi, "345", "64" ja "+". Talletettuihin tokeneihin
* viitataan postfixArray-structin avulla, joka sisältää taulukon pointtereita muistialueille, ja 
* int-tyyppisen muuttujan, joka kertoo taulukon koon. Syy merkkijonon pilkkomiseen on, että tällä tavoin itse
* ohjelmalogiikka on helppo toteuttaa, kun tokenit ovat jo valmiiksi eroteltuina.
*/

/* Tokenien maksimilukumäärän määrittely. */
#define MAX_TOKENS 80

/* postfixArray-structin määrittely.*/
struct postfixArray{
	char** array;
	int size;
};
typedef struct postfixArray postfixArray;

/*
* Funktio: createPostfixArray
* Palautusarvo: pointteri postfixArray-structiin 
* Parametrit: pointteri RPN-muotoiseen merkkijonoon.
* Muuttaa: Ei mitään.
* 
* Funktio varaa dynaamisesti muistin uudelle postfixArray-structille ja
* pilkkoo annetun merkkijonon tokeneiksi, joille myös varataan dynaamisesti muistia, ja joihin osoittavat
* pointterit sijoitetaan luodun structin sisältämän taulukon sisään.
* 
* Luodun postfixArray:n muistialue on käytön jälkeen vapautettava destructPostfixArray-funktiolla.
*
* Käyttää hyväkseen stackCalculator.h:ssa määriteltyjä funktioita.
*/
postfixArray* createPostfixArray(char*);

/*
* Funktio: printPostfixArrayContents
* Palautusarvo: void
* Parametrit: pointteri postfixArray-structiin
* Muuttaa: Ei mitään.
*
* Funktio, joka printtaa annetun structin sisällön stderr-tulostusvirtaan. Debuggauskäyttöön tarkoitettu
*/
void printPostfixArrayContents(postfixArray*);

/*
* Funktio: destructPostfixArray
* Palatusarvo: void
* Parametrit: pointteri postfixArray-structiin
* Muuttaa: annetun pointterin takana olevaa structia
*
* Funktio vapauttaa ensin structin sisältämän taulukon osoittamille tokeneille varatut tilat,
* ja sen jälkeen itse structille varatun tilan.
*
*/
void destructPostfixArray(postfixArray*);
