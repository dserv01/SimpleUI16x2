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
		/** The Constructor. Used to configure the UI.
		 *  @param[in] lcd 					The LiquidCrystal Object, create with 'new LiquidCrystal(param)'. 
		 *  @param[in] getButton 			The function to read out the buttons, see examples and the 
		 *  								button-codes above
		 *  @param[in] display_light_pin 	If your display light is controlled with an pin, you can set it
		 *  								here. 0 means undefined.
		 */
		SimpleUI16x2(LiquidCrystal *lcd, uint8_t (*getButton)(), uint8_t disp_light_pin=0){
			this->displayLightPin=disp_light_pin;
			this->getButton=getButton;
			this->lcd=lcd;
			lcd->begin(16,2); //May be have to changed for some displays  which are not 16x2
			lcd->clear();
		}

		//@TODO accept more than strings.
		/** Easy Output with Autoclean
		 *  @param[in] text 	The Text to write
		 */
		void write(char* text);
		/** Easy Output with Autoclean
		 *  @param[in] text1 	Text for the first row
		 *  @param[in] text2 	Text for the second row
		 */
		void write(char* text1, char* text2);
		/** Easy Output with Autoclean
		 *  @param[in] row 		The row to write in. (0,1)
		 *  @param[in] column   The column to start. (0,...,16)
		 *  @param[in] text 	The text to write
		 *  @TODO Test if (0,1) and (0,...,16) are correct
		 */
		void write(uint8_t row, short column, char* text);

		//Output Modification (Write something into the old screen(=>No Autoclean))
		/** Write something on the old screen.
		 *  @param[in] row 		The row to write in. (0,1)
		 *  @param[in] column   The column to start. (0,...,16)
		 *  @param[in] text 	The text to write
		 */
		void overwrite(uint8_t row, short column, char* text);
		/** Clears the display but does not turn off the light.
		 */
		void clear();

		//Displaylight
		/** Modifies the display light by seting the PWM of the displaylight to brightness.
		 *  The DisplayLightPin has to be set.
		 *  @param[in] brightness 	The PWM-Value
		 */
		void setBrightness(uint8_t brightness);
		/** Turns the display light on or off
		 *  The DisplayLightPin has to be set
		 *  @param[in] toOn 	true->On, false->Off
		 */
		void setDisplaylight(bool toOn);
		/** Clears the display and turns off the light.
		 *  The DisplayLightPin has to be set to turn off the light
		 */
		void turnOff(); //Clears Displays and turn of light
		/** Returns the DisplayLight-PWM.
		 *  @return The value of brightness_
		 */
		uint8_t getBrightness(){ return brightness_;}

		
		
		/** Shows a menu in which you can navigate through using the UP and DOWN Keys. 
		 *  Select an Entry using the RIGHT or SELECT keys. Abort with LEFT, if allowed.
		 *  @param[in] title 		The Menu-Title
		 *  @param[in] text 		An Array with the Menu-Entries
		 *  @param[in] allow_abort 	Allows aborting with the LEFT key
		 *  @param[in] i 			The entry displayed first, normally the entry 0
		 *  @return The entry selected (0,...,n-1) or -1 if aborted
		 */
		int8_t showMenu(char* title, char** text, bool allow_abort=true, int8_t i=0);

		/** Creates a numberinput. The sumand, a decimal power, can be changed using the LEFT and RIGHT keys.
		 *  Add or substract the summand by using UP and DOWN. Finish with SELECT.
		 *  @param[in] def 	The value to start with
		 *  @bug does not work yet
		 *  @return The number input
		 */
		uint16_t getUInt(uint16_t def=0);

		/** Creates a string input (letters and numbers). Similar to game consoles.
		 *  Use LEFT and RIGHT to change the position. UP and DOWN to change the symbol. SELECT to finish.
		 *  @TODO allow to change the symbollist.
		 *  @param[in,out] buffer 		To be displayed and written in.
		 *  @bug doesnt work as expected if the buffer contains illegal symbols
		 *  @param[in] maxLenght 		The buffersize
		 *  @TODO I guess maxLength is not a good name for the buffersize
		 *  @param[in] dontClearBuffer 	If set to true(default) the buffer will be cleaned up.
		 */
		uint8_t getString(char* buffer, uint8_t maxLength, bool dontClearBuffer=false);

		/** Creates a input for percents. Use LEFT and RIGHT to make 10% steps, UP and DOWN for 1% steps.
		 *  A function can be called every time the value changes if you want to give the user an 
		 *  example(volume etc.)
		 *  @param[in] title 	The title of the input
		 *  @param[in] def 		The start-value
		 *  @param[in] onChange The function to be called on changes. 0 means undefined.
		 *  @return returns the value
		 */ 
		uint8_t getPercent(char* title, uint8_t def, void(*onChange)(uint8_t x)=0);

		/** Waits for a button or Serial-Input and calls the function. If the function is undefined (0) 
		 *  the button (or Serial) will be ignored. 
		 *  @TODO Create a option to autoloop.
		 *  @param[in] selectPressed 	Called if SELECT is pressed. 0 to ignore.
		 *  @param[in] leftPressed 		Called if LEFT is pressed. 0 to ignore.
		 *  @param[in] upPressed 		Called if UP is pressed. 0 to ignore.
		 *  @param[in] downPressed 		Called if DOWN is pressed. 0 to ignore.
		 *  @param[in] rightPressed 	Called if RIGHT is pressed. 0 to ignore.
		 *  @param[in] serialInput 		Called if Serial.isAvailable(). 0 to ignore.
		 */
		void sleep(void (*selectPressed)(), void (*leftPressed)(), void (*upPressed)(), void (*downPressed)(), void (*rightPressed)(), void (*serialInput)());//Waiting for an action

		/** Waits for a button to be pressed.
		 *  @return the code for the pressed Button.
		 *  @TODO debounce. I have an hardwaredebounce
		 */
		uint8_t waitButton();
		/** Waits for a button to be released. 
		 *  @return the released button.
		 *  @TODO debounce. I have an hardwaredebounce
		 */
		uint8_t waitButtonRelease();

		/** Writes a number as string into a buffer.
		 *  @param[in] input 		The number to be converted to string
		 *  @param[out] buffer 		The buffer to write in
		 *  @param[in] buffersize 	The size of the buffer.
		 *  @return The size of the buffer used.
		 */
		uint8_t toString(uint16_t input, char* buffer, uint8_t bufferSize);

	private:
		uint16_t tenpot(uint8_t n); //Zehnerpotenz
};
#endif
