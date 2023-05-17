#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "sfml.h"
#include <stdio.h>
#define EXPORT 0
Klass *renderwinclass,*circleclass,*rectclass,*evclass,*colorclass;
PltObject nil;
PltObject init()
{
    nil.type = PLT_NIL;
    //Initialize classes
    renderwinclass = vm_allocKlass();
    renderwinclass->name = "RenderWindow";
    renderwinclass->members.emplace("__construct__",PObjFromMethod("__construct__",&RenderWindow__construct,renderwinclass));
    renderwinclass->members.emplace("clear",PObjFromMethod("clear",&RenderWindow__clear,renderwinclass));
    renderwinclass->members.emplace("draw",PObjFromMethod("draw",&RenderWindow__draw,renderwinclass));
    renderwinclass->members.emplace("display",PObjFromMethod("display",&RenderWindow__display,renderwinclass));
    renderwinclass->members.emplace("pollEvent",PObjFromMethod("pollEvent",&RenderWindow__pollevent,renderwinclass));
    renderwinclass->members.emplace("close",PObjFromMethod("close",&RenderWindow__close,renderwinclass));
    
    circleclass = vm_allocKlass();
    circleclass->name = "Circle";
    circleclass->members.emplace("__construct__",PObjFromMethod("__construct__",&Circle__construct,circleclass));
    circleclass->members.emplace("setPosition",PObjFromMethod("setPosition",&Circle__setpos,circleclass));
    circleclass->members.emplace("setFillColor",PObjFromMethod("setFillColor",&Circle__setfillcolor,circleclass));
    circleclass->members.emplace("setPointCount",PObjFromMethod("setPointCount",&Circle__setpointcount,circleclass));
    circleclass->members.emplace("__del__",PObjFromMethod("__del__",&Circle__del,circleclass));
    colorclass = vm_allocKlass();
    colorclass->name = "Color";
    colorclass->members.emplace("__construct__",PObjFromMethod("__construct__",&Color__construct,colorclass));
    colorclass->members.emplace("__del__",PObjFromMethod("__del__",&Color__del,colorclass));
    /*Klass* rectclass = vm_allocKlass();
    rectclass->name = "Rectangle";
    rectclass->members.emplace("__construct__",PObjFromMethod("__construct__",&Rect__construct,rectclass));
    rectclass->members.emplace("setPosition",PObjFromMethod("setPosition",&Rect__setpos,rectclass));
    rectclass->members.emplace("setFillColor",PObjFromMethod("setFillColor",&Rect__setfillcolor,rectclass));
    */
    evclass = vm_allocKlass();
    evclass->name = "Event";
    evclass->members.emplace("__construct__",PObjFromMethod("__construct__",&Event__construct,evclass));
    evclass->members.emplace("__del__",PObjFromMethod("__del__",&Event__del,evclass));
    evclass->members.emplace("type",nil);

    //Add classes to module
    Module* sfml = vm_allocModule();
    sfml->name = "sfml";
    sfml->members.emplace("RenderWindow",PObjFromKlass(renderwinclass));
    sfml->members.emplace("Circle",PObjFromKlass(circleclass));
    sfml->members.emplace("Color",PObjFromKlass(colorclass));
  //  sfml->members.emplace("Rectangle",PObjFromKlass(rectclass));
    sfml->members.emplace("Event",PObjFromKlass(evclass));
    sfml->members.emplace("EventClosed",PObjFromInt(sf::Event::Closed));

    return PObjFromModule(sfml);
       
}
//RenderWindow
PltObject RenderWindow__construct(PltObject* args,int n)
{
    if(n!=4)
        return Plt_Err(ARGUMENT_ERROR,"4 arguments needed!");
    if(args[0].type!=PLT_OBJ && ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
        return Plt_Err(TYPE_ERROR,"self must be an instance of RenderWindow");
    if(args[1].type!='i' || args[2].type!='i' || args[3].type!='s')
        return Plt_Err(TYPE_ERROR,"Invalid types of arguments!");
    string& title = *((string*)args[3].ptr);
    sf::RenderWindow* w = new sf::RenderWindow(sf::VideoMode(args[1].i,args[2].i),title);
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    k->members.emplace(".handle",PObjFromPtr((void*)w)); //we use .handle so that user can't change it's value
    //constructors don't return anything
}
PltObject RenderWindow__clear(PltObject* args,int n)
{
    if(n!=1)
    {
        return Plt_Err(ARGUMENT_ERROR,"1 argument needed!");
        
    }
    if(args[0].type!=PLT_OBJ && ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
    {
        return Plt_Err(TYPE_ERROR,"self must be an instance of RenderWindow");
        
    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RenderWindow* w = (sf::RenderWindow*)k->members[".handle"].ptr;
    w->clear();
}
PltObject RenderWindow__close(PltObject* args,int n)
{
    if(n!=1)
        return Plt_Err(ARGUMENT_ERROR,"1 argument needed!");
    if(args[0].type!=PLT_OBJ && ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
        return Plt_Err(TYPE_ERROR,"self must be an instance of RenderWindow");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RenderWindow* w = (sf::RenderWindow*)k->members[".handle"].ptr;
    w->close();
    delete w;
    k->members[".handle"] = nil;
}
PltObject RenderWindow__display(PltObject* args,int n)
{
    if(n!=1)
    {
        return Plt_Err(ARGUMENT_ERROR,"1 argument needed!");
        
    }
    if(args[0].type!=PLT_OBJ && ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
    {
        return Plt_Err(TYPE_ERROR,"self must be an instance of RenderWindow");
        
    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RenderWindow* w = (sf::RenderWindow*)k->members[".handle"].ptr;
    w->display();
}
PltObject RenderWindow__draw(PltObject* args,int n)
{
    if(n!=2)
    {
        return Plt_Err(ARGUMENT_ERROR,"2 arguments needed!");
        
    }
    if(args[0].type!=PLT_OBJ && ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
    {
        return Plt_Err(TYPE_ERROR,"self must be an instance of RenderWindow");
        
    }
    if(args[1].type!=PLT_OBJ)
    {
        return Plt_Err(TYPE_ERROR,"Argument must be a drawable sfml object!");
        
    }
    KlassInstance* obj = (KlassInstance*)args[1].ptr;
    if(obj->klass!=rectclass && obj->klass!=circleclass)
    {
        return Plt_Err(TYPE_ERROR,"Argument must be a drawable sfml object!");
        
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
PltObject RenderWindow__pollevent(PltObject* args,int n)
{
    if(n!=2)
    {
        return Plt_Err(ARGUMENT_ERROR,"2 argument needed!");
        
    }
    if(args[0].type!=PLT_OBJ && ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
    {
        return Plt_Err(TYPE_ERROR,"self must be an instance of RenderWindow");
        
    }
    if(args[1].type!=PLT_OBJ)
    {
        return Plt_Err(TYPE_ERROR,"Argument must be an instance of Event class.");
        
    }
    KlassInstance* obj = (KlassInstance*)args[1].ptr;
    if(obj->klass!=evclass)
    {
        return Plt_Err(TYPE_ERROR,"Argument must be an instance of Event class.");
        
    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RenderWindow* w = (sf::RenderWindow*)k->members[".handle"].ptr;
    sf::Event* e = (sf::Event*)obj->members[".handle"].ptr;
    bool b = w->pollEvent(*e);
    if(b)
      obj->members["type"] = PObjFromInt(e->type);
    return PObjFromBool( b );
        
}

//Event
PltObject Event__construct(PltObject* args,int n)
{
    if(n!=1 || args[0].type!=PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass!=evclass)
    {
      return Plt_Err(ARGUMENT_ERROR,"1 argument self needed which must be instance of event");
      
    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::Event* e = new sf::Event;
    k->members.emplace(".handle",PObjFromPtr(e));
    
}
PltObject Event__del(PltObject* args,int n)
{
  if(n != 1)
    return nil;
  if(args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != evclass)
    return nil;
  KlassInstance* ki = (KlassInstance*)args[0].ptr;
  if(ki->members[".handle"].type == PLT_NIL)
    return nil;
  sf::Event* ev = (sf::Event*)ki->members[".handle"].ptr;
  delete ev;
  ki->members[".handle"] = nil;
  return nil;
}
//Circle
PltObject Circle__construct(PltObject* args,int n)
{
  if(n!=1 && n!=2)
  {
    return Plt_Err(ARGUMENT_ERROR,"Two or One arguments needed!");
    
  }
  float radius = 0;
  if(args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass!=circleclass)
  {
    return Plt_Err(TYPE_ERROR,"self must be an instance of circle class!");
    
  }
  if(n==2)
  {
    if(args[1].type!=PLT_FLOAT)
    {
        return Plt_Err(TYPE_ERROR,"Radius must be a float!");
        
    }
    radius = static_cast<float>(args[1].f);
  }
  KlassInstance* k = (KlassInstance*)args[0].ptr;
  sf::CircleShape* c = new sf::CircleShape(radius);
  k->members.emplace(".handle",PObjFromPtr(c));
  
}
PltObject Circle__setpos(PltObject* args,int n)
{
  if(n!=3)
  {
    return Plt_Err(ARGUMENT_ERROR,"Three arguments needed!");
    
  }
  float radius = 0;
  if(args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass!=circleclass)
  {
    return Plt_Err(TYPE_ERROR,"self must be an instance of circle class!");
    
  }
  if(args[1].type!=PLT_FLOAT || args[2].type!=PLT_FLOAT)
  {
    return Plt_Err(TYPE_ERROR,"Position coordinates must be floats!");
    
  }

  KlassInstance* k = (KlassInstance*)args[0].ptr;
  sf::CircleShape* c = (sf::CircleShape*)k->members[".handle"].ptr;
  float x = (float)args[1].f;
  float y = (float)args[2].f;
  c->setPosition(x,y);
  
}
PltObject Circle__setpointcount(PltObject* args,int n)
{
  if(n!=2)
  {
    return Plt_Err(ARGUMENT_ERROR,"Two arguments needed!");
    
  }
  float radius = 0;
  if(args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass!=circleclass)
  {
    return Plt_Err(TYPE_ERROR,"self must be an instance of circle class!");
    
  }
  if(args[1].type!=PLT_INT && args[1].type!=PLT_INT64)
  {
    return Plt_Err(TYPE_ERROR,"Point count must be an integer!");
    
  }

  KlassInstance* k = (KlassInstance*)args[0].ptr;
  sf::CircleShape* c = (sf::CircleShape*)k->members[".handle"].ptr;
  if(args[1].type==PLT_INT)
    c->setPointCount(args[1].i);
  else
    c->setPointCount(args[1].l);
  
}
PltObject Circle__setfillcolor(PltObject* args,int n)
{
  if(n!=2)
    return Plt_Err(ARGUMENT_ERROR,"Two arguments needed!");
  if(args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass!=circleclass)
    return Plt_Err(TYPE_ERROR,"Argument 1(self) must be an instance of circle class!");
  if(args[1].type!=PLT_OBJ || ((KlassInstance*)args[1].ptr)->klass!=colorclass)
    return Plt_Err(TYPE_ERROR,"Argument 2 must be an instance of class Color!");
  KlassInstance* k = (KlassInstance*)args[0].ptr;
  KlassInstance* j = (KlassInstance*)args[1].ptr;
  sf::CircleShape* c = (sf::CircleShape*)k->members[".handle"].ptr;
  sf::Color* color = (sf::Color*)j->members[".handle"].ptr;
  c->setFillColor(*color);
  
}
PltObject Circle__del(PltObject* args,int n)
{
  if(n != 1)
    return nil;
  if(args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != circleclass)
    return nil;
  KlassInstance* ki = (KlassInstance*)args[0].ptr;
  if(ki->members[".handle"].type == PLT_NIL)
    return nil;
  sf::CircleShape* circle = (sf::CircleShape*)ki->members[".handle"].ptr;
  delete circle;
  ki->members[".handle"] = nil;
  return nil;
}
//Color
PltObject Color__construct(PltObject* args,int n)
{
  if(n!=4)
  {
    return Plt_Err(ARGUMENT_ERROR,"4 arguments needed!");
    
  }
  if(args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass!=colorclass)
  {
    return Plt_Err(TYPE_ERROR,"self must be an instance of Color class!");
    
  }
  if(args[1].type!=PLT_INT || args[2].type!=PLT_INT || args[3].type!=PLT_INT)
  {
    return Plt_Err(TYPE_ERROR,"RGB values must be integers!");
    
  }
  KlassInstance* k = (KlassInstance*)args[0].ptr;
  sf::Color* c = new sf::Color(args[1].i,args[2].i,args[3].i);
  k->members.emplace(".handle",PObjFromPtr(c));
  
}
PltObject Color__del(PltObject* args,int n)
{
  if(n != 1)
    return nil;
  if(args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != colorclass)
    return nil;
  KlassInstance* ki = (KlassInstance*)args[0].ptr;
  if(ki->members[".handle"].type == PLT_NIL)
    return nil;
  sf::Color* color = (sf::Color*)ki->members[".handle"].ptr;
  delete color;
  ki->members[".handle"] = nil;
  return nil;
}
//Rectangle
