//The bot has two ultrasonic sensors mounted on the right side, and has the circular structure to move around on its right side and moves in clockwise direction viewed from above 
//motors
int motor1a=8;                                    //declaring motor and enable pins of left and right motor
int motor1b=9;
int en1=7;
int en2=6;
int motor2a=10;
int motor2b=11;
int minLspeed=150;                               //declaring the minimum and maximum speeds of left and right motors as we want
int minRspeed=150;
int maxLspeed=255;
int maxRspeed=255;
int Lmotorspeed;
int Rmotorspeed;
int motorspeed;

//ultrasonic
int trig1=4;                                      //declaring trigger and echo pins
int echo1=5;
int trig2=2;
int echo2=3;

float d1=0,d2=0;                                 //declaring variables to be used in calculation and decision making
float duration=0;
float mean;

int p=0,i=0,d=0;                                       //declaring variables and constants to be used in P.I.D algorithm part of the code
const float Kp=1,Ki=0,Kd=0;                      //Pid constants, should be obtained by tuning the bot
const int y=2;                                   //the range of error in which the bot should move
const int preset=10;                             //the radius of the circle in which the bot should move
float error,preverror=0;

void dist(void);
void forward(int ,int );
void turnright(void);
void rest(void);

void setup() {
  // put your setup code here, to run once:

  pinMode(trig1,OUTPUT);                        //declaring the mode of HC-SR04 ultrasonic sensor pins
  pinMode(echo1,INPUT);
  pinMode(trig2,OUTPUT);
  pinMode(echo2,INPUT);

  pinMode(motor1a,OUTPUT);                      //declaring the mode of motor and enable pins 
  pinMode(motor1b,OUTPUT);
  pinMode(motor2a,OUTPUT);
  pinMode(motor2b,OUTPUT);
  pinMode(en1,OUTPUT);
  pinMode(en2,OUTPUT);
  digitalWrite(en1,HIGH);                     //Initially make enable as HIGH
  digitalWrite(en2,HIGH);
  Serial.begin(9600);                         //begin serial communication
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  dist();                                     //Calculate the distance from sensors and also get the average of both sensor values in mean
  error=mean-preset;                          //calculate the error by subtracting the value obtained from sensors and the preset value
  if(abs(error)>30){                          //if our bot goes too far from the object then this will help to turn right and come back to its track and with error as 10
    turnright();
    delay(100);
    error=10;
  }
  //PID logic
  if(error<y && error>-y){                  //If the error is within a certain acceptable limit then the make motor speed as zero      
    motorspeed=0;
  }
  if(error>y){                             //If the error is greater than the limit i.e the bot is far from the object, so use the pid logic based on the errors made and move towards until stablize
    p=error;                               //use the proportional, integration(sum), derivation(difference from previous) of the present and previous errors
    i=i+error;
    d=error-preverror;
    preverror=error;
    motorspeed=(int)((Kp*p)+(Ki*i)+(Kd*d));//After getting the values multiply them with thier corresponding constants that gives a certian motor speed
  }
  if(error<-y){                            //If the error is lesser than the limit i.e. the bot is close to the object, so use the pid logic to move away 
    p=error;
    i=i+error;
    d=error-preverror;
    preverror=error;
    motorspeed=(int)((Kp*p)+(Ki*i)+(Kd*d));
  }
  //Serial.println(motorspeed);          //to be used while calibrating 
  Rmotorspeed=minRspeed+motorspeed;   //+10 if need be //Add the motor speed with the minimum speed for the right motor
  Lmotorspeed=minLspeed-motorspeed;         //Subtract the motor speed from the minimum speed for the left motor(This is done to manage the overdamp and underdamped oscillations of the bot)
  if(Lmotorspeed<125){                     //If the Left motor speed is very less(<0 or in my case below 125 my motor stops) then make the Left motor speed as zero or where the motor stops working
    Lmotorspeed=110;
  }
  else if(Lmotorspeed>maxLspeed){         //If the Left motor speed exceeds the maximum speed then its speed must be maximum speed as 256 is the maximum we can allow.
    Lmotorspeed=maxLspeed;
  }
  if(Rmotorspeed<125){
    Rmotorspeed=110;
  }
  else if(Rmotorspeed>maxRspeed){
    Rmotorspeed=maxRspeed;
  }
  //Serial.println(Lmotorspeed);       //to be used while calibrating
  //Serial.println(Rmotorspeed);
  //Serial.println("/");
  forward(Lmotorspeed,Rmotorspeed);     //Move forward with these speeds
  delay(2000);
  
}

void dist(){                                 //function to get the distance from left and right sensors

  digitalWrite(trig1,HIGH);                  //make trigger of right sensor high for 10us
  delayMicroseconds(10);
  digitalWrite(trig1,LOW);                  //make it low for right sesnor low for 2us
  delayMicroseconds(2);
  duration=pulseIn(echo1,HIGH);             //get the time from echopin which is high, by using the ultrasonic sensor logic(8 pulses....)
  d1=(duration/20000)*340;                  //to calculate the distance in terms of cm using d=v*t
  
  digitalWrite(trig2,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2,LOW);
  delayMicroseconds(2);
  duration=pulseIn(echo2,HIGH);
  d2=(duration/20000)*340;

  //Serial.println(d1);
  //Serial.println(d2);
  mean=(d1+d2)/2;
  //Serial.println(mean);
  delay(100); 
}
//The configurations of HIGH and LOW might vary depending on motor and pin connections made
void forward(int Lspeed,int Rspeed){
  analogWrite(en1,Lspeed);         //set the motors speed as obtained from the logic and keep moving forward
  analogWrite(en2,Rspeed);
  digitalWrite(motor1a,HIGH);
  digitalWrite(motor1b,LOW);
  digitalWrite(motor2a,HIGH);
  digitalWrite(motor2b,LOW);
}
void backward(){
  digitalWrite(motor1a,LOW);
  digitalWrite(motor1b,HIGH);
  digitalWrite(motor2a,LOW);
  digitalWrite(motor2b,HIGH);
}
void turnright(){
  digitalWrite(motor1a,HIGH);
  digitalWrite(motor1b,LOW);
  digitalWrite(motor2a,LOW);
  digitalWrite(motor2b,LOW);
}
/*void turnleft(){
  digitalWrite(motor1a,LOW);
  digitalWrite(motor1b,LOW);
  digitalWrite(motor2a,HIGH);
  digitalWrite(motor2b,LOW);
}*/
void rest(){
  digitalWrite(motor1a,LOW);
  digitalWrite(motor1b,LOW);
  digitalWrite(motor2a,LOW);
  digitalWrite(motor2b,LOW);
}
