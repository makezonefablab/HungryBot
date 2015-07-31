//update 2014.10.16
//Hungrybot by Makezone 

// Length of Arrays
#define MATRIX_SIZE 8

// Current Color State
#define NONE 0
#define RED 1
#define GREEN 2
#define BLUE 3

#define DELAY_COUNT 2

// matrix add lib
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

//color sensor var setup
int s0=3,s1=4,s2=5,s3=6;
int flag=0;
int counter=0;
int countR=0,countG=0,countB=0;

int state; // Current color state
int prevState; // Previous color state

int count; // Matrix animation count
int value; // Compare max color value

// 컬러센서에서 빨간색이 들어왔을 때의 화면 설정입니다.
// 각 각의 0과 1이 꺼지고 켜짐을 나타내며 
// {}안의 값이 출력되는 영상의 하나의 프레임이라고 생각하시고 수정하시면 됩니다.

//빨간색을 입력 받았을 때의 반복되는 화면입니다.
const uint8_t PROGMEM heart[][MATRIX_SIZE] = {
  {
    B00000000,
    B01100110,
    B11111111,
    B11111111,
    B01111110,
    B00111100,
    B00011000,
    B00000000 }
  ,
  { 
    B00000000,
    B00100100,
    B01111110,
    B01111110,
    B00111100,
    B00011000,
    B00000000,
    B00000000 }
};

//녹색을 입력 받았을 때의 반복되는 화면입니다.
const uint8_t PROGMEM monster[][MATRIX_SIZE] = {
  {
    B00000000,
    B00000000,
    B00000000,
    B00000001,
    B00000001,
    B00000001,
    B00000001,
    B00000001 }
  ,
  { 
    B00000000,
    B00000001,
    B00000001,
    B00000011,
    B00000010,
    B00000011,
    B00000010,
    B00000010 }
  ,
  { 
    B00000001,
    B00000010,
    B00000011,
    B00000111,
    B00000101,
    B00000111,
    B00000101,
    B00000101 }
  ,
  { 
    B00000100,
    B00000100,
    B00000111,
    B00001111,
    B00001011,
    B00001111,
    B00001010,
    B00001010 }
  ,
  { 
    B00000100,
    B00001001,
    B00001111,
    B00011111,
    B00010110,
    B00011111,
    B00010101,
    B00010101 }
  ,   
  { 
    B00010010,
    B00010010,
    B00011110,
    B00111111,
    B00101101,
    B00111111,
    B00101010,
    B00101010 }
  ,
  { 
    B00010010,
    B00100100,
    B00111100,
    B01111110,
    B01011010,
    B01111110,
    B01010100,
    B01010100 }
  ,
  { 
    B01001000,
    B01001000,
    B01111000,
    B11111100,
    B10110100,
    B11111100,
    B10101000,
    B10101000 }
  ,   
  { 
    B01001000,
    B10010000,
    B11110000,
    B11111000,
    B01101000,
    B11111000,
    B01010000,
    B01010000 }
  ,
  { 
    B00100000,
    B00100000,
    B11100000,
    B11110000,
    B11010000,
    B11110000,
    B10100000,
    B10100000 }
  ,
  { 
    B00100000,
    B01000000,
    B11000000,
    B11100000,
    B10100000,
    B11100000,
    B01000000,
    B01000000 }
  ,
  { 
    B10000000,
    B10000000,
    B10000000,
    B11000000,
    B01000000,
    B11000000,
    B10000000,
    B10000000 }
  , 
  { 
    B10000000,
    B00000000,
    B00000000,
    B10000000,
    B10000000,
    B10000000,
    B00000000,
    B00000000 }
  ,
  { 
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000 }
  ,
  { 
    B00000000,
    B00000000,
    B00000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000 }
  ,
  { 
    B00000000,
    B10000000,
    B10000000,
    B11000000,
    B01000000,
    B11000000,
    B01000000,
    B01000000 }
  ,
  { 
    B10000000,
    B01000000,
    B11000000,
    B11100000,
    B10100000,
    B11100000,
    B10100000,
    B10100000 }
  ,
  { 
    B00100000,
    B00100000,
    B11100000,
    B11110000,
    B11010000,
    B11110000,
    B01010000,
    B01010000 }
  ,   
  { 
    B00100000,
    B10010000,
    B11110000,
    B11111000,
    B01101000,
    B11111000,
    B10101000,
    B10101000 }
  ,
  { 
    B01001000,
    B01001000,
    B01111000,
    B11111100,
    B10110100,
    B11111100,
    B01010100,
    B01010100 }
  ,
  { 
    B01001000,
    B00100100,
    B00111100,
    B01111110,
    B01011010,
    B01111110,
    B00101010,
    B00101010 }
};

// 청색을 입력 받았을 때의 반복되는 화면입니다.
const uint8_t PROGMEM soso[][MATRIX_SIZE] = {
  { 
    B00111100,
    B01111110,
    B11111111,
    B11011011,
    B11111111,
    B11000011,
    B01111110,
    B00111100 }
  ,
  { 
    B00111100,
    B01111110,
    B11111111,
    B10110111,
    B11111111,
    B10000111,
    B01111110,
    B00111100 }
  ,
  { 
    B00111100,
    B01111110,
    B11111111,
    B01101111,
    B11111111,
    B00001111,
    B01111110,
    B00111100 }
  ,
  { 
    B00111100,
    B01111110,
    B11111111,
    B10110111,
    B11111111,
    B10000111,
    B01111110,
    B00111100 }
  ,
  { 
    B00111100,
    B01111110,
    B11111111,
    B11011011,
    B11111111,
    B11000011,
    B01111110,
    B00111100 }
  ,
  { 
    B00111100,
    B01111110,
    B11111111,
    B11101101,
    B11111111,
    B11100001,
    B01111110,
    B00111100 }
  ,
  { 
    B00111100,
    B01111110,
    B11111111,
    B11110110,
    B11111111,
    B11110000,
    B01111110,
    B00111100 }
  ,
  { 
    B00111100,
    B01111110,
    B11111111,
    B11101101,
    B11111111,
    B11100001,
    B01111110,
    B00111100 }
};

void setup()
{
  Serial.begin(115200);
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT); 
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);

  //matrix begin
  matrix.begin(0x70);  // pass in the address
  
  state = NONE;
  count = 0;
  
  matrix.setRotation(0); // 매트릭스 초기화
}

void TCS()
{
  digitalWrite(s1,HIGH);
  digitalWrite(s0,LOW);
  flag=0;
  attachInterrupt(0, ISR_INTO, CHANGE);
  timer2_init();
}

void ISR_INTO()
{
  counter++;
}

void timer2_init(void)
{
  TCCR2A=0x00;
  TCCR2B=0x07; //the clock frequency source 1024 points
  TCNT2= 100;    //10 ms overflow again
  TIMSK2 = 0x01; //allow interrupt
}

ISR(TIMER2_OVF_vect)//the timer 2, 10ms interrupt overflow again. Internal overflow interrupt executive function
{
  TCNT2=100;
  flag++;
  if(flag==1)
  {
    counter=0;
  }
  else if(flag==2)
  {
    digitalWrite(s2,LOW);
    digitalWrite(s3,LOW); 
    countR=counter/1.051;
    digitalWrite(s2,HIGH);
    digitalWrite(s3,HIGH);   
  }
  else if(flag==3)
  {
    countG=counter/1.0157;
    digitalWrite(s2,LOW);
    digitalWrite(s3,HIGH); 

  }
  else if(flag==4)
  {
    countB=counter/1.114;
    digitalWrite(s2,LOW);
    digitalWrite(s3,LOW);
  }
  else
  {
    flag=0; 
    TIMSK2 = 0x00;
  }
  counter=0;
  delay(2);
}

// loop()안에는 아두이노 계속처리할 작업을 적어줍니다.
void loop()
{
  delay(100);
  
  TCS();
  
  value = max(countR, max(countG, countB));
  
  if(value < 6) { // None
    state = NONE;
  }
  else if(value == countR) { // Red
    state = RED;
  }
  else if(value == countG) { // Green
    state = GREEN;
  }
  else { // Blue
    state = BLUE;
  }
  
  if(prevState == state) {
    count++;
  }
  else {
    count = 0;
  }
  //화면을 바꾸기 전 화면을 초기화하는 함수
  matrix.clear();
  
  if(state == RED) {//적색이 들어왔을 때 화면을 그립니다. matrix.drawBitmap() ==>맨 위에서 수정한  0과1의 그림을 불러옵니다.
    matrix.drawBitmap(0, 0, heart[(count / DELAY_COUNT) % (sizeof(heart) / MATRIX_SIZE)], MATRIX_SIZE, MATRIX_SIZE, LED_ON);
  }
  else if(state == GREEN) {//녹색이 들어왔을 때 화면을 그립니다.
    matrix.drawBitmap(0, 0, monster[(count / DELAY_COUNT) % (sizeof(monster) / MATRIX_SIZE)], MATRIX_SIZE, MATRIX_SIZE, LED_ON);
  }
  else if(state == BLUE) {//청색이 들어왔을 때 화면을 그립니다.
    matrix.drawBitmap(0, 0, soso[count % (sizeof(soso) / MATRIX_SIZE)], MATRIX_SIZE, MATRIX_SIZE, LED_ON);
  }
  else { 
  
    // NONE 아무색도 입력받지 않았을 때의 기본화면입니다.
	// Matrix.print(반복되는 문자열) 입력하시면 원하는 글자가 반복됩니다.
    matrix.setTextSize(1);
    matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
    matrix.setTextColor(LED_ON);
    matrix.print("Hungry");
    matrix.setCursor(-(count % 37), 0);
  }
  
  prevState = state;
  
  //불러온화면을 led에 그려냅니다.
  matrix.writeDisplay();
}
