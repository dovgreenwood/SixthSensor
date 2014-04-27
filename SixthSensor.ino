
/*TO BE USED ON THE ARDUINO MEGA ONLY!*/

void setup() {
	pinMode(22, OUTPUT);
	pinMode(23, INPUT);
	pinMode(2, OUTPUT);

	pinMode(24, OUTPUT);
	pinMode(25, INPUT);
	pinMode(3, OUTPUT);
}

void loop() {
	distanceFeedback(22, 23, 2, A0);
	distanceFeedback(24, 25, 3, -1);
}



/*
trig, echo, vMotor: pins corresponding to the trig, echo, and vibration motor pins
pet: pin corresponding to the petentiometer if the ultrasonic sensor is facing forward.  Otherwise, give it a value of -1.
*/
void distanceFeedback(int trig, int echo, int vMotor, int pet) {
	digitalWrite(trig, LOW); 
	delayMicroseconds(2); 

	digitalWrite(trig, HIGH);
	delayMicroseconds(10); 
 
	digitalWrite(trig, LOW);
	int duration = pulseIn(echo, HIGH);
	int distance = duration / 2 / 29.1;
 
	if(pet != -1) {
		int feedback = distance * (analogRead(pet) / 100 + 1); //scale of 1 - 11
  
		if(feedback > 255) //lowering to a legitimate analog value
			feedback = 255;
  
		analogWrite(vMotor, (255 - feedback) * 0.7); //can only take maximum of 3v
	}
	else {
		downFeedback(vMotor, distance);
	}
}



/*feedback for the down-facing ultrasonic distance sensor.  The reason for the distances 239 and 218 is the following:
The downward facing sensor is meant to be used to warn the user of falls or rises in altitude.  Therefore, the sensor should be able to warn the user a long distance before the fall.

      |\ 
+14in | \
      |  \
      |\  \
      | \  \
      |  \  \
      |   a  b
47in  |    \  \
      |     \  \
      |      \ \
      |       \ \
      |________\\
        72in

- 14in: from 47 to 61 inches is the ideal distance for holding up your hand.
- 72: the ideal distance to be warned of a large drop.
- through pythagorean theorem:
 --> the minimum distance from the ground is 86in -- 218cm (a)
 --> the maximum distance from the ground is 94in -- 239cm (b)
*/
void downFeedback(int vMotor, int distance) {
	if(distance > 239)
		digitalWrite(vMotor, HIGH);
	else if(distance < 218) {
		digitalWrite(vMotor, HIGH);
		delay(1000);
		digitalWrite(vMotor, LOW);
		delay(1000);
	}
	else
		digitalWrite(vMotor, LOW);
}



