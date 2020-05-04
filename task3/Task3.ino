// I use nor gates 
// if weight sensor more than 70 kg
// only the motor stop but can tack any request  

bool isCall []={0,0,0,0,0,0,0,0},workFlag= true;
unsigned long prevMillisSwitches[]={0,0,0,0,0,0,0,0};
int keypadValues []={719,894,911,929,822,837,852,761};
int moterStep=1,motorCounter []={0,0,0,0};
bool highFlag=1;
int currentFloor=0,target=-1;
unsigned long previousMillisMotor=0;

void setup() {
  for (int i=0 ;i<8;i++)
    pinMode(i,INPUT);
  for (int i=9 ;i<=12;i++)
     pinMode(i,OUTPUT);
     //for motor 
  pinMode(A5,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A2,OUTPUT);
  attachInterrupt(0,checkCall , RISING);
}
void loop() {
  writeInSeg(currentFloor );
  moveMotor();
  checkWightSensor();
  readKeypad();
  checkCall ();
  checkAnyCall();

}
void checkAnyCall(){
  int newTarget=-1;
  if(highFlag){
  for (int i=currentFloor+1;i<8;i++){
    if(isCall[i]) {
      newTarget=i;
      break;
    }
    }
    if(newTarget==-1 && target==-1)
      for (int i=0;i<currentFloor;i++){
        if(isCall[i]) {
          newTarget=i;
          highFlag=0;
          break;
    }
      }
    target=newTarget;
      }
  else{
          for (int i=0;i<currentFloor;i++){
        if(isCall[i]) {
          newTarget=i;
          break;
    }
      }
      if(newTarget==-1 && target==-1)
       for (int i=currentFloor+1;i<8;i++){
        if(isCall[i]) {
          newTarget=i;
          highFlag=1;
          break;
    }
    }
       target=newTarget;
  }
  //writeInSeg(target);
  }

void moveMotor(){
  if(workFlag)
  if((unsigned long)(millis()-previousMillisMotor) >1000){
  if(moterStep%9==0){
  for (int i=0;i<4;i++)
    motorCounter [i]=0;
  moterStep=1;
  if(highFlag)currentFloor++;
  else currentFloor--;
  
  if(currentFloor==target){
    isCall[target]=0;
    target=-1;
    previousMillisMotor= millis();
    }
    }
    if(target!=-1){
if(highFlag==1)
  rotateMotor(A3,A4,A5,A2);// to move backward 
else
rotateMotor(A5,A4,A3,A2);// to move in direct
  
  }}
  }
 // read keypad
void readKeypad(){
   int sensorValue = analogRead(A0);  
  for(int i=0 ; i<=7;i++){
    if(sensorValue==keypadValues[i]){
        isCall[i]=true;
        }
        }
}
// if call 
void checkCall (){
  //TODO -- in this case not check more than 200 milliseconds
   for(int i=0 ; i<=7;i++)
      if(digitalRead(i)==1){
        if(prevMillisSwitches[i]==0)
              prevMillisSwitches[i]=millis();
        else
          if((unsigned long)(millis()-prevMillisSwitches[i])>=200){
             isCall[i]=true;
             prevMillisSwitches[i]=0;
             }
}
}

// sensor wieght 
void checkWightSensor(){
  int sensorValue = analogRead(A1);
  if(sensorValue>716)  workFlag=false;
  else                 workFlag=true;
  digitalWrite(12,!workFlag);
  }

//write in seven Signment
void writeInSeg(int num ){
  digitalWrite(11,num%2);
  num=num/2;
  digitalWrite(10,num%2);
  num=num/2;
  digitalWrite(9,num%2);
  }

//motor movement 
  void rotateMotor(int pin1,int pin2,int pin3,int pin4){
   if(motorCounter[0]<=70)
     motorCounter[0]++;
      
   else if(motorCounter[1]<=70)
      motorCounter[1]++;
    else if(motorCounter[2]<=70)
      motorCounter[2]++;
        else if(motorCounter[3]<=70)
      motorCounter[3]++;
   else
      for (int i=0;i<4;i++)
          motorCounter [i]=0;
    if(motorCounter[0]==70){
    digitalWrite(pin1,1);
    digitalWrite(pin2,0);
    digitalWrite(pin3,0);
    digitalWrite(pin4,0);
     
    }
   
    if(motorCounter[1]==70){
    digitalWrite(pin1,0);
    digitalWrite(pin2,1);
    digitalWrite(pin3,0);
    digitalWrite(pin4,0);
    }
   if(motorCounter[2]==70){
    digitalWrite(pin1,0);
    digitalWrite(pin2,0);
    digitalWrite(pin3,1);
    digitalWrite(pin4,0);
    
    }
   if(motorCounter[3]==70){
    digitalWrite(pin1,0);
    digitalWrite(pin2,0);
    digitalWrite(pin3,0);
    digitalWrite(pin4,1);
     moterStep++;
    
    }
    }
