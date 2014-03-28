#include <OneWire.h>

int DS18S20_Pin = 28; //DS18S20 Signal pin on digital 2
int ledPin = 46; // pin for LED indicating heat is turned on

//Temperature chip i/o
OneWire ds(DS18S20_Pin);  // on digital pin 2

float temperature;
float tempSet = 25;
// float difference; // determine difference between actual T and set point

void setup(void) {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop(void) {
  temperature = getTemp();
  Serial.println(temperature);

  if (temperature < tempSet) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Temperature below setpoint");
  }
  else if (temperature == tempSet) {
    digitalWrite(ledPin, LOW);
    Serial.println("Temperature at setpoint");
  }
  else if (temperature > tempSet) {
    digitalWrite(ledPin, LOW);
    Serial.println("Temperature above setpoint");
  }

  delay(1000); //just here to slow down the output so it is easier to read
  
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