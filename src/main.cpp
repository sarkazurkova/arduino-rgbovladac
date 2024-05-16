
#include <Arduino.h>
#define IR_USE_AVR_TIMER 1
#include <IRremote.hpp>
#define IR_RECEIVE_PIN 12

#define redEnter 3091726080 //tlacitko CH+
#define greenEnter 3158572800 //tlacitko PLAY/PAUSE
#define blueEnter 4127850240 //talcitko EQ

#define red 9 //cervena ledka je na pinu 9
#define green 10 //zelena ledka je na pinu 10
#define blue 5 // modra ledka je na pinu 5
#define gnd 8 //minus rgb ledky je na pinu 8
//String StringNum;
//int led=2;
String stringNum;
/*int bar[]= {2,3,4,5,6,7,8,9,10,11};*/
unsigned long codes []={
        3910598400,                               // 0
        4077715200,                               // 1
        3877175040,                               // 2
        2707357440,                               // 3
        4144561920,                               // 4
        3810328320,                               // 5
        2774204160,                               // 6
        3175284480,                               // 7
        2907897600,                               // 8
        3041591040,                               // 9
};

int codesSize = sizeof(codes)/sizeof(codes[0]);
/*int barSize = sizeof(bar)/sizeof(bar[0]);*/

String recievedNum(unsigned long irData){
  for(int i =0; i< codesSize; i++){
    if(irData==codes[i]){
      return String(i);
    }
  }
}

void barOff (){
  for(int i = 2; i<12;i++){
  digitalWrite(i, LOW);
}
}

void setBar(int intNum){
  //led = 2;
  barOff();
  for(int i = 2; i<12; i++){
    digitalWrite(i, bitRead(intNum, 12-i-1));
  }
}

void rgbSet(int led, int intNum){
  analogWrite(led, intNum);
}

void setup()
{
/*for (int i = 2; i < 13; i++)
{
  pinMode(i, OUTPUT);
}
barOff();
digitalWrite(2, HIGH);*/

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(gnd, OUTPUT);
  digitalWrite(gnd, LOW);
  Serial.begin(9600);
}


void loop() {
  
  if (IrReceiver.decode()) { 
    unsigned long  irData= (IrReceiver.decodedIRData.decodedRawData);
    int intNum;
      // Print "old" raw data
     // IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
  if(irData>0){ 
    switch (irData)
    {
    case redEnter:
     intNum = stringNum.toInt();
      if (intNum<256){
       rgbSet(red, intNum);
        stringNum = "";
         Serial.println(irData);
      }else{
        Serial.println("Mimo rozsah");
        stringNum = "";
      }
      break;

    case greenEnter:
      intNum = stringNum.toInt();
      if (intNum<256){
       rgbSet(green, intNum);
        stringNum = "";
         Serial.println(irData);
      }else{
        Serial.println("Mimo rozsah");
        stringNum = "";
      }
      break;

      case blueEnter:
        intNum = stringNum.toInt();
      if (intNum<256){
       rgbSet(blue, intNum);
        stringNum = "";
         Serial.println(irData);
      }else{
        Serial.println("Mimo rozsah");
        stringNum = "";
      }
      break;
    default: 
      stringNum = stringNum + recievedNum(irData);
      Serial.println(stringNum);
      Serial.println(irData);
    
      break;
    }
    
  }
  
      IrReceiver.resume(); // Enable receiving of the next value
}
}