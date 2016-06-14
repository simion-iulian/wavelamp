/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 
 
Servo servo1;
Servo servo2;// create servo object to control a servo 
Servo servo3;
const int NUM_SERVOS = 3;// twelve servo objects can be created on most boards
Servo servos[NUM_SERVOS];
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  delay(3000);
  servo1.attach(3);  // attaches the servo on pin 9 to the servo object 
  servo2.attach(5);
  servo3.attach(6);
  servos[0] = servo1;
  servos[1] = servo2;
  servos[2] = servo3;
} 
 
void loop() 
{ 
  int p = 75;
  int s = 60;
  int e = 160;
  int increment = 1;
  for(pos = s; pos <= e; pos += increment) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    for(int i = 0; i<NUM_SERVOS;i++){
      servos[i].write(pos);
    }// tell servo to go to position in variable 'pos' 
    
    delay(p);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = e; pos>=s; pos-=increment)     // goes from 180 degrees to 0 degrees 
  {                                
    for(int i = 0; i<NUM_SERVOS;i++){
      servos[i].write(pos);
    } 
    delay(p);                       // waits 15ms for the servo to reach the position 
  } 
} 

