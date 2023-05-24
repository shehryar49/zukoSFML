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
   - \_\_consturct\_\_(width,height,title)
   - display()
   - clear(color = Black)
   - pollEvent(eventObject)
   - draw(drawableObj)
   - close
   - setFramerateLimit(x)
 - Event
   - \_\_construct\_\_()
   - type
   - \_\_del\_\_()
   - Other members are added to object(based on the type of event) when you pollEvent
 - Circle
   - \_\_construct\_\_(radius)
   - setPosition(x,y)
   - setFillColor(color)
   - setPointCount(n)
   - \_\_del\_\_()
 - Rectangle
   - \_\_construct\_\_(width,height)
   - setSize(width,height)
   - setPosition(x,y)
   - setFillColor(color)
   - setOutlineColor(color)
   - setOutlineThickness(x)
   - getPosition()
   - getGlobalBounds()
   - \_\_del\_\_()
 - VertexArray
   - \_\_construct\_\_()
   - resize(n)
   - setPrimitiveType(type)
   - setKth(x,y)
   - \_\_del\_\_()
 - Sprite
   - \_\_construct\_\_()
   - setTexture(texture)
   - \_\_del\_\_()
 - Texture
   - \_\_construct\_\_()
   - loadFromFile(filename)
   - \_\_del\_\_()
 - Font
   - \_\_construct\_\_()
   - loadFromFile(filename)
   - \_\_del\_\_()
 - Text
   - \_\_construct\_\_()
   - setFont(font)
   - setCharacterSize(n)
   - setPosition(x,y)
   - setString(str)
   - setFillColor(color)
   - \_\_del\_\_()
 - Vector2f
   - x
   - y
 - Clock
   - \_\_construct\_\_()
   - restart()
   - \_\_del\_\_()
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
 
