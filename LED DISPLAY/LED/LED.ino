#include<LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8,7);
void setup() {
lcd.begin(16,2);  

}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("WELCOME");
  lcd.setCursor(0,1);
  lcd.print("KLMCOLLEGE");
}
