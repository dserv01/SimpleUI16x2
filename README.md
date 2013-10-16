SimpleUI16x2
============

This library provides a simple User Interface for Input and Output with an 
16x2 Character Display and some Buttons. Some examples:
<pre>  
 ============================== A simple menu with some entries. You can navigate through
 | Titel                      | it using the Up and Down Keys. For selecting an entry use
 | > Entry                    | Right or Select Key. To abort, if you allow it, use the Left Key.
 ============================== The return will be 0-(N-1) for the entry or -1 for abort.

 ============================== A nice input in percents. Input in 1% steps using the up/down keys and 10%
 | Titel                      | using the left/right keys. You ca also set a function, which will be called
 | [==========       ]  63%   | every time something changes (for example you want to adjust the volume
 ============================== with an sound example every time the volume is changed).

 ============================== Fast Number Input with the arrow keys. With Up/Down you can add/substract
 | 2356                       | the Summand 10^N (1,10,100,...), which you can using Right/Left.
 |                &lt;+/-100&gt;    | With Select you submit the number.
 ==============================

 ============================== Simple String Input like those on Game Consoles. With only arrow-keys</br>
 | stringinput_               | you can't get a less worse option. The writing position blinks.</br>
 |                            |</br>
 ==============================</br>
 </pre>
 There are also some functions for Buttons. You have to set(constructor) the function for the buttons 
 yourself, since I don't know how to read your buttons. You will find an example for that.
 Maybe there are still some bugs, but the library is short and easy. You will have no problems fixing
 them by yourself.

 It only works with LiquidCrystal-Library-Displays, but you should have no problem to wrap any other
 display-library or change this library.

Please see also (german and english): 
http://www.dserv01.de/2013/10/einfaches-arduino-userinterface-mit-16x2-display/
