#include <LED.h>
#include <stdlib.h>
#include "Switch.h"
#include "Buzzer.h"
#define BUZ_PIN 11
#include "RgbLcd.h"
#include <FND.h>

FND myfnd;
RgbLcd lcd;
Buzzer myBuzzer;
Switch pushSwitch;
LED myled;

int count = 0; // 점수를 전역변수로 초기화
void setup() {
  lcd.begin(62,63,64,65,66,67,45,44,43,42,16,2);
  lcd.onBacklightGreen();
  lcd.print("WelCome !");
  lcd.setCursor(0,1);
  lcd.print("Push Any Key! ");

  myfnd.begin(38,32);
  myled.begin(36);
  pushSwitch.begin();
  Serial.begin(9600);
  myBuzzer.begin(BUZ_PIN);
}

void loop() {
  int i = 0; // 카운트 0으로 초기화
  uint8_t pushKey1 = pushSwitch.waitGetPushKey(); // 스위치 입력 대기
  
  if(pushKey1>0){ // 스위치를 클릭하면 게임 시작
  lcd.clear(); // lcd 램 초기화
  lcd.print("START !");
  for( i = 10; i>=0; i--){ // 10초동안 게임 실행
  myfnd.setAllNum(i); // fnd에 10초 카운트다운 출력
  int random = 0; 
    
  random = rand()%9; //0부터 8까지 난수 생성
  myled.On(random); //난수 번호를 LED에 2초동안 출력
  delay(1000); // 랜덤 led출력 1.5초동안 지속
  uint8_t pushKey = pushSwitch.getPushKey(); // 스위치 클릭값 가져옴

  if(random == 0){
    random++; // random값이 0이라면, 1을 더해줌으로서 스위치와 비교할 수 있게끔 바꾸어준다. 
  }

  Serial.println(random);
  
  if(pushKey==random){ // 두더지를 잡으면
   count++;
   Serial.println(pushKey);
   lcd.onBacklightGreen(); // 맞추면 초록색으로
   myBuzzer.setFreq(261.6256); // 4옥타브 도로 부저소리 설정
   myBuzzer.On();
   delay(100);
  }else{ // 두더지를 못잡으면
   count--;
   if(count<0){ // 점수가 -를 가지지 않도록 조절
    count++;
   }
   Serial.println(pushKey);
   myBuzzer.setFreq(391.9954); // 4옥타브 솔로 부저소리 설정
   lcd.onBacklightRed(); // 틀리면 빨간색으로
   myBuzzer.On();
   delay(200);
  }

  lcd.setCursor(0,1); // lcd의 다음줄로 이동
  lcd.print(count); // 점수 출력
  
  lcd.onBacklight(0,0); // lcd모니터 색상 초기화
  
  myBuzzer.Off();
  delay(10);
  myled.Off(random);
  delay(10);
    
  }
  lcd.clear();
  lcd.print("END");
  lcd.setCursor(0,1);
  lcd.print("Point : ");
  lcd.print(count);
  delay(5000); // 점수 5초동안 출력
  
  count = 0;
  lcd.clear();
  }
 lcd.print("push any key");
 lcd.setCursor(0,1);
 lcd.print("to restart");  
}
