#include <EEPROM.h>

void setup() {
  
int i, j;

//Serial.begin(115200);

//Start up pgm

for(int i = 0; i<1021; i++){
 EEPROM.write(i,0);
}

EEPROM.write(1021,24);
EEPROM.write(1022,0);
EEPROM.write(1023,16);

//for(int i = 0; i<1024; i++){
// Serial.println(EEPROM.read(i));
//}

}

void loop() {
  
}
