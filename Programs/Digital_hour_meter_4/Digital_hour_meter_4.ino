#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif18pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int buttonPin = A0;
int buttonState;             
int lastButtonState = LOW;   

unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;
unsigned long write_count_patient;
unsigned long write_count_background;
unsigned long previous_seconds;
unsigned long previous_seconds_patient;
unsigned long previous_seconds_background;
unsigned long seconds_patient;
unsigned long seconds_reset;
unsigned long current_time_patient;
unsigned long current_time_background;
unsigned long val1 = 10000;
unsigned long val2 = 100000;
unsigned long val3 = 1000000;
unsigned long val4 = 10000000;
unsigned long val5 = 100000000;
unsigned long Hrs_start;
unsigned long Hrs_reset;
unsigned long Hrs_patient;

void setup() {
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){ 
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }
  
  pinMode(buttonPin,INPUT);
  
}

void loop() {
     
    byte address_LSB_patient = EEPROM.read(1021);
    byte address_ones_patient = address_LSB_patient%10;
    byte address_tens_patient = (address_LSB_patient/10)%10;
    
    byte address_MSB_patient = EEPROM.read(1020);
    byte address_hundreds_patient = address_MSB_patient%10;
    byte address_thousands_patient = (address_MSB_patient/10)%10;
    
    int next_cycle_address_patient = (address_ones_patient) + (address_tens_patient*10) + (address_hundreds_patient*100) + (address_thousands_patient*1000);
     
    int current_address_patient = (next_cycle_address_patient -= 16);
    
    byte address_byte_1_patient = EEPROM.read(current_address_patient);
    byte ones_1_patient = address_byte_1_patient%10;
    byte tens_1_patient = (address_byte_1_patient/10)%10;
    current_address_patient++;
    
    byte address_byte_2_patient = EEPROM.read(current_address_patient);
    byte ones_2_patient = address_byte_2_patient%10;
    byte tens_2_patient = (address_byte_2_patient/10)%10;
    current_address_patient++;
    
    byte address_byte_3_patient = EEPROM.read(current_address_patient);
    byte ones_3_patient = address_byte_3_patient%10;
    byte tens_3_patient = (address_byte_3_patient/10)%10;
    current_address_patient++; 
    
    byte address_byte_4_patient = EEPROM.read(current_address_patient);
    byte ones_4_patient = address_byte_4_patient%10;
    byte tens_4_patient = (address_byte_4_patient/10)%10;
    current_address_patient++;
    
    byte address_byte_5_patient = EEPROM.read(current_address_patient);
    byte ones_5_patient = address_byte_5_patient%10;
    current_address_patient++;
    
    previous_seconds_patient = (ones_1_patient) + (tens_1_patient*10) + (ones_2_patient*100) + (tens_2_patient*1000) + (ones_3_patient*val1) + (tens_3_patient*val2) + (ones_4_patient*val3) + (tens_4_patient*val4) + (ones_5_patient*val5);
    
    byte count_byte_1_patient = EEPROM.read(current_address_patient);
    byte WL_1_patient = count_byte_1_patient%10;
    byte WL_2_patient = (count_byte_1_patient/10)%10;
    current_address_patient++;
    
    byte count_byte_2_patient = EEPROM.read(current_address_patient);
    byte WL_3_patient = count_byte_2_patient%10;
    byte WL_4_patient = (count_byte_2_patient/10)%10;
    current_address_patient++;
    
    byte count_byte_3_patient = EEPROM.read(current_address_patient);
    byte WL_5_patient = count_byte_3_patient%10;
    
    write_count_patient = (WL_1_patient) + ((WL_2_patient)*(10)) + ((WL_3_patient)*(100)) + ((WL_4_patient)*(1000)) + ((WL_5_patient)*(val1));
    
      for(int a = 0; a < 60; a++){  
        
        for(int b = 0; b < 15; b++){
          
          int reading = digitalRead(buttonPin);
          
            if (reading != lastButtonState) {
              lastDebounceTime = millis();
            }
            
            if ((millis() - lastDebounceTime) > debounceDelay) {
  
              if (reading != buttonState) {
                buttonState = reading;
                
                if (buttonState == HIGH) {
                 
                 delay(400); 
                 int readings = digitalRead(buttonPin);
                 
                 if(readings == LOW){
                  byte address_LSB = EEPROM.read(1023);
                  byte address_ones = address_LSB%10;
                  byte address_tens = (address_LSB/10)%10;
                  
                  byte address_MSB = EEPROM.read(1022);
                  byte address_hundreds = address_MSB%10;
                  byte address_thousands = (address_MSB/10)%10;
                  
                  int next_cycle_address = (address_ones) + (address_tens*10) + (address_hundreds*100) + (address_thousands*1000);
                  
                  int current_address = (next_cycle_address -= 16);
                  
                  byte address_byte_1 = EEPROM.read(current_address);
                  byte ones_1 = address_byte_1%10;
                  byte tens_1 = (address_byte_1/10)%10;
                  current_address++;
                  
                  byte address_byte_2 = EEPROM.read(current_address);
                  byte ones_2 = address_byte_2%10;
                  byte tens_2 = (address_byte_2/10)%10;
                  current_address++;
                  
                  byte address_byte_3 = EEPROM.read(current_address);
                  byte ones_3 = address_byte_3%10;
                  byte tens_3 = (address_byte_3/10)%10;
                  current_address++; 
                  
                  byte address_byte_4 = EEPROM.read(current_address);
                  byte ones_4 = address_byte_4%10;
                  byte tens_4 = (address_byte_4/10)%10;
                  current_address++;
                  
                  byte address_byte_5 = EEPROM.read(current_address);
                  byte ones_5 = address_byte_5%10;
                  current_address++;
                  
                  previous_seconds = (ones_1) + (tens_1*10) + (ones_2*100) + (tens_2*1000) + (ones_3*val1) + (tens_3*val2) + (ones_4*val3) + (tens_4*val4) + (ones_5*val5);
                
                  byte Sec = previous_seconds % 60;
                  previous_seconds /= 60;              
                  byte Min = previous_seconds % 60;
                  previous_seconds /= 60;
                  Hrs_start = previous_seconds;
                  
                  if((Min < 10) && (Hrs_start < 10)){
                  display.clearDisplay();             
                  display.setTextColor(WHITE);
                  display.setFont(&FreeSerif9pt7b);
                  display.setCursor(4,15);             
                  display.print("Total User Time");
                  display.setFont(&FreeSerif12pt7b);
                  display.setCursor(4,46);
                  display.print("00000");             
                  display.print(Hrs_start);
                  display.print(':');
                  display.print("0");
                  display.print(Min);
                  display.display();
                  delay(2000);  
                  }
                  else if((Min < 10) && (Hrs_start < 100)){
                    display.clearDisplay();             
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(4,15);             
                    display.print("Total User Time");
                    display.setFont(&FreeSerif12pt7b);
                    display.setCursor(4,46);
                    display.print("0000");             
                    display.print(Hrs_start);
                    display.print(':');
                    display.print("0");
                    display.print(Min);
                    display.display();
                    delay(2000);
                  }
                  else if((Min < 10) && (Hrs_start < 1000)){
                    display.clearDisplay();             
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(4,15);             
                    display.print("Total User Time");
                    display.setFont(&FreeSerif12pt7b);
                    display.setCursor(4,46);
                    display.print("000");             
                    display.print(Hrs_start);
                    display.print(':');
                    display.print("0");
                    display.print(Min);
                    display.display();
                    delay(2000);
                  }
                  else if((Min < 10) && (Hrs_start < 10000)){
                    display.clearDisplay();             
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(4,15);             
                    display.print("Total User Time");
                    display.setFont(&FreeSerif12pt7b);
                    display.setCursor(4,46);
                    display.print("00");             
                    display.print(Hrs_start);
                    display.print(':');
                    display.print("0");
                    display.print(Min);
                    display.display();
                    delay(2000);
                  }
                  else if((Min < 10) && (Hrs_start < 100000)){
                    display.clearDisplay();             
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(4,15);             
                    display.print("Total User Time");
                    display.setFont(&FreeSerif12pt7b);
                    display.setCursor(4,46);
                    display.print("0");             
                    display.print(Hrs_start);
                    display.print(':');
                    display.print("0");
                    display.print(Min);
                    display.display();
                    delay(2000);
                  }
                  else if((Min < 10) && (Hrs_start < 1000000)){
                    display.clearDisplay();             
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(4,15);             
                    display.print("Total User Time");
                    display.setFont(&FreeSerif12pt7b);
                    display.setCursor(4,46);             
                    display.print(Hrs_start);
                    display.print(':');
                    display.print("0");
                    display.print(Min);
                    display.display();
                    delay(2000);
                  }
                  else if((Min >= 10) && (Hrs_start < 10)){
                  display.clearDisplay();             
                  display.setTextColor(WHITE);
                  display.setFont(&FreeSerif9pt7b);
                  display.setCursor(4,15);             
                  display.print("Total User Time");
                  display.setFont(&FreeSerif12pt7b);
                  display.setCursor(4,46);
                  display.print("00000");             
                  display.print(Hrs_start);
                  display.print(':');
                  display.print(Min);
                  display.display();
                  delay(2000);  
                  }
                  else if((Min >= 10) && (Hrs_start < 100)){
                    display.clearDisplay();             
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(4,15);             
                    display.print("Total User Time");
                    display.setFont(&FreeSerif12pt7b);
                    display.setCursor(4,46);
                    display.print("0000");             
                    display.print(Hrs_start);
                    display.print(':');
                    display.print(Min);
                    display.display();
                    delay(2000);
                  }
                  else if((Min >= 10) && (Hrs_start < 1000)){
                    display.clearDisplay();             
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(4,15);             
                    display.print("Total User Time");
                    display.setFont(&FreeSerif12pt7b);
                    display.setCursor(4,46);
                    display.print("000");             
                    display.print(Hrs_start);
                    display.print(':');
                    display.print(Min);
                    display.display();
                    delay(2000);
                  }
                  else if((Min >= 10) && (Hrs_start < 10000)){
                    display.clearDisplay();             
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(4,15);             
                    display.print("Total User Time");
                    display.setFont(&FreeSerif12pt7b);
                    display.setCursor(4,46);
                    display.print("00");             
                    display.print(Hrs_start);
                    display.print(':');
                    display.print(Min);
                    display.display();
                    delay(2000);
                  }
                  else if((Min >= 10) && (Hrs_start < 100000)){
                    display.clearDisplay();             
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(4,15);             
                    display.print("Total User Time");
                    display.setFont(&FreeSerif12pt7b);
                    display.setCursor(4,46);
                    display.print("0");             
                    display.print(Hrs_start);
                    display.print(':');
                    display.print(Min);
                    display.display();
                    delay(2000);
                  }
                  else if((Min >= 10) && (Hrs_start < 1000000)){
                    display.clearDisplay();             
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(4,15);             
                    display.print("Total User Time");
                    display.setFont(&FreeSerif12pt7b);
                    display.setCursor(4,46);             
                    display.print(Hrs_start);
                    display.print(':');
                    display.print(Min);
                    display.display();
                    delay(2000);
                  }
                 }
                 else{
                  
                  delay(1000); 
                  a = 0;
                  previous_seconds_patient = 0;
        
                  current_address_patient = (current_address_patient -= 7); 
                  write_count_patient = (write_count_patient += 8);
        
                  if(write_count_patient == 95000){
                  
                  current_address_patient = (current_address_patient += 16);
                    
                  byte address_LSBB_reset = EEPROM.read(1021);
                  byte address_oness_reset = address_LSBB_reset%10;
                  byte address_tenss_reset = (address_LSBB_reset/10)%10;
                  
                  byte address_MSBB_reset = EEPROM.read(1020);
                  byte address_hundredss_reset = address_MSBB_reset%10;
                  byte address_thousandss_reset = (address_MSBB_reset/10)%10;
                  
                  int next_cycle_addresss_reset = (address_oness_reset) + (address_tenss_reset*10) + (address_hundredss_reset*100) + (address_thousandss_reset*1000);
                  
                  next_cycle_addresss_reset = (next_cycle_addresss_reset += 16);
        
                  if(next_cycle_addresss_reset == 1032){
                    display.setFont(&FreeSerif18pt7b);
                    display.clearDisplay();             
                    display.setTextColor(WHITE);               
                    display.setCursor(0,40);             
                    display.print("Expired!");
                    display.display();
                    delay(val5); 
                  }
                  
                  byte oness_reset = next_cycle_addresss_reset%10;
                  byte tenss_reset = (next_cycle_addresss_reset/10)%10;
                  
                  byte address1_reset = (oness_reset) + (tenss_reset*10);
                  
                  EEPROM.write(1021,address1_reset);
                  
                  byte hundredss_reset = (next_cycle_addresss_reset/100)%10;
                  byte thousandss_reset = (next_cycle_addresss_reset/1000)%10;
                  
                  byte address2_reset = (hundredss_reset) + (thousandss_reset*10);
                  
                  EEPROM.write(1020,address2_reset);
                  
                  EEPROM.write(current_address_patient,0);
                  current_address_patient++;
                  EEPROM.write(current_address_patient,0);
                  current_address_patient++;
                  EEPROM.write(current_address_patient,0);
                  current_address_patient++;
                  EEPROM.write(current_address_patient,0);
                  current_address_patient++;
                  EEPROM.write(current_address_patient,0);
                  current_address_patient++;
                  EEPROM.write(current_address_patient,8);
                  current_address_patient++;
                  EEPROM.write(current_address_patient,0);
                  current_address_patient++;
                  EEPROM.write(current_address_patient,0);
                  
                  current_address_patient = (current_address_patient -= 23);
                  }
                
                
                EEPROM.write(current_address_patient,0);
                current_address_patient++;
                EEPROM.write(current_address_patient,0);
                current_address_patient++;
                EEPROM.write(current_address_patient,0);
                current_address_patient++;
                EEPROM.write(current_address_patient,0);
                current_address_patient++;
                EEPROM.write(current_address_patient,0);
                current_address_patient++;
                 
                byte onesss_reset = write_count_patient%10;
                byte tensss_reset = (write_count_patient/10)%10;
                byte hundredsss_reset = (write_count_patient/100)%10;
                byte thousandsss_reset = (write_count_patient/1000)%10;
                byte ten_thousandsss_reset = (write_count_patient/val1)%10;
                              
                byte lastt_reset = (onesss_reset) + (tensss_reset*10);
                byte second_lastt_reset = (hundredsss_reset) + (thousandsss_reset*10);
                byte third_lastt_reset = (ten_thousandsss_reset);
                
                EEPROM.write(current_address_patient,lastt_reset);
                current_address_patient++;
                EEPROM.write(current_address_patient,second_lastt_reset);
                current_address_patient++;
                EEPROM.write(current_address_patient,third_lastt_reset);
                
                seconds_reset = ((previous_seconds_patient*60) + a);
                byte Sec_reset = seconds_reset % 60;
                seconds_reset /= 60;              
                byte Min_reset = seconds_reset % 60;
                seconds_reset /= 60;
                Hrs_reset = seconds_reset;
  
                  if((Hrs_reset < 10) && (Min_reset < 10) && (Sec_reset < 10)){
                    display.clearDisplay();             
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(18,15);             
                    display.print("Patient Time");
                    display.setFont(&FreeSerif18pt7b);
                    display.setCursor(2,50);
                    display.print("0");              
                    display.print(Hrs_reset);
                    display.print(':');
                    display.print("0");
                    display.print(Min_reset);
                    display.print(':');
                    display.print("0");
                    display.print(Sec_reset);
                    display.display();
                    delay(1000); 
                  }
                  else if((Hrs_reset < 10) && (Min_reset < 10) && (Sec_reset >= 10)){             
                    display.clearDisplay();
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(18,15);             
                    display.print("Patient Time");
                    display.setFont(&FreeSerif18pt7b);
                    display.setCursor(2,50);
                    display.print("0");              
                    display.print(Hrs_reset);
                    display.print(':');
                    display.print("0");
                    display.print(Min_reset);
                    display.print(':');
                    display.print(Sec_reset);
                    display.display();
                    delay(1000); 
                  }
                  else if((Hrs_reset < 10) && (Min_reset >= 10) && (Sec_reset < 10)){
                    display.clearDisplay();             
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(18,15);             
                    display.print("Patient Time");
                    display.setFont(&FreeSerif18pt7b);
                    display.setCursor(2,50);
                    display.print("0");              
                    display.print(Hrs_reset);
                    display.print(':');
                    display.print(Min_reset);
                    display.print(':');
                    display.print("0");
                    display.print(Sec_reset);
                    display.display();
                    delay(1000); 
                  }
                  else if((Hrs_reset < 10) && (Min_reset >= 10) && (Sec_reset >= 10)){             
                    display.clearDisplay();
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(18,15);             
                    display.print("Patient Time");
                    display.setFont(&FreeSerif18pt7b);
                    display.setCursor(2,50);
                    display.print("0");              
                    display.print(Hrs_reset);
                    display.print(':');
                    display.print(Min_reset);
                    display.print(':');
                    display.print(Sec_reset);
                    display.display();
                    delay(1000); 
                  }
                  else if((Hrs_reset >= 10) && (Min_reset < 10) && (Sec_reset < 10)){             
                    display.clearDisplay();
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(18,15);             
                    display.print("Patient Time");
                    display.setFont(&FreeSerif18pt7b);
                    display.setCursor(2,50);              
                    display.print(Hrs_reset);
                    display.print(':');
                    display.print("0");
                    display.print(Min_reset);
                    display.print(':');
                    display.print("0");
                    display.print(Sec_reset);
                    display.display();
                    delay(1000); 
                  }
                  else if((Hrs_reset >= 10) && (Min_reset < 10) && (Sec_reset >= 10)){             
                    display.clearDisplay();
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(18,15);             
                    display.print("Patient Time");
                    display.setFont(&FreeSerif18pt7b);
                    display.setCursor(2,50);              
                    display.print(Hrs_reset);
                    display.print(':');
                    display.print("0");
                    display.print(Min_reset);
                    display.print(':');
                    display.print(Sec_reset);
                    display.display();
                    delay(1000); 
                  }
                  else if((Hrs_reset >= 10) && (Min_reset >= 10) && (Sec_reset < 10)){             
                    display.clearDisplay();
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(18,15);             
                    display.print("Patient Time");
                    display.setFont(&FreeSerif18pt7b);
                    display.setCursor(2,50);              
                    display.print(Hrs_reset);
                    display.print(':');
                    display.print(Min_reset);
                    display.print(':');
                    display.print("0");
                    display.print(Sec_reset);
                    display.display();
                    delay(1000); 
                  }
                  else if((Hrs_reset >= 10) && (Min_reset >= 10) && (Sec_reset >= 10)){             
                    display.clearDisplay();
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(18,15);             
                    display.print("Patient Time");
                    display.setFont(&FreeSerif18pt7b);
                    display.setCursor(2,50);             
                    display.print(Hrs_reset);
                    display.print(':');
                    display.print(Min_reset);
                    display.print(':');
                    display.print(Sec_reset);
                    display.display();
                    delay(1000); 
                  }
                       
                  }                
                }
              }
            }
  
          lastButtonState = reading;
          
          seconds_patient = ((previous_seconds_patient*60) + a);
          byte Sec_patient = seconds_patient % 60;
          seconds_patient /= 60;              
          byte Min_patient = seconds_patient % 60;
          seconds_patient /= 60;
          Hrs_patient = seconds_patient;
  
          
          if((Hrs_patient < 10) && (Min_patient < 10) && (Sec_patient < 10)){            
                    display.clearDisplay();
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(18,15);             
                    display.print("Patient Time");
                    display.setFont(&FreeSerif18pt7b);
                    display.setCursor(2,50);
                    display.print("0");              
                    display.print(Hrs_patient);
                    display.print(':');
                    display.print("0");
                    display.print(Min_patient);
                    display.print(':');
                    display.print("0");
                    display.print(Sec_patient);
                    display.display();
                    delay(10); 
                  }
                  else if((Hrs_patient < 10) && (Min_patient < 10) && (Sec_patient >= 10)){             
                    display.clearDisplay();
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(18,15);             
                    display.print("Patient Time");
                    display.setFont(&FreeSerif18pt7b);
                    display.setCursor(2,50);
                    display.print("0");              
                    display.print(Hrs_patient);
                    display.print(':');
                    display.print("0");
                    display.print(Min_patient);
                    display.print(':');
                    display.print(Sec_patient);
                    display.display();
                    delay(10); 
                  }
                  else if((Hrs_patient < 10) && (Min_patient >= 10) && (Sec_patient < 10)){             
                    display.clearDisplay();
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(18,15);             
                    display.print("Patient Time");
                    display.setFont(&FreeSerif18pt7b);
                    display.setCursor(2,50);
                    display.print("0");              
                    display.print(Hrs_patient);
                    display.print(':');
                    display.print(Min_patient);
                    display.print(':');
                    display.print("0");
                    display.print(Sec_patient);
                    display.display();
                    delay(10); 
                  }
                  else if((Hrs_patient < 10) && (Min_patient >= 10) && (Sec_patient >= 10)){            
                    display.clearDisplay();
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(18,15);             
                    display.print("Patient Time");
                    display.setFont(&FreeSerif18pt7b);
                    display.setCursor(2,50);
                    display.print("0");              
                    display.print(Hrs_patient);
                    display.print(':');
                    display.print(Min_patient);
                    display.print(':');
                    display.print(Sec_patient);
                    display.display();
                    delay(10); 
                  }
                  else if((Hrs_patient >= 10) && (Min_patient < 10) && (Sec_patient < 10)){             
                    display.clearDisplay();
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(18,15);             
                    display.print("Patient Time");
                    display.setFont(&FreeSerif18pt7b);
                    display.setCursor(2,50);              
                    display.print(Hrs_patient);
                    display.print(':');
                    display.print("0");
                    display.print(Min_patient);
                    display.print(':');
                    display.print("0");
                    display.print(Sec_patient);
                    display.display();
                    delay(10); 
                  }
                  else if((Hrs_patient >= 10) && (Min_patient < 10) && (Sec_patient >= 10)){            
                    display.clearDisplay();
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(18,15);             
                    display.print("Patient Time");
                    display.setFont(&FreeSerif18pt7b);
                    display.setCursor(2,50);              
                    display.print(Hrs_patient);
                    display.print(':');
                    display.print("0");
                    display.print(Min_patient);
                    display.print(':');
                    display.print(Sec_patient);
                    display.display();
                    delay(10); 
                  }
                  else if((Hrs_patient >= 10) && (Min_patient >= 10) && (Sec_patient < 10)){             
                    display.clearDisplay();
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(18,15);             
                    display.print("Patient Time");
                    display.setFont(&FreeSerif18pt7b);
                    display.setCursor(2,50);              
                    display.print(Hrs_patient);
                    display.print(':');
                    display.print(Min_patient);
                    display.print(':');
                    display.print("0");
                    display.print(Sec_patient);
                    display.display();
                    delay(10); 
                  }
                  else if((Hrs_patient >= 10) && (Min_patient >= 10) && (Sec_patient >= 10)){             
                    display.clearDisplay();
                    display.setTextColor(WHITE);
                    display.setFont(&FreeSerif9pt7b);
                    display.setCursor(18,15);             
                    display.print("Patient Time");
                    display.setFont(&FreeSerif18pt7b);
                    display.setCursor(2,50);             
                    display.print(Hrs_patient);
                    display.print(':');
                    display.print(Min_patient);
                    display.print(':');
                    display.print(Sec_patient);
                    display.display();
                    delay(10); 
                  }
               delay(1);
            }     
      
      }
      
    current_time_patient = previous_seconds_patient + 1; 
    byte ones_patient = current_time_patient%10;
    byte tens_patient = (current_time_patient/10)%10;
    byte hundreds_patient = (current_time_patient/100)%10;
    byte thousands_patient = (current_time_patient/1000)%10;
    byte ten_thousands_patient = (current_time_patient/val1)%10;
    byte lakh_patient = (current_time_patient/val2)%10;
    byte ten_lakh_patient = (current_time_patient/val3)%10;
    byte crore_patient = (current_time_patient/val4)%10;
    byte ten_crore_patient = (current_time_patient/val5)%10;
    
    byte last_patient = (ones_patient) + (tens_patient*10);
    byte second_last_patient = (hundreds_patient) + (thousands_patient*10);
    byte third_last_patient = (ten_thousands_patient) + (lakh_patient*10);
    byte fourth_last_patient = (ten_lakh_patient) + (crore_patient*10);
    byte fifth_last_patient = (ten_crore_patient);
    
    current_address_patient = (current_address_patient -= 7); 
    write_count_patient = (write_count_patient += 8);
    
      if(write_count_patient == 95000){
      
      current_address_patient = (current_address_patient += 16);
        
      byte address_LSBB_patient = EEPROM.read(1021);
      byte address_oness_patient = address_LSBB_patient%10;
      byte address_tenss_patient = (address_LSBB_patient/10)%10;
      
      byte address_MSBB_patient = EEPROM.read(1020);
      byte address_hundredss_patient = address_MSBB_patient%10;
      byte address_thousandss_patient = (address_MSBB_patient/10)%10;
      
      int next_cycle_addresss_patient = (address_oness_patient) + (address_tenss_patient*10) + (address_hundredss_patient*100) + (address_thousandss_patient*1000);
      
      next_cycle_addresss_patient = (next_cycle_addresss_patient += 16);

      if(next_cycle_addresss_patient == 1032){
        display.setFont(&FreeSerif18pt7b);
        display.clearDisplay();             
        display.setTextColor(WHITE);               
        display.setCursor(0,40);             
        display.print("Expired!");
        display.display();
        delay(val5);      
          }
      
      byte oness_patient = next_cycle_addresss_patient%10;
      byte tenss_patient = (next_cycle_addresss_patient/10)%10;
      
      byte address1_patient = (oness_patient) + (tenss_patient*10);
      
      EEPROM.write(1021,address1_patient);
      
      byte hundredss_patient = (next_cycle_addresss_patient/100)%10;
      byte thousandss_patient = (next_cycle_addresss_patient/1000)%10;
      
      byte address2_patient = (hundredss_patient) + (thousandss_patient*10);
      
      EEPROM.write(1020,address2_patient);
      
      EEPROM.write(current_address_patient,last_patient);
      current_address_patient++;
      EEPROM.write(current_address_patient,second_last_patient);
      current_address_patient++;
      EEPROM.write(current_address_patient,third_last_patient);
      current_address_patient++;
      EEPROM.write(current_address_patient,fourth_last_patient);
      current_address_patient++;
      EEPROM.write(current_address_patient,fifth_last_patient);
      current_address_patient++;
      EEPROM.write(current_address_patient,8);
      current_address_patient++;
      EEPROM.write(current_address_patient,0);
      current_address_patient++;
      EEPROM.write(current_address_patient,0);
      
      current_address_patient = (current_address_patient -= 23);
      }
        
    EEPROM.write(current_address_patient,last_patient);
    current_address_patient++;
    EEPROM.write(current_address_patient,second_last_patient);
    current_address_patient++;
    EEPROM.write(current_address_patient,third_last_patient);
    current_address_patient++;
    EEPROM.write(current_address_patient,fourth_last_patient);
    current_address_patient++;
    EEPROM.write(current_address_patient,fifth_last_patient);
    current_address_patient++;
     
    byte onesss_patient = write_count_patient%10;
    byte tensss_patient = (write_count_patient/10)%10;
    byte hundredsss_patient = (write_count_patient/100)%10;
    byte thousandsss_patient = (write_count_patient/1000)%10;
    byte ten_thousandsss_patient = (write_count_patient/val1)%10;
        
    byte lastt_patient = (onesss_patient) + (tensss_patient*10);
    byte second_lastt_patient = (hundredsss_patient) + (thousandsss_patient*10);
    byte third_lastt_patient = (ten_thousandsss_patient);
    
    EEPROM.write(current_address_patient,lastt_patient);
    current_address_patient++;
    EEPROM.write(current_address_patient,second_lastt_patient);
    current_address_patient++;
    EEPROM.write(current_address_patient,third_lastt_patient);

// Background recorder

      byte address_LSB_background = EEPROM.read(1023);
      byte address_ones_background = address_LSB_background%10;
      byte address_tens_background = (address_LSB_background/10)%10;
      
      byte address_MSB_background = EEPROM.read(1022);
      byte address_hundreds_background = address_MSB_background%10;
      byte address_thousands_background = (address_MSB_background/10)%10;
      
      int next_cycle_address_background = (address_ones_background) + (address_tens_background*10) + (address_hundreds_background*100) + (address_thousands_background*1000);
      
      int current_address_background = (next_cycle_address_background -= 16);
      
      byte address_byte_1_background = EEPROM.read(current_address_background);
      byte ones_1_background = address_byte_1_background%10;
      byte tens_1_background = (address_byte_1_background/10)%10;
      current_address_background++;
      
      byte address_byte_2_background = EEPROM.read(current_address_background);
      byte ones_2_background = address_byte_2_background%10;
      byte tens_2_background = (address_byte_2_background/10)%10;
      current_address_background++;
      
      byte address_byte_3_background = EEPROM.read(current_address_background);
      byte ones_3_background = address_byte_3_background%10;
      byte tens_3_background = (address_byte_3_background/10)%10;
      current_address_background++; 
      
      byte address_byte_4_background = EEPROM.read(current_address_background);
      byte ones_4_background = address_byte_4_background%10;
      byte tens_4_background = (address_byte_4_background/10)%10;
      current_address_background++;
      
      byte address_byte_5_background = EEPROM.read(current_address_background);
      byte ones_5_background = address_byte_5_background%10;
      current_address_background++;
      
      previous_seconds_background = (ones_1_background) + (tens_1_background*10) + (ones_2_background*100) + (tens_2_background*1000) + (ones_3_background*val1) + (tens_3_background*val2) + (ones_4_background*val3) + (tens_4_background*val4) + (ones_5_background*val5);

      byte count_byte_1_background = EEPROM.read(current_address_background);
      byte WL_1_background = count_byte_1_background%10;
      byte WL_2_background = (count_byte_1_background/10)%10;
      current_address_background++;
      
      byte count_byte_2_background = EEPROM.read(current_address_background);
      byte WL_3_background = count_byte_2_background%10;
      byte WL_4_background = (count_byte_2_background/10)%10;
      current_address_background++;
      
      byte count_byte_3_background = EEPROM.read(current_address_background);
      byte WL_5_background = count_byte_3_background%10;
      
      write_count_background = (WL_1_background) + (WL_2_background*10) + (WL_3_background*100) + (WL_4_background*1000) + (WL_5_background*val1);
      
      current_time_background = previous_seconds_background + 60;
            
      byte ones_background = current_time_background%10;
      byte tens_background = (current_time_background/10)%10;
      byte hundreds_background = (current_time_background/100)%10;
      byte thousands_background = (current_time_background/1000)%10;
      byte ten_thousands_background = (current_time_background/val1)%10;
      byte lakh_background = (current_time_background/val2)%10;
      byte ten_lakh_background = (current_time_background/val3)%10;
      byte crore_background = (current_time_background/val4)%10;
      byte ten_crore_background = (current_time_background/val5)%10;
      
      byte last_background = (ones_background) + (tens_background*10);
      byte second_last_background = (hundreds_background) + (thousands_background*10);
      byte third_last_background = (ten_thousands_background) + (lakh_background*10);
      byte fourth_last_background = (ten_lakh_background) + (crore_background*10);
      byte fifth_last_background = (ten_crore_background);
      
      current_address_background = (current_address_background -= 7); 
      write_count_background = (write_count_background += 8);
      
      if(write_count_background == 95000){
      
      current_address_background = (current_address_background += 16);
      
      byte address_LSBB_background = EEPROM.read(1023);
      byte address_oness_background = address_LSBB_background%10;
      byte address_tenss_background = (address_LSBB_background/10)%10;
      
      byte address_MSBB_background = EEPROM.read(1022);
      byte address_hundredss_background = address_MSBB_background%10;
      byte address_thousandss_background = (address_MSBB_background/10)%10;
      
      int next_cycle_addresss_background = (address_oness_background) + (address_tenss_background*10) + (address_hundredss_background*100) + (address_thousandss_background*1000);
      
      next_cycle_addresss_background = (next_cycle_addresss_background += 16);

      if(next_cycle_addresss_background == 1024){
        display.setFont(&FreeSerif18pt7b);
        display.clearDisplay();             
        display.setTextColor(WHITE);               
        display.setCursor(0,40);             
        display.print("Expired!");
        display.display();
        delay(val5);            
          }
      
      byte oness_background = next_cycle_addresss_background%10;
      byte tenss_background = (next_cycle_addresss_background/10)%10;
      
      byte address1_background = (oness_background) + (tenss_background*10);
      
      EEPROM.write(1023,address1_background);
      
      byte hundredss_background = (next_cycle_addresss_background/100)%10;
      byte thousandss_background = (next_cycle_addresss_background/1000)%10;
      
      byte address2_background = (hundredss_background) + (thousandss_background*10);
      
      EEPROM.write(1022,address2_background);
      
      EEPROM.write(current_address_background,last_background);
      current_address_background++;
      EEPROM.write(current_address_background,second_last_background);
      current_address_background++;
      EEPROM.write(current_address_background,third_last_background);
      current_address_background++;
      EEPROM.write(current_address_background,fourth_last_background);
      current_address_background++;
      EEPROM.write(current_address_background,fifth_last_background);
      current_address_background++;
      EEPROM.write(current_address_background,8);
      current_address_background++;
      EEPROM.write(current_address_background,0);
      current_address_background++;
      EEPROM.write(current_address_background,0);
      
      current_address_background = (current_address_background -= 23);
      }
            
      EEPROM.write(current_address_background,last_background);
      current_address_background++;
      EEPROM.write(current_address_background,second_last_background);
      current_address_background++;
      EEPROM.write(current_address_background,third_last_background);
      current_address_background++;
      EEPROM.write(current_address_background,fourth_last_background);
      current_address_background++;
      EEPROM.write(current_address_background,fifth_last_background);
      current_address_background++;
      
      byte onesss_background = write_count_background%10;
      byte tensss_background = (write_count_background/10)%10;
      byte hundredsss_background = (write_count_background/100)%10;
      byte thousandsss_background = (write_count_background/1000)%10;
      byte ten_thousandsss_background = (write_count_background/val1)%10;
      
      
      byte lastt_background = (onesss_background) + (tensss_background*10);
      byte second_lastt_background = (hundredsss_background) + (thousandsss_background*10);
      byte third_lastt_background = (ten_thousandsss_background);
      
      EEPROM.write(current_address_background,lastt_background);
      current_address_background++;
      EEPROM.write(current_address_background,second_lastt_background);
      current_address_background++;
      EEPROM.write(current_address_background,third_lastt_background);
    
}
