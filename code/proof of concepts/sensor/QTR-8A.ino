// Define pinnummers voor QTR-8A sensor
const int QTR_PIN[] = {1, 2, 3, 4, 5, 6};

void setup() {
  Serial.begin(9600);  // Start de seriële communicatie
}

void loop() {
  // Lees de sensorwaarden
  int sensorWaarden[6];
  for (int i = 0; i < 6; i++) {
    sensorWaarden[i] = analogRead(QTR_PIN[i]);
  }

  // Toon de gelezen waarden op de seriële monitor
  for (int i = 0; i < 6; i++) {
    Serial.print(sensorWaarden[i]);
    Serial.print("\t");
  }
  Serial.println();

  // Voer hier je logica uit op basis van de sensorwaarden
  // Bijvoorbeeld: stuur de robot naar links als de linker sensoren een donkere lijn detecteren, en naar rechts als de rechter sensoren een donkere lijn detecteren.

  delay(100); // Wacht een korte tijd voordat je de sensoren opnieuw uitleest
}
