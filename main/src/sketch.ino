#include <OneWire.h>

int DS18S20_Pin = 28; //DS18S20 Signal pin on digital 2
int ledPin = 46; // pin for LED indicating heat is turned on

//Temperature chip i/o
OneWire ds(DS18S20_Pin);  // on digital pin 2

String commandIn;

char command[20];
char* c1;
char* c2;
char* c3;

float temperature;
float tempSet = 25;
float difference; // determine difference between actual T and set point

void setup(void) {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop(void) {
  Serial.println();
  Serial.println();
  temperature = getTemp();
  //Serial.println(temperature);

  difference = temperature - tempSet;

  printTempInfo();

  serialCommandAccept();

  delay(1750); //just here to slow down the output so it is easier to read
  
}


void printTempInfo() {
  Serial.print("Set point is ");
  Serial.print(tempSet);
  Serial.println(" C");

  if (temperature < tempSet) {
    digitalWrite(ledPin, HIGH);
    Serial.print("Temperature is ");
    Serial.print(temperature);
    Serial.println(" C");
    Serial.print("Temperature is ");
    Serial.print(-difference);
    Serial.println(" C below the set point.");
    Serial.println();
  }
  else if (temperature == tempSet) {
    digitalWrite(ledPin, LOW);
    Serial.print("Temperature is ");
    Serial.print(temperature);
    Serial.println(" C");
    Serial.println("Temperature is at the set point.");
    Serial.println();
  }
  else if (temperature > tempSet) {
    digitalWrite(ledPin, LOW);
    Serial.print("Temperature is ");
    Serial.print(temperature);
    Serial.println(" C");
    Serial.print("Temperature is ");
    Serial.print(difference);
    Serial.println(" C above the set point.");
    Serial.println();
  }
}

float getTemp(){
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }
  
  ds.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum;
  
}

void serialCommandAccept () {
  // Serial.print("temperature set at: ");
  // Serial.println(temperature);

  Serial.print("Awaiting command...");
  delay(1000);

  // if serial comms are receiving
  if (Serial.available() > 0) {
    delay(1000);
    // read string
    commandIn = Serial.readString();
    commandIn.toCharArray(command, 20);
    // print string 
    // Serial.print("Your command was: ");
    // Serial.println(command);

    c1 = strtok(command," ");
    c2 = strtok(NULL," ");
    c3 = strtok(NULL," ");
    // Serial.print("c1 is: ");
    // Serial.println(c1);
    // Serial.print("c2 is: ");
    // Serial.println(c2);
    // Serial.print("c3 is: ");
    // Serial.println(c3);

    // make the character array lowercase
    String c1string = String(c1);           // make a String from the character array c1
    c1string.toLowerCase();             // make the String lower case
    c1string.toCharArray(c1,c1string.length()+1); // send the lower case String characters back to the character array c1
  
    String c2string = String(c2);           // make a String from the character array c1
    c2string.toLowerCase();             // make the String lower case
    c2string.toCharArray(c2,c2string.length()+1); // send the lower case String characters back to the character array c1


    if (strcmp(c1,"temperature") == 0 || strcmp(c1,"temp") == 0 ) {
      // Serial.println("command temperature recognized");
      
      if (strcmp(c2,"set") == 0) {
        // Serial.println("command temperature set recognized");
        tempSet = atof(c3);
        Serial.print("  ... command received.");
      }
      else if (strcmp(c2,"increase") == 0 || strcmp(c2,"inc") == 0) {
        // Serial.println("command temperature increase recognized");
        if (c3) {
          // Serial.println("c3 is present");
          tempSet = tempSet + atof(c3);
          Serial.print("  ... command received.");
        }
        // else {
        //  Serial.println("Amount to increace temperatureerature setpoint not specified.");
        //  Serial.println("Try again using format 'temperature inc #' where '#' is the amount that the temperatureerature should increase by.");
        // }
      }
      else if (strcmp(c2,"decrease") == 0 || strcmp(c2,"dec") == 0) { 
        // Serial.println("command temperature decrease recognized");
        if (c3) {
          // Serial.println("c3 is present");
          tempSet = tempSet - atof(c3);
          Serial.print("  ... command received.");
        }
        // else {
        //  temperature = temperature - 0.1;
        // }
      }
      else {
        Serial.println("  ... temperature comand not recognized. try again.");
      }
    }
    // elseif() {

    // }
    else {
      Serial.println("  .... comand received, but not recognized. check formatting and try again.");
    }
  
  }
  else {
    Serial.println("  ... no command registered.");
  }
}