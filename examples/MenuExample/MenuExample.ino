#include <LiquidCrystal.h>
#include <SimpleUI16x2.h>

//CONFIGURATION/////////////////////////////////////////////
LiquidCrystal lcd(8,9,4,5,6,7);
SimpleUI16x2 simpleui(&lcd,getButton);

//The Button function you have to define by yourself
uint8_t getButton(){
	int adc_key_in = analogRead(0);
	if (adc_key_in > 790) return BUTTON_NONE;
	if (adc_key_in < 50) {
		return BUTTON_RIGHT;
	}
	if (adc_key_in < 195) {
		return BUTTON_UP;
	}
	if (adc_key_in < 380) {
		return BUTTON_DOWN;
	}
	if (adc_key_in < 555) {
		return BUTTON_LEFT; 
	}
	if (adc_key_in < 790) {
		return BUTTON_SELECT;  
	} 
	return BUTTON_NONE;
}
//////////////////////////////////////////////////////////////

void setup(){
  simpleui.write("Hello","World!");
  delay(1000);
  simpleui.write("Hold any button");
  simpleui.waitButton();
  simpleui.write("Release Button");
  simpleui.waitButtonRelease();
  simpleui.clear();
  delay(1000);
}

void loop(){
  char buffer[20];
  uint16_t i;
  char* menu[] = {"Input Number","Input String", "Input Precent", 0}; //last entry has to be 0
  switch(simpleui.showMenu("titel",menu)){
    case 0:
      i = simpleui.getUInt();
      simpleui.toString(i, buffer, 20);
      simpleui.write(buffer);
      simpleui.waitButton();
      break;
    case 1:     
      simpleui.getString(buffer,20);
      simpleui.write(buffer);
      simpleui.waitButton();
      break;
    case 2:
      uint8_t p = simpleui.getPercent("titel", 50, percentfunc);
      break;     
  }
}

void percentfunc(uint8_t p){
  if(p==42){
    simpleui.write("You reached 42");
    delay(1000);
  }
}



