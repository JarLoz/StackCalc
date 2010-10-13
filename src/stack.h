/*
* Tiedosto: stack.h
* Tyyppi: Header
* Kirjoittaja: Kimmo Heikkinen
* Kuvaus:
* stack.h:ssa olevat funktiot toteuttavat pinon toiminnallisuuden double-tyyppisille alkiolle käyttäen
* tunnussolmutonta yhteen suuntaan linkitettyä listaa rakenteenaan. 
*/

/* listan solmun määrittely*/
struct doubleStack{
	double value;
	struct doubleStack *next;
};

typedef struct doubleStack doubleStack;

/*
* Funktio: createStackNode
* Parametrit: double-tyyppinen arvo
* Palautusarvo: pointteri doubleStack-tyyppiseen structiin
* Muuttaa: Ei mitään.
* Kuvaus:
* Funktio varaa tilaa uudelle doubleStack-struktille ja sijoittaa valueksi annetun double-arvon,
* sekä asettaa next-pointterin osoittamaan NULLiin.
*/
doubleStack* createStackNode(double);

/*
* Funktio: push
* Parametrit: double-tyyppinen arvo, doubleStack-tyyppinen pointteri pinon ensimmäiseen alkioon (head).
* Palautusarvo: pointteri pinon uuteen ensimmäiseen solmuun.
* Muuttaa: Ei mitään
* Kuvaus:
* Toteuttaa pinon push-operaation luomalla uuden solmun createStackNode-funktiolla käyttäen annettua arvoa ja 
* asettaen uuden solmun next-arvoksi annetun head-solmun, ja palauttaa viitteen tähän uuteen solmuun.
*/
doubleStack* push(double, doubleStack*);

/*
* Funktio: pop
* Parametrit: pointteri pinon ensimmäiseen alkioon osoittavaan pointteriin, pointteri int-tyyppiseen lippuun.
* Palautusarvo: pinon päällimmäinen double-arvo
* Muuttaa: Pinon ensimmäiseen alkioon osoittavaa pointteria, ja int-tyyppistä lippua
* Kuvaus:
* Toteuttaa pinon pop-operaation ottamalla talteen päällimmäisen solmun sisältämän double-arvon, poistamalla tämän
* solmun, ja päivittämällä annetun head-pointterin osoittamaan uuteen head-pointteriin. Annettu int-tyyppinen
* lippu liittyy pinolaskurin toteutukseen: Jos annettu lippu on 1, se tarkoittaa, että käsiteltävä RPN-tyyppinen
* lasku on validia. Pinolaskurin toteutuksen mukaan, jos algoritmi yrittää popata tyhjästä pinosta arvoa, on annettu
* lasku epävalidi. Tällöin muutetaan lipun arvoa nollaan, jolloin kaikki muut operaatiot osaavat lopettaa
* laskutoimituksen käsittelyn.
*/
double pop(doubleStack**, int*);

/*
* Funktio: printStackContent
* Parametrit: pointteri pinon ensimmäiseen alkioon.
* Palautusarvo: void
* Muuttaa: Ei mitään
* Kuvaus:
* Printtaa pinon sisällön stderr-tulostusvirtaan. Debuggauskäyttöön.
*/
void printStackContent(doubleStack*);

/*
* Funktio: destructStack
* Parametrit: pointteri pinon ensimmäiseen alkioon.
* Palautusarvo: void
* Muuttaa: Ei mitään
* Kuvaus:
* Vapauttaa pinoon käytetyn muistialueen kutsumalla jokaiselle solmulle free()-funktiota.
*/
void* destructStack(doubleStack*);
