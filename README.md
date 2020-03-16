# Breakout SDL
The classic game of Breakout ported to modern systems using the [SDL](https://www.libsdl.org/index.php).

<img src="https://media3.giphy.com/media/U5OubI1BQAO3n87gMk/giphy.gif">

# Intro

Main purpose of this project was to get familiar with techniques such as :

* Creating a level via loading and using a tilemap
* Implementing a better collision system

# Overview

* The game supports one player and WASD movement of the paddle*

# Building in Linux

1) Grab the dependencies using the following commands in terminal : 
`sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev`
2) Clone the project's repository 
3) Open a terminal window inside the cloned folder
4) Use the following command : `make`
5) Run the executable : `./breakout`
