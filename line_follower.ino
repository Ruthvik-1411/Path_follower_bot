int motor1a=8;                                //declaring the motor pins
int motor1b=9;
int motor2a=10;
int motor2b=11;

int val1=0;                                  //declaring ir sensor pins and the values obtained
int val2=0;
const int ir1=A0;
const int ir2=A1;

void setup() {
  // put your setup code here, to run once:
pinMode(ir1,INPUT);                        //defining the mode of sensor pins and motor pins
pinMode(ir2,INPUT);
pinMode(motor1a,OUTPUT);
pinMode(motor1b,OUTPUT);
pinMode(motor2a,OUTPUT);
pinMode(motor2b,OUTPUT);
Serial.begin(9600);
delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
val1=analogRead(ir1);                         //read the sensor values left,right respectively, digitalread can also be used here, we get 1,0 then
val2=analogRead(ir2);
//Serial.println(val1);     //to be used while calibrating
//Serial.println(val2);
if(val1>500 && val2>500){                   //if there is nothing(black tape) in the way the go forward
  forward();
  //Serial.println("F");
}
else if(val1>500 && val2<500){              //if the bot crosses the line and left sensor encounters something(black tape) the turn right 
  turnleft();
  //Serial.println("L");
}
else if(val1<500 && val2>500){             //if the bot crosses the line and right sensor encounter something(black tape) the turn left
  turnright();
  //Serial.println("R");
}
else if(val1<500 && val2<500){            //if both the sensors encounter something then stop there
  rest();
  //Serial.println("S");
}
delay(300);

}
//the configurations of HIGH and LOW changes according to the connections made
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
