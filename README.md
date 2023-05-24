# pltSFML
SFML binding for Plutonium Programming Language

This is a sfml module for plutonium programming language.


# HOW TO COMPILE
-----------------
 Compile as a shared library on linux or dll on Windows
 
 ## For linux Use command: 
 
   ```g++ -shared sfml.cpp -o sfml.so -lsfml-graphics-s -lsfml-system-s -lsfml-window-s -fPIC```
   
   or don't link statically it's your choice
 ## For Windows:
   Create a dll project and add sfml.h and sfml.cpp as sources to this project. Make sure all functions are exported
   correctly using __declspec(dllexport)
   
   Link sfml libraries to the project,compile and enjoy :)
   
   
 You need to copy the resultant shared library or DLL to plutonium's modules folder(C:\plutonium\modules for Windows
  and /opt/plutonium/modules for Linux)
 
 # Naming Conventions
 | C++   | Plutonium |
 | ----- | --------- |
 |sf::RenderWindow|sfml.RenderWindow|
 |sf::Color|sfml.Color|
 |sf::Event|sfml.Event|
 |sf::Circle|sfml.Circle|
 |sf::Event::Closed| sfml.EventClosed|
 |sf::Keyboard::A|sfml.KeyboardA|
 
