#include <Keyboard.h>
#define READ_SPD         5

 enum PinAssignments
 {
  encoderPinA = 0,
  encoderPinB = 1,
  encoderPinC = 3,
  encoderPinD = 2,

 };
//This is up to your pin wiring
 
 int encoderPos[] = {0,0};
 static boolean rotating[] = {false,false};
 
 boolean A_set = false;              
 boolean B_set = false;
 boolean C_set = false;              
 boolean D_set = false;
 
void setup()
{
  pinMode(4, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  Keyboard.begin();

  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderPinC, INPUT_PULLUP);
  pinMode(encoderPinD, INPUT_PULLUP);
 
  attachInterrupt(0, doEncoderC, CHANGE);
  attachInterrupt(1, doEncoderD, CHANGE);
 
  attachInterrupt(2, doEncoderA, CHANGE);
  attachInterrupt(3, doEncoderB, CHANGE);
//  Serial.begin(9600);
}

void loop() {
  if(digitalRead(4)==LOW){
    Keyboard.press('y');
  }
  else{
    Keyboard.release('y');
  }
  
  if(digitalRead(A0)==LOW){
    Keyboard.press('d');
  }
  else{
    Keyboard.release('d');
  }
  
  if(digitalRead(A1)==LOW){
    Keyboard.press('f');
  }
  else{
    Keyboard.release('f');
  }
  
  if(digitalRead(A2)==LOW){
    Keyboard.press('j');
  }
  else{
    Keyboard.release('j');
  }
  
  if(digitalRead(A3)==LOW){
    Keyboard.press('k');
  }
  else{
    Keyboard.release('k');
  }
  
  if(digitalRead(A4)==LOW){
    Keyboard.press('v');
  }
  else{
    Keyboard.release('v');
  }
  
  if(digitalRead(A5)==LOW){
    Keyboard.press('n');
  }
  else{
    Keyboard.release('n');
  }
  //Encoder Reset  

  char encoderKey[2][2] = {
      {'q','w'},
      {'o','p'}
    };
   
  for(int i=0;i<=1;i++)
  {
    rotating[i] = true;
    if (encoderPos[i] != 0)
    {
      if(encoderPos[i] > READ_SPD) {
        Keyboard.press(encoderKey[i][1]);
        Keyboard.release(encoderKey[i][0]);
      } else if(encoderPos[i] < READ_SPD * (-1)) {
        Keyboard.press(encoderKey[i][0]);
        Keyboard.release(encoderKey[i][1]);
      }
    } else { // 엔코더 포지션이 0이면
      Keyboard.release(encoderKey[i][0]);
      Keyboard.release(encoderKey[i][1]);
    }
    encoderPos[i] = 0;
  }
}
 
void doEncoderA()
{
  if( digitalRead(encoderPinA) != A_set )
  {  
    A_set = !A_set;
 
    if ( A_set && !B_set )
      encoderPos[0] += 1;
 
    rotating[0] = false;  
  }
}
 
void doEncoderB()
{
  if( digitalRead(encoderPinB) != B_set ) {
    B_set = !B_set;
   
    if( B_set && !A_set )
      encoderPos[0] -= 1;
 
    rotating[0] = false;
  }
}
 
void doEncoderC()
{
  if( digitalRead(encoderPinC) != C_set )
  {  
    C_set = !C_set;
 
    if ( C_set && !D_set )
      encoderPos[1] += 1;
 
    rotating[1] = false;
  }
}
 
void doEncoderD()
{
  if( digitalRead(encoderPinD) != D_set ) {
    D_set = !D_set;
   
    if( D_set && !C_set )
      encoderPos[1] -= 1;
 
    rotating[1] = false;
  }
}

//original code : LEONARDOJoy (http://pastebin.com/3ypgaRBd)
//modified by QC.G0X
