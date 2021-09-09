# pltSFML
SFML binding for Plutonium Programming Language

This is a sfml module for plutonium programming language.

Note: This module is not complete.It includes very basic things like windows,events,circles,rectangles,colors and rotation.

HOW TO COMPILE
-----------------
 Compile as a shared library
 
 Use command: 
   g++ -shared sfml.cpp -o sfml.dll -lsfml-graphics-s -lsfml-system-s -lfsml-window-s -lwinmm -lopengl32
 Then copy the sfml.so to plutonium's modules folder
 
