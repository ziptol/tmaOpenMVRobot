//ArduinoMain - By: Zack Perry - Fri April 10, 2020

#include <AutoPID.h>

//define motor control pins
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

//create an AutoPID object
double input, setpoint=180, output;
double outputMin=-255, outputMax=255;
double Kp=3, Ki=0.005 , Kd=0; 
AutoPID pid(&input,&setpoint,&output,outputMin,outputMax,Kp,Ki,Kd);

void setup() {
  // set motor control pinmode
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  //establish serial connection to H7
  delay(2000);
  Serial.begin(57600);

  //set AutoPID options
  pid.setTimeStep(1);
  pid.setBangBang(100);
}

void loop() {
  if(Serial.available()>0){
    input = Serial.parseInt();
    pid.run();
    mGen(-output);
    if (pid.atSetPoint(15)){
      mStop();
    }
  }
  else{
    mStop();
  }
}

//move according to mspeed (-255 -> 255)
void mGen(double msp){
  int mspeed = msp;
  
  if(mspeed<0){
    /*if(mspeed>-110){
      mspeed = -110;
    }*/
    mLeft(-1*mspeed);
  } else{
    /*if(mspeed<110){
      mspeed = 110;
    }*/
    mRight(mspeed);
  }
}


//movement commands
void mRight(int pwm){
  analogWrite(ENA, pwm);  
  analogWrite(ENB, pwm); 
  digitalWrite(IN1, HIGH);      
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, HIGH);      
  digitalWrite(IN4, LOW);  
}
void mLeft(int pwm){
  analogWrite(ENA, pwm);  
  analogWrite(ENB, pwm); 
  digitalWrite(IN1, LOW);      
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, LOW);      
  digitalWrite(IN4, HIGH);  
}
void mStop(){
  digitalWrite(ENA, LOW);  
  digitalWrite(ENB, LOW);
}
