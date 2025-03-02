
#include<Keypad.h>
#include<LiquidCrystal_I2C.h>
#include<Wire.h>

const int buzzer=12;
const int led=2;
LiquidCrystal_I2C lcd(0x27,16,2);

const char no_of_rows=4;
const char no_of_cols=3;

char row_pins[no_of_rows]={9,7,8,6};
char col_pins[no_of_cols]={5,4,3};

char key_arr[4][3]={
  {'1','2','3'},
  {'7','8','9'},
  {'4','5','6'},
  {'*','0','#'}
};

Keypad k=Keypad(makeKeymap(key_arr),row_pins,col_pins,no_of_rows,no_of_cols);

const String correct_password = "1234";  
String entered_password = ""; 
const int password_length = 4;  

void setup() {
  Serial.begin(9600);

  pinMode(buzzer,OUTPUT);
  pinMode(led,OUTPUT);
  lcd.begin();
  lcd.backlight();  

  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
  
}

void loop() {
  char key_pressed=k.getKey();
  if (Serial.available() > 0) {
    String dataFromEsp32 = Serial.readString();
    Serial.print("Received from Esp32: ");
    Serial.println(dataFromEsp32);
    if (dataFromEsp32) {
      // Handle special keys
      if (dataFromEsp32 == "*") {  // Reset password input
        entered_password = "";
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter Password:");
      } 
      else if (dataFromEsp32 == "Enter") {  // Check password
        lcd.clear();
        lcd.setCursor(0, 0);
        if (entered_password == correct_password) {
          lcd.print("Access Granted");
          digitalWrite(led,HIGH);
          delay(5000);
          digitalWrite(led,LOW);
        } else {
          lcd.print("Access Denied");
          digitalWrite(buzzer,HIGH);
          delay(5000);
          digitalWrite(buzzer,LOW);
        }
        entered_password = "";  // Reset input after checking
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter Password:");
      } 
      else {  // Store digits in entered_password
        if (entered_password.length() < password_length) {
          entered_password += dataFromEsp32;
          lcd.setCursor(entered_password.length(), 1);
          lcd.print('*');  // Show '*' instead of the actual number
          // lcd.setCursor(entered_password.length() - 1, 1);
          // lcd.print(key_pressed);  // Display the actual number
          Serial.println(entered_password);
        }
      }
    }
  }
  // if(key_pressed){
    // Serial.println(key_pressed);
    // lcd.clear();
    
    // lcd.setCursor(0,0);
    // lcd.print(key_pressed);
  // }
  if (key_pressed) {
    // Handle special keys
    if (key_pressed == '*') {  // Reset password input
      entered_password = "";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter Password:");
    } 
    else if (key_pressed == '#') {  // Check password
      lcd.clear();
      lcd.setCursor(0, 0);
      if (entered_password == correct_password) {
        lcd.print("Access Granted");
        digitalWrite(led,HIGH);
        delay(5000);
        digitalWrite(led,LOW);
      } else {
        lcd.print("Access Denied");
        digitalWrite(buzzer,HIGH);
        delay(5000);
        digitalWrite(buzzer,LOW);
      }
      entered_password = "";  // Reset input after checking
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter Password:");
    } 
    else {  // Store digits in entered_password
      if (entered_password.length() < password_length) {
        entered_password += key_pressed;
        lcd.setCursor(entered_password.length(), 1);
        lcd.print('*');  // Show '*' instead of the actual number
        // lcd.setCursor(entered_password.length() - 1, 1);
        // lcd.print(key_pressed);  // Display the actual number
        Serial.println(entered_password);
      }
    }
  }
}
