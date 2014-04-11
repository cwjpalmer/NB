
bool alarmNow = 		true;
int switchPin = 		22;
int switchLEDPin = 		23;

void setup() {
	Serial.begin(9600);
	pinMode(switchPin, INPUT);
	pinMode(switchLEDPin, OUTPUT);s
}

void loop () {
	int switchState = digitalRead(switchPin);
	Serial.print(switchState);
	delay(5);
	if(alarmNow) {
		digitalWrite(switchLEDPin, HIGH);
		if (switchState) {
			alarmNow = false;
		}
	}
	else {
		digitalWrite(switchLEDPin, LOW);
	}
}
