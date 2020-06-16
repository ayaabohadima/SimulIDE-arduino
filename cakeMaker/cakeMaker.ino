String order = "";
const int inputsKey[] = {911, 929, 837, 852};
bool IsKeypressed = false;
int currentPhase = 0;
int phaseAction = 0;
int stepperStep = 0;
int revolute = 0;
unsigned long prevMills = millis();
unsigned long prevMillsServo = millis();
void setup() {
  for (int i = 0; i < 14; i++)
    pinMode(i, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  // all servo motores in zero position 
  servoPulse (A1, 0);
  servoPulse (9, 0);
  servoPulse (10, 0);
  servoPulse (11, 0);
  servoPulse (5, 0);
}

void loop() {
  readKeypad();
  phases();
}
// determine phase :
void phases() {
  if (order != "") {
    if (currentPhase == 0)
      phase1();
    if (currentPhase == 1)
      phase2();
    else if (currentPhase == 2)
      for (int i = 1; i < 5; i++) {
        if (char(i) == order[0])
          phase3(i);
      }
  }
}
//////////////////////////////////////
///phase 3 :
void phase3(int currentNum) {
  if (order != "") {
    moveStepperByTwoPins();
    if (currentNum == 1) {
      if (phaseAction == 0) {
        phaseAction++;
        servoPulse (A1, 120);
      }
      if (revolute < 8 && phaseAction == 1 )
        digitalWrite(A3, 1);
      else if (phaseAction == 1) {
        revolute = 0;
        servoPulse (A1, 180);
        phaseAction++;
      }
      else if (phaseAction == 2 && revolute < 8) {
        digitalWrite(A3, 0);
        digitalWrite(A2, 1);
      }
      else if (phaseAction == 2) {
        deleteOrder();
        servoPulse (A1, 0);
        digitalWrite(A2, 0);
        digitalWrite(A3, 0);
      }
    }
    else if (currentNum == 2) {
      if (revolute % 2 == 0 && revolute < 9) {
        servoPulse (A1, 120);
        digitalWrite(A3, 1);
        digitalWrite(A2, 0);
      }
      else if (revolute % 2 == 1 && revolute < 9) {
        servoPulse (A1, 180);
        digitalWrite(A2, 1);
        digitalWrite(A3, 0);
      }
      else if (revolute == 9) {
        deleteOrder();
        servoPulse (A1, 0);
        digitalWrite(A2, 0);
        digitalWrite(A3, 0);
      }
    }
    else if (currentNum == 3) {
      if (revolute < 9) {
        servoPulse (A1, 0);
        digitalWrite(A2, 0);
        digitalWrite(A3, 1);
      }
      else if (revolute < 17 ) {
        if ((unsigned long)(millis() - prevMills) <= 125 || ((unsigned long)(millis() - prevMills) <= 375 && (unsigned long)(millis() - prevMills) >= 250)) {
          servoPulse (A1, 180);
          digitalWrite(A2, 1);
          digitalWrite(A3, 0);
        }
        else {
          digitalWrite(A2, 0);
        }
      }
      else {
        deleteOrder();
        servoPulse (A1, 0);
        digitalWrite(A2, 0);
        digitalWrite(A3, 0);
      }
    }
    else if (currentNum == 4) {
      if (revolute < 17) {
        if (revolute < 9)  servoPulse (A1, 0);
        else  servoPulse (A1, 60);
        digitalWrite(A2, 1);
        digitalWrite(A3, 0);
      }
      else if (revolute < 25 ) {
        if ((unsigned long)(millis() - prevMills) <= 125) {
          servoPulse (A1, 180);
          digitalWrite(A2, 1);
          digitalWrite(A3, 0);
        } else if ((unsigned long)(millis() - prevMills) <= 375 && (unsigned long)(millis() - prevMills) >= 250) {
          servoPulse (A1, 180);
          digitalWrite(A2, 0);
          digitalWrite(A3, 1);
        }
        else {
          digitalWrite(A2, 0);
          digitalWrite(A3, 0);
        }
      }
      else {
        deleteOrder();
        servoPulse (A1, 0);
        digitalWrite(A2, 0);
        digitalWrite(A3, 0);
      }
    }
  }
}
///////////////////////////////////////
////delete an order
void deleteOrder() {
  //Serial.println(sorder);
  String s = "";
  for (int i = 1; i < order.length(); i++)
    s += order[i];
  order = s;
  prevMills = millis();
  prevMillsServo = millis();
  currentPhase = 0;
  phaseAction = 0;
  stepperStep = 0;
  revolute = 0;
}
///////////////////////////////////////////
///// phase 2
void phase2() {
  if (order != "") {
    if (phaseAction == 0 && stepperStep == 0)
      moveStepper(100, 5);
    if (stepperStep == 1) {
      phaseAction++;
      stepperStep = 0;
      // Serial.print(phaseAction);
      prevMills = millis();
    }
    else if (phaseAction == 1 && (unsigned long)(millis() - prevMills) <= 1000 )
      digitalWrite(12 , HIGH);
    else if (phaseAction == 1) {
      digitalWrite(12 , LOW);
      prevMills = millis();
      phaseAction++;

    }
    else if (phaseAction == 2)
      moveStepper(100, 5);
    else if ((unsigned long)(millis() - prevMills) >= 1000 ) {
      currentPhase = 2;
      phaseAction = 0;
      prevMills = millis();
      prevMillsServo = millis();
    }
  }
}
////////////////////////////////////////////////////
////phase one :
void phase1() {
  if (order != "") {
      int laststepsNum=0;
      if (phaseAction == 0){
        digitalWrite(A2, 0);
        digitalWrite(A3, 0); 
        moveServo(9, 500);}
      if (stepperStep < 5 && phaseAction == 1)
        moveStepper(25, 0);
      else if (stepperStep == 5)
      {
        phaseAction++;
        stepperStep = 0;
        prevMillsServo = millis();
  
      }
      else  if (phaseAction == 2){
        moveServo(11, 100); // should be vanalia pin
        moveStepper(25, 0);
        laststepsNum=stepperStep;
      } else  if (stepperStep < 4+laststepsNum&& phaseAction == 3)
        moveStepper(25, 0);
      else if (stepperStep == 4)
      {
        phaseAction++;
        stepperStep = 0;
        prevMillsServo = millis();
      } else  if (phaseAction == 4)
        moveServo(10, 200); // should be suger pin
      else  if (stepperStep < 10 && phaseAction == 5)
        moveStepper(25, 0);
      else if (stepperStep == 10) {
        stepperStep = 0;
        phaseAction++;
        prevMillsServo = millis();
      }
      else if (phaseAction == 6)
        moveServo(5, 200); // should be flour pin
      else if (phaseAction == 7 && stepperStep < 4)
        moveStepper(50, 0);
      else if (stepperStep == 4) {
        stepperStep = 0;
        phaseAction++;
        prevMillsServo = millis();
      }
      else if (phaseAction == 8)
        moveServo(5, 200); // should be flour pin
      else if (phaseAction == 9 && stepperStep < 4)
        moveStepper(50, 0);
      else if (stepperStep == 4) {
        stepperStep = 0;
        phaseAction++;
        prevMillsServo = millis();
      }
      else if (phaseAction == 10)
        moveServo(5, 200); // should be flour pin
      else if (phaseAction == 11 && stepperStep < 4)
        moveStepper(50, 0);
      else if (stepperStep == 4) {
        stepperStep = 0;
        phaseAction++;
        prevMillsServo = millis();
      }
      else if ( phaseAction == 12) {
        currentPhase = 1;
        phaseAction = 0;
        prevMills = millis();
      }
  }
}
//////////////////////////////////////
// move stepper motor :
void moveStepper(int speed, int pinShift) {
  if ((unsigned long)(millis() - prevMills) <= speed  )
    for (int i = 0; i < 4; i++)
      digitalWrite(i + pinShift == 5 ? 4 : i + pinShift, i == 0 ? HIGH : LOW);
  else if ((unsigned long)(millis() - prevMills) <= speed * 2 && (unsigned long)(millis() - prevMills) >= speed)
    for (int i = 0; i < 4; i++)
      digitalWrite(i + pinShift == 5 ? 4 : i + pinShift, i == 1 ? HIGH : LOW);
  else if ((unsigned long)(millis() - prevMills) <= speed * 3 && (unsigned long)(millis() - prevMills) >= speed * 2)
    for (int i = 0; i < 4; i++)
      digitalWrite(i + pinShift == 5 ? 4 : i + pinShift, i == 2 ? HIGH : LOW);
  else if ((unsigned long)(millis() - prevMills) <= speed * 4 && (unsigned long)(millis() - prevMills) >= speed * 3)
    for (int i = 0; i < 4; i++)
      digitalWrite(i + pinShift == 5 ? 4 : i + pinShift, i == 3 ? HIGH : LOW);
  else {
    prevMills = millis();
    stepperStep++;
  }
}
///////////////////////////////////////////
//////// move servo motor angle :
void servoPulse (int servo, int angle)
{
  int   pwm = (angle * 10.5) + 500;
  digitalWrite(servo, HIGH);
  delayMicroseconds(pwm); //First delay
  digitalWrite(servo, LOW);
}
/////////////////////////////////////////
// read from keypad
void readKeypad() {
  bool notRead = true;
  int keypadValue = analogRead(A0);
  for (int i = 0; i < 4; i++)
    if (keypadValue == inputsKey[i]) {
      notRead = false;
      int num = i + 1;
      if (order == "") {
        prevMills = millis();
        prevMillsServo = millis();
      }
      if (!IsKeypressed || char(num) != order[order.length() - 1])
        order += char(num);

    }
  if (notRead == true) {
    IsKeypressed = false;
  }
  else IsKeypressed = true;

}
/////////////////////////////////////////////////
// move servo as volves
void moveServo(int servoPin, int delayTime ) {
  servoPulse (servoPin, 180);
  if ( (unsigned long)(millis() - prevMillsServo) >= delayTime) {
    servoPulse (servoPin, 0);
    phaseAction++;
    prevMills = millis();
  }
}
///////////////////////////////////////////////////
// move servo with 2 pins 
void moveStepperByTwoPins() {
  if ((unsigned long)(millis() - prevMills) <= 250) {
    digitalWrite(A5, 1);
    digitalWrite(A4, 1);
    stepperStep = 1;
  }
  else if ((unsigned long)(millis() - prevMills) <= 500) {
    stepperStep = 0;
    digitalWrite(A5, 0);
    digitalWrite(A4, 0);
  }
  else {
    prevMills = millis();
    revolute++;
  }
}
