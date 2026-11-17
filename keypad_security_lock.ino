
#include <Keypad.h>
#include <Servo.h>

Servo lockServo;

const int buzzer = 11;

const byte rows = 4;
const byte cols = 4;

char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[rows] = {9, 8, 7, 6};
byte colPins[cols] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys),
rowPins, colPins, rows, cols);

String password = "1234";
String inputPassword = "";

void setup() {
  Serial.begin(9600);

  lockServo.attach(10);
  pinMode(buzzer, OUTPUT);

  lockServo.write(0);

  Serial.println("Keypad Security Lock");
  Serial.println("Enter Password:");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {

      if (inputPassword == password) {
        Serial.println("Access Granted");

        lockServo.write(90);
        tone(buzzer, 1000, 200);

        delay(3000);

        lockServo.write(0);
        Serial.println("Door Locked");
      }
      else {
        Serial.println("Wrong Password");

        tone(buzzer, 500, 1000);
      }

      inputPassword = "";
      Serial.println("Enter Password:");
    }

    else if (key == '*') {
      inputPassword = "";
      Serial.println("Password Cleared");
    }

    else if (inputPassword.length() < 4) {
      inputPassword += key;
      Serial.println("Key Pressed");
    }
  }
}
