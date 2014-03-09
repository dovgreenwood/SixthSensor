
int trig = 2, echo = 4; //for the HC-SR04
int vMotor = 5; //a PWM pin
int pet = A0; //petentiometer for controlling sensitivity

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(5, OUTPUT);
}

void loop() {
 digitalWrite(trig, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trig, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trig, LOW);
 int duration = pulseIn(echo, HIGH);
 int distance = duration /2 /29.1;
 
 int feedback = distance * (analogRead(pet) / 100 + 1); //scale of 1 - 11
 
 if(feedback > 255) //lowering to a legitimate analog value
   feedback = 255;
 
 analogWrite(vMotor, (255 - feedback) * 0.7); //can only take maximum of 3v
}
