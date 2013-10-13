SimpleUI16x2
============

A simple UserInterface-Libary for Arduino with an 16x2-Display


This library provides a simple User Interface for Input and Output with an 
16x2 Character Display and some Buttons. Some examples:
  
 ============================== A simple menu with some entries. You can navigate through</br>
 | Titel                      | it using the Up and Down Keys. For selecting an entry use</br>
 | > Entry                    | Right or Select Key. To abort, if you allow it, use the Left Key. </br>
 ============================== The return will be 0-(N-1) for the entry or -1 for abort.</br>

 ============================== A nice input in percents. Input in 1% steps using the up/down keys and 10%</br>
 | Titel                      | using the left/right keys. You ca also set a function, which will be called</br>
 | [==========       ]  63%   | every time something changes (for example you want to adjust the volume </br>
 ============================== with an sound example every time the volume is changed).</br>

 ============================== Fast Number Input with the arrow keys. With Up/Down you can add/substract</br>
 | 2356                       | the Summand 10^N (1,10,100,...), which you can using Right/Left.</br>
 |                <+/-100>    | With Select you submit the number.</br>
 ==============================</br>

 ============================== Simple String Input like those on Game Consoles. With only arrow-keys</br>
 | stringinput                | you can't get a less worse option. The writing position blinks.</br>
 |                            |</br>
 ==============================</br>
 
 There are also some functions for Buttons. You have to set(constructor) the function for the buttons 
 yourself, since I don't know how to read your buttons. You will find an example for that.
 Maybe there are still some bugs, but the library is short and easy. You will have no problems fixing
 them by yourself.

 It only works with LiquidCrystal-Library-Displays, but you should have no problem to wrap any other
 display-library or change this library.


