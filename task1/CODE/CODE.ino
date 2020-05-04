int AZ,AO,AT,ATH;
void setup() {
  // put your setup code here, to run once:
pinMode(8,INPUT);
pinMode(7,INPUT);
pinMode(2,INPUT);
pinMode(4,INPUT);
pinMode(13,OUTPUT);
pinMode(12,OUTPUT);
pinMode(11,OUTPUT);
pinMode(10,OUTPUT);
pinMode(9,OUTPUT);
pinMode(6,OUTPUT);
pinMode(5,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
AZ= digitalRead(2);
AO= digitalRead(4);
AT= digitalRead(7);
ATH= digitalRead(8);
digitalWrite(13,(ATH+AT+AO+!AZ)*(ATH+!AT+AZ+AO)*(!ATH+!AO+!AZ+AT)*(!ATH+!AT+AO+!AZ)==0?LOW:HIGH); //ONE
digitalWrite(12,(ATH+!AT+AO+!AZ)*(ATH+!AT+!AO+AZ)*(!ATH+AT+!AO+!AZ)*(!ATH+!AT+AO+AZ)*(!ATH+!AT+!AO)==0?LOW:HIGH); //TWO
digitalWrite(11,(ATH+AT+!AO+AZ)*(!ATH+!AT+AO+AZ)*(!ATH+!AT+!AO)==0?LOW:HIGH); //THREE
digitalWrite(10,(ATH+AT+AO+!AZ)*(ATH+!AT+AO+AZ)*(ATH+!AO+!AZ+!AT)*(!ATH+AT+!AO+AZ)*(!ATH+!AT+!AO+!AZ)==0?LOW:HIGH); //FOUR
digitalWrite(9,(ATH+AT+!AZ)*(ATH+!AT+AO)*(ATH+!AT+!AO+!AZ)*(!ATH+AT+AO+!AZ)==0?LOW:HIGH);  //FIVE
digitalWrite(6,(ATH+AT+AO+!AZ)*(ATH+AT+!AO)*(ATH+!AT+!AO+!AZ)*(!ATH+!AT+!AZ+AO)==0?LOW:HIGH);  //SIX
digitalWrite(5,(ATH+AT+AO)*(AZ+!ATH+!AT+AO)==0?LOW:HIGH );  //SEVEN

}
