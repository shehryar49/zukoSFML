#ifndef PLTSFML_H_
#define PLTSFML_H_
#ifdef _WIN32
  #include "C:\\zuko\\ZObject.h"
  #define EXPORT __declspec(dllexport)
#else
  #include "/opt/zuko/ZObject.h"
  #define EXPORT
#endif

extern "C"
{
    EXPORT ZObject init();
    EXPORT ZObject getMousePosition(ZObject*, int);

    //RenderWindow methods
    EXPORT ZObject RenderWindow__construct(ZObject*, int);
    EXPORT ZObject RenderWindow__draw(ZObject*, int);
    EXPORT ZObject RenderWindow__clear(ZObject*, int);
    EXPORT ZObject RenderWindow__display(ZObject*, int);
    EXPORT ZObject RenderWindow__pollevent(ZObject*, int);
    EXPORT ZObject RenderWindow__setFrameRateLimit(ZObject*, int);
    EXPORT ZObject RenderWindow__close(ZObject*, int);

    //Circle Methods
    EXPORT ZObject Circle__construct(ZObject*, int);
    EXPORT ZObject Circle__setpointcount(ZObject*, int);
    EXPORT ZObject Circle__setfillcolor(ZObject*, int);
    EXPORT ZObject  Circle__setpos(ZObject*, int);
    EXPORT ZObject Circle__del(ZObject*, int);
    //Color methods
    EXPORT ZObject  Color__construct(ZObject*, int);
    EXPORT ZObject Color__del(ZObject*, int);
    //Rectangle Methods
    EXPORT ZObject  Rect__construct(ZObject*, int);
    EXPORT ZObject  Rect__setfillcolor(ZObject*, int);
    EXPORT ZObject  Rect__setOutlineColor(ZObject*, int);
    EXPORT ZObject  Rect__setOutlineThickness(ZObject*, int);
    EXPORT ZObject  Rect__setpos(ZObject*, int);
    EXPORT ZObject Rect__getPosition(ZObject*, int);
    EXPORT ZObject Rect__getGlobalBounds(ZObject*, int);
    EXPORT ZObject  Rect__setSize(ZObject*, int);
    EXPORT ZObject  Rect__del(ZObject*, int);
    //Event Methods
    EXPORT ZObject  Event__construct(ZObject*, int);
    EXPORT ZObject  Event__del(ZObject*, int);
    //Texture Methods
    EXPORT ZObject  Texture__construct(ZObject*, int);
    EXPORT ZObject  Texture__loadFromFile(ZObject*, int);
    EXPORT ZObject  Texture__del(ZObject*, int);
    //Sprite Methods
    EXPORT ZObject  Sprite__construct(ZObject*, int);
    EXPORT ZObject  Sprite__setTexture(ZObject*, int);
    EXPORT ZObject  Sprite__del(ZObject*, int);
    //Clock Methods
    EXPORT ZObject  Clock__construct(ZObject*, int);
    EXPORT ZObject  Clock__restart(ZObject*, int);
    EXPORT ZObject  Clock__del(ZObject*, int);
    //Time Methods
    EXPORT ZObject Time__asSeconds(ZObject*, int);
    EXPORT ZObject Time__del(ZObject*, int);
    //VertexArray Methods
    EXPORT ZObject  VertexArray__construct(ZObject*, int);
    EXPORT ZObject  VertexArray__setKth(ZObject*, int);
    EXPORT ZObject  VertexArray__resize(ZObject*, int);
    EXPORT ZObject  VertexArray__setPrimType(ZObject*, int);
    EXPORT ZObject  VertexArray__del(ZObject*, int);
    //Font Methods
    EXPORT ZObject  Font__construct(ZObject*, int);
    EXPORT ZObject  Font__loadFromFile(ZObject*, int);
    EXPORT ZObject  Font__del(ZObject*, int);
    //Text Methods
    EXPORT ZObject  Text__construct(ZObject*, int);
    EXPORT ZObject  Text__setString(ZObject*, int);
    EXPORT ZObject  Text__setPostion(ZObject*, int);
    EXPORT ZObject  Text__setCharacterSize(ZObject*, int);
    EXPORT ZObject  Text__setFont(ZObject*, int);
    EXPORT ZObject  Text__setFillColor(ZObject*, int);
    EXPORT ZObject  Text__del(ZObject*, int);
  
    //FloatRect Methods
    EXPORT ZObject FloatRect__intersects(ZObject*, int);
}
#endif
