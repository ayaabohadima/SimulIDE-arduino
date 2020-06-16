// should add emotions && numbers drawing
 const int keypadValues[]={681,911,929,837,852,773,786,719,730,672};
 const int lednums []={24,10,18,18,19,18,21,18,20,21};//from 0-9 numbers  
int mode=0; //if 0 self-test for colums 1 self test for rows 2 numoric 3 emotions 
int song=-1;
bool playSong=0,changePassNow=false; 
int prevNumber=-1;
int currentNum=-1;
int currentDelay=0;
bool isKey=false;
bool changPass=false;
// when enter password will print nothing the system will wait key pressed
// pins 0,1 for modes 
// 00 colums & 01 for rows & 10 for numbers & 11 for emotions
// will out  the delay counter 
// print 00001 in mode colums & will turn on frist coloum 
//print  00000 in mode colums &will turn on secound coloum
// will out current number in 4 pins 
#define  c     3830    // 261 Hz
#define  d     3400    // 294 Hz
#define  e     3038    // 329 Hz
#define  f     2864    // 349 Hz
#define  g     2550    // 392 Hz
#define  a     2272    // 440 Hz
#define  b     2028    // 493 Hz
#define  y     1912    // 523 Hz
#define  r     1567
#define w     3520
int melody[] = {  r,c,d,f,y,g,a,b,w,e};
int beats[]  = { 8, 8, 8,  8,  8,  8, 8, 8, 8, 8, 8, 8 };
long tempo = 100;   
int password[]={1,2,3,4};
int changPassword[]={1,2,1,2};
int currentInPass=0;
int currentChangPassIndex=0;
unsigned long prevMills=millis(); //for drawing

void setup() {
 for (int i =0;i<12;i++)
    pinMode(i,OUTPUT);
 pinMode(A1,OUTPUT);
}

void loop() {
 playTone();
 checkMode();
}

void checkMode(){
   if(mode==0){
    digitalWrite(0,0);
    digitalWrite(1,0);
    PrintDelay();
    }
   else if(mode==1){
    digitalWrite(0,1);
    digitalWrite(1,0);
    PrintDelay();
    }
    else if(mode==2)
    {printNumber(lednums[currentNum]);
      digitalWrite(0,0);
      digitalWrite(1,1);
      readKeypad();
    }
    else if(mode==3){
      digitalWrite(0,1);
      digitalWrite(1,1);
      readKeypad();
      printNumber(37);
  }
}
//print number and delay
void printNumber(int modeINC){
  if(currentNum!=-1 && currentDelay<modeINC){
  int num=currentNum;
  for(int i=8;i<12;i++){
    digitalWrite(i==9?12:i,num%2==0?LOW:HIGH);
    num=num/2;
    }
   num=currentDelay;
  for (int i=2;i<=7;i++){
    digitalWrite(i,num%2==0?0:1);
    num=num/2;
  }
  if((unsigned long )(millis()-prevMills)>=100){
  currentDelay++;
  prevMills=millis();
  }
  }else if(currentNum==-1)
  {
      int num=10;
  for(int i=8;i<12;i++){
    digitalWrite(i==9?12:i,num%2==0?LOW:HIGH);
    num=num/2;
    }
    }
  }
//print delay value
void PrintDelay(){
 int num=currentDelay;
  for (int i=2;i<6;i++){
    digitalWrite(i,num%2==0?0:1);
    num=num/2;
  }
  if((unsigned long )(millis()-prevMills)>=200){
  currentDelay++;
  if(currentDelay==10)
  {
    currentDelay=0;
    mode++;
    if(mode==2)
    for (int i=2;i<6;i++){
    digitalWrite(i,0);
    }
  }
  prevMills=millis();
  }
}

//read keypad
void readKeypad(){
  bool key=false;
   int keypadValue = analogRead(A0);  
   for(int i ;i<10;i++)
    if(keypadValue==keypadValues[i]){
      key=true;
      if(isKey&&i==prevNumber)
        return;   
      prevMills=millis();
      playSong=true;
      song=0;
      changePassNow=false;
      prevNumber=i;
      if(i!=currentNum){
      currentNum=i;
      currentDelay=0;
      }
      checkPassAndChangePass(i);
   }
   if(key == true )isKey=true;
   else isKey=false;
 }
 // check if key is chang password or any of password:
void checkPassAndChangePass(int i){
     if(changPass==false){
      if(mode==2)
        if(i==password[currentInPass]){
            currentInPass++;
            if(currentInPass==4)
            {
              currentNum=-1;
              printNumber(1);
              currentInPass=0;
              mode=3;
              currentDelay=0;
              changePassNow=true;
          }
       }
       else {
       currentInPass=0;
       if(i==password[currentInPass]){
            currentInPass++;
            if(currentInPass==4)
            {currentNum=-1;
              currentInPass=0;
              
              currentNum=-1;
              printNumber(1);
              currentDelay=0;
              mode=3;
          }
       }
       }else if(i==password[3-currentInPass]){
            currentInPass++;
            if(currentInPass==4)
            {
              currentInPass=0;
              mode=2;
              currentDelay=0;
              currentNum=-1;
              printNumber(1);
              changePassNow=true;
          }
      }else{ 
          currentInPass=0;
          if(i==password[3-currentInPass]){
            currentInPass++;
            if(currentInPass==4)
            {
              currentDelay=0;
              currentInPass=0;
              currentNum=-1;
              printNumber(1);
              mode=2;
          }
      }   
      }if(i==changPassword[currentChangPassIndex]){
        currentChangPassIndex++;
        if(currentChangPassIndex==4){
            changPass=true;
            currentInPass=0;
            currentChangPassIndex=0;
        }
        }
        else{
            currentChangPassIndex=0;
            if(i==changPassword[currentChangPassIndex]){
        currentChangPassIndex++;
        if(currentChangPassIndex==4){
            changPass=true;
            currentInPass=0;
            currentChangPassIndex=0;
        }
        }
        }
      }
      else
        {
          password[currentInPass]=i;
          currentInPass++;
          if(currentInPass==4)
           changPass=false;
          }
  }
  // to send sound
  void playTone() {
    if(playSong){
      song++;
      if(song==150 &&!changePassNow)
      playSong=false;
      else if(song==500 &&changePassNow){
        changePassNow=false;
      playSong=false;}
    int tone_ = melody[changePassNow?2:currentNum];
    int beat = beats[currentNum];
    //int duration = beat * tempo; // Set up timing

  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has
    //  played less long than 'duration', pulse speaker HIGH and LOW
  //  while (elapsed_time < duration) {

      digitalWrite(9,HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(9, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    }
}

  }
