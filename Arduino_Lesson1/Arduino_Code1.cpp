int button1 = 9;
int button2 = 10;
int button3 = 11;

int led1 = 2;
int led2 = 3;
int led3 = 4;

void setup() {
    pinMode(button1, INPUT_PULLUP);
    pinMode(button2, INPUT_PULLUP);
    pinMode(button3, INPUT_PULLUP);

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
}

void loop() {


    if (digitalRead(button1) == LOW) {
        digitalWrite(led1, HIGH);
    }
    else {
        digitalWrite(led1, LOW);
    }

    if (digitalRead(button2) == LOW) {
        digitalWrite(led2, HIGH);
    }
    else {
        digitalWrite(led2, LOW);
    }

    if (digitalRead(button3) == LOW) {
        digitalWrite(led3, HIGH);
    }
    else {
        digitalWrite(led3, LOW);
    }
}