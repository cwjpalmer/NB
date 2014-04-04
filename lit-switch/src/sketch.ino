int switchPin = 		22;
int switchLEDPin = 		23;
int LEDPin = 			26;


void setup() {
	Serial.begin(9600);
	pinMode(switchPin, INPUT);
	pinMode(switchLEDPin, OUTPUT);
}

void loop () {
	// int switchState = digitalRead(switchPin);
	// Serial.print(switchState);
	// delay(5);
	digitalWrite(LEDPin, HIGH);
	delay(100);
	digitalWrite(LEDPin, LOW);
	delay(100);
}
