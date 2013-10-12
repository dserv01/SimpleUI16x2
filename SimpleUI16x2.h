/**
 * This library provides a simple User Interface for Input and Output with an 
 * 16x2 Character Display and some Buttons. Some examples:
 * 
 * ============================== A simple menu with some entries. You can navigate through
 * | Titel                      | it using the Up and Down Keys. For selecting an entry use
 * | > Entry                    | Right or Select Key. To abort, if you allow it, use the Left Key. 
 * ============================== The return will be 0-(N-1) for the entry or -1 for abort.
 *
 * ============================== A nice input in percents. Input in 1% steps using the up/down keys and 10%
 * | Titel                      | using the left/right keys. You ca also set a function, which will be called
 * | [==========       ]  63%   | every time something changes (for example you want to adjust the volume 
 * ============================== with an sound example every time the volume is changed).
 *
 * ============================== Fast Number Input with the arrow keys. With Up/Down you can add/substract
 * | 2356                       | the Summand 10^N (1,10,100,...), which you can using Right/Left.
 * |                <+/-100>    | With Select you submit the number.
 * ==============================
 *
 * ============================== Simple String Input like those on Game Consoles. With only arrow-keys
 * | stringinput_               | you can't get a less worse option. The writing position blinks.
 * |                            |
 * ==============================
 * 
 * There are also some functions for Buttons. You have to set(constructor) the function for the buttons 
 * yourself, since I don't know how to read your buttons. You will find an example for that.
 * Maybe there are still some bugs, but the library is short and easy. You will have no problems fixing
 * them by yourself.
 *
 * It only works with LiquidCrystal-Library-Displays, but you should have no problem to wrap any other
 * display-library or change this library.
 *
 */


#ifndef SIMPLEUI16x2.H
#define SIMPLEUI16x2.H

/**
 * Use this codes for your button-function return.
 */
#define BUTTON_RIGHT  0
#define BUTTON_UP     1
#define BUTTON_DOWN   2
#define BUTTON_LEFT   3
#define BUTTON_SELECT 4
#define BUTTON_NONE   5



#include "Arduino.h"
#include "LiquidCrystal.h"
class SimpleUI16x2 {
	private:
		LiquidCrystal *lcd; //The display to write on. Set in the constructor
		uint8_t (*getButton)(); //The function to get the pressed key. Set in the constructor
		uint8_t displayLightPin; //The pin to control the display-light. Set in the constructor
		uint8_t brightness_=100; //The display brightness, if setable
	public:
		/**
		 * lcd: The LiquidCrystal Object, create with 'new LiquidCrystal(param)'. 
		 * getButton: the function to read out the buttons, see examples and the button-codes above
		 * display_light_pin if your display light is controlled with an pin, you can set it here
		 */
		SimpleUI16x2(LiquidCrystal *lcd, uint8_t (*getButton)(), uint8_t disp_light_pin=0){
			this->displayLightPin=disp_light_pin;
			this->getButton=getButton;
			this->lcd=lcd;
			lcd->begin(16,2); //May be have to changed for some displays  which are not 16x2
			lcd->clear();
		}

		//Easy Output with Autoclean
		void write(char* text);
		void write(char* text1, char* text2);
		void write(uint8_t row, short column, char* text);

		//Output Modification (Write something into the old screen(=>No Autoclean))
		void overwrite(uint8_t row, short column, char* text);
		void clear();

		//Displaylight
		void setBrightness(uint8_t brightness);
		void setDisplaylight(bool toOn);
		void turnOff(); //Clears Displays and turn of light
		uint8_t getBrightness(){ return brightness_;}

		//UI (HighUI)
		int8_t showMenu(char* title,char** text, bool allow_abort=true, int8_t i=0);
		uint16_t getUInt(uint16_t def=0);
		uint8_t getString(char* buffer, uint8_t maxLength, bool dontClearBuffer=false);
		uint8_t getPercent(char* title, uint8_t def, void(*onChange)(uint8_t x));
		void sleep(void (*selectPressed)(), void (*leftPressed)(), void (*upPressed)(), void (*downPressed)(), void (*rightPressed)(), void (*serialInput)());//Waiting for an action

		//ButtonInput (LowUI)
		uint8_t waitButton();
		uint8_t waitButtonRelease();

		//HelpFunctions
		uint8_t toString(uint16_t input, char* buffer, uint8_t bufferSize);

	private:
		uint16_t tenpot(uint8_t n); //Zehnerpotenz
};
#endif
