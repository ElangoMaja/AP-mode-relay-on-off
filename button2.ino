
const int  buttonPin = 10;    
//const int ledPin = 16;
int buttonPushCounter = 0;   
int buttonState = 0;        
int lastButtonState = 0;    

void setup() {
  pinMode(buttonPin, INPUT);
 // pinMode(ledPin, OUTPUT);
 Serial.begin(9600);
 }

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
     
      buttonPushCounter++;
      }
   }Serial.write("A\n");
  lastButtonState = buttonState;
  if (buttonPushCounter % 2 == 0) {
    //digitalWrite(ledPin, HIGH);
   
  } else {
   // digitalWrite(ledPin, LOW);
 
  }
}



