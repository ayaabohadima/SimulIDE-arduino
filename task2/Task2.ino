unsigned long previousMillisfan=0,previousMillisInter=0,intervalfan=500,previousMillisLed=0,intervalLed=1000,previouseTest=0; // millis() returns an unsigned long.long
int state=11,InrightRight=0,InrightLeft=0,test3=0,stepFan=0;
bool ledState = false,fanWork=false,interptOn=true; // state variable for the LED
void setup() {
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  for(int i=0 ; i<=4;i++)
   pinMode(2,INPUT);
   for(int i=6 ; i<=13;i++)
    pinMode(i,OUTPUT);
attachInterrupt(digitalPinToInterrupt(2), ActivateFan, RISING); //LOW - CHANGE - RISING - FALLING - HIGH for Due, Zero  
}

void loop() {
  
 led();  
 checkCorrect();
 checkFan();
 determineState();
 workrotor();
}
void checkCorrect(){
  if(interptOn){
    unsigned long currentMillis = millis(); // grab current time
  if (digitalRead(1)&&(unsigned long)(currentMillis - previousMillisInter) >= intervalfan) {
    if(digitalRead(2)){
    previousMillisfan=millis();
     fanWork=true;} 
     else
       interptOn=0;
     }
    
}}
void led(){
  
    unsigned long currentMillis = millis(); // grab current time
  if (digitalRead(1)&&(unsigned long)(currentMillis - previousMillisLed) >= intervalLed) {
    ledState = !ledState; // "toggles" the state
    digitalWrite(13, ledState); // sets the LED based on ledState
    // save the "current" time
     previousMillisLed = millis(); 
     }
  }
void ActivateFan() {
    interptOn=true;
    previousMillisInter=millis();
    previousMillisfan= millis();
}
void checkFan(){
    unsigned long currentMillis = millis(); // grab current time
  if (fanWork&&digitalRead(1)&&(unsigned long)(currentMillis - previousMillisfan ) <= intervalfan) 
    workFan();   
     else
     fanWork=false;
     }
void workFan(){
  if(stepFan%100==0){
  moveStepper1(12,11,12,11);
  }
  stepFan++;
  }
void moveStepper(int pn1,int pn2){
  digitalWrite(pn1,1);
  digitalWrite(pn2,1);
  digitalWrite(pn1,0);
  digitalWrite(pn2,0);
  }

void sendTriger(){
 
  digitalWrite( 6, LOW ); 
  delayMicroseconds( 2 );
 
  digitalWrite( 6, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( 6, LOW );
  }

// void sendTriger1(){
// 
//  unsigned long currentTrig=micros();
//if(currentTrig-previouseTest <2){
//  digitalWrite( 6, LOW ); 
//  test1=1;
//  }
// else if(currentTrig-previouseTest <12){
//  digitalWrite( 6, HIGH );
//  }
//  else{
//  digitalWrite( 6, LOW );
//  test1=2;
//  } 
//  }
 void determineState(){
  if(!fanWork&&digitalRead(1)){
     sendTriger();
if(ultrasonic(3)) {
  sendTriger();
  if(ultrasonic(4)){
    sendTriger();
    if(ultrasonic(0)){
    state=00;
  }else
    state=10;
}else
    state=01;
}else
    state=11;
        }
  }
void workrotor(){
  if(!fanWork&&digitalRead(1)){
   if(state==11){
        moveStepper1(A0,8,A1,7);
        moveStepper1(A2,9,A3,10);
  }
  else if(state==01){
     moveStepper1(A0,8,A1,7);
    }
     else if(state==10){
        
         moveStepper2(A2,9,A3,10);
     }else{
           moveStepper2(A0,8,A1,7);
           moveStepper2(A2,9,A3,10);
          }
} 
}
bool ultrasonic(int pin ){
int counter = 0;
float duration = 0;
unsigned long time=0;
  while(  --counter!=0  )
  {
  if( digitalRead(pin) ) 
  {
    time = micros();
    break;
  }
  }
  while( --counter!=0 )
  {
  if( digitalRead(pin)==0 ) 
  {
    duration = micros()-time;
    break;
  }
  }
   if(  (duration/2 ) * 0.0344< 60 )
          return true;
   else 
          return false;
  }
void moveStepper1(int pn1,int pn2,int pn3,int pn4){
  digitalWrite(pn1,1);
   digitalWrite(pn2,0);
   digitalWrite(pn3,0);
   digitalWrite(pn4,0);
 
  digitalWrite(pn1,0);
   digitalWrite(pn2,1);
   digitalWrite(pn3,0);
   digitalWrite(pn4,0);
  
    digitalWrite(pn1,0);
   digitalWrite(pn2,0);
   digitalWrite(pn3,1);
   digitalWrite(pn4,0);
  
    digitalWrite(pn1,0);
   digitalWrite(pn2,0);
   digitalWrite(pn3,0);
   digitalWrite(pn4,1);
   
  }
   void moveStepper2(int pn1,int pn2,int pn3,int pn4){
    
   digitalWrite(pn1,0);
   digitalWrite(pn2,0);
   digitalWrite(pn3,1);
   digitalWrite(pn4,0);
   
   digitalWrite(pn1,0);
   digitalWrite(pn2,1);
   digitalWrite(pn3,0);
   digitalWrite(pn4,0);
  
  digitalWrite(pn1,1);
   digitalWrite(pn2,0);
   digitalWrite(pn3,0);
   digitalWrite(pn4,0);
   
    digitalWrite(pn1,0);
   digitalWrite(pn2,0);
   digitalWrite(pn3,0);
   digitalWrite(pn4,1);

   
  }
 
