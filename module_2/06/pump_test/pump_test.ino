// Pins
int motorPinPlus = 14;
int motorPinMinus = 15;

// Setup
void setup() 
{ 
  pinMode(motorPinPlus, OUTPUT);
  pinMode(motorPinMinus, OUTPUT);
  Serial.begin(115200);

  setMotor(true);
} 
 
// Loop 
void loop() 
{ 
  
} 

// Function to control the motor
void setMotor(boolean forward){
    digitalWrite(motorPinPlus, forward);
    digitalWrite(motorPinMinus, !forward);
}
