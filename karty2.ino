#define USE_ALB_RFID
#define USE_ALB_LCD_I2C 
#define SS_PIN 10 // Chip Select Pin
#define RST_PIN 9 // Reset Pin
#include "ArduinoLearningBoard.h"
ALB_LCD_I2C lcd;
RFID rfid(SS_PIN, RST_PIN);
int serNum[5];
const byte PIN_RED = 7;
const byte PIN_GREEN = 6;
const byte PIN_BLUE = 5;

const byte COLOR_RED[] = {255,0,0};
const byte COLOR_BLUE[] = {0,0,255};
const byte COLOR_GREEN[] = {0,128,0};

void setup()
{
  SPI.begin();
  rfid.init();
  setColor(COLOR_BLUE);
  lcd.init();
  lcd.clear();
  lcd.backlight(); 
  startingScreen2();
  

}
void setColor(byte colors[]) {
  analogWrite(PIN_RED, colors[0]);
  analogWrite(PIN_GREEN, colors[1]);
  analogWrite(PIN_BLUE, colors[2]);
}

void tabl() {
    String message = "Please put your";
    String message2 = "card here";
    String tab1[18];
    String tab2[18];

    for(int j= 0 ; j<message.length(); j++){
          tab1[j] = message[j];
          lcd.print(tab1[j]);
          delay(50);
    }
    lcd.setCursor(0,1);  
    for(int i=0; i<message2.length(); i++){
            tab2[i] = message2[i];
            lcd.print(tab2[i]);
            delay(50);
          }           
    
}

void startingScreen2(){
  
    lcd.setCursor(0, 0);
    setColor(COLOR_BLUE);
    tabl();
    delay(1000);
  
    
}

void accessG(){
  String message = "Access granted";
  String tab[14];
  setColor(COLOR_GREEN);
  
    for(int j= 0 ; j<message.length(); j++){
          tab[j] = message[j];
          lcd.print(tab[j]);
          delay(50);
    }
}

void accessD(){
  String message = "Access denied";
  String tab[11];
  setColor(COLOR_RED);
  
    for(int j= 0 ; j<message.length(); j++){
          tab[j] = message[j];
          lcd.print(tab[j]);
          delay(50);
    }
}

void loop()
{
	if(rfid.isCard())
	{
		if(rfid.readCardSerial())
		{
			lcd.clear(); 
      lcd.setCursor(0, 0); 
      bool accessGranted = true;
      byte expectedSerial[] = {0x83, 0xB8, 0x2B, 0x25, 0x35};
      for (int i = 0; i < 5; i++) {
        if (rfid.serNum[i] != expectedSerial[i]) {
          accessGranted = false;
          break;
        }
      }

      if(accessGranted)
      {
        accessG();
        delay(5000);
        lcd.clear();
        rfid.halt();
        startingScreen2();
      }
      else 
      {
        accessD();
        delay(2000);
        lcd.clear();
        rfid.halt();
        startingScreen2();
      }
		}
	}
}