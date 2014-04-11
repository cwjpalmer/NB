
#define LED_1r 	34
#define LED_1g	35
#define LED_1b	36
// #define LED_PIN_2 	30
// #define LED_PIN_2c 	31
// #define LED_PIN_3 	32
// #define LED_PIN_3c	33

void setup()
{
    pinMode(LED_1r, OUTPUT);
    pinMode(LED_1g, OUTPUT);
    pinMode(LED_1b, OUTPUT);
}

void loop()
{
    digitalWrite(LED_1r, HIGH);
    delay(250);
    digitalWrite(LED_1g, HIGH);
    delay(250);
    digitalWrite(LED_1b, HIGH);
    delay(250);
    digitalWrite(LED_1r, LOW);
    delay(250);
    digitalWrite(LED_1g, LOW);
    delay(250);
    digitalWrite(LED_1b, LOW);
    delay(250);
}
