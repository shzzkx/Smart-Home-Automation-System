#include <string>


//What pin does what
const int yellow = 11;
const int green = 10;
const int blue = 9;
const int buzzer = 2;
const int button = 13;
const int soundDigital = 12;
const int soundAnalog = A5;


//Initialize the keypad
#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;


//Define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
 };


//Connect to the row and column pinouts of the keypad
byte rowPins[ROWS] = {A0, A1, 8, 7};
byte colPins[COLS] = {6, 5, 4, 3};


//Initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS,
COLS);


//Initialize LED numbers
const int first = 4;
const int second = 3;
const int third = 2;


//Initialize servo
#include <Servo.h>
Servo fan;


//Variable for state of fan
bool fanOn = false;


//Variable for state of button
int pressed = 0;


//Variable for state of buzzer
bool buzzerOn = false;


//Variable for state of sound
int soundState = 0;


//Variable for what key the user presses on the keypad
int key = 0;


void setup() {
    //Start serial monitor
    Serial.begin(9600);
 
    //Initialize LEDs
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(blue, OUTPUT);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);


    //Initialize Buzzer
    pinMode(buzzer, OUTPUT);
    digitalWrite(buzzer, LOW);
 
    //Initialize Servo
    fan.attach(A2);


    //Initialize Button Sensor
    pinMode(button, INPUT);
 
    //Initialize Sound Sensor
    pinMode(soundDigital, INPUT);
}


void loop() {
  //Button Sensor + Buzzer
    pressed = digitalRead(button);
    //If button pressed, change state of buzzer
    if (pressed == true) {
      if (buzzerOn == false) {
        //Turn on buzzer
        digitalWrite(buzzer, HIGH);
        buzzerOn = true;
        Serial.println("BUZZER ON");
      }
      else {
        //Turn off buzzer
        digitalWrite(buzzer, LOW);
        buzzerOn = false;
        Serial.println("BUZZER OFF");
      }
    }
 
   
    //User enters key
    char keyChar = customKeypad.getKey();
   
      //Keypad Sensor + LEDs
      if (keyChar) {
        String key = "";
        key += keyChar;
        //Switch case based on what key the user entered
        if (key == "0") {
          digitalWrite(yellow, LOW);
          digitalWrite(green, LOW);
          digitalWrite(blue, LOW);
          Serial.println("OFF");
        }
        else if (key == "1") {
          digitalWrite(yellow, HIGH);
          digitalWrite(green, LOW);
          digitalWrite(blue, LOW);
          Serial.println("YELLOW");
        }
        else if (key == "2") {
          digitalWrite(yellow, LOW);
          digitalWrite(green, HIGH);
          digitalWrite(blue, LOW);
          Serial.println("GREEN");
        }
        else if (key == "3") {
          digitalWrite(yellow, LOW);
          digitalWrite(green, LOW);
          digitalWrite(blue, HIGH);
          Serial.println("BLUE");
        }
        else {
          Serial.println("Invalid key entered.");
        }
      }


    //Servo (fan)
    if (fanOn == true) {
      //fan.write(0);
      digitalWrite(blue, HIGH);
    }
    else {
      //fan.write(90);
      digitalWrite(blue, LOW);
    }


    //Sound Sensor + Servo (fan)
    soundState = digitalRead(soundDigital);
    Serial.print("Digital Sound Val: ");
    Serial.println(soundState);
    int temp = analogRead(soundAnalog);
    Serial.print("Analog Sound Val: ");
    Serial.println(temp);
    if (soundState == HIGH) {
      /*if (fanOn == true) {
        fanOn = false;
      }
      else {
        fanOn = true;
      }*/
      digitalWrite(blue, HIGH);
      Serial.println("HIGH");
    }
    else {
      digitalWrite(blue, LOW);
      Serial.println("LOW");
    }


   
    delay(500);


 }

