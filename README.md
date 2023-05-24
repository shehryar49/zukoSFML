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
 # Classes
 The module provides following classes:
 - RenderWindow
   - __consturct__(width,height,title)
   - display()
   - clear(color = Black)
   - pollEvent(eventObject)
   - draw(drawableObj)
   - close
   - setFramerateLimit(x)
 - Event
   - __construct__()
   - type
   - __del__
   - Other members are added to object(based on the type of event) when you pollEvent
 - Circle
   - __construct__(radius)
   - setPosition(x,y)
   - setFillColor(color)
   - setPointCount(n)
   - __del__()
 - Rectangle
   - __construct__(width,height)
   - setSize(width,height)
   - setPosition(x,y)
   - setFillColor(color)
   - setOutlineColor(color)
   - setOutlineThickness(x)
   - getPosition()
   - getGlobalBounds()
   - __del__()
 - VertexArray
   - __construct__()
   - resize(n)
   - setPrimitiveType(type)
   - setKth(x,y)
   - __del__()
 - Sprite
   - __construct__()
   - setTexture(texture)
   - __del__()
 - Texture
   - __construct__()
   - loadFromFile(filename)
   - __del__()
 - Font
   - __construct__()
   - loadFromFile(filename)
   - __del__()
 - Text
   - __construct__()
   - setFont(font)
   - setCharacterSize(n)
   - setPosition(x,y)
   - setString(str)
   - setFillColor(color)
   - __del__()
 - Vector2f
   - x
   - y
 - Clock
   - __construct__()
   - restart()
   - __del__()
 - Time
   - asSeconds()
 # Naming Conventions
 | C++   | Plutonium |
 | ----- | --------- |
 |sf::RenderWindow|sfml.RenderWindow|
 |sf::Color|sfml.Color|
 |sf::Event|sfml.Event|
 |sf::Circle|sfml.Circle|
 |sf::Event::Closed| sfml.EventClosed|
 |sf::Keyboard::A|sfml.KeyboardA|
 
