/*
* Tiedosto: stackCalculator.h
* Tyyppi: Header
* Kirjoittaja: Kimmo Heikkinen.
* Kuvaus:
* stackCalculator.h:ssa esitellyt funktiot toteuttavat pinolaskurin toiminnallisuuden käyttäen
* hyväkseen stack:h:ssa määriteltyä pinototeutusta. 
*/



/*
* Funktio: calculatorAlgo
* Parametrit: Laskutoimitus postfixArray:n määrittelemässä muodossa, laskutoimituksen tokenien määrä, pointteri double-arvoon
* Palautusarvo: 0, jos annettu laskutoimitus ei ole validi, muuten 1
* Muuttaa: annetun double-pointterin osoittamaa muuttujaa
* Kuvaus:
* Toteuttaa pinolaskurin toiminnallisuuden käyttämällä hyväkseen stack.h:ssa määriteltyä pinototeutusta ja postfixArray-modulissa
* luotua taulukkokuvausta itse laskutoimituksesta. Algoritmi käy läpi postfix-muotoisen merkkijonoista koostuvan taulukon, ja
* suorittaa asiaankuuluvat pinolaskurin toimenpiteet. Kun taulukko on käyty läpi, muutetaan annetun double-pointterin takaa löytyvä
* arvo pinon päällimmäiseksi arvoksi. Jos pino tyhjenee kesken toimenpiteen, todetaan että laskutoimituksen muoto ei ole validi, ja
* algoritmin suoritus keskeytetään.
*/
int calculatorAlgo(char**, int, double*);

/*
* Funktio: isPlus
* Parametrit: char-tyyppinen merkki
* Palautusarvo: 1, jos merkki on '+', muuten 0
* Kuvaus:
* Funktio tarkastaa onko annettu merkki plus-operaatio.
*/
int isPlus(char);

/*
* Funktio: isMinus
* Parametrit: char-tyyppinen merkki
* Palautusarvo: 1, jos merkki on '-', muuten 0
* Kuvaus:
* Funktio tarkastaa onko annettu merkki minus-operaatio.
*/
int isMinus(char);

/*
* Funktio: isMultiplying
* Parametrit: char-tyyppinen merkki
* Palautusarvo: 1, jos merkki on '*', muuten 0
* Kuvaus:
* Funktio tarkastaa onko annettu merkki kertoma-operaatio.
*/
int isMultiplying(char);

/*
* Funktio: isDivision
* Parametrit: char-tyyppinen merkki
* Palautusarvo: 1, jos merkki on '/', muuten 0
* Kuvaus:
* Funktio tarkastaa onko annettu merkki jakamis-operaatio.
*/
int isDivision(char);

/*
* Funktio: isWhiteSpace
* Parametrit: char-tyyppinen merkki
* Palautusarvo: 1, jos merkki on ' ', '/n', '/0' tai '/t' muuten 0
* Kuvaus:
* Funktio tarkastaa onko annettu merkki whitespacea.
*/
int isWhiteSpace(char);

/*
* Funktio: isLiteral
* Parametrit: char-tyyppinen merkki
* Palautusarvo: 1, jos merkki on numeroliteraali, muuten 0
* Kuvaus:
* Funktio tarkastaa onko annettu merkki tulkittava numeroksi.
*/
int isLiteral(char);

