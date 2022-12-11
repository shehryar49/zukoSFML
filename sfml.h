#ifndef PLTSFML_H_
#define PLTSFML_H_
#include "../include/PltObject.h"
extern "C"
{
    void init(PltObject*);
    
    //RenderWindow methods
    void RenderWindow__construct(PltObject*,int,PltObject*);
    void RenderWindow__draw(PltObject*,int,PltObject*);
    void RenderWindow__clear(PltObject*,int,PltObject*);
    void RenderWindow__display(PltObject*,int,PltObject*);
    void RenderWindow__pollevent(PltObject*,int,PltObject*);
    void RenderWindow__close(PltObject*,int,PltObject*);
    
    //Circle Methods
    void Circle__construct(PltObject*,int,PltObject*);
    void Circle__setpointcount(PltObject*,int,PltObject*);
    void Circle__setfillcolor(PltObject*,int,PltObject*);
    void Circle__setpos(PltObject*,int,PltObject*);
    
    //Color methods
    void Color__construct(PltObject*,int,PltObject*);

    //Rectangle Methods
    void Rect__construct(PltObject*,int,PltObject*);
    void Rect__setfillcolor(PltObject*,int,PltObject*);
    void Rect__setpos(PltObject*,int,PltObject*);

    //Event Methods
    void Event__construct(PltObject*,int,PltObject*);

}
#endif