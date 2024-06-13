#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

const int RU = 9;
const int LH = A3;
const int LU = 10;
const int RH = 11;
const int onetwo = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(115200); // for robot  
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(8,OUTPUT);
  Serial.println("Program Started");

}
void sendPacketMRTEXE(unsigned char exeIndex)
{
  unsigned char exeCmd[15] = {0xff, 0xff, 0x4c, 0x53, 0x00, 
                              0x00, 0x00, 0x00, 0x30, 0x0c, 0x03, // 0x0c=동작 실행 명령 0x03=파라메타수 
                              0x01, 0x00, 100, 0x00};             // Index 01 명령어 샘플
/*                             |      |    |    `---Check sum
                               |      |    `--------속도      파라1
                               |      `-------------지연시간  파라2
                               `--------------------Index    파라3
*/
  exeCmd[11] = exeIndex;
  exeCmd[14] = 0x00;    // checksum
    
  for (int i=6;i<14;i++){
    exeCmd[14]+=exeCmd[i];    
  }
  mySerial.write(exeCmd,15);   
}
void loop() {
  // put your main code here, to run repeatedly:
  int zap = 0;
  zap = analogRead(A1);
  int st = 0;
  st = analogRead(A2);
  int onetwo = 0;
  onetwo = analogRead(A0);

  if(onetwo>0&&onetwo<=200)
  {
    sendPacketMRTEXE(36);
     delay(1000);
  }
  if(zap<600)
  {
    sendPacketMRTEXE(30);
     delay(1000);
  }
  if(st<600)
  {
    sendPacketMRTEXE(33);
     delay(1000);
  }
  if(digitalRead(RU))
  {
    sendPacketMRTEXE(35);
     delay(1000);
  }
  if(digitalRead(LH))
  {
    sendPacketMRTEXE(31);
     delay(1000);
  }
  if(digitalRead(LU))
  {
    sendPacketMRTEXE(32);
     delay(1000);
  }
  if(digitalRead(RH))
  {
    sendPacketMRTEXE(34);
     delay(1000);
  }

}
