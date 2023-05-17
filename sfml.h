#ifndef PLTSFML_H_
#define PLTSFML_H_
#include "PltObject.h"
extern "C"
{
    PltObject init();
    
    //RenderWindow methods
    PltObject RenderWindow__construct(PltObject*,int);
    PltObject RenderWindow__draw(PltObject*,int);
    PltObject RenderWindow__clear(PltObject*,int);
    PltObject RenderWindow__display(PltObject*,int);
    PltObject RenderWindow__pollevent(PltObject*,int);
    PltObject RenderWindow__close(PltObject*,int);

    //Circle Methods
    PltObject Circle__construct(PltObject*,int);
    PltObject Circle__setpointcount(PltObject*,int);
    PltObject Circle__setfillcolor(PltObject*,int);
    PltObject  Circle__setpos(PltObject*,int);
    PltObject Circle__del(PltObject*,int);
    //Color methods
    PltObject  Color__construct(PltObject*,int);
    PltObject Color__del(PltObject*,int);
    //Rectangle Methods
    PltObject  Rect__construct(PltObject*,int);
    PltObject  Rect__setfillcolor(PltObject*,int);
    PltObject  Rect__setpos(PltObject*,int);
    PltObject  Rect__del(PltObject*,int);
    //Event Methods
    PltObject  Event__construct(PltObject*,int);
    PltObject  Event__del(PltObject*,int);
}
#endif
