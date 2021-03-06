String commandIn;

char command[20];
char* c1;
char* c2;
char* c3;

float temp; // THIS IS IN THE MAIN SKETCH !!! chance temp throughout to match name of temp set point in main sketch

void setup() {
	Serial.begin(9600);
	temp = 25.0;
}

void loop () {
	Serial.print("temp set at: ");
	Serial.println(temp);

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
		Serial.print("c1 is: ");
		Serial.println(c1);
		Serial.print("c2 is: ");
		Serial.println(c2);
		Serial.print("c3 is: ");
		Serial.println(c3);

		// make the character array lowercase
		String c1string = String(c1); 					// make a String from the character array c1
		c1string.toLowerCase();							// make the String lower case
		c1string.toCharArray(c1,c1string.length()+1);	// send the lower case String characters back to the character array c1
	
		String c2string = String(c2); 					// make a String from the character array c1
		c2string.toLowerCase();							// make the String lower case
		c2string.toCharArray(c2,c2string.length()+1);	// send the lower case String characters back to the character array c1


		if (strcmp(c1,"temp") == 0) {
			// Serial.println("command temp recognized");
			
			if (strcmp(c2,"set") == 0) {
				// Serial.println("command temp set recognized");
				temp = atof(c3);
			}
			else if (strcmp(c2,"increase") == 0 || strcmp(c2,"inc") == 0) {
				// Serial.println("command temp increase recognized");
				if (c3) {
					// Serial.println("c3 is present");
					temp = temp + atof(c3);
				}
				// else {
				// 	Serial.println("Amount to increace temperature setpoint not specified.");
				// 	Serial.println("Try again using format 'temp inc #' where '#' is the amount that the temperature should increase by.");
				// }
			}
			else if (strcmp(c2,"decrease") == 0 || strcmp(c2,"dec") == 0) { 
				// Serial.println("command temp decrease recognized");
				if (c3) {
					// Serial.println("c3 is present");
					temp = temp - atof(c3);
				}
				// else {
				// 	temp = temp - 0.1;
				// }
			}
			else {
				Serial.println("temp comand not recognized. try again.");
			}
		}
		// elseif() {

		// }
		else {
			Serial.println("comand received, but not recognized. check formatting and try again.");
		}
	
	}
	else {
		Serial.println("No command registered");
	}
Serial.println();
Serial.println();
}
