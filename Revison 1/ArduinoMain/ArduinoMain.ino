//ArduinoMain - By: Zack Perry - Fri April 10, 2020

//define motor control pins
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

//define the bounds of the target
static int error = 80;
static int rightBound = 180 - (error/2);
static int leftBound = 180 + (error/2);

int lastVal;

void setup() {
  // put your setup code here, to run once:

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  //setup serial connection to H7
  delay(2000);
  Serial.begin(57600);
  lastVal = 0;
}

void loop() {
  // wait for data on serial
  if(Serial.available()>0){
    int xcor = Serial.parseInt();

    //if the value is not the same as the last value & within bounds of camera FOV
    if(xcor!=lastVal && xcor>5 && xcor<315){   
      if(xcor > leftBound){
        digitalWrite(LED_BUILTIN, HIGH);
        mRight(100);
      }
      else if(xcor < rightBound){
        digitalWrite(LED_BUILTIN, HIGH);
        mLeft(100);
      }
      else{
        digitalWrite(LED_BUILTIN, LOW);
        mStop();
      }

    }
    lastVal = xcor;
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
  digitalWrite(ENA, pwm);  
  digitalWrite(ENB, pwm); 
  digitalWrite(IN1, LOW);      
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, LOW);      
  digitalWrite(IN4, HIGH);  
}
void mStop(){
  digitalWrite(ENA, LOW);  
  digitalWrite(ENB, LOW);
}
