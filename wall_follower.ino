//motors
int motor1a=8;                                //declaring motor pins
int motor1b=9;
int motor2a=10;
int motor2b=11;

//ir
int val1=0;                                  //declaring ir sensor pins and its values
int val2=0;
const int ir1=A0;
const int ir2=A1;

//ultrasonic
int trig1 = 4;       //left                              //declaring trigger and echo pins
int echo1=5;
int trig2 = 6;      //right
int echo2=7;

float d1=0,d2=0;                                          //declaring variables to be used in calculation and decision making
float duration=0;

void readir(void);                                      //declaring functions to read the ir sensor and ultrasonic sensor values
void dist(void);
void forward(void);                                     //declarinf functions to movement of the bot
void backward(void);
void turnleft(void);
void turnright(void);
void rest(void);

void setup() {
  // put your setup code here, to run once:
  pinMode(ir1,INPUT);                                  //defining the mode of ir sensor pins
  pinMode(ir2,INPUT);

  pinMode(trig1,OUTPUT);                               //defining the mode of ultrasonic sesnor pins
  pinMode(echo1,INPUT);
  pinMode(trig2,OUTPUT);
  pinMode(echo2,INPUT);

  pinMode(motor1a,OUTPUT);                           //defining the mode of motor pins
  pinMode(motor1b,OUTPUT);
  pinMode(motor2a,OUTPUT);
  pinMode(motor2b,OUTPUT);
  Serial.begin(9600);                                //begin serial communication at 9600 baud
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  dist();                                           //calculate the distance from both ultrasonic sensors on left and right
  readir();                                         //get the status of objects in front of the bot
  while(d2>40 && d1<30){                            //as long as there is some obstacle to the left of the bot and right is free, keep doing the following
    while(d1>20&&d1<25){                           //as long as the bot is 20-25cm away the left wall do this
      if(val1>500 && val2>500){                    //if there is no obstacle infront of the bot keep moving forward
        forward();
      }
      else if(val1<500 && val2>500){              //if there is an obstacle on the left corner then turn right
        turnright();
      }
      else if(val1>500 && val2<500){              //if there is an obstacle on the right corner the turn left
        turnleft();
      }
      else if(val1<500 && val2<500){            //if there is an obstacle in front of the bot then stop and calculate the distance on right and if there is no obstacle then turn right
        rest();
        dist();
        if(d2>30){
          turnright();
        }
      }
      dist();                                  //calculate the distance again to see if we are still in the range of 20-25cm from the left wall
    }
    if(d1<20){                               //if the distance from wall on left is less than 20cm i.e. we are close, so turn right
      turnright();
    }
    else if(d1>25){                         //if the distance from wall on left is gretaer than 25cm i.e. we are away, so turn left
      turnleft();
    }
    dist();                                 //calculate the distance again to see if the obstacle(wall) on left is still there and on right there is nothing, if its true then loop continues 
  }
  while(d1>40 && d2<30){                    //as long as there is something the right of the bot and the left is empty, do this
    while((d2>20&&d2<25)){                  //as long as the bot is within 20-25cm from the wall to the, right do this
      if(val1>500 && val2>500){             //if there is no obstacle n front of the bot then keep moving forward
        forward();
      }
      else if(val1<500 && val2>500){        //if there is an obstacle in the left corner of the bot then turn right
        turnright();
      }
      else if(val1>500 && val2<500){       //if there is an obstacle in the right corner of the bot then turn left
        turnleft();
      }
      else if(val1<500 && val2<500){     //if there is an obstacle in front of the bot the stop and get the distance on left, if no obstacle then turn left
        rest();
        dist();
        if(d1>30){
          turnleft();
        }
      }
      dist();                           //get the distance to see if we are still 20-25cm from the wall on the right
    }
    if(d2<20){                        //if the distance from the wall on right  is less than 20cm i.e. we are close to the wall, then turn left
      turnleft();
    }
    else if(d2>25){                  //if the distance from the wall on right is greater than 25cm i.e. we are away from the wall, then turn right
      turnright();
    }
    dist();                          //calculate the distance againg to see if the obstacle(wall) on the right is still there and on left there is nothing, if its true then the loop continues
  }
  delay(100);                        //wait for 100milli seconds and stop and continue again, added for better results
  rest();
}
void readir(){
  val1=analogRead(ir1);
  val2=analogRead(ir2);
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
  delay(100); 
}

void backward(){
  digitalWrite(motor1a,HIGH);
  digitalWrite(motor1b,LOW);
  digitalWrite(motor2a,HIGH);
  digitalWrite(motor2b,LOW);
}
void forward(){
  digitalWrite(motor1a,LOW);
  digitalWrite(motor1b,HIGH);
  digitalWrite(motor2a,LOW);
  digitalWrite(motor2b,HIGH);
}
void turnright(){
  digitalWrite(motor1a,LOW);
  digitalWrite(motor1b,HIGH);
  digitalWrite(motor2a,LOW);
  digitalWrite(motor2b,LOW);
}
void turnleft(){
  digitalWrite(motor1a,LOW);
  digitalWrite(motor1b,LOW);
  digitalWrite(motor2a,LOW);
  digitalWrite(motor2b,HIGH);
}
void rest(){
  digitalWrite(motor1a,LOW);
  digitalWrite(motor1b,LOW);
  digitalWrite(motor2a,LOW);
  digitalWrite(motor2b,LOW);
}
