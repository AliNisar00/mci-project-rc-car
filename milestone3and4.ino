#include <Servo.h> 

// Motor A,B, Arduino and L298N connections
const int enA = 3;   //ENABLE pin for Motor A to provide PWM 
const int enB = 5;     //ENABLE pin for Motor B to provide PWM 
const int in1 = 4;   //IN1 pin for Motor A for direction
const int in2 = 2;   //IN2 pin for Motor A for direction
const int in3 = 8;     //IN3 pin for Motor B for direction
const int in4 = 7;     //IN4 pin for Motor B for direction
const int trigPin = 13; // Trigger pin for the ultrasonic sensor
const int echoPin = 6;    // Echo pin for the ultrasonic sensor
const int servoPin = 10;
bool control_flag = false; // This is to check 
#define R_S A5
#define L_S A0
long duration;
float distance;
Servo Sirwo; 
void setup() {
  Serial.begin(9600); //Serial initializing for Debugging
  pinMode(R_S, INPUT); // declare if sensor as input  
  pinMode(L_S, INPUT); // declare ir sensor as input
  
  //pinModes for enA, in1 and in2 below
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  //pinModes for enB, in1 and in2 below
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  // For Ultra Sonic Sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Sirwo.attach(servoPin);
  Sirwo.write(0); 
}

void loop() {
  //Both motors go forward
     if(Serial.available()>0)
   {     
      char data= Serial.read(); // reading the data received from the bluetooth module
      switch(data)
      {
        case 'F': // when up arrow is pressed on the app
            Serial.print("FORWARD");
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            digitalWrite(in3, LOW);
            digitalWrite(in4, HIGH);
            analogWrite(enA, 110); //PWM value for enA
            analogWrite(enB, 160 ); //PWM value for enB
            break;
        case 'B': // when down is pressed in the app
            Serial.print("BACK");
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            digitalWrite(in3, HIGH);
            digitalWrite(in4, LOW);
            analogWrite(enA, 110); //PWM value for enA
            analogWrite(enB, 160 ); //PWM value for enB
            break;
        case 'R': // when right is pressed in the app
            Serial.print("RIGHT");
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            digitalWrite(in3, LOW);
            digitalWrite(in4, LOW);
            analogWrite(enA, 110); //PWM value for enA
            analogWrite(enB, 160 ); //PWM value for enB
            break;
        case 'L': // when left is pressed in the app
            Serial.print("LEFT");
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
            digitalWrite(in3, LOW);
            digitalWrite(in4, HIGH);
            analogWrite(enA, 110); //PWM value for enA
            analogWrite(enB, 160 ); //PWM value for enB
            break;
            
        case 'I': // when forward-right is pressed in the app
            Serial.print("FORWARD-RIGHT");
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            digitalWrite(in3, LOW);
            digitalWrite(in4, HIGH);
            analogWrite(enA, 110); //PWM value for enA
            analogWrite(enB, 80); //PWM value for enB
            break;
        case 'G': // when forward-left is pressed in the app
            Serial.print("FORWARD-LEFT");
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            digitalWrite(in3, LOW);
            digitalWrite(in4, HIGH);
            analogWrite(enA, 55); //PWM value for enA
            analogWrite(enB, 160); //PWM value for enB
            break;
        case 'H': // when backward-left is pressed in the app
            Serial.print("BACKWARD-LEFT");
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            digitalWrite(in3, HIGH);
            digitalWrite(in4, LOW);
            analogWrite(enA, 55); //PWM value for enA
            analogWrite(enB, 160 ); //PWM value for enB
            break;
        case 'J': // when backward-right is pressed in the app
            Serial.print("BACKWARD-RIGHT");
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            digitalWrite(in3, HIGH);
            digitalWrite(in4, LOW);
            analogWrite(enA, 110); //PWM value for enA
            analogWrite(enB, 80 ); //PWM value for enB
            break;
        case 'X':
              while(1)
              {  
              if (check_d()>=7)
              {
              if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0))
              {forword();}   //if Right Sensor and Left Sensor are at White color then it will call forword function
              
              if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0))
              {turnLeft();} //if Right Sensor is Black and Left Sensor is White then it will call turn Right function  
              
              if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1))
              {turnRight();}  //if Right Sensor is White and Left Sensor is Black then it will call turn Left function
              
              if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 1))
              {Stop();
//              flap();
                 Sirwo.write(120); 
                 delay(3000); 
                Sirwo.write(0);
                 delay(1000);
              break;} //if Right Sensor and Left Sensor are at Black color then it will call Stop function
              }
              else
              {
                Stop();
              }
              }
        case 'x':
              break;
           
            
            
        default: // when no button is pressed in the app
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
            digitalWrite(in3, LOW);
            digitalWrite(in4, LOW);
            break;
      }
      Serial.println(data);
     
   }

//    delay(3000);

}

void forword(){  //forword
analogWrite(enA, 85); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
analogWrite(enB, 140); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 
digitalWrite(in1, LOW); //Right Motor forword Pin 
digitalWrite(in2, HIGH);  //Right Motor backword Pin 
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, HIGH); //Left Motor forword Pin 
}

void turnRight(){ //turnRight
 analogWrite(enA, 85); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
analogWrite(enB, 140); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 
digitalWrite(in1, LOW);  //Right Motor forword Pin 
digitalWrite(in2, HIGH); //Right Motor backword Pin  
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, LOW); //Left Motor forword Pin 
}

void turnLeft(){ //turnLeft
analogWrite(enA, 85); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
analogWrite(enB, 140); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 
digitalWrite(in1, LOW); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, LOW); //Left Motor backword Pin 
digitalWrite(in4, HIGH);  //Left Motor forword Pin 
}

void Stop(){ //stop
analogWrite(enA, 85); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
analogWrite(enB, 140); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 
digitalWrite(in1, LOW); //Right Motor forword Pin 
digitalWrite(in2, LOW); //Right Motor backword Pin 
digitalWrite(in3, LOW); //Left Motor backword Pin 
digitalWrite(in4, LOW); //Left Motor forword Pin 
}

long check_d() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  return(distance);
}


//void flap()
//{ 
//   // Make servo go to 180 degrees 
////   Sirwo.write(180); 
////   delay(1000); 
////   Sirwo.write(0);
////   delay(1000);
//}
