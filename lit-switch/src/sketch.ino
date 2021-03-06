int switchPin = 		22;
int switchLEDPin = 		23;
int LEDPin = 			13;
int poweredPin = 		28;


void setup() {
	Serial.begin(9600);
	pinMode(switchPin, INPUT);
	pinMode(switchLEDPin, OUTPUT);
	pinMode(poweredPin, OUTPUT);
	digitalWrite(poweredPin, HIGH);

}

void loop () {
	int switchState = digitalRead(switchPin);
	Serial.print(switchState);
	delay(5);
	if(switchState) {
		digitalWrite(switchLEDPin, HIGH);
		digitalWrite(LEDPin, HIGH);
	}
	else {
		digitalWrite(switchLEDPin, LOW);
		digitalWrite(LEDPin, LOW);
	}
}
