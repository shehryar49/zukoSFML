#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "PltObject.h"
#define EXPORT __declspec(dllexport)

int TypeMistmatch(string pattern,PltArgs args)
{
  int k = 0;
  for(int k=0;k<pattern.length();k+=1)
  {
    if(pattern[k]!=args[k].type)
      return k;//argument number k is causing a type mismatch
  }
  return -1;//all good
}


std::unordered_map<void*,string> objects;
extern "C"
{
    // Methods
    EXPORT PltObject isOpen(PltObject&,PltArgs);
    EXPORT PltObject eventType(PltObject&,PltArgs);
    EXPORT PltObject display(PltObject&,PltArgs);
    EXPORT PltObject clear(PltObject&,PltArgs);
    EXPORT PltObject draw(PltObject&,PltArgs);
    EXPORT PltObject keyCodeFromEvent(PltObject&,PltArgs);
    EXPORT PltObject pollEvent(PltObject&,PltArgs);
    EXPORT PltObject close(PltObject&,PltArgs);
    EXPORT PltObject setFillColor(PltObject&,PltArgs);
    EXPORT PltObject setPointCount(PltObject&,PltArgs);
    EXPORT PltObject setPosition(PltObject&,PltArgs);
    EXPORT PltObject setOrigin(PltObject&,PltArgs);
    EXPORT PltObject rotate(PltObject&,PltArgs);

    EXPORT PltObject RenderWindow(PltArgs args)
    {
        if(args.size()!=3)
        {
           return Plt_Err(VALUE_ERROR,"Three arguments needed!");
        }
        int k = TypeMistmatch("iis",args);
        if( (k!=-1))
        {
          return Plt_Err(TYPE_ERROR,"Error invalid type of argument "+to_string(k+1));
        }
        int width = args[0].i;
        int height = args[1].i;
        string title = args[1+1].s;
        sf::RenderWindow* w = new sf::RenderWindow(sf::VideoMode(width,height),title);
        NativeObject obj;
        obj.ptr = (void*)w;
        obj.attr.emplace((string)"internalType",(string)"sfRenderWindow");
        obj.attr.emplace((string)"close",&close);
        obj.attr.emplace((string)"isOpen",&isOpen);
        obj.attr.emplace((string)"draw",&draw);
        obj.attr.emplace((string)"display",&display);
        obj.attr.emplace((string)"pollEvent",&pollEvent);
        obj.attr.emplace((string)"clear",&clear);
        PltObject ret = obj;
        return ret;
    }
   EXPORT PltObject isOpen(PltObject& self,PltArgs args)
{
    if(args.size()!=0)
      return Plt_Err(VALUE_ERROR,"Zero argument needed!");
    NativeObject* p = (NativeObject*)self.ptr;
    sf::RenderWindow* w = (sf::RenderWindow*)p->ptr;
    PltObject ret;
    ret.type = 'b';
    ret.i =(bool) w->isOpen();
    return ret;
}
EXPORT PltObject display(PltObject& self,PltArgs args)
{
    if(args.size()!=0)
      return Plt_Err(VALUE_ERROR,"Zero arguments needed!");
    NativeObject* p = (NativeObject*)self.ptr;
    PltObject iType = p->attr[(string)"internalType"];
    sf::RenderWindow* w = (sf::RenderWindow*) p->ptr;
    PltObject ret;
    w->display();
    return ret;
}
EXPORT PltObject Event(PltArgs args)
{
  //Create a new event object and return it
  if(args.size()!=0)
    return Plt_Err(VALUE_ERROR,"Zero arguments needed!");
  sf::Event* e = new sf::Event;
  NativeObject obj;
  obj.ptr = (void*)e;
  obj.attr.emplace((string)"internalType",(string)"sfEvent");
  obj.attr.emplace((string)"keycode",(Method)&keyCodeFromEvent);
  obj.attr.emplace((string)"type",(Method)&eventType);
  PltObject ret = obj;
  objects.emplace((void*)e,"sfEvent");
  return ret;
}
EXPORT PltObject pollEvent(PltObject& self,PltArgs args)
{
//  printf("polling event\n");
  if(args.size()!=1)
    return Plt_Err(VALUE_ERROR,"one argument needed!");
  if(args[0].type!='c')
    return Plt_Err(TYPE_ERROR,"Error invalid type of argument 1");
  NativeObject* p = (NativeObject*)args[0].ptr;
  PltObject iType = p->attr[(string)"internalType"];
  if(iType.s!="sfEvent")
    return Plt_Err(UNKNOWN_ERROR,"Error need an object of type sfEvent but got "+iType.s);
  NativeObject* A = (NativeObject*)self.ptr;

  sf::RenderWindow* w = (sf::RenderWindow*)A->ptr;
  sf::Event* e = (sf::Event*)p->ptr;
  PltObject ret;
  ret .i = w->pollEvent(*e);
  ret.type = 'b';
  return ret;
}
EXPORT PltObject eventType(PltObject& self,PltArgs args)
{
  if(args.size()!=0)
    return Plt_Err(VALUE_ERROR,"Zero arguments needed!");
  NativeObject* p = (NativeObject*)self.ptr;
  sf::Event e = *(sf::Event*)p->ptr;
  PltObject ret;
  ret.type = 'i';
  ret.i = e.type;
  return ret;
}
EXPORT PltObject keyCodeFromEvent(PltObject& self,PltArgs args)
{
    if(args.size()!=0)
      return Plt_Err(VALUE_ERROR,"Zero arguments needed!");
    NativeObject* p = (NativeObject*)self.ptr;
    sf::Event e = *(sf::Event*)p->ptr;
    PltObject ret;
    ret.type ='i';
    ret.i = e.key.code;
    return ret;
}
EXPORT PltObject Circle(PltArgs args)
{
    if(args.size()==1)
    {
      if(args[0].type!='i')
        return Plt_Err(TYPE_ERROR,"Error integer argument needed!");
      sf::CircleShape* shape = new sf::CircleShape(args[0].i);
      NativeObject obj;
      obj.ptr = (void*)shape;
      obj.attr.emplace((string)"internalType",(string)"sfCircle");
      obj.attr.emplace((string)"setPointCount",&setPointCount);
      obj.attr.emplace((string)"setFillColor",&setFillColor);
      obj.attr.emplace((string)"setPosition",&setPosition);
      obj.attr.emplace((string)"setOrigin",&setOrigin);
      obj.attr.emplace((string)"rotate",(Method)&rotate);
      PltObject ret = obj;
      objects.emplace(obj.ptr,ret.s);
      return ret;
    }
    return Plt_Err(VALUE_ERROR,"One argument needed!");
}
EXPORT PltObject Rect(PltArgs args)
{
    if(args.size()!=2)
      return Plt_Err(VALUE_ERROR,"Two arguments needed");
    if(args[0].type!='i' || args[1].type!='i')
      return Plt_Err(TYPE_ERROR,"Error both arguments should of type integer!");
    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(args[0].i,args[1].i));
    PltObject ret;
    ret.type = 'c';
    ret.ptr = (void*)shape;
    ret.s = "sfRect";
    objects.emplace(ret.ptr,ret.s);
    return ret;

}

EXPORT PltObject draw(PltObject& self,PltArgs args)
{
     if(args.size()!=1)
       return Plt_Err(VALUE_ERROR,"One arguments needed!");
    if(args[0].type!='c')
       return Plt_Err(TYPE_ERROR,"Invalid type of argument 1");
    NativeObject* p = (NativeObject*)args[0].ptr;

    string type = p->attr[(string)"internalType"].s;
    if(type=="sfCircle")
    {
      sf::CircleShape* shape = (sf::CircleShape*)p->ptr;
      p = (NativeObject*)self.ptr;
      sf::RenderWindow* w  = (sf::RenderWindow*)p->ptr;
      w->draw(*shape);
    }
    else if(type=="sfRect")
    {
      sf::RectangleShape* shape = (sf::RectangleShape*)p->ptr;
      p = (NativeObject*)self.ptr;
      sf::RenderWindow* w  = (sf::RenderWindow*)p->ptr;
      w->draw(*shape);
    }
    else
    {
      return Plt_Err(TYPE_ERROR,"Invalid type of argument 1!");
    }
    PltObject ret;
    ret.type = 'n';
    return ret;
}

EXPORT PltObject clear(PltObject& self,PltArgs args)
{
    if(args.size()!=1)
      return Plt_Err(VALUE_ERROR,"Error one arguments needed!");
    if(args[0].type!='c' )
      return Plt_Err(TYPE_ERROR,"Error invalid type of argument 1!");
    NativeObject* p = (NativeObject*)self.ptr;
    sf::RenderWindow* w = (sf::RenderWindow*)p->ptr;
    p = (NativeObject*)args[0].ptr;
    if(p->attr[(string)"internalType"].s!="sfColor")
      return Plt_Err(TYPE_ERROR,"Error invalid type of argument 1");

    sf::Color* c = (sf::Color*)p->ptr;
    w->clear(*c);
    PltObject ret;
    return ret;
}
EXPORT PltObject close(PltObject& self,PltArgs args)
{
  if(args.size()!=0)
    return Plt_Err(VALUE_ERROR,"Error 0 arguments needed!");
    NativeObject* p = (NativeObject*)self.ptr;
    sf::RenderWindow* w = (sf::RenderWindow*)p->ptr;
    w->close();
    PltObject ret;
    return ret;
}
EXPORT PltObject Color(PltArgs args)
{
    if(args.size()!=3)
      return Plt_Err(VALUE_ERROR,"Error three arguments needed!");
    if(args[0].type!='i' || args[1].type!='i' || args[2].type!='i')
      return Plt_Err(TYPE_ERROR,"Error all three arguments should be integers!");
    sf::Color* c = new sf::Color(args[0].i,args[1].i,args[1+1].i);
    NativeObject obj;
    obj.ptr = (void*)c;
    obj.attr.emplace((string)"internalType",(string)"sfColor");
    PltObject ret = obj;
    objects.emplace(obj.ptr,"sfColor");
    return ret;
}
EXPORT PltObject setFillColor(PltObject& self,PltArgs args)
{
    if(args.size()!=1)
      return Plt_Err(VALUE_ERROR,"Error one argument needed!");
    if(args[0].type!='c')
      return Plt_Err(TYPE_ERROR,"Error an argument of sfColor object needed!");
    NativeObject* p = (NativeObject*)self.ptr;
    string objType = p->attr[(string)"internalType"].s;

    if(objType=="sfCircle")
    {
    sf::CircleShape* c = (sf::CircleShape*)p->ptr;
    p = (NativeObject*)args[0].ptr;
    sf::Color* e = (sf::Color*)p->ptr;
    c->setFillColor(*e);
    }
    else if(args[0].s=="sfRect")
    {
    sf::RectangleShape* c = (sf::RectangleShape*)p->ptr;
    p = (NativeObject*)args[0].ptr;
    sf::Color* e = (sf::Color*)p->ptr;
    c->setFillColor(*e);
    }
    PltObject ret;
    return ret;
}

EXPORT PltObject setPointCount(PltObject& self,PltArgs args)
{
    if(args.size()!=1)
      return Plt_Err(VALUE_ERROR,"Error one argument needed!");
    if(args[0].type!='i')
        return Plt_Err(TYPE_ERROR,"Error type of argument 1 should be integer!");
    NativeObject* p = (NativeObject*)self.ptr;
    string objType = p->attr[(string)"internalType"].s;

    if(objType=="sfCircle")
    {
    sf::CircleShape* c = (sf::CircleShape*)p->ptr;
    c->setPointCount(args[0].i);
    }
    PltObject ret;
    return ret;
}
EXPORT PltObject setPosition(PltObject& self,PltArgs args)
{
    if(args.size()!=2)
      return Plt_Err(VALUE_ERROR,"Error two arguments needed!");
    if(args[0].type!='i' || args[1].type!='i')
      return Plt_Err(TYPE_ERROR,"Error first and second arguments both should be integers!");
    NativeObject* p = (NativeObject*)self.ptr;
    string objType = p->attr[(string)"internalType"].s;

    if(objType=="sfCircle")
    {
    sf::CircleShape* c = (sf::CircleShape*)p->ptr;
    sf::Vector2<float> p(args[0].i,args[1].i);
    c->setPosition(p);
    }
    else if(objType=="sfRect")
    {
    sf::RectangleShape* c = (sf::RectangleShape*)p->ptr;
    sf::Vector2<float> p(args[0].i,args[1].i);
    c->setPosition(p);
    }
    PltObject ret;
    return ret;
}
EXPORT PltObject rotate(PltObject& self,PltArgs args)
{
  if(args.size()!=1)
    return Plt_Err(VALUE_ERROR,"Error two arguments needed!");
  if(args[0].type!='i')
    return Plt_Err(TYPE_ERROR,"Error first argument should be integer!");
    NativeObject* p = (NativeObject*)self.ptr;
    string objType = p->attr[(string)"internalType"].s;
    if(objType=="sfCircle")
    {
    sf::CircleShape* c = (sf::CircleShape*)p->ptr;
    c->rotate(args[0].i);
    }
    else if(objType=="sfRect")
    {
    sf::RectangleShape* c = (sf::RectangleShape*)p->ptr;
    c->rotate(args[0].i);
    }
    PltObject ret;
    return ret;
}
EXPORT PltObject setOrigin(PltObject& self,PltArgs args)
{
  if(args.size()!=2)
    return Plt_Err(VALUE_ERROR,"Error two arguments needed!");
  if(args[0].type!='i' || args[1].type!='i')
    return Plt_Err(TYPE_ERROR,"Error first and second argument should be integer!");
    NativeObject* p = (NativeObject*)self.ptr;
    string objType = p->attr[(string)"internalType"].s;
    if(objType=="sfCircle")
    {
    sf::CircleShape* c = (sf::CircleShape*)p->ptr;
    c->setOrigin(args[0].i,args[1].i);
    }
    else if(objType!="sfRect")
    {
    sf::RectangleShape* c = (sf::RectangleShape*)p->ptr;
    c->setOrigin(args[0].i,args[1].i);
    }
    PltObject ret;
    return ret;
}
EXPORT void OnModuleUnload() // This function is called when the
//plutonium interpreter frees the module
{
  for(auto e: objects)
  {
    if(e.second=="sfRenderWindow")
    {
       sf::RenderWindow* p = (sf::RenderWindow*)e.first;
       delete p;
    }
    else if(e.second=="sfRect")
    {
      sf::RectangleShape* p = (sf::RectangleShape*)e.first;
      delete p;
    }
    else if(e.second=="sfCirlce")
    {
      sf::CircleShape* p = (sf::CircleShape*)e.first;
      delete p;
    }
    else if(e.second=="sfColor")
    {
      sf::Color* p = (sf::Color*)e.first;
      delete p;
    }
    else if(e.second=="sfEvent")
    {
      sf::Event* p = (sf::Event*)e.first;
      delete p;
    }
  }
}
}//end extern "C"
