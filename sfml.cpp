#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "sfml.h"
#include <stdio.h>
#define EXPORT 0
Klass *renderwinclass,*circleclass,*rectclass,*evclass,*colorclass;
void init(PltObject* rr)
{
    //Initialize classes
    renderwinclass = vm_allocKlass();
    renderwinclass->name = "RenderWindow";
    renderwinclass->members.emplace("__construct__",PltObjectFromMethod("__construct__",&RenderWindow__construct,renderwinclass));
    renderwinclass->members.emplace("clear",PltObjectFromMethod("clear",&RenderWindow__clear,renderwinclass));
    renderwinclass->members.emplace("draw",PltObjectFromMethod("draw",&RenderWindow__draw,renderwinclass));
    renderwinclass->members.emplace("display",PltObjectFromMethod("display",&RenderWindow__display,renderwinclass));
    renderwinclass->members.emplace("pollEvent",PltObjectFromMethod("pollEvent",&RenderWindow__pollevent,renderwinclass));
    renderwinclass->members.emplace("close",PltObjectFromMethod("close",&RenderWindow__close,renderwinclass));
    
    
    circleclass = vm_allocKlass();
    circleclass->name = "Circle";
    circleclass->members.emplace("__construct__",PltObjectFromMethod("__construct__",&Circle__construct,circleclass));
    circleclass->members.emplace("setPosition",PltObjectFromMethod("setPosition",&Circle__setpos,circleclass));
    circleclass->members.emplace("setFillColor",PltObjectFromMethod("setFillColor",&Circle__setfillcolor,circleclass));
    circleclass->members.emplace("setPointCount",PltObjectFromMethod("setPointCount",&Circle__setpointcount,circleclass));
    
    colorclass = vm_allocKlass();
    colorclass->name = "Color";
    colorclass->members.emplace("__construct__",PltObjectFromMethod("__construct__",&Color__construct,colorclass));

    /*Klass* rectclass = vm_allocKlass();
    rectclass->name = "Rectangle";
    rectclass->members.emplace("__construct__",PltObjectFromMethod("__construct__",&Rect__construct,rectclass));
    rectclass->members.emplace("setPosition",PltObjectFromMethod("setPosition",&Rect__setpos,rectclass));
    rectclass->members.emplace("setFillColor",PltObjectFromMethod("setFillColor",&Rect__setfillcolor,rectclass));
    */
    evclass = vm_allocKlass();
    evclass->name = "Event";
    evclass->members.emplace("__construct__",PltObjectFromMethod("__construct__",&Event__construct,evclass));
    evclass->members.emplace("type",PltObject());

    //Add classes to module
    Module* sfml = vm_allocModule();
    sfml->name = "sfml";
    sfml->members.emplace("RenderWindow",PltObjectFromKlass(renderwinclass));
    sfml->members.emplace("Circle",PltObjectFromKlass(circleclass));
    sfml->members.emplace("Color",PltObjectFromKlass(colorclass));
  //  sfml->members.emplace("Rectangle",PltObjectFromKlass(rectclass));
    sfml->members.emplace("Event",PltObjectFromKlass(evclass));
    sfml->members.emplace("EventClosed",PltObjectFromInt(sf::Event::Closed));

    *rr = PltObjectFromModule(sfml);
       
}
//RenderWindow
void RenderWindow__construct(PltObject* args,int n,PltObject* rr)
{
    if(n!=4)
    {
        *rr = Plt_Err(ARGUMENT_ERROR,"4 arguments needed!");
        return;
    }
    if(args[0].type!=PLT_OBJ && ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
    {
        *rr = Plt_Err(TYPE_ERROR,"self must be an instance of RenderWindow");
        return;
    }
    if(args[1].type!='i' || args[2].type!='i' || args[3].type!='s')
    {
        *rr = Plt_Err(TYPE_ERROR,"Invalid types of arguments!");
        return;
    }
    string& title = *((string*)args[3].ptr);
    sf::RenderWindow* w = new sf::RenderWindow(sf::VideoMode(args[1].i,args[2].i),title);
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    k->members.emplace(".handle",PltObjectFromPointer((void*)w)); //we use .handle so that user can't change it's value
    //constructors don't return anything
}
void RenderWindow__clear(PltObject* args,int n,PltObject* rr)
{
    if(n!=1)
    {
        *rr = Plt_Err(ARGUMENT_ERROR,"1 argument needed!");
        return;
    }
    if(args[0].type!=PLT_OBJ && ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
    {
        *rr = Plt_Err(TYPE_ERROR,"self must be an instance of RenderWindow");
        return;
    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RenderWindow* w = (sf::RenderWindow*)k->members[".handle"].ptr;
    w->clear();
}
void RenderWindow__close(PltObject* args,int n,PltObject* rr)
{
    if(n!=1)
    {
        *rr = Plt_Err(ARGUMENT_ERROR,"1 argument needed!");
        return;
    }
    if(args[0].type!=PLT_OBJ && ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
    {
        *rr = Plt_Err(TYPE_ERROR,"self must be an instance of RenderWindow");
        return;
    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RenderWindow* w = (sf::RenderWindow*)k->members[".handle"].ptr;
    w->close();
}
void RenderWindow__display(PltObject* args,int n,PltObject* rr)
{
    if(n!=1)
    {
        *rr = Plt_Err(ARGUMENT_ERROR,"1 argument needed!");
        return;
    }
    if(args[0].type!=PLT_OBJ && ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
    {
        *rr = Plt_Err(TYPE_ERROR,"self must be an instance of RenderWindow");
        return;
    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RenderWindow* w = (sf::RenderWindow*)k->members[".handle"].ptr;
    w->display();
}
void RenderWindow__draw(PltObject* args,int n,PltObject* rr)
{
    if(n!=2)
    {
        *rr = Plt_Err(ARGUMENT_ERROR,"2 arguments needed!");
        return;
    }
    if(args[0].type!=PLT_OBJ && ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
    {
        *rr = Plt_Err(TYPE_ERROR,"self must be an instance of RenderWindow");
        return;
    }
    if(args[1].type!=PLT_OBJ)
    {
        *rr = Plt_Err(TYPE_ERROR,"Argument must be a drawable sfml object!");
        return;
    }
    KlassInstance* obj = (KlassInstance*)args[1].ptr;
    if(obj->klass!=rectclass && obj->klass!=circleclass)
    {
        *rr = Plt_Err(TYPE_ERROR,"Argument must be a drawable sfml object!");
        return;
    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RenderWindow* w = (sf::RenderWindow*)k->members[".handle"].ptr;
    if(obj->klass==circleclass)
    {
        sf::CircleShape* d = (sf::CircleShape*)obj->members[".handle"].ptr; 
        w->draw(*d);
    }
    else if(obj->klass==rectclass)
    {
        sf::RectangleShape* d = (sf::RectangleShape*)obj->members[".handle"].ptr; 
        w->draw(*d);
    }
    
}
void RenderWindow__pollevent(PltObject* args,int n,PltObject* rr)
{
    if(n!=2)
    {
        *rr = Plt_Err(ARGUMENT_ERROR,"2 argument needed!");
        return;
    }
    if(args[0].type!=PLT_OBJ && ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
    {
        *rr = Plt_Err(TYPE_ERROR,"self must be an instance of RenderWindow");
        return;
    }
    if(args[1].type!=PLT_OBJ)
    {
        *rr = Plt_Err(TYPE_ERROR,"Argument must be an instance of Event class.");
        return;
    }
    KlassInstance* obj = (KlassInstance*)args[1].ptr;
    if(obj->klass!=evclass)
    {
        *rr = Plt_Err(TYPE_ERROR,"Argument must be an instance of Event class.");
        return;
    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RenderWindow* w = (sf::RenderWindow*)k->members[".handle"].ptr;
    sf::Event* e = (sf::Event*)obj->members[".handle"].ptr;
    obj->members["type"] = PltObjectFromInt(e->type);
    rr->type = PLT_BOOL;
    rr->i = w->pollEvent(*e);
    return;    
}
//Event
void Event__construct(PltObject* args,int n,PltObject* rr)
{
    if(n!=1 || args[0].type!=PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass!=evclass)
    {
      *rr = Plt_Err(ARGUMENT_ERROR,"1 argument self needed which must be instance of event");
      return;
    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::Event* e = new sf::Event;
    k->members.emplace(".handle",PltObjectFromPointer(e));
    return;
}
//Circle
void Circle__construct(PltObject* args,int n,PltObject* rr)
{
  if(n!=1 && n!=2)
  {
    *rr = Plt_Err(ARGUMENT_ERROR,"Two or One arguments needed!");
    return;
  }
  float radius = 0;
  if(args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass!=circleclass)
  {
    *rr = Plt_Err(TYPE_ERROR,"self must be an instance of circle class!");
    return;
  }
  if(n==2)
  {
    if(args[1].type!=PLT_FLOAT)
    {
        *rr = Plt_Err(TYPE_ERROR,"Radius must be a float!");
        return;
    }
    radius = static_cast<float>(args[1].f);
  }
  KlassInstance* k = (KlassInstance*)args[0].ptr;
  sf::CircleShape* c = new sf::CircleShape(radius);
  k->members.emplace(".handle",PltObjectFromPointer(c));
  return;
}
void Circle__setpos(PltObject* args,int n,PltObject* rr)
{
  if(n!=3)
  {
    *rr = Plt_Err(ARGUMENT_ERROR,"Three arguments needed!");
    return;
  }
  float radius = 0;
  if(args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass!=circleclass)
  {
    *rr = Plt_Err(TYPE_ERROR,"self must be an instance of circle class!");
    return;
  }
  if(args[1].type!=PLT_FLOAT || args[2].type!=PLT_FLOAT)
  {
    *rr = Plt_Err(TYPE_ERROR,"Position coordinates must be floats!");
    return;
  }

  KlassInstance* k = (KlassInstance*)args[0].ptr;
  sf::CircleShape* c = (sf::CircleShape*)k->members[".handle"].ptr;
  float x = (float)args[1].f;
  float y = (float)args[2].f;
  c->setPosition(x,y);
  return;
}
void Circle__setpointcount(PltObject* args,int n,PltObject* rr)
{
  if(n!=2)
  {
    *rr = Plt_Err(ARGUMENT_ERROR,"Two arguments needed!");
    return;
  }
  float radius = 0;
  if(args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass!=circleclass)
  {
    *rr = Plt_Err(TYPE_ERROR,"self must be an instance of circle class!");
    return;
  }
  if(args[1].type!=PLT_INT && args[1].type!=PLT_INT64)
  {
    *rr = Plt_Err(TYPE_ERROR,"Point count must be an integer!");
    return;
  }

  KlassInstance* k = (KlassInstance*)args[0].ptr;
  sf::CircleShape* c = (sf::CircleShape*)k->members[".handle"].ptr;
  if(args[1].type==PLT_INT)
    c->setPointCount(args[1].i);
  else
    c->setPointCount(args[1].l);
  return;
}
void Circle__setfillcolor(PltObject* args,int n,PltObject* rr)
{
  if(n!=2)
  {
    *rr = Plt_Err(ARGUMENT_ERROR,"Two arguments needed!");
    return;
  }
  if(args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass!=circleclass)
  {
    *rr = Plt_Err(TYPE_ERROR,"self must be an instance of circle class!");
    return;
  }
  if(args[1].type!=PLT_OBJ || ((KlassInstance*)args[1].ptr)->klass!=colorclass)
  {
    *rr = Plt_Err(TYPE_ERROR,"Color must an instance of class Color!");
    return;
  }

  KlassInstance* k = (KlassInstance*)args[0].ptr;
  KlassInstance* j = (KlassInstance*)args[1].ptr;
  sf::CircleShape* c = (sf::CircleShape*)k->members[".handle"].ptr;
  sf::Color* color = (sf::Color*)j->members[".handle"].ptr;
  c->setFillColor(*color);
  return;
}
//Color
void Color__construct(PltObject* args,int n,PltObject* rr)
{
  if(n!=4)
  {
    *rr = Plt_Err(ARGUMENT_ERROR,"4 arguments needed!");
    return;
  }
  if(args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass!=colorclass)
  {
    *rr = Plt_Err(TYPE_ERROR,"self must be an instance of Color class!");
    return;
  }
  if(args[1].type!=PLT_INT || args[2].type!=PLT_INT || args[3].type!=PLT_INT)
  {
    *rr = Plt_Err(TYPE_ERROR,"RGB values must be integers!");
    return;
  }
  KlassInstance* k = (KlassInstance*)args[0].ptr;
  sf::Color* c = new sf::Color(args[1].i,args[2].i,args[3].i);
  k->members.emplace(".handle",PltObjectFromPointer(c));
  return;
}
//Rectangle