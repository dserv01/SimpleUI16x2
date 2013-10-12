#include "SimpleUI16x2.h"
#include "Arduino.h"


void SimpleUI16x2::write(char* text){
	write(0,0, text);
}

void SimpleUI16x2::write(char* text1, char* text2){
	write(0,0, text1);
	overwrite(1,0,text2);
}

void SimpleUI16x2::write(uint8_t row, short column, char* text){
	clear();
	overwrite(row,column, text);
}

void SimpleUI16x2::overwrite(uint8_t row, short column, char* text){
	lcd->setCursor(column, row);
	lcd->print(text);
}


void SimpleUI16x2::setBrightness(uint8_t brightness){
	this->brightness_=brightness;
	if(displayLightPin){
		pinMode(displayLightPin, OUTPUT);
		analogWrite(displayLightPin, brightness);
	}
}

void SimpleUI16x2::setDisplaylight(bool toOn){
	if(displayLightPin){
		if(toOn){
			analogWrite(displayLightPin, brightness_);
		} else {
			analogWrite(displayLightPin, 0);
		}
	}
}

void SimpleUI16x2::turnOff(){
	clear();
	setDisplaylight(false);
}


void SimpleUI16x2::clear(){
	lcd->clear();
}

int8_t SimpleUI16x2::showMenu(char* title, char** text, bool allow_abort, int8_t i){
	write(title);
	while(true){
		write(title, "> ");
		overwrite(1,2,text[i]);
		switch(waitButtonRelease()){
			case BUTTON_UP:
				if(i>0) i--;
				break;
			case BUTTON_DOWN:
				if(text[i+1]!=0) i++;
				break;
			case BUTTON_LEFT:
				if(allow_abort) return -1;
				break;
			case BUTTON_RIGHT:
			case BUTTON_SELECT:
				return i;
			default:
				break;
		}
	}
}
uint8_t SimpleUI16x2::toString(uint16_t input, char* buffer, uint8_t bufferSize){
	if(bufferSize<2) return 0;
	if(input==0){ buffer[0]='0',buffer[1]=0; return 1; }
	uint8_t n=0;
	while(input>0){
		n++;
		buffer[bufferSize-n]=48+input%10;
		input/=10;
		if(n==bufferSize) return 0;
	}
	for(uint8_t i=0; i<n; i++) buffer[i]=buffer[bufferSize-n+i];
	buffer[n]=0;
	return n;
}

uint16_t SimpleUI16x2::tenpot(uint8_t n){
	uint16_t rVal=1;
	for(;n>1;n--) rVal*=10;
	return rVal;
}
uint16_t SimpleUI16x2::getUInt(uint16_t def){
	uint16_t pos=1;
	uint16_t rVal=0;
	while(true){
		{
			char buffer[10];
			if(!toString(rVal,buffer,10)) write("ERROR");
			else{
				write(">");
				overwrite(0,1,buffer);
				toString(tenpot(pos),buffer,10);
				overwrite(1,11-pos,"<+/-");
				overwrite(1,15-pos,buffer);
				overwrite(1,15,">");
			}

		}
		switch(waitButtonRelease()){
			case BUTTON_LEFT:
				if(pos<8) pos++;
				break;
			case BUTTON_UP:
				if(rVal+tenpot(pos)>rVal) rVal+=tenpot(pos);
				else rVal=~0;
				break;
			case BUTTON_DOWN:
				if(tenpot(pos)<=rVal) rVal-=tenpot(pos);
				break;
			case BUTTON_RIGHT:
				if(pos>1) pos--;
				break;
			case BUTTON_SELECT:
				return rVal;
			default: 
				continue;
		}
	}

}

uint8_t SimpleUI16x2::getString(char* buffer, uint8_t maxLength, bool dontClearBuffer){
	if(!dontClearBuffer){ for(uint8_t i=0; i<maxLength; i++) buffer[i]=0;} //Clear Buffer with \0
	uint8_t pos=0;
	while(true){
		if(buffer[pos]==0) buffer[pos]=' ';
		//Display
		{
			uint8_t offset=pos/16;
			write(&buffer[offset*16]);

			lcd->setCursor(pos%16,0);
			lcd->cursor();
			lcd->blink();


		}
		//Interaction
		switch(waitButtonRelease()){
			case BUTTON_LEFT:
				if(pos>0) pos--;
				break;
			case BUTTON_UP:
				buffer[pos]++;
				switch(buffer[pos]){
					case ' '+1: 
						buffer[pos]='a';
						break;
					case '9'+1:
						buffer[pos]=' ';
						break;
					case 'z'+1:
						buffer[pos]='A';
						break;
					case 'Z'+1:
						buffer[pos]='0';
						break;
					default:
						break;
				}
				break;
			case BUTTON_DOWN:
				buffer[pos]--;
				switch(buffer[pos]){
					case ' '-1:
						buffer[pos]='9';
						break;
					case '0'-1:
						buffer[pos]='Z';
						break;
					case 'a'-1:
						buffer[pos]=' ';
						break;
					case 'A'-1:
						buffer[pos]='z';
						break;
					default:
						break;
				}
				break;
			case BUTTON_RIGHT:
				if(pos<maxLength-2) pos++;
				//if(pos==length){ buffer[pos]=' '; length++;}
				break;
			case BUTTON_SELECT:
				uint8_t length;
				for(length=maxLength-1; length>0; length--){
					if(buffer[length-1]==' ') buffer[length-1]=0;
					else break;
				}
				lcd->noCursor();
				lcd->noBlink();
				return length;
		}
	}
	return 0;

}

uint8_t SimpleUI16x2::getPercent(char* title, uint8_t def, void(*onChange)(uint8_t x)){
	if(def>100) def=100;
	while(true){
		//Print
		{
			write(title,"[          ]   %");
			char buffer[4];
			toString(def, buffer, 4);
			overwrite(1,12+(def!=100?1:0)+(def<10?1:0),buffer);
			for(uint8_t i=def/10; i>0; i--){
				overwrite(1,i,"=");
			}
		}
		switch(waitButtonRelease()){
			case BUTTON_LEFT:
				if(def<=10){ def=0; }
				else { def-=10; }
				break;
			case BUTTON_RIGHT:
				if(def>=90){ def=100; }
				else { def+=10; }
				break;
			case BUTTON_UP:
				if(def!=100) def++;
				break;
			case BUTTON_DOWN:
				if(def>0) def--;
				break;
			case BUTTON_SELECT:
				return def;
		}
		if(onChange!=0) onChange(def);
	}
}

uint8_t SimpleUI16x2::waitButton(){
	uint8_t rBtn=BUTTON_NONE;
	while((rBtn=getButton() )== BUTTON_NONE) delay(50);
	delay(100);
	return rBtn;
}
uint8_t SimpleUI16x2::waitButtonRelease(){
	uint8_t rBtn=waitButton();
	while(getButton()!=BUTTON_NONE) delay(10);
	return rBtn;
}

void SimpleUI16x2::sleep(void (*selectPressed)(), void (*leftPressed)(), void (*upPressed)(), void (*downPressed)(), void (*rightPressed)(), void (*serialInput)()){
	while(true){
		if(getButton()!=BUTTON_NONE){
			switch(waitButtonRelease()){
				case BUTTON_SELECT:
					if(selectPressed==0) break;
					selectPressed();
					return;
				case BUTTON_LEFT:
					if(leftPressed==0) break;
					leftPressed();
					return;
				case BUTTON_UP:
					if(upPressed==0) break;
					upPressed();
					return;
				case BUTTON_DOWN:
					if(downPressed==0) break;
					downPressed();
					return;
				case BUTTON_RIGHT:
					if(rightPressed==0) break;
					rightPressed();
					return;
				default:
					break;
			}
			if(serialInput!=0 && Serial.available()>0);
		}
		delay(50);
	}
}

