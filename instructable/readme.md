### Instructable

### stap 1

Bestel alle benodigde componenten uit de materiaallijst. Ik heb er al voor gezorgd dat deze allemaal compatibel zijn met elkaar.

### stap 2

Voer afzonderlijke tests uit voor elk component met behulp van verschillende Proof of Concepts. Hierdoor kun je verifiëren of de componenten naar behoren functioneren en krijg je inzicht in de werking van elk onderdeel.

### stap 3a

Bouw de auto op, beginnend met het creëren van de basis. Houd rekening met de voertuigeisen en focus voorlopig op het puur mechanische aspect. Test regelmatig of elk component goed op de auto past, maar bevestig of sluit nog niets aan. Controleer ook of het geheel goed past, om later verrassingen te voorkomen, zoals een batterijhouder die niet meer onder de auto past of een sensor die te laag hangt.
 
### stap 3b

Nu je de basis van je auto hebt en elk component een plaats heeft, kan je doorgaan met het monteren en aansluiten van de verschillende onderdelen op de auto. Denk aan de H-brug, de HC-05 module, de sensor en je microcontroller. Test ook hier elk component opnieuw na bevestiging met behulp van de Proof of Concepts om te verifiëren of alles correct werkt. Ga pas naar stap 4 als alles gemonteerd is. Probeer meerdere PoC te combineren om zo je programma telkens meer en meer uit te breiden.

### stap 4a

Het uploaden van de volledige code.

#a. Verbind je Arduino met je pc via een kabel.

#b. Compileer de code en controleer op sintaxfouten.

#c. Upload je code via het Arduino IDE-programma.

#d. Koppel de kabel los.

#e. Test de auto via de bluetooth-communicatie.

### stap 4b

Download de mobiele app "Serial Bluetooth Terminal" uit de Google Play Store. Maak een bluetooth verbinden met de HC-05 module. Configureer de beschikbare knoppen om snel commando's door te sturen naar je wagentje. Handig zijn de commando's: "SET", "DEBUG" en "CALIBRATE". Hiermee kan je de auto draadloos instellen en waarden uitlezen.

### stap 5 

Pas eventuele parameters aan om de auto sneller te laten rijden en met minder oscillaties. Dit kan via de bluetooth-communicatie. Test deze aanpassingen grondig en neem de tijd om ervoor te zorgen dat je auto soepel en correct functioneert. De parameters die je kan aanpassen zijn Kp, Kd, Ki, Diff, Power en Cycle.

