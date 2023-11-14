#include "EEPROMAnything.h"
#include "SerialCommand.h"

#define SerialPort Serial
#define SerialGate Serial1
#define Baudrate 9600

SerialCommand sCmd(SerialPort);
SerialCommand sCmd1(SerialGate);

bool debug;
unsigned long previous;
unsigned long calculationTime;
const int sensor[] = {A5, A4, A3, A2, A1, A0};
int ledPowerOn = 3;
int buttonStartStop = 2;
bool running = LOW;


struct param_t{
  unsigned long cycleTime;
  unsigned int speed;
  float Kp;
  float Ki;
  float Kd;
  int black[6];
  int white[6];
  float position;
} params;


void setup()
{
  SerialPort.begin(Baudrate);
  SerialGate.begin(Baudrate);

  sCmd.addCommand("set", onSet);
  sCmd.addCommand("debug", onDebug);
  sCmd.addCommand("calibrate", onCalibrate);
  sCmd.addCommand("start", onStart);
  sCmd.addCommand("stop", onStop);
  sCmd.setDefaultHandler(onUnknownCommand);

  sCmd1.addCommand("SET", onSet);
  sCmd1.addCommand("DEBUG", onDebug);
  sCmd1.addCommand("CALIBRATE", onCalibrate);
  sCmd1.addCommand("START", onStart);
  sCmd1.addCommand("STOP", onStop);
  sCmd1.setDefaultHandler(onUnknownCommand);

  EEPROM_readAnything(0, params);

  pinMode(ledPowerOn, OUTPUT);
  pinMode(buttonStartStop, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonStartStop), interrupt, RISING);
  SerialPort.println("ready");
}


void loop()
{
  sCmd.readSerial();
  sCmd1.readSerial(); 
  digitalWrite(ledPowerOn, running);
  
  unsigned long current = micros();
  if (current - previous >= params.cycleTime)
  {
    previous = current;
    long normalised[6];
    
    /* code die cyclisch moet uitgevoerd worden programmeer je hier ... */
    SerialPort.print("normalised values: ");
    for (int i = 0; i < 6; i ++)
    {
      long value = analogRead(sensor[i]);
      normalised[i] = map(value, params.black[i], params.white[i], 0, 1000);
      Serial.print(normalised[i]);
      Serial.print(" ");
    }
    Serial.println(" ");

    int index = 0;
    for (int i = 1; i < 6; i++) if (normalised[i] < normalised[index]) index = i;

    
    if (index == 0) params.position = -30;
    else if (index == 5) params.position = 30;
    else{
    int sZero = normalised[index];
    int sMinusOne = normalised[index-1];
    int sPlusOne = normalised[index+1];

    float b = sPlusOne - sMinusOne;
    b = b / 2;
    float a = sPlusOne - b - sZero;

    params.position = -b / (2 * a);  
    params.position += index; 
    params.position -= 2.5;   
    params.position *= 15;  //sensor distance in mm
    }
    /* pid regeling */

    /* aansturen motoren */

    
     EEPROM_writeAnything(0, params);
  }
  unsigned long difference = micros() - current;
  if (difference > calculationTime) calculationTime = difference;
}

void onUnknownCommand(char *command){
  SerialPort.print("unknown command: \"");
  SerialPort.print(command);
  SerialPort.println("\"");
}

void onSet(){  
  char* param = sCmd.next(); //OP PC
  char* value = sCmd.next();
  if (strcmp(param, "cycle") == 0) params.cycleTime = atol(value);
  if (strcmp(param, "speed") == 0) params.speed = atoi(value);
  if (strcmp(param, "kp") == 0) params.Kp = atof(value);
  if (strcmp(param, "ki") == 0) params.Ki = atof(value);
  if (strcmp(param, "kd") == 0) params.Kd = atof(value);

  char* param1 = sCmd1.next(); //DRAADLOOS
  char* value1 = sCmd1.next();
  if (strcmp(param1, "cycle") == 0) params.cycleTime = atol(value1);
  if (strcmp(param1, "speed") == 0) params.speed = atoi(value1);
  if (strcmp(param1, "kp") == 0) params.Kp = atof(value1);
  if (strcmp(param1, "ki") == 0) params.Ki = atof(value1);
  if (strcmp(param1, "kd") == 0) params.Kd = atof(value1);

  EEPROM_writeAnything(0, params);
}

void onDebug(){
  SerialGate.print("cycle time: ");
  SerialGate.println(params.cycleTime);

  SerialGate.print("calculation time: ");
  SerialGate.println(calculationTime);

  SerialGate.print("speed: ");
  SerialGate.println(params.speed);

  SerialGate.print("calibration white: ");
  for (int i = 0; i < 6; i++){  
    SerialGate.print(params.white[i]);
    SerialGate.print(" ");
  } SerialGate.println(" ");

  SerialGate.print("calibration black: ");
  for (int i = 0; i < 6; i++){  
    SerialGate.print(params.black[i]);
    SerialGate.print(" ");
  } SerialGate.println(" ");

  SerialGate.print("Position: ");
  SerialGate.println(params.position);

  SerialGate.print("Kp: ");
  SerialGate.println(params.Kp);

  SerialGate.print("Ki: ");
  SerialGate.println(params.Ki);

  SerialGate.print("Kd: ");
  SerialGate.println(params.Kd);
  
  calculationTime = 0;
}

void onCalibrate(){
  char* param = sCmd.next(); //OP PC

  if (strcmp(param, "black") == 0)
  {
    SerialPort.print("start calibrating black... ");
    for (int i = 0; i < 6; i++) params.black[i]=analogRead(sensor[i]);
    SerialPort.println("done");
  }
  else if (strcmp(param, "white") == 0)
  {
    SerialPort.print("start calibrating white... ");    
    for (int i = 0; i < 6; i++) params.white[i]=analogRead(sensor[i]);  
    SerialPort.println("done");      
  }

 
  char* param1 = sCmd1.next();  //DRAADLOOS

  if (strcmp(param1, "black") == 0)
  {
    SerialGate.print("start calibrating black... ");
    for (int i = 0; i < 6; i++) params.black[i]=analogRead(sensor[i]);
    SerialGate.println("done");
  }
  else if (strcmp(param1, "white") == 0)
  {
    SerialGate.print("start calibrating white... ");    
    for (int i = 0; i < 6; i++) params.white[i]=analogRead(sensor[i]);  
    SerialGate.println("done");      
  }
  
  EEPROM_writeAnything(0, params);
}

void interrupt(){
  static unsigned long vorigeInterrupt = 0;
  unsigned long interruptTijd = millis();
  if (interruptTijd - vorigeInterrupt > 100){
    running =! running;
  }
  vorigeInterrupt = interruptTijd;
}

void onStart(){
  running = true;
}

void onStop(){
  running = false;
}
