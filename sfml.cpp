#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "sfml.h"
#include <stdio.h>

Klass *renderwinclass, *circleclass, *rectclass, *evclass, *colorclass;
Klass *clockclass;
Klass *timeclass;
Klass *vaclass;
Klass *fontclass;
Klass *textclass;
Klass *textureclass;
Klass *spriteclass;
Klass *vector2fclass;
Klass *floatrectclass;

ZObject nil;
ZObject init()
{
    nil.type = Z_NIL;
    // Initialize classes
    renderwinclass = vm_allocKlass();
    renderwinclass->name = "RenderWindow";
    Klass_addNativeMethod(renderwinclass,"__construct__", &RenderWindow__construct);
    Klass_addNativeMethod(renderwinclass,"clear",&RenderWindow__clear);
    Klass_addNativeMethod(renderwinclass,"draw",&RenderWindow__draw);
    Klass_addNativeMethod(renderwinclass,"display",&RenderWindow__display);
    Klass_addNativeMethod(renderwinclass,"pollEvent",&RenderWindow__pollevent);
    Klass_addNativeMethod(renderwinclass,"setFramerateLimit", &RenderWindow__setFrameRateLimit);
    Klass_addNativeMethod(renderwinclass,"close",&RenderWindow__close);

    circleclass = vm_allocKlass();
    circleclass->name = "Circle";
    Klass_addNativeMethod(circleclass,"__construct__",&Circle__construct);
    Klass_addNativeMethod(circleclass,"setPosition",&Circle__setpos);
    Klass_addNativeMethod(circleclass,"setFillColor",&Circle__setfillcolor);
    Klass_addNativeMethod(circleclass,"setPointCount",&Circle__setpointcount);
    Klass_addNativeMethod(circleclass,"__del__",&Circle__del);
  
    colorclass = vm_allocKlass();
    colorclass->name = "Color";
    Klass_addNativeMethod(colorclass,"__construct__",&Color__construct);
    Klass_addNativeMethod(colorclass,"__del__",&Color__del);

    rectclass = vm_allocKlass();
    rectclass->name = "Rectangle";
    Klass_addNativeMethod(rectclass,"__construct__",&Rect__construct);
    Klass_addNativeMethod(rectclass,"setPosition", &Rect__setpos);
    Klass_addNativeMethod(rectclass,"setFillColor", &Rect__setfillcolor);
    Klass_addNativeMethod(rectclass,"setOutlineColor", &Rect__setOutlineColor);
    Klass_addNativeMethod(rectclass,"setOutlineThickness",&Rect__setOutlineThickness);
    Klass_addNativeMethod(rectclass,"setPosition",&Rect__setpos);
    Klass_addNativeMethod(rectclass,"getPosition",&Rect__getPosition);
    Klass_addNativeMethod(rectclass,"getGlobalBounds",&Rect__getGlobalBounds);
    Klass_addNativeMethod(rectclass,"setSize",&Rect__setSize);

    evclass = vm_allocKlass();
    evclass->name = "Event";
    Klass_addNativeMethod(evclass,"__construct__",&Event__construct);
    Klass_addNativeMethod(evclass,"__del__",&Event__del);
    Klass_addMember(evclass,"type", nil);
    Klass_addMember(evclass,"keycode", nil);

    textureclass = vm_allocKlass();
    textureclass->name = "Texture";
    Klass_addNativeMethod(textureclass,"__construct__", &Texture__construct);
    Klass_addNativeMethod(textureclass,"loadFromFile", &Texture__loadFromFile);
    Klass_addNativeMethod(textureclass,"__del__", &Texture__del);

    clockclass = vm_allocKlass();
    clockclass->name = "Clock";
    Klass_addNativeMethod(clockclass,"__construct__", &Clock__construct);
    Klass_addNativeMethod(clockclass,"restart", &Clock__restart);
    Klass_addNativeMethod(clockclass,"__del__", &Clock__del);

    vaclass = vm_allocKlass();
    vaclass->name = "VertexArray";
    Klass_addNativeMethod(vaclass,"__construct__", &VertexArray__construct);
    Klass_addNativeMethod(vaclass,"resize", &VertexArray__resize);
    Klass_addNativeMethod(vaclass,"setPrimitiveType", &VertexArray__setPrimType);
    Klass_addNativeMethod(vaclass,"setKth", &VertexArray__setKth);
    Klass_addNativeMethod(vaclass,"__del__", &VertexArray__del);

    fontclass = vm_allocKlass();
    fontclass->name = "Font";
    Klass_addNativeMethod(fontclass,"__construct__", &Font__construct);
    Klass_addNativeMethod(fontclass,"loadFromFile", &Font__loadFromFile);
    Klass_addNativeMethod(fontclass,"__del__", &Font__del);

    spriteclass = vm_allocKlass();
    spriteclass->name = "Sprite";
    Klass_addNativeMethod(spriteclass,"__construct__", &Sprite__construct);
    Klass_addNativeMethod(spriteclass,"setTexture", &Sprite__setTexture);
    Klass_addNativeMethod(spriteclass,"__del__", &Sprite__del);

    textclass = vm_allocKlass();
    textclass->name = "Text";
    Klass_addNativeMethod(textclass,"__construct__", &Text__construct);
    Klass_addNativeMethod(textclass,"setCharacterSize", &Text__setCharacterSize);
    Klass_addNativeMethod(textclass,"setString", &Text__setString);
    Klass_addNativeMethod(textclass,"setPosition", &Text__setPostion);
    Klass_addNativeMethod(textclass,"setFont", &Text__setFont);
    Klass_addNativeMethod(textclass,"setFillColor", &Text__setFillColor);
    Klass_addNativeMethod(textclass,"__del__", &Text__del);

    timeclass = vm_allocKlass();
    timeclass->name = "Time";
    Klass_addNativeMethod(timeclass,"asSeconds", &Time__asSeconds);
    Klass_addNativeMethod(timeclass,"__del__", &Time__del);

    vector2fclass = vm_allocKlass();
    vector2fclass->name = "Vector2f";
    Klass_addMember(vector2fclass,"x", nil);
    Klass_addMember(vector2fclass,"y", nil);

    floatrectclass = vm_allocKlass();
    floatrectclass->name = "FloatRect";
    Klass_addMember(floatrectclass,"width", nil);
    Klass_addMember(floatrectclass,"height", nil);
    Klass_addMember(floatrectclass,"top", nil);
    Klass_addMember(floatrectclass,"left", nil);
    Klass_addNativeMethod(floatrectclass,"intersects", &FloatRect__intersects);

    vm_markImportant(timeclass);
    vm_markImportant(vector2fclass);
    vm_markImportant(floatrectclass);

    // Add classes to module
    Module *sfml = vm_allocModule();
    sfml->name = "sfml";
    Module_addMember(sfml,"RenderWindow", ZObjFromKlass(renderwinclass));
    Module_addMember(sfml,"Circle", ZObjFromKlass(circleclass));
    Module_addMember(sfml,"Color", ZObjFromKlass(colorclass));
    Module_addMember(sfml,"Rectangle", ZObjFromKlass(rectclass));
    Module_addMember(sfml,"Event", ZObjFromKlass(evclass));
    Module_addMember(sfml,"Clock", ZObjFromKlass(clockclass));
    Module_addMember(sfml,"VertexArray", ZObjFromKlass(vaclass));
    Module_addMember(sfml,"Font", ZObjFromKlass(fontclass));
    Module_addMember(sfml,"Text", ZObjFromKlass(textclass));
    Module_addMember(sfml,"Texture", ZObjFromKlass(textureclass));
    Module_addMember(sfml,"Sprite", ZObjFromKlass(spriteclass));
    Module_addMember(sfml,"Vector2f", ZObjFromKlass(vector2fclass));

    Module_addMember(sfml,"getMousePosition", ZObjFromFunction("getMousePosition", &getMousePosition));

    Module_addMember(sfml,"EventClosed", ZObjFromInt(sf::Event::Closed));
    Module_addMember(sfml,"EventKeyPressed", ZObjFromInt(sf::Event::KeyPressed));
    Module_addMember(sfml,"EventMouseButtonPressed", ZObjFromInt(sf::Event::MouseButtonPressed));
    Module_addMember(sfml,"EventMouseMoved", ZObjFromInt(sf::Event::MouseMoved));
    Module_addMember(sfml,"KeyboardA", ZObjFromInt(sf::Keyboard::A));
    Module_addMember(sfml,"KeyboardS", ZObjFromInt(sf::Keyboard::S));
    Module_addMember(sfml,"KeyboardD", ZObjFromInt(sf::Keyboard::D));
    Module_addMember(sfml,"KeyboardW", ZObjFromInt(sf::Keyboard::W));
    Module_addMember(sfml,"KeyboardUp", ZObjFromInt(sf::Keyboard::Up));
    Module_addMember(sfml,"KeyboardDown", ZObjFromInt(sf::Keyboard::Down));
    Module_addMember(sfml,"KeyboardLeft", ZObjFromInt(sf::Keyboard::Left));
    Module_addMember(sfml,"KeyboardRight", ZObjFromInt(sf::Keyboard::Right));
    Module_addMember(sfml,"KeyboardEsc", ZObjFromInt(sf::Keyboard::Escape));
    Module_addMember(sfml,"KeyboardEnter", ZObjFromInt(sf::Keyboard::Enter));
    // More keymappings to be added later

    Module_addMember(sfml,"LinesStrip", ZObjFromInt(sf::LinesStrip));
    Module_addMember(sfml,"MouseLeft", ZObjFromInt(sf::Mouse::Left));

    return ZObjFromModule(sfml);
}
// Global Module functions
ZObject getMousePosition(ZObject *args, int n)
{
    if (n != 1)
        return Z_Err(ArgumentError, "1 argument needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != renderwinclass)
    {
        return Z_Err(TypeError, "Argument 1 must be an instance of RenderWindow");
    }
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::RenderWindow *w = (sf::RenderWindow *)AS_PTR(KlassObj_getMember(k,".handle"));
    KlassObject *ki = vm_allocKlassObject(vector2fclass);
    sf::Vector2i v = sf::Mouse::getPosition(*w);
    
    KlassObj_setMember(ki,"x",ZObjFromDouble(v.x));
    KlassObj_setMember(ki,"y",ZObjFromDouble(v.y));
    
    return ZObjFromKlassObj(ki);
}
// RenderWindow
ZObject RenderWindow__construct(ZObject *args, int n)
{
    if (n != 4)
        return Z_Err(ArgumentError, "4 arguments needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != renderwinclass)
        return Z_Err(TypeError, "self must be an instance of RenderWindow");
    if (args[1].type != 'i' || args[2].type != 'i' || args[3].type != 's')
        return Z_Err(TypeError, "Invalid types of arguments!");
    ZStr* title = AS_STR(args[3]);
    sf::RenderWindow *w = new sf::RenderWindow(sf::VideoMode(args[1].i, args[2].i), title->val);
    KlassObject *k = (KlassObject *)args[0].ptr;
    KlassObj_setMember(k,".handle",ZObjFromPtr((void*)w));// we use .handle so that user can't change it's value
    return nil;                                            //
}
ZObject RenderWindow__clear(ZObject *args, int n)
{
    if (n != 1 && n != 2)
    {
        return Z_Err(ArgumentError, "1 or 2 arguments needed!");
    }
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != renderwinclass)
    {
        return Z_Err(TypeError, "self must be an instance of RenderWindow");
    }
    sf::Color c = sf::Color::Black;
    if (n == 2)
    {
        if (args[1].type != Z_OBJ || ((KlassObject *)args[1].ptr)->klass != colorclass)
            return Z_Err(TypeError, "Argument 2 must be an instance of Color");
        KlassObject *ki = (KlassObject *)args[1].ptr;
        sf::Color *color = (sf::Color *)AS_PTR(KlassObj_getMember(ki,".handle"));
        c = *color;
    }
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::RenderWindow *w = (sf::RenderWindow *)AS_PTR(KlassObj_getMember(k,".handle"));
    w->clear(c);
    return nil;
}
ZObject RenderWindow__close(ZObject *args, int n)
{
    if (n != 1)
        return Z_Err(ArgumentError, "1 argument needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != renderwinclass)
        return Z_Err(TypeError, "self must be an instance of RenderWindow");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::RenderWindow *w = (sf::RenderWindow *)AS_PTR(KlassObj_getMember(k,".handle"));
    w->close();
    delete w;
    KlassObj_setMember(k,".handle",nil);
    return nil;
}
ZObject RenderWindow__display(ZObject *args, int n)
{
    if (n != 1)
    {
        return Z_Err(ArgumentError, "1 argument needed!");
    }
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != renderwinclass)
    {
        return Z_Err(TypeError, "self must be an instance of RenderWindow");
    }
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::RenderWindow *w = (sf::RenderWindow *)AS_PTR(KlassObj_getMember(k,".handle"));;
    w->display();
    return nil;
}
ZObject RenderWindow__draw(ZObject *args, int n)
{
    if (n != 2)
    {
        return Z_Err(ArgumentError, "2 arguments needed!");
    }
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != renderwinclass)
    {
        return Z_Err(TypeError, "self must be an instance of RenderWindow");
    }
    if (args[1].type != Z_OBJ)
    {
        return Z_Err(TypeError, "Argument must be a drawable sfml object!");
    }
    KlassObject *obj = (KlassObject *)args[1].ptr;

    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::RenderWindow *w = (sf::RenderWindow *)AS_PTR(KlassObj_getMember(k,".handle"));;
    if (obj->klass == circleclass)
    {
        sf::CircleShape *d = (sf::CircleShape *)AS_PTR(KlassObj_getMember(obj,".handle"));;
        w->draw(*d);
    }
    else if (obj->klass == rectclass)
    {
        sf::RectangleShape *d = (sf::RectangleShape *)AS_PTR(KlassObj_getMember(obj,".handle"));;
        w->draw(*d);
    }
    else if (obj->klass == spriteclass)
    {
        sf::Sprite *d = (sf::Sprite *)AS_PTR(KlassObj_getMember(obj,".handle"));
        w->draw(*d);
    }
    else if (obj->klass == textclass)
    {
        sf::Text *d = (sf::Text *)AS_PTR(KlassObj_getMember(obj,".handle"));
        w->draw(*d);
    }
    else if (obj->klass == vaclass)
    {
        sf::VertexArray *d = (sf::VertexArray *)AS_PTR(KlassObj_getMember(obj,".handle"));
        w->draw(*d);
    }
    else
        return Z_Err(TypeError, "Argument must be a drawable sfml object!");
    return nil;
}
ZObject RenderWindow__pollevent(ZObject *args, int n)
{
    if (n != 2)
    {
        return Z_Err(ArgumentError, "2 argument needed!");
    }
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != renderwinclass)
    {
        return Z_Err(TypeError, "self must be an instance of RenderWindow");
    }
    if (args[1].type != Z_OBJ)
    {
        return Z_Err(TypeError, "Argument must be an instance of Event class.");
    }
    KlassObject *obj = (KlassObject *)args[1].ptr;
    if (obj->klass != evclass)
    {
        return Z_Err(TypeError, "Argument must be an instance of Event class.");
    }
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::RenderWindow *w = (sf::RenderWindow *)AS_PTR(KlassObj_getMember(k,".handle"));;
    sf::Event *e = (sf::Event *)AS_PTR(KlassObj_getMember(obj,".handle"));;
    bool b = w->pollEvent(*e);
    if (b)
    {
        KlassObj_setMember(obj,"type",ZObjFromInt(e->type));
        if (e->type == sf::Event::KeyPressed)
            KlassObj_setMember(obj,"keycode",ZObjFromInt(e->key.code));
        if (e->type == sf::Event::MouseButtonPressed)
            KlassObj_setMember(obj,"mouseButton",ZObjFromInt(e->mouseButton.button));
    }
    return ZObjFromBool(b);
}
ZObject RenderWindow__setFrameRateLimit(ZObject *args, int n)
{
    if (n != 2)
        return Z_Err(ArgumentError, "2 argument needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != renderwinclass)
        return Z_Err(TypeError, "self must be an instance of RenderWindow");
    if (args[1].type != Z_INT)
        return Z_Err(TypeError, "Argument 2  must be an integer.");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::RenderWindow *w = (sf::RenderWindow *)AS_PTR(KlassObj_getMember(k,".handle"));;
    w->setFramerateLimit(args[1].i);
    return nil;
}

// Event
ZObject Event__construct(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != evclass)
    {
        return Z_Err(ArgumentError, "1 argument self needed which must be instance of event");
    }
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Event *e = new sf::Event;
    KlassObj_setMember(k,".handle",ZObjFromPtr(e));
    return nil;
}
ZObject Event__del(ZObject *args, int n)
{
    if (n != 1)
        return nil;
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != evclass)
        return nil;
    KlassObject *ki = (KlassObject *)args[0].ptr;
    ZObject ptr = KlassObj_getMember(ki,".handle");
    if (ptr.type == Z_NIL)
        return nil;
    sf::Event *ev = (sf::Event *)ptr.ptr;
    delete ev;
    KlassObj_setMember(ki,".handle",nil);
    return nil;
}
// Circle
ZObject Circle__construct(ZObject *args, int n)
{
    if (n != 1 && n != 2)
    {
        return Z_Err(ArgumentError, "Two or One arguments needed!");
    }
    float radius = 0;
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != circleclass)
    {
        return Z_Err(TypeError, "self must be an instance of circle class!");
    }
    if (n == 2)
    {
        if (args[1].type != Z_FLOAT)
        {
            return Z_Err(TypeError, "Radius must be a float!");
        }
        radius = static_cast<float>(args[1].f);
    }
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::CircleShape *c = new sf::CircleShape(radius);
    KlassObj_setMember(k,".handle", ZObjFromPtr(c));
    
    return nil;
}
ZObject Circle__setpos(ZObject *args, int n)
{
    if (n != 3)
    {
        return Z_Err(ArgumentError, "Three arguments needed!");
    }
    float radius = 0;
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != circleclass)
    {
        return Z_Err(TypeError, "self must be an instance of circle class!");
    }
    if (args[1].type != Z_FLOAT || args[2].type != Z_FLOAT)
    {
        return Z_Err(TypeError, "Position coordinates must be floats!");
    }

    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::CircleShape *c = (sf::CircleShape *)AS_PTR(KlassObj_getMember(k,".handle"));
    float x = (float)args[1].f;
    float y = (float)args[2].f;
    c->setPosition(x, y);
    return nil;
}
ZObject Circle__setpointcount(ZObject *args, int n)
{
    if (n != 2)
    {
        return Z_Err(ArgumentError, "Two arguments needed!");
    }
    float radius = 0;
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != circleclass)
    {
        return Z_Err(TypeError, "self must be an instance of circle class!");
    }
    if (args[1].type != Z_INT && args[1].type != Z_INT64)
    {
        return Z_Err(TypeError, "Point count must be an integer!");
    }

    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::CircleShape *c = (sf::CircleShape *)AS_PTR(KlassObj_getMember(k,".handle"));
    if (args[1].type == Z_INT)
        c->setPointCount(args[1].i);
    else
        c->setPointCount(args[1].l);
    return nil;
}
ZObject Circle__setfillcolor(ZObject *args, int n)
{
    if (n != 2)
        return Z_Err(ArgumentError, "Two arguments needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != circleclass)
        return Z_Err(TypeError, "Argument 1(self) must be an instance of circle class!");
    if (args[1].type != Z_OBJ || ((KlassObject *)args[1].ptr)->klass != colorclass)
        return Z_Err(TypeError, "Argument 2 must be an instance of class Color!");
    KlassObject *k = (KlassObject *)args[0].ptr;
    KlassObject *j = (KlassObject *)args[1].ptr;
    sf::CircleShape *c = (sf::CircleShape *)AS_PTR(KlassObj_getMember(k,".handle"));
    sf::Color *color = (sf::Color *)AS_PTR(KlassObj_getMember(j,".handle"));
    c->setFillColor(*color);
    return nil;
}
ZObject Circle__del(ZObject *args, int n)
{
    if (n != 1)
        return nil;
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != circleclass)
        return nil;
    KlassObject *ki = (KlassObject *)args[0].ptr;
    if (KlassObj_getMember(ki,".handle").type == Z_NIL)
        return nil;
    sf::CircleShape *circle = (sf::CircleShape *)AS_PTR(KlassObj_getMember(ki,".handle"));
    delete circle;
    KlassObj_setMember(ki,".handle",nil);
    return nil;
}
// Rectangle
ZObject Rect__construct(ZObject *args, int n)
{
    if (n != 3)
    {
        return Z_Err(ArgumentError, "3 arguments needed!");
    }
    float width = 0;
    float height = 0;
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != rectclass)
        return Z_Err(TypeError, "self must be an instance of Rectangle class!");
    if (args[1].type != Z_FLOAT || args[2].type != Z_FLOAT)
        return Z_Err(TypeError, "Width and height must be floats!");

    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::RectangleShape *c = new sf::RectangleShape(sf::Vector2f(args[1].f, args[2].f));
    KlassObj_setMember(k,".handle", ZObjFromPtr(c));
    return nil;
}
ZObject Rect__setpos(ZObject *args, int n)
{
    if (n != 3)
    {
        return Z_Err(ArgumentError, "Three arguments needed!");
    }
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != rectclass)
    {
        return Z_Err(TypeError, "self must be an instance of Rectangle class!");
    }
    if (args[1].type != Z_FLOAT || args[2].type != Z_FLOAT)
    {
        return Z_Err(TypeError, "Position coordinates must be floats!");
    }
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::RectangleShape *c = (sf::RectangleShape *)AS_PTR(KlassObj_getMember(k,".handle"));
    c->setPosition(args[1].f, args[2].f);
    return nil;
}
ZObject Rect__setSize(ZObject *args, int n)
{
    if (n != 3)
    {
        return Z_Err(ArgumentError, "Three arguments needed!");
    }
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != rectclass)
    {
        return Z_Err(TypeError, "self must be an instance of Rectangle class!");
    }
    if (args[1].type != Z_FLOAT || args[2].type != Z_FLOAT)
    {
        return Z_Err(TypeError, "Size values must be floats!");
    }
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::RectangleShape *c = (sf::RectangleShape *)AS_PTR(KlassObj_getMember(k,".handle"));
    c->setSize(sf::Vector2f(args[1].f, args[2].f));
    return nil;
}
ZObject Rect__getPosition(ZObject *args, int n)
{
    if (n != 1)
        return Z_Err(ArgumentError, "1 argument needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != rectclass)
        return Z_Err(TypeError, "self must be an instance of Rectangle class!");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::RectangleShape *c = (sf::RectangleShape *)AS_PTR(KlassObj_getMember(k,".handle"));
    KlassObject *ki = vm_allocKlassObject(vector2fclass);
    sf::Vector2f v = c->getPosition();
    KlassObj_setMember(ki,"x",ZObjFromDouble(v.x));
    KlassObj_setMember(ki,"y",ZObjFromDouble(v.y));
    return ZObjFromKlassObj(ki);
}
ZObject Rect__getGlobalBounds(ZObject *args, int n)
{
    if (n != 1)
        return Z_Err(ArgumentError, "1 argument needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != rectclass)
        return Z_Err(TypeError, "self must be an instance of Rectangle class!");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::RectangleShape *c = (sf::RectangleShape *)AS_PTR(KlassObj_getMember(k,".handle"));
    KlassObject *ki = vm_allocKlassObject(floatrectclass);

    sf::FloatRect v = c->getGlobalBounds();

    KlassObj_setMember(ki,"width",ZObjFromDouble(v.width));
    KlassObj_setMember(ki,"height",ZObjFromDouble(v.height));
    KlassObj_setMember(ki,"left",ZObjFromDouble(v.left));
    KlassObj_setMember(ki,"top",ZObjFromDouble(v.top));
    return ZObjFromKlassObj(ki);
}
ZObject Rect__setOutlineThickness(ZObject *args, int n)
{
    if (n != 2)
    {
        return Z_Err(ArgumentError, "Three arguments needed!");
    }
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != rectclass)
    {
        return Z_Err(TypeError, "self must be an instance of Rectangle class!");
    }
    if (args[1].type != Z_FLOAT)
    {
        return Z_Err(TypeError, "Argument 1 must be a float!");
    }
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::RectangleShape *c = (sf::RectangleShape *)AS_PTR(KlassObj_getMember(k,".handle"));
    c->setOutlineThickness(args[1].f);
    return nil;
}
ZObject Rect__setfillcolor(ZObject *args, int n)
{
    if (n != 2)
        return Z_Err(ArgumentError, "Two arguments needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != rectclass)
        return Z_Err(TypeError, "Argument 1(self) must be an instance of Rectangle class!");
    if (args[1].type != Z_OBJ || ((KlassObject *)args[1].ptr)->klass != colorclass)
        return Z_Err(TypeError, "Argument 2 must be an instance of class Color!");
    KlassObject *k = (KlassObject *)args[0].ptr;
    KlassObject *j = (KlassObject *)args[1].ptr;
    sf::RectangleShape *c = (sf::RectangleShape *)AS_PTR(KlassObj_getMember(k,".handle"));
    sf::Color *color = (sf::Color *)AS_PTR(KlassObj_getMember(j,".handle"));
    c->setFillColor(*color);
    return nil;
}
ZObject Rect__setOutlineColor(ZObject *args, int n)
{
    if (n != 2)
        return Z_Err(ArgumentError, "Two arguments needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != rectclass)
        return Z_Err(TypeError, "Argument 1(self) must be an instance of Rectangle class!");
    if (args[1].type != Z_OBJ || ((KlassObject *)args[1].ptr)->klass != colorclass)
        return Z_Err(TypeError, "Argument 2 must be an instance of class Color!");
    KlassObject *k = (KlassObject *)args[0].ptr;
    KlassObject *j = (KlassObject *)args[1].ptr;
    sf::RectangleShape *c = (sf::RectangleShape *)AS_PTR(KlassObj_getMember(k,".handle"));
    sf::Color *color = (sf::Color *)AS_PTR(KlassObj_getMember(j,".handle"));
    c->setOutlineColor(*color);
    return nil;
}
ZObject Rect__del(ZObject *args, int n)
{
    if (n != 1)
        return nil;
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != rectclass)
        return nil;
    KlassObject *ki = (KlassObject *)args[0].ptr;
    if (KlassObj_getMember(ki,".handle").type == Z_NIL)
        return nil;
    sf::RectangleShape *rect = (sf::RectangleShape *)AS_PTR(KlassObj_getMember(ki,".handle"));
    delete rect;
    KlassObj_setMember(ki,".handle",nil);
    return nil;
}
// Color
ZObject Color__construct(ZObject *args, int n)
{
    if (n != 4)
    {
        return Z_Err(ArgumentError, "4 arguments needed!");
    }
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != colorclass)
    {
        return Z_Err(TypeError, "self must be an instance of Color class!");
    }
    if (args[1].type != Z_INT || args[2].type != Z_INT || args[3].type != Z_INT)
    {
        return Z_Err(TypeError, "RGB values must be integers!");
    }
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Color *c = new sf::Color(args[1].i, args[2].i, args[3].i);
    KlassObj_setMember(k,".handle", ZObjFromPtr(c));
    return nil;
}
ZObject Color__del(ZObject *args, int n)
{
    if (n != 1)
        return nil;
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != colorclass)
        return nil;
    KlassObject *ki = (KlassObject *)args[0].ptr;
    if (KlassObj_getMember(ki,".handle").type == Z_NIL)
        return nil;
    sf::Color *color = (sf::Color *)AS_PTR(KlassObj_getMember(ki,".handle"));
    delete color;
    KlassObj_setMember(ki,".handle",nil);
    return nil;
}
// Clock
ZObject Clock__construct(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != clockclass)
        return Z_Err(ArgumentError, "1 argument self needed which must be instance of Clock");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Clock *e = new sf::Clock;
    KlassObj_setMember(k,".handle", ZObjFromPtr(e));
    return nil; // values returned by consructors are ignored anyway
}
ZObject Clock__restart(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != clockclass)
        return Z_Err(ArgumentError, "1 argument self needed which must be instance of Clock");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Clock *e = (sf::Clock *)AS_PTR(KlassObj_getMember(k,".handle"));
    sf::Time *t = new sf::Time(e->restart());
    KlassObject *ki = vm_allocKlassObject(timeclass);
    KlassObj_setMember(ki,".handle", ZObjFromPtr(t));
    return ZObjFromKlassObj(ki);
}
ZObject Clock__del(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != clockclass)
        return nil;
    KlassObject *k = (KlassObject *)args[0].ptr;
    if (KlassObj_getMember(k,".handle").type == Z_NIL)
        return nil;
    sf::Clock *e = (sf::Clock *)AS_PTR(KlassObj_getMember(k,".handle"));
    delete e;
    KlassObj_setMember(k,".handle",nil);
    return nil;
}

// Time
ZObject Time__asSeconds(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != timeclass)
        return Z_Err(ArgumentError, "1 argument self needed which must be instance of Time");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Time *t = (sf::Time *)AS_PTR(KlassObj_getMember(k,".handle"));

    return ZObjFromDouble(t->asSeconds());
}
ZObject Time__del(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != timeclass)
        return nil;
    KlassObject *k = (KlassObject *)args[0].ptr;
    if (KlassObj_getMember(k,".handle").type == Z_NIL)
        return nil;
    sf::Time *t = (sf::Time *)AS_PTR(KlassObj_getMember(k,".handle"));
    delete t;
    KlassObj_setMember(k,".handle",nil);
    return nil;
}
// Texture
ZObject Texture__construct(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != textureclass)
        return Z_Err(ArgumentError, "1 argument self needed which must be instance of Texture");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Texture *e = new sf::Texture;
    KlassObj_setMember(k,".handle", ZObjFromPtr(e));
    return nil; // values returned by consructors are ignored anyway
}
ZObject Texture__loadFromFile(ZObject *args, int n)
{
    if (n != 2)
        return Z_Err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != textureclass)
        return Z_Err(TypeError, "Argument 1 must be instance of Texture");
    if (args[1].type != Z_STR)
        return Z_Err(TypeError, "Argument 2 must be a string!");
    auto fname = AS_STR(args[1]);
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Texture *f = (sf::Texture *)AS_PTR(KlassObj_getMember(k,".handle"));
    f->loadFromFile(fname->val);
    return nil;
}
ZObject Texture__del(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != textureclass)
        return nil;
    KlassObject *k = (KlassObject *)args[0].ptr;
    if (KlassObj_getMember(k,".handle").type == Z_NIL)
        return nil;
    sf::Texture *e = (sf::Texture *)AS_PTR(KlassObj_getMember(k,".handle"));
    // delete e;
    return nil; // values returned by consructors/destructors are ignored anyway
}
// VertexArray
ZObject VertexArray__construct(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != vaclass)
        return Z_Err(ArgumentError, "1 argument self needed which must be instance of VertexArray");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::VertexArray *e = new sf::VertexArray;
    KlassObj_setMember(k,".handle", ZObjFromPtr(e));
    return nil; // values returned by consructors are ignored anyway
}
ZObject VertexArray__setPrimType(ZObject *args, int n)
{
    if (n != 2)
        return Z_Err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != vaclass)
        return Z_Err(TypeError, "Argument 1  must be instance of VertexArray");
    if (args[1].type != Z_INT)
        return Z_Err(TypeError, "Argument 2 must be an integer!");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::VertexArray *va = (sf::VertexArray *)AS_PTR(KlassObj_getMember(k,".handle"));
    va->setPrimitiveType((sf::PrimitiveType)args[1].i);
    return nil;
}
ZObject VertexArray__resize(ZObject *args, int n)
{
    if (n != 2)
        return Z_Err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != vaclass)
        return Z_Err(TypeError, "Argument 1  must be instance of VertexArray");
    if (args[1].type != Z_INT)
        return Z_Err(TypeError, "Argument 2 must be an integer!");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::VertexArray *va = (sf::VertexArray *)AS_PTR(KlassObj_getMember(k,".handle"));
    va->resize(args[1].i);
    return nil;
}
ZObject VertexArray__setKth(ZObject *args, int n)
{
    if (n != 4)
        return Z_Err(ArgumentError, "3 arguments needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != vaclass)
        return Z_Err(TypeError, "Argument 1  must be instance of VertexArray");
    if (args[1].type != Z_INT)
        return Z_Err(TypeError, "Argument 1 must be an integer!");
    if (args[2].type != Z_FLOAT || args[3].type != Z_FLOAT)
        return Z_Err(TypeError, "Argument 3 and 4 must be floats!");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::VertexArray *va = (sf::VertexArray *)AS_PTR(KlassObj_getMember(k,".handle"));
    (*va)[args[1].i].position = sf::Vector2f(args[2].f, args[3].f);
    return nil;
}
ZObject VertexArray__del(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != vaclass)
        return nil;
    KlassObject *k = (KlassObject *)args[0].ptr;
    if (KlassObj_getMember(k,".handle").type == Z_NIL)
        return nil;
    sf::VertexArray *e = (sf::VertexArray *)AS_PTR(KlassObj_getMember(k,".handle"));
    delete e;
    return nil;
}
// Font
ZObject Font__construct(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != fontclass)
        return Z_Err(ArgumentError, "1 argument self needed which must be instance of Font");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Font *e = new sf::Font;
    KlassObj_setMember(k,".handle", ZObjFromPtr(e));
    return nil; // values returned by consructors are ignored anyway
}
ZObject Font__loadFromFile(ZObject *args, int n)
{
    if (n != 2)
        return Z_Err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != fontclass)
        return Z_Err(TypeError, "Argument 1 must be instance of Font");
    if (args[1].type != Z_STR)
        return Z_Err(TypeError, "Argument 2 must be a string!");
    auto fname = AS_STR(args[1]);
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Font *f = (sf::Font *)AS_PTR(KlassObj_getMember(k,".handle"));
    f->loadFromFile(fname->val);
    return nil;
}
ZObject Font__del(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != fontclass)
        return nil;
    KlassObject *k = (KlassObject *)args[0].ptr;
    if (KlassObj_getMember(k,".handle").type == Z_NIL)
        return nil;
    sf::Font *e = (sf::Font *)AS_PTR(KlassObj_getMember(k,".handle"));
    // delete e; //Deleting this was causing SegFault
    // even tho no illegal memory access was made by Plutonium
    // Prolly a SFML thing
    return nil; // values returned by consructors are ignored anyway
}
// Text
ZObject Text__construct(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != textclass)
        return Z_Err(ArgumentError, "1 argument self needed which must be instance of Text");
    KlassObject *k = (KlassObject *)args[0].ptr;
    auto e = new sf::Text;
    KlassObj_setMember(k,".handle", ZObjFromPtr(e));
    return nil; // values returned by consructors are ignored anyway
}
ZObject Text__setCharacterSize(ZObject *args, int n)
{
    if (n != 2)
        return Z_Err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != textclass)
        return Z_Err(TypeError, "Argument 1 must be instance of Text");
    if (args[1].type != Z_INT)
        return Z_Err(TypeError, "Argument 2 must be an integer!");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Text *t = (sf::Text *)AS_PTR(KlassObj_getMember(k,".handle"));
    t->setCharacterSize(args[1].i);
    return nil;
}
ZObject Text__setPostion(ZObject *args, int n)
{
    if (n != 3)
        return Z_Err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != textclass)
        return Z_Err(TypeError, "Argument 1 must be instance of Text");
    if (args[1].type != Z_FLOAT || args[2].type != Z_FLOAT)
        return Z_Err(TypeError, "Argument 2 and 3 must be an floats!");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Text *t = (sf::Text *)AS_PTR(KlassObj_getMember(k,".handle"));
    t->setPosition(sf::Vector2f(args[1].f, args[2].f));
    return nil;
}
ZObject Text__setString(ZObject *args, int n)
{
    if (n != 2)
        return Z_Err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != textclass)
        return Z_Err(TypeError, "Argument 1 must be instance of Text");
    if (args[1].type != Z_STR)
        return Z_Err(TypeError, "Argument 2 must be a string!");
    auto str = AS_STR(args[1]);
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Text *t = (sf::Text *)AS_PTR(KlassObj_getMember(k,".handle"));
    t->setString(str->val);
    return nil;
}
ZObject Text__setFont(ZObject *args, int n)
{
    if (n != 2)
        return Z_Err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != textclass)
        return Z_Err(TypeError, "Argument 1 must be instance of Text");
    if (args[1].type != Z_OBJ || ((KlassObject *)args[1].ptr)->klass != fontclass)
        return Z_Err(TypeError, "Argument 2 must be an instance of Font!");
    KlassObject *k1 = (KlassObject *)args[1].ptr;
    sf::Font *f = (sf::Font *)AS_PTR(KlassObj_getMember(k1,".handle"));
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Text *t = (sf::Text *)AS_PTR(KlassObj_getMember(k,".handle"));
    t->setFont(*(sf::Font *)AS_PTR(KlassObj_getMember(k1,".handle")));
    vm_markImportant(k1);
    return nil;
}
ZObject Text__setFillColor(ZObject *args, int n)
{
    if (n != 2)
        return Z_Err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != textclass)
        return Z_Err(TypeError, "Argument 1 must be instance of Text");
    if (args[1].type != Z_OBJ || ((KlassObject *)args[1].ptr)->klass != colorclass)
        return Z_Err(TypeError, "Argument 2 must be an instance of Color!");
    KlassObject *k1 = (KlassObject *)args[1].ptr;
    sf::Color *f = (sf::Color *)AS_PTR(KlassObj_getMember(k1,".handle"));
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Text *t = (sf::Text *)AS_PTR(KlassObj_getMember(k,".handle"));
    t->setFillColor(*f);
    vm_markImportant(k1);
    return nil;
}
ZObject Text__del(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != textclass)
        return nil;
    KlassObject *k = (KlassObject *)args[0].ptr;
    if (KlassObj_getMember(k,".handle").type == Z_NIL)
        return nil;
    sf::Text *e = (sf::Text *)AS_PTR(KlassObj_getMember(k,".handle"));
    delete e;
    return nil;
}

// Sprite
ZObject Sprite__construct(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != spriteclass)
        return Z_Err(ArgumentError, "1 argument self needed which must be instance of Sprite");
    KlassObject *k = (KlassObject *)args[0].ptr;
    auto e = new sf::Sprite;
    KlassObj_setMember(k,".handle", ZObjFromPtr(e));
    return nil; // values returned by consructors are ignored anyway
}
ZObject Sprite__setTexture(ZObject *args, int n)
{
    if (n != 2)
        return Z_Err(ArgumentError, "2 arguments needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != spriteclass)
        return Z_Err(TypeError, "Argument 1 must be instance of Sprite");
    if (args[1].type != Z_OBJ || ((KlassObject *)args[1].ptr)->klass != textureclass)
        return Z_Err(TypeError, "Argument 2 must be an instance of Texture!");
    KlassObject *k1 = (KlassObject *)args[1].ptr;
    sf::Texture *f = (sf::Texture *)AS_PTR(KlassObj_getMember(k1,".handle"));
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Sprite *t = (sf::Sprite *)AS_PTR(KlassObj_getMember(k,".handle"));
    t->setTexture(*(sf::Texture *)AS_PTR(KlassObj_getMember(k1,".handle")));
    vm_markImportant(k1);
    return nil;
}
ZObject Sprite__del(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != spriteclass)
        return nil;
    KlassObject *k = (KlassObject *)args[0].ptr;
    if (KlassObj_getMember(k,".handle").type == Z_NIL)
        return nil;
    sf::Sprite *e = (sf::Sprite *)AS_PTR(KlassObj_getMember(k,".handle"));
    delete e;
    return nil;
}
// FloatRect
ZObject FloatRect__intersects(ZObject *args, int n)
{
    if (n != 2)
        return Z_Err(ArgumentError, "2 arguments required");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != floatrectclass)
        return Z_Err(TypeError, "Argument 1 must be an instance of FloatRect");
    if (args[1].type != Z_OBJ || ((KlassObject *)args[1].ptr)->klass != floatrectclass)
        return Z_Err(TypeError, "Argument 2 must be an instance of FloatRect");
    KlassObject *k1 = (KlassObject *)args[0].ptr;
    KlassObject *k2 = (KlassObject *)args[1].ptr;
    sf::FloatRect v1;
    sf::FloatRect v2;
    v1.width = AS_DOUBLE(KlassObj_getMember(k1,"width"));
    v1.height = AS_DOUBLE(KlassObj_getMember(k1,"height"));
    v1.left = AS_DOUBLE(KlassObj_getMember(k1,"left"));
    v1.top = AS_DOUBLE(KlassObj_getMember(k1,"top"));

    v2.width = AS_DOUBLE(KlassObj_getMember(k2,"width"));
    v2.height = AS_DOUBLE(KlassObj_getMember(k2,"height"));
    v2.left = AS_DOUBLE(KlassObj_getMember(k2,"left"));
    v2.top = AS_DOUBLE(KlassObj_getMember(k2,"top"));

    return ZObjFromBool(v1.intersects(v2));
}
