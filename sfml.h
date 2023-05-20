#ifndef PLTSFML_H_
#define PLTSFML_H_
#include "C:\\plutonium\\PltObject.h"
#define EXPORT __declspec(dllexport)
extern "C"
{
    EXPORT PltObject init();
    EXPORT PltObject getMousePosition(PltObject*, int);

    //RenderWindow methods
    EXPORT PltObject RenderWindow__construct(PltObject*, int);
    EXPORT PltObject RenderWindow__draw(PltObject*, int);
    EXPORT PltObject RenderWindow__clear(PltObject*, int);
    EXPORT PltObject RenderWindow__display(PltObject*, int);
    EXPORT PltObject RenderWindow__pollevent(PltObject*, int);
    EXPORT PltObject RenderWindow__setFrameRateLimit(PltObject*, int);
    EXPORT PltObject RenderWindow__close(PltObject*, int);

    //Circle Methods
    EXPORT PltObject Circle__construct(PltObject*, int);
    EXPORT PltObject Circle__setpointcount(PltObject*, int);
    EXPORT PltObject Circle__setfillcolor(PltObject*, int);
    EXPORT PltObject  Circle__setpos(PltObject*, int);
    EXPORT PltObject Circle__del(PltObject*, int);
    //Color methods
    EXPORT PltObject  Color__construct(PltObject*, int);
    EXPORT PltObject Color__del(PltObject*, int);
    //Rectangle Methods
    EXPORT PltObject  Rect__construct(PltObject*, int);
    EXPORT PltObject  Rect__setfillcolor(PltObject*, int);
    EXPORT PltObject  Rect__setOutlineColor(PltObject*, int);
    EXPORT PltObject  Rect__setOutlineThickness(PltObject*, int);
    EXPORT PltObject  Rect__setpos(PltObject*, int);
    EXPORT PltObject Rect__getPosition(PltObject*, int);
    EXPORT PltObject Rect__getGlobalBounds(PltObject*, int);
    EXPORT PltObject  Rect__setSize(PltObject*, int);
    EXPORT PltObject  Rect__del(PltObject*, int);
    //Event Methods
    EXPORT PltObject  Event__construct(PltObject*, int);
    EXPORT PltObject  Event__del(PltObject*, int);
    //Texture Methods
    EXPORT PltObject  Texture__construct(PltObject*, int);
    EXPORT PltObject  Texture__loadFromFile(PltObject*, int);
    EXPORT PltObject  Texture__del(PltObject*, int);
    //Sprite Methods
    EXPORT PltObject  Sprite__construct(PltObject*, int);
    EXPORT PltObject  Sprite__setTexture(PltObject*, int);
    EXPORT PltObject  Sprite__del(PltObject*, int);
    //Clock Methods
    EXPORT PltObject  Clock__construct(PltObject*, int);
    EXPORT PltObject  Clock__restart(PltObject*, int);
    EXPORT PltObject  Clock__del(PltObject*, int);
    //Time Methods
    EXPORT PltObject Time__asSeconds(PltObject*, int);
    EXPORT PltObject Time__del(PltObject*, int);
    //VertexArray Methods
    EXPORT PltObject  VertexArray__construct(PltObject*, int);
    EXPORT PltObject  VertexArray__setKth(PltObject*, int);
    EXPORT PltObject  VertexArray__resize(PltObject*, int);
    EXPORT PltObject  VertexArray__setPrimType(PltObject*, int);
    EXPORT PltObject  VertexArray__del(PltObject*, int);
    //Font Methods
    EXPORT PltObject  Font__construct(PltObject*, int);
    EXPORT PltObject  Font__loadFromFile(PltObject*, int);
    EXPORT PltObject  Font__del(PltObject*, int);
    //Text Methods
    EXPORT PltObject  Text__construct(PltObject*, int);
    EXPORT PltObject  Text__setString(PltObject*, int);
    EXPORT PltObject  Text__setPostion(PltObject*, int);
    EXPORT PltObject  Text__setCharacterSize(PltObject*, int);
    EXPORT PltObject  Text__setFont(PltObject*, int);
    EXPORT PltObject  Text__setFillColor(PltObject*, int);
    EXPORT PltObject  Text__del(PltObject*, int);
  
    //FloatRect Methods
    EXPORT PltObject FloatRect__intersects(PltObject*, int);
}
#endif