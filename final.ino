#include <IRremote.h>
int button1Pin = 2;                      //The SW1 button is connect to pin 2 of the Arduino.
int button2Pin = 3;                      //The SW2 button is connect to pin 3 of the Arduino.
int password[] = {-1, -1, -1, -1, -1};   //initialize the password with all -1 stored
int input[] = {-1, -1, -1, -1, -1};      //initialize the input with all -1 stored
int passwordLen = 5;                     //initialize the password length as 5
int RECV_PIN = 6;                        //The RECV pin is connected pin 6 of the Arduino.
int redLedPin  = 12 ;                    //The red LED is connected pin 12 of the Arduino.
int blueLedPin = 13 ;                    //The blue LED is connected pin 13 of the Arduino.
int RGBGreenPin = 10;                    //The rgb green LED is connected pin 10 of the Arduino.
int RGBRedPin = 9;                       //The rgb red LED is connected pin 9 of the Arduino.
int RGBBluePin = 11;                     //The rgb blue LED is connected pin 11 of the Arduino.
int buzzerPin  = 5 ;                     //The buzzer is connected pin 5 of the Arduino.
boolean finish = false;                  // set finish as false initial
int count = 0;                           //count for the input position, initialize to 0
int attempt = 0;                         //count for the attempt times, initialize to 0
boolean answer = true;                   //answer initialize to true, for checking password compare with input
IRrecv irrecv(RECV_PIN);                 //initialize irremote
decode_results results;

void setup() {
  pinMode(button1Pin, INPUT);            //Setup button PinS
  pinMode(button2Pin, INPUT);
  Serial.begin(9600);                    //Setup serial monitor
  Serial.println("Enabling IRin");       //Setup Irremote
  irrecv.enableIRIn();
  Serial.println("Enabled IRin");
  pinMode(buzzerPin, OUTPUT);            //Setup buzzer pin as an output pin.
  pinMode(redLedPin, OUTPUT);            //Set all light pin as an output pin.
  pinMode(blueLedPin, OUTPUT);
  pinMode(RGBGreenPin, OUTPUT);
  pinMode(RGBBluePin, OUTPUT);
  pinMode(RGBRedPin, OUTPUT);
}

void loop() {
  boolean answer = true;                  //initialize all the value except attempts times to make the function run successful
  boolean finish = false;
  int input[] = {-1, -1, -1, -1, -1};
  int password[] = {-1, -1, -1, -1, -1};
  int count = 0;
  boolean done = false;
  analogWrite(RGBGreenPin, LOW);
  digitalWrite(redLedPin, LOW);
  analogWrite(RGBBluePin, LOW);
  analogWrite(RGBRedPin, LOW);
  if (attempt >= 3) {                     //check whether there is already 3 bad attempts. If so, buzz forever.
    while (true) {
      tone(buzzerPin, 400, 408);
      delay(600);
    }
  }
  while (digitalRead(button1Pin) == HIGH) { //nothing happens until SW1 buttons pressed.
  }
  for (int i = 0; i < passwordLen; i++) { //generate password randomly after SW1 pressed
    password[i] = random(0, 6);       //random number from 0 to 5
  }
  //checking only
  Serial.println("Show the password"); //show the active password values
  for ( int i : password) {
    Serial.print(i);
  }
  Serial.println(".");                //end the line

  
  while (!finish) {                  //if SW2 button is not pressed or number of input is less than password length, keep get into the loop
    if (irrecv.decode(&results)) {
      Serial.println(results.value, DEC);
      irrecv.resume();
    }
    delay(100);
    if (results.value == 16734375 && done == true) { //if button pressed in the ready condition(represent as done == true) delete the last input.
      //tone(buzzerPin, 400,408);
      input[count - 1] = -1;
      if (count >= 1) {                           // position go back 1 place unless position is 0
        count -= 1;
      }
      done = false;//set done back to false to make sure even result.value satisfy the condition, it wont enter the loop a second time until reset done to true
      digitalWrite(blueLedPin, HIGH);//all the light turn on to show we delete a number in the input
      analogWrite(RGBBluePin, HIGH);
      analogWrite(RGBRedPin, HIGH);
      analogWrite(RGBGreenPin, HIGH);
    }
    if (results.value == 16718055) { //set the condition back to ready(done = true), turn off all the light in this condition.
      done = true;
      digitalWrite(blueLedPin, LOW);
      analogWrite(RGBBluePin, LOW);
      analogWrite(RGBRedPin, LOW);
      analogWrite(RGBGreenPin, LOW);
    }
    if (results.value == 16724175 && count < 5 && done == true) { //set input values with different pin, only run into the condition when the product is ready(done == true).
      input[count] = 0;                                        //number on the button is 0
      count += 1;                                              //position + 1 in the array
      digitalWrite(blueLedPin, HIGH);                         //blue light turn on to represent the number is entered
      done = false;                                           //set done back to false to make sure program will not enter a second time untill ready button pressed
    }
    if (results.value == 16756815 && count < 5 && done == true) {
      input[count] = 1;                                       //number on the button is 1
      digitalWrite(blueLedPin, HIGH);
      count += 1;
      done = false;
    }
    if (results.value == 16740495 && count < 5 && done == true) {
      input[count] = 2;                                       //number on the button is 2
      digitalWrite(blueLedPin, HIGH);
      count += 1;
      done = false;
    }
    if (results.value == 16713975 && count < 5 && done == true) {
      input[count] = 3;                                       //number on the button is 3
      digitalWrite(blueLedPin, HIGH);
      count += 1;
      done = false;
    }
    if (results.value == 16746615 && count < 5 && done == true) {
      input[count] = 4;                                       //gitalWrite(blueLedPin, HIGH);     //label for now user can enter password.
number on the button is 4
      digitalWrite(blueLedPin, HIGH);
      count += 1;
      done = false;
    }
    if (results.value == 16730295 && count < 5 && done == true) {
      input[count] = 5;                                       //number on the button is 5
      digitalWrite(blueLedPin, HIGH);
      count += 1;
      done = false;
    }
    //number end here
    if (input[4] >= 0) {                                     //check if last position has value, then rgb blue turn on to remind user
      analogWrite(RGBBluePin, HIGH);
    }
    else {                                                   //cause sometime all input is decleared, but user delete the information, program should check whether its full each time
      analogWrite(RGBBluePin, LOW);
    }
    if (digitalRead(button2Pin) == LOW && input[4] != -1) {                    //press SW2 to comfirm the input
      //checking only
      for ( int i : input) {                                   //show the value of input on the serial board
        Serial.println(i);
      }
      finish = true;                                         //satisfy: 1.input length correct. 2.SW2 button press.  Then run out of the whole while loop
      digitalWrite(blueLedPin, LOW);                         //led blue turn off to show program get into the comfirm stage
      for (int i = 0; i < passwordLen; i++) {                //check two array whether all information can be matched
        if (input[i] != password[i]) {                       //check if one of the value is wrong
          digitalWrite(redLedPin, HIGH);                   //red light turns on
          answer = false;                                  //answer get into false condition
          attempt += 1;
          break;
        }
      }
    }
  }
  if (answer) {                                               //condition when all password matches, answer is true
    analogWrite(RGBBluePin, LOW);
    analogWrite(RGBGreenPin, HIGH);                         //green light turns on to show answer is correct
    attempt = 0;
  }
  delay(5000);                                                //restart the program after 5 seconds
}
