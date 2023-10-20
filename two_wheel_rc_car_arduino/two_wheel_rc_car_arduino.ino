// Motor A,B, Arduino and L298N connections
const int enA = 26;   //ENABLE pin for Motor A to provide PWM 
const int enB = ;     //ENABLE pin for Motor B to provide PWM 
const int in1 = 11;   //IN1 pin for Motor A for direction
const int in2 = 12;   //IN2 pin for Motor A for direction
const int in3 = ;     //IN3 pin for Motor B for direction
const int in4 = ;     //IN4 pin for Motor B for direction

void setup() {
  Serial.begin(115200); //Serial initializing for Debugging
  
  //pinModes for enA, in1 and in2 below
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  //pinModes for enA, in1 and in2 below
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  /*
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
``*/
}

void loop() {

    //Both motors go forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    
    analogWrite(enA, 200); //PWM value for enA
    analogWrite(enB, 200); //PWM value for enB
}
