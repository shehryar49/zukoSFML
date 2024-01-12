# zukoSFML
SFML binding for Zuko Programming Language

This is a sfml module for zuko programming language.
# INSTALLATION
  Use fiza package manager to install this module. Zuko must be already installed.
  ## Windows
    cd C:\zuko
    zuko fiza.zk install sfml
  
  ## Linux
  Make sure you have libsfml-dev installed before running the following command.
    
    fiza instll sfml

# HOW TO COMPILE
-----------------
 If you want to compile from source(perhaps to contribute or test) then run cmake directly.
 Note: You must install zuko first on your system.
 
   ```cmake . -DCMAKE_BUILD_TYPE=Release```
 You need to copy the resultant shared library or DLL to zuko's modules folder(C:\zuko\modules for Windows
  and /opt/zuko/modules for Linux)
 # Classes
 The module provides following classes:
 - RenderWindow
   - \_\_consturct\_\_(width,height,title)
   - display()
   - clear(color = Black)
   - pollEvent(eventObject)
   - draw(drawableObj)
   - close()
   - setFramerateLimit(x)
 - Event
   - \_\_construct\_\_()
   - type
   - \_\_del\_\_()
   - Other members are added to object(based on the type of event) when you pollEvent
 - Color
   - \_\_construct\_\_(r,g,b)
   - \_\_del\_\_()
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
 - FloatRect
   - width
   - height
   - top
   - left
   - intersects(FloatRectObj)
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
 
