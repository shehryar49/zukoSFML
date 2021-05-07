#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "PltObject.h"

#define PltArgs const vector<PltObject>&
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
PltObject Plt_Err(ErrCode e,string des)
{
  PltObject ret;
  ret.type = 'e';
  ret.s = des;
  ret.i = e;
  return ret;
}
std::unordered_map<void*,string> objects;
extern "C"
{

    PltObject RenderWindow(PltArgs args)
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
        PltObject ret;
        ret.type = 'c';//Means custom object
        ret.ptr = (void*)w;
        ret.s = "sfRenderWindow";//Description of object
        objects.emplace(ret.ptr,ret.s);
        return ret;
    }
PltObject isOpen(PltArgs args)
{
    if(args.size()!=1)
      return Plt_Err(VALUE_ERROR,"One argument needed!");
    if(args[0].type!='c')
      return Plt_Err(TYPE_ERROR,"Error argument of invalid type!");
    if(args[0].s!="sfRenderWindow")
      return Plt_Err(TYPE_ERROR,"Error argument of invalid type!");
    sf::RenderWindow* w = (sf::RenderWindow*) args[0].ptr;
    PltObject ret;
    ret.type = 'b';
    ret.i =(bool) w->isOpen();
    return ret;
}
PltObject display(PltArgs args)
{
    if(args.size()!=1)
      return Plt_Err(VALUE_ERROR,"One argument needed!");
    if(args[0].type!='c')
      return Plt_Err(TYPE_ERROR,"Error argument of invalid type!");
    if(args[0].s!="sfRenderWindow")
      return Plt_Err(TYPE_ERROR,"Error argument of invalid type!");
    sf::RenderWindow* w = (sf::RenderWindow*) args[0].ptr;
    PltObject ret;
    ret.type = 'n';
    w->display();
    return ret;
}
PltObject Event(PltArgs args)
{
  //Create a new event object and return it
  if(args.size()!=0)
    return Plt_Err(VALUE_ERROR,"Zero arguments needed!");
  sf::Event* e = new sf::Event;
  PltObject ret;
  ret.type = 'c';
  ret.ptr = (void*)e;
  ret.s = "sfEvent";
  objects.emplace(ret.ptr,ret.s);
  return ret;
}
PltObject pollEvent(PltArgs args)
{
  if(args.size()!=2)
    return Plt_Err(VALUE_ERROR,"Two arguments needed!");
  if(args[0].type!='c' || args[0].s!="sfRenderWindow")
    return Plt_Err(TYPE_ERROR,"Error invalid type of argument 1");
  if(args[1].type!='c' || args[1].s!="sfEvent")
    return Plt_Err(TYPE_ERROR,"Error invalid type of argument 2");
  sf::RenderWindow* w = (sf::RenderWindow*) args[0].ptr;
  sf::Event* e = (sf::Event*)args[1].ptr;
  PltObject ret;
  ret .i = w->pollEvent(*e);
  ret.type = 'b';
  return ret;
}
PltObject eventType(PltArgs args)
{
  if(args.size()!=1)
    return Plt_Err(VALUE_ERROR,"One argument needed!");
  if(args[0].type!='c' || args[0].s!="sfEvent")
    return Plt_Err(TYPE_ERROR,"Error argument is of invalid type!");
  sf::Event e = *(sf::Event*)args[0].ptr;
  PltObject ret;
  ret.type = 'i';
  ret.i = e.type;
  return ret;
}
PltObject keyCodeFromEvent(PltArgs args)
{
  if(args.size()!=1)
    return Plt_Err(VALUE_ERROR,"One argument needed!");
  if(args[0].type!='c' || args[0].s!="sfEvent")
    return Plt_Err(TYPE_ERROR,"Error argument is of invalid type!");
    sf::Event e = *(sf::Event*)args[0].ptr;
    PltObject ret;
    ret.type ='i';
    ret.i = e.key.code;
    return ret;
}
PltObject Circle(PltArgs args)
{
    if(args.size()==1)
    {
      if(args[0].type!='i')
        return Plt_Err(TYPE_ERROR,"Error integer argument needed!");
      sf::CircleShape* shape = new sf::CircleShape(args[0].i);
      PltObject ret;
      ret.type = 'c';
      ret.ptr = (void*)shape;
      ret.s="sfCircle";
      objects.emplace(ret.ptr,ret.s);
      return ret;
    }
    return Plt_Err(VALUE_ERROR,"One argument needed!");
}
PltObject Rect(PltArgs args)
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

PltObject draw(PltArgs args)
{
     if(args.size()!=2)
       return Plt_Err(VALUE_ERROR,"Two arguments needed!");
    if(args[0].type!='c')
       return Plt_Err(TYPE_ERROR,"Invalid type of argument 1!");
    if(args[1].type!='c' || args[1].s!="sfRenderWindow")
    {
      return Plt_Err(TYPE_ERROR,"Invalid type of argument 2!");
    }
    string type = args[0].s;
    if(type=="sfCircle")
    {
      sf::CircleShape* shape = (sf::CircleShape*)args[0].ptr;
      sf::RenderWindow* w  = (sf::RenderWindow*)args[1].ptr;
      w->draw(*shape);
    }
    else if(type=="sfRect")
    {
      sf::RectangleShape* shape = (sf::RectangleShape*)args[0].ptr;
      sf::RenderWindow* w  = (sf::RenderWindow*)args[1].ptr;
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

PltObject clear(PltArgs args)
{
    if(args.size()!=2)
      return Plt_Err(VALUE_ERROR,"Error two arguments needed!");
    if(args[0].type!='c' || args[0].s!="sfRenderWindow")
      return Plt_Err(TYPE_ERROR,"Error invalid type of argument 1!");
    if(args[1].type!='c' || args[1].s!="sfColor")
        return Plt_Err(TYPE_ERROR,"Error invalid type of argument 2!");
    sf::RenderWindow* w = (sf::RenderWindow*)args[0].ptr;
    sf::Color* c = (sf::Color*)args[1].ptr;
    w->clear(*c);
    PltObject ret;
    ret.type = 'n';
    return ret;
}
PltObject close(PltArgs args)
{
  if(args.size()!=1)
    return Plt_Err(VALUE_ERROR,"Error one argument needed!");
  if(args[0].type!='c' || args[0].s!="sfRenderWindow")
    return Plt_Err(TYPE_ERROR,"Error invalid type of argument 1!");
    sf::RenderWindow* w = (sf::RenderWindow*)args[0].ptr;
    w->close();
    PltObject ret;
    ret.type = 'n';
    return ret;
}
PltObject Color(PltArgs args)
{
    if(args.size()!=3)
      return Plt_Err(VALUE_ERROR,"Error three arguments needed!");
    if(args[0].type!='i' || args[1].type!='i' || args[2].type!='i')
      return Plt_Err(TYPE_ERROR,"Error all three arguments should be integers!");
    sf::Color* c = new sf::Color(args[0].i,args[1].i,args[1+1].i);
    PltObject ret;
    ret.type = 'c';
    ret.ptr = (void*)c;
    ret.s = "sfColor";
    objects.emplace(ret.ptr,ret.s);
    return ret;
}
PltObject setFillColor(PltArgs args)
{
    if(args.size()!=2)
      return Plt_Err(VALUE_ERROR,"Error two argument needed!");
    if(args[0].type!='c')
      return Plt_Err(TYPE_ERROR,"Error invalid type of argument 1!");
    if(args[1].type!='c' || args[1].s!="sfColor")
        return Plt_Err(TYPE_ERROR,"Error invalid type of argument 2!");
    if(args[0].s=="sfCircle")
    {
    sf::CircleShape* c = (sf::CircleShape*)args[0].ptr;
    sf::Color* e = (sf::Color*)args[1].ptr;
    c->setFillColor(*e);
    }
    else if(args[0].s=="sfRect")
    {
    sf::RectangleShape* c = (sf::RectangleShape*)args[0].ptr;
    sf::Color* e = (sf::Color*)args[1].ptr;
    c->setFillColor(*e);
    }
    else
        return Plt_Err(TYPE_ERROR,"Error invalid type of argument 1!");
    PltObject ret;
    ret.type = 'n';
    return ret;
}

PltObject setPointCount(PltArgs args)
{
    if(args.size()!=2)
      return Plt_Err(VALUE_ERROR,"Error two argument needed!");
    if(args[0].type!='c')
      return Plt_Err(TYPE_ERROR,"Error invalid type of argument 1!");
    if(args[1].type!='i')
        return Plt_Err(TYPE_ERROR,"Error type of argument 2 should be integer!");
    if(args[0].s=="sfCircle")
    {
    sf::CircleShape* c = (sf::CircleShape*)args[0].ptr;
    c->setPointCount(args[1].i);
    }
    else
        return Plt_Err(TYPE_ERROR,"Error invalid type of argument 1!");
    PltObject ret;
    ret.type = 'n';
    return ret;
}
PltObject setPosition(PltArgs args)
{
  if(args.size()!=3)
    return Plt_Err(VALUE_ERROR,"Error three arguments needed!");
  if(args[0].type!='c')
    return Plt_Err(TYPE_ERROR,"Error invalid type of argument 1!");
  if(args[1].type!='i' || args[2].type!='i')
    return Plt_Err(TYPE_ERROR,"Error second and third arguments both should be integers!");
    if(args[0].s!="sfCircle")
    {
    sf::CircleShape* c = (sf::CircleShape*)args[0].ptr;
    sf::Vector2<float> p(args[1].i,args[1+1].i);
    c->setPosition(p);
    }
    else if(args[0].s!="sfRect")
    {
    sf::RectangleShape* c = (sf::RectangleShape*)args[0].ptr;
    sf::Vector2<float> p(args[1].i,args[1+1].i);
    c->setPosition(p);
    }
    if(args[0].type!='c')
      return Plt_Err(TYPE_ERROR,"Error invalid type of argument 1!");
    PltObject ret;
    ret.type = 'n';
    return ret;
}
PltObject rotate(PltArgs args)
{
  if(args.size()!=2)
    return Plt_Err(VALUE_ERROR,"Error two arguments needed!");
  if(args[0].type!='c')
    return Plt_Err(TYPE_ERROR,"Error invalid type of argument 1!");
  if(args[1].type!='i')
    return Plt_Err(TYPE_ERROR,"Error second argument should be integer!");
    if(args[0].s!="sfCircle")
    {
    sf::CircleShape* c = (sf::CircleShape*)args[0].ptr;
    c->rotate(args[1].i);
    }
    else if(args[0].s!="sfRect")
    {
    sf::RectangleShape* c = (sf::RectangleShape*)args[0].ptr;
    c->rotate(args[1].i);
    }
    if(args[0].type!='c')
      return Plt_Err(TYPE_ERROR,"Error invalid type of argument 1!");
    PltObject ret;
    ret.type = 'n';
    return ret;
}
PltObject setOrigin(PltArgs args)
{
  if(args.size()!=3)
    return Plt_Err(VALUE_ERROR,"Error two arguments needed!");
  if(args[0].type!='c')
    return Plt_Err(TYPE_ERROR,"Error invalid type of argument 1!");
  if(args[1].type!='i' || args[2].type!='i')
    return Plt_Err(TYPE_ERROR,"Error second and third argument should be integer!");
    if(args[0].s!="sfCircle")
    {
    sf::CircleShape* c = (sf::CircleShape*)args[0].ptr;
    c->setOrigin(args[1].i,args[2].i);
    }
    else if(args[0].s!="sfRect")
    {
    sf::RectangleShape* c = (sf::RectangleShape*)args[0].ptr;
    c->setOrigin(args[1].i,args[2].i);
    }
    if(args[0].type!='c')
      return Plt_Err(TYPE_ERROR,"Error invalid type of argument 1!");
    PltObject ret;
    ret.type = 'n';
    return ret;
}
void OnModuleUnload() // This function is called when the
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
