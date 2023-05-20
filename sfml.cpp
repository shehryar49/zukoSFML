#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "sfml.h"
#include <stdio.h>

Klass* renderwinclass, * circleclass, * rectclass, * evclass, * colorclass;
Klass* clockclass;
Klass* timeclass;
Klass* vaclass;
Klass* fontclass;
Klass* textclass;
Klass* textureclass;
Klass* spriteclass;
Klass* vector2fclass;
Klass* floatrectclass;

PltObject nil;
PltObject init()
{
    nil.type = PLT_NIL;
    //Initialize classes
    renderwinclass = vm_allocKlass();
    renderwinclass->name = "RenderWindow";
    renderwinclass->members.emplace("__construct__", PObjFromMethod("__construct__", &RenderWindow__construct, renderwinclass));
    renderwinclass->members.emplace("clear", PObjFromMethod("clear", &RenderWindow__clear, renderwinclass));
    renderwinclass->members.emplace("draw", PObjFromMethod("draw", &RenderWindow__draw, renderwinclass));
    renderwinclass->members.emplace("display", PObjFromMethod("display", &RenderWindow__display, renderwinclass));
    renderwinclass->members.emplace("pollEvent", PObjFromMethod("pollEvent", &RenderWindow__pollevent, renderwinclass));
    renderwinclass->members.emplace("setFramerateLimit", PObjFromMethod("setFramerateLimit", &RenderWindow__setFrameRateLimit, renderwinclass));
    renderwinclass->members.emplace("close", PObjFromMethod("close", &RenderWindow__close, renderwinclass));

    circleclass = vm_allocKlass();
    circleclass->name = "Circle";
    circleclass->members.emplace("__construct__", PObjFromMethod("__construct__", &Circle__construct, circleclass));
    circleclass->members.emplace("setPosition", PObjFromMethod("setPosition", &Circle__setpos, circleclass));
    circleclass->members.emplace("setFillColor", PObjFromMethod("setFillColor", &Circle__setfillcolor, circleclass));
    circleclass->members.emplace("setPointCount", PObjFromMethod("setPointCount", &Circle__setpointcount, circleclass));
    circleclass->members.emplace("__del__", PObjFromMethod("__del__", &Circle__del, circleclass));
    colorclass = vm_allocKlass();
    colorclass->name = "Color";
    colorclass->members.emplace("__construct__", PObjFromMethod("__construct__", &Color__construct, colorclass));
    colorclass->members.emplace("__del__", PObjFromMethod("__del__", &Color__del, colorclass));

    rectclass = vm_allocKlass();
    rectclass->name = "Rectangle";
    rectclass->members.emplace("__construct__", PObjFromMethod("__construct__", &Rect__construct, rectclass));
    rectclass->members.emplace("setPosition", PObjFromMethod("setPosition", &Rect__setpos, rectclass));
    rectclass->members.emplace("setFillColor", PObjFromMethod("setFillColor", &Rect__setfillcolor, rectclass));
    rectclass->members.emplace("setOutlineColor", PObjFromMethod("setOutlineColor", &Rect__setOutlineColor, rectclass));
    rectclass->members.emplace("setOutlineThickness", PObjFromMethod("setOutlineThickness", &Rect__setOutlineThickness, rectclass));
    rectclass->members.emplace("setPosition", PObjFromMethod("setPosition", &Rect__setpos, rectclass));
    rectclass->members.emplace("getPosition", PObjFromMethod("getPosition", &Rect__getPosition, rectclass));
    rectclass->members.emplace("getGlobalBounds", PObjFromMethod("getGlobalBounds", &Rect__getGlobalBounds, rectclass));
    rectclass->members.emplace("setSize", PObjFromMethod("setSize", &Rect__setSize, rectclass));


    evclass = vm_allocKlass();
    evclass->name = "Event";
    evclass->members.emplace("__construct__", PObjFromMethod("__construct__", &Event__construct, evclass));
    evclass->members.emplace("__del__", PObjFromMethod("__del__", &Event__del, evclass));
    evclass->members.emplace("type", nil);
    evclass->members.emplace("keycode", nil);

    textureclass = vm_allocKlass();
    textureclass->name = "Texture";
    textureclass->members.emplace("__construct__", PObjFromMethod("__construct__", &Texture__construct, textureclass));
    textureclass->members.emplace("loadFromFile", PObjFromMethod("loadFromFile", &Texture__loadFromFile, textureclass));
    textureclass->members.emplace("__del__", PObjFromMethod("__del__", &Texture__del, textureclass));

    clockclass = vm_allocKlass();
    clockclass->name = "Clock";
    clockclass->members.emplace("__construct__", PObjFromMethod("__construct__", &Clock__construct, clockclass));
    clockclass->members.emplace("restart", PObjFromMethod("restart", &Clock__restart, clockclass));
    clockclass->members.emplace("__del__", PObjFromMethod("__del__", &Clock__del, clockclass));

    vaclass = vm_allocKlass();
    vaclass->name = "VertexArray";
    vaclass->members.emplace("__construct__", PObjFromMethod("__construct__", &VertexArray__construct, vaclass));
    vaclass->members.emplace("resize", PObjFromMethod("resize", &VertexArray__resize, vaclass));
    vaclass->members.emplace("setPrimitiveType", PObjFromMethod("setPrimitiveType", &VertexArray__setPrimType, vaclass));
    vaclass->members.emplace("setKth", PObjFromMethod("setKth", &VertexArray__setKth, vaclass));
    vaclass->members.emplace("__del__", PObjFromMethod("__del__", &VertexArray__del, vaclass));

    fontclass = vm_allocKlass();
    fontclass->name = "Font";
    fontclass->members.emplace("__construct__", PObjFromMethod("__construct__", &Font__construct, fontclass));
    fontclass->members.emplace("loadFromFile", PObjFromMethod("loadFromFile", &Font__loadFromFile, fontclass));
    fontclass->members.emplace("__del__", PObjFromMethod("__del__", &Font__del, fontclass));

    spriteclass = vm_allocKlass();
    spriteclass->name = "Sprite";
    spriteclass->members.emplace("__construct__", PObjFromMethod("__construct__", &Sprite__construct, spriteclass));
    spriteclass->members.emplace("setTexture", PObjFromMethod("setTexture", &Sprite__setTexture, spriteclass));
    spriteclass->members.emplace("__del__", PObjFromMethod("__del__", &Sprite__del, spriteclass));

    textclass = vm_allocKlass();
    textclass->name = "Text";
    textclass->members.emplace("__construct__", PObjFromMethod("__construct__", &Text__construct, textclass));
    textclass->members.emplace("setCharacterSize", PObjFromMethod("setCharacterSize", &Text__setCharacterSize, textclass));
    textclass->members.emplace("setString", PObjFromMethod("setString", &Text__setString, textclass));
    textclass->members.emplace("setPosition", PObjFromMethod("setPosition", &Text__setPostion, textclass));
    textclass->members.emplace("setFont", PObjFromMethod("setFont", &Text__setFont, textclass));
    textclass->members.emplace("setFillColor", PObjFromMethod("setFillColor", &Text__setFillColor, textclass));
    textclass->members.emplace("__del__", PObjFromMethod("__del__", &Text__del, textclass));



    timeclass = vm_allocKlass();
    timeclass->name = "Time";
    timeclass->members.emplace("asSeconds", PObjFromMethod("asSeconds", &Time__asSeconds, timeclass));
    timeclass->members.emplace("__del__", PObjFromMethod("__del__", &Time__del, timeclass));

    vector2fclass = vm_allocKlass();
    vector2fclass->name = "Vector2f";
    vector2fclass->members.emplace("x", nil);
    vector2fclass->members.emplace("y", nil);

    floatrectclass = vm_allocKlass();
    floatrectclass->name = "FloatRect";
    floatrectclass->members.emplace("width", nil);
    floatrectclass->members.emplace("height", nil);
    floatrectclass->members.emplace("top", nil);
    floatrectclass->members.emplace("left", nil);
    floatrectclass->members.emplace("intersects", PObjFromMethod("intersects", &FloatRect__intersects, floatrectclass));

    vm_markImportant(timeclass);
    vm_markImportant(vector2fclass);
    vm_markImportant(floatrectclass);

    //Add classes to module
    Module* sfml = vm_allocModule();
    sfml->name = "sfml";
    sfml->members.emplace("RenderWindow", PObjFromKlass(renderwinclass));
    sfml->members.emplace("Circle", PObjFromKlass(circleclass));
    sfml->members.emplace("Color", PObjFromKlass(colorclass));
    sfml->members.emplace("Rectangle", PObjFromKlass(rectclass));
    sfml->members.emplace("Event", PObjFromKlass(evclass));
    sfml->members.emplace("Clock", PObjFromKlass(clockclass));
    sfml->members.emplace("VertexArray", PObjFromKlass(vaclass));
    sfml->members.emplace("Font", PObjFromKlass(fontclass));
    sfml->members.emplace("Text", PObjFromKlass(textclass));
    sfml->members.emplace("Texture", PObjFromKlass(textureclass));
    sfml->members.emplace("Sprite", PObjFromKlass(spriteclass));
    sfml->members.emplace("Vector2f", PObjFromKlass(vector2fclass));

    sfml->members.emplace("getMousePosition", PObjFromFunction("getMousePosition", &getMousePosition));

    sfml->members.emplace("EventClosed", PObjFromInt(sf::Event::Closed));
    sfml->members.emplace("EventKeyPressed", PObjFromInt(sf::Event::KeyPressed));
    sfml->members.emplace("EventMouseButtonPressed", PObjFromInt(sf::Event::MouseButtonPressed));
    sfml->members.emplace("EventMouseMoved", PObjFromInt(sf::Event::MouseMoved));
    sfml->members.emplace("KeyboardA", PObjFromInt(sf::Keyboard::A));
    sfml->members.emplace("KeyboardS", PObjFromInt(sf::Keyboard::S));
    sfml->members.emplace("KeyboardD", PObjFromInt(sf::Keyboard::D));
    sfml->members.emplace("KeyboardW", PObjFromInt(sf::Keyboard::W));
    sfml->members.emplace("KeyboardUp", PObjFromInt(sf::Keyboard::Up));
    sfml->members.emplace("KeyboardDown", PObjFromInt(sf::Keyboard::Down));
    sfml->members.emplace("KeyboardLeft", PObjFromInt(sf::Keyboard::Left));
    sfml->members.emplace("KeyboardRight", PObjFromInt(sf::Keyboard::Right));
    sfml->members.emplace("KeyboardEsc", PObjFromInt(sf::Keyboard::Escape));
    sfml->members.emplace("KeyboardEnter", PObjFromInt(sf::Keyboard::Enter));
    //More keymappings to be added later

    sfml->members.emplace("LinesStrip", PObjFromInt(sf::LinesStrip));
    sfml->members.emplace("MouseLeft", PObjFromInt(sf::Mouse::Left));


    return PObjFromModule(sfml);

}
//Global Module functions
PltObject getMousePosition(PltObject* args, int n)
{
    if (n != 1)
        return Plt_Err(ARGUMENT_ERROR, "1 argument needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
    {
        return Plt_Err(TYPE_ERROR, "Argument 1 must be an instance of RenderWindow");
    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RenderWindow* w = (sf::RenderWindow*)k->members[".handle"].ptr;
    KlassInstance* ki = vm_allocKlassInstance();
    ki->klass = vector2fclass;
    ki->members = vector2fclass->members;
    sf::Vector2i v = sf::Mouse::getPosition(*w);
    ki->members["x"] = PObjFromDouble(v.x);
    ki->members["y"] = PObjFromDouble(v.y);
    return PObjFromKlassInst(ki);
}
//RenderWindow
PltObject RenderWindow__construct(PltObject* args, int n)
{
    if (n != 4)
        return Plt_Err(ARGUMENT_ERROR, "4 arguments needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
        return Plt_Err(TYPE_ERROR, "self must be an instance of RenderWindow");
    if (args[1].type != 'i' || args[2].type != 'i' || args[3].type != 's')
        return Plt_Err(TYPE_ERROR, "Invalid types of arguments!");
    string& title = *((string*)args[3].ptr);
    sf::RenderWindow* w = new sf::RenderWindow(sf::VideoMode(args[1].i, args[2].i), title);
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    k->members.emplace(".handle", PObjFromPtr((void*)w)); //we use .handle so that user can't change it's value
    return nil;//
}
PltObject RenderWindow__clear(PltObject* args, int n)
{
    if (n != 1 && n != 2)
    {
        return Plt_Err(ARGUMENT_ERROR, "1 or 2 arguments needed!");
    }
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
    {
        return Plt_Err(TYPE_ERROR, "self must be an instance of RenderWindow");

    }
    sf::Color c = sf::Color::Black;
    if (n == 2)
    {
        if (args[1].type != PLT_OBJ || ((KlassInstance*)args[1].ptr)->klass != colorclass)
            return Plt_Err(TYPE_ERROR, "Argument 2 must be an instance of Color");
        KlassInstance* ki = (KlassInstance*)args[1].ptr;
        sf::Color* color = (sf::Color*)ki->members[".handle"].ptr;
        c = *color;
    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RenderWindow* w = (sf::RenderWindow*)k->members[".handle"].ptr;
    w->clear(c);
    return nil;
}
PltObject RenderWindow__close(PltObject* args, int n)
{
    if (n != 1)
        return Plt_Err(ARGUMENT_ERROR, "1 argument needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
        return Plt_Err(TYPE_ERROR, "self must be an instance of RenderWindow");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RenderWindow* w = (sf::RenderWindow*)k->members[".handle"].ptr;
    w->close();
    delete w;
    k->members[".handle"] = nil;
    return nil;
}
PltObject RenderWindow__display(PltObject* args, int n)
{
    if (n != 1)
    {
        return Plt_Err(ARGUMENT_ERROR, "1 argument needed!");

    }
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
    {
        return Plt_Err(TYPE_ERROR, "self must be an instance of RenderWindow");

    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RenderWindow* w = (sf::RenderWindow*)k->members[".handle"].ptr;
    w->display();
    return nil;
}
PltObject RenderWindow__draw(PltObject* args, int n)
{
    if (n != 2)
    {
        return Plt_Err(ARGUMENT_ERROR, "2 arguments needed!");

    }
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
    {
        return Plt_Err(TYPE_ERROR, "self must be an instance of RenderWindow");

    }
    if (args[1].type != PLT_OBJ)
    {
        return Plt_Err(TYPE_ERROR, "Argument must be a drawable sfml object!");

    }
    KlassInstance* obj = (KlassInstance*)args[1].ptr;

    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RenderWindow* w = (sf::RenderWindow*)k->members[".handle"].ptr;
    if (obj->klass == circleclass)
    {
        sf::CircleShape* d = (sf::CircleShape*)obj->members[".handle"].ptr;
        w->draw(*d);
    }
    else if (obj->klass == rectclass)
    {
        sf::RectangleShape* d = (sf::RectangleShape*)obj->members[".handle"].ptr;
        w->draw(*d);
    }
    else if (obj->klass == spriteclass)
    {
        sf::Sprite* d = (sf::Sprite*)obj->members[".handle"].ptr;
        w->draw(*d);
    }
    else if (obj->klass == textclass)
    {
        sf::Text* d = (sf::Text*)obj->members[".handle"].ptr;
        w->draw(*d);
    }
    else if (obj->klass == vaclass)
    {
        sf::VertexArray* d = (sf::VertexArray*)obj->members[".handle"].ptr;
        w->draw(*d);
    }
    else
        return Plt_Err(TYPE_ERROR, "Argument must be a drawable sfml object!");
    return nil;
}
PltObject RenderWindow__pollevent(PltObject* args, int n)
{
    if (n != 2)
    {
        return Plt_Err(ARGUMENT_ERROR, "2 argument needed!");

    }
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
    {
        return Plt_Err(TYPE_ERROR, "self must be an instance of RenderWindow");

    }
    if (args[1].type != PLT_OBJ)
    {
        return Plt_Err(TYPE_ERROR, "Argument must be an instance of Event class.");

    }
    KlassInstance* obj = (KlassInstance*)args[1].ptr;
    if (obj->klass != evclass)
    {
        return Plt_Err(TYPE_ERROR, "Argument must be an instance of Event class.");

    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RenderWindow* w = (sf::RenderWindow*)k->members[".handle"].ptr;
    sf::Event* e = (sf::Event*)obj->members[".handle"].ptr;
    bool b = w->pollEvent(*e);
    if (b)
    {
        obj->members["type"] = PObjFromInt(e->type);
        if (e->type == sf::Event::KeyPressed)
            obj->members["keycode"] = PObjFromInt(e->key.code);
        if (e->type == sf::Event::MouseButtonPressed)
            obj->members.emplace("mouseButton", PObjFromInt(e->mouseButton.button));
    }
    return PObjFromBool(b);


}
PltObject RenderWindow__setFrameRateLimit(PltObject* args, int n)
{
    if (n != 2)
        return Plt_Err(ARGUMENT_ERROR, "2 argument needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != renderwinclass)
        return Plt_Err(TYPE_ERROR, "self must be an instance of RenderWindow");
    if (args[1].type != PLT_INT)
        return Plt_Err(TYPE_ERROR, "Argument 2  must be an integer.");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RenderWindow* w = (sf::RenderWindow*)k->members[".handle"].ptr;
    w->setFramerateLimit(args[1].i);
    return nil;
}

//Event
PltObject Event__construct(PltObject* args, int n)
{
    if (n != 1 || args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != evclass)
    {
        return Plt_Err(ARGUMENT_ERROR, "1 argument self needed which must be instance of event");

    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::Event* e = new sf::Event;
    k->members.emplace(".handle", PObjFromPtr(e));
    return nil;
}
PltObject Event__del(PltObject* args, int n)
{
    if (n != 1)
        return nil;
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != evclass)
        return nil;
    KlassInstance* ki = (KlassInstance*)args[0].ptr;
    if (ki->members[".handle"].type == PLT_NIL)
        return nil;
    sf::Event* ev = (sf::Event*)ki->members[".handle"].ptr;
    delete ev;
    ki->members[".handle"] = nil;
    return nil;
}
//Circle
PltObject Circle__construct(PltObject* args, int n)
{
    if (n != 1 && n != 2)
    {
        return Plt_Err(ARGUMENT_ERROR, "Two or One arguments needed!");

    }
    float radius = 0;
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != circleclass)
    {
        return Plt_Err(TYPE_ERROR, "self must be an instance of circle class!");

    }
    if (n == 2)
    {
        if (args[1].type != PLT_FLOAT)
        {
            return Plt_Err(TYPE_ERROR, "Radius must be a float!");

        }
        radius = static_cast<float>(args[1].f);
    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::CircleShape* c = new sf::CircleShape(radius);
    k->members.emplace(".handle", PObjFromPtr(c));
    return nil;

}
PltObject Circle__setpos(PltObject* args, int n)
{
    if (n != 3)
    {
        return Plt_Err(ARGUMENT_ERROR, "Three arguments needed!");

    }
    float radius = 0;
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != circleclass)
    {
        return Plt_Err(TYPE_ERROR, "self must be an instance of circle class!");

    }
    if (args[1].type != PLT_FLOAT || args[2].type != PLT_FLOAT)
    {
        return Plt_Err(TYPE_ERROR, "Position coordinates must be floats!");

    }

    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::CircleShape* c = (sf::CircleShape*)k->members[".handle"].ptr;
    float x = (float)args[1].f;
    float y = (float)args[2].f;
    c->setPosition(x, y);
    return nil;

}
PltObject Circle__setpointcount(PltObject* args, int n)
{
    if (n != 2)
    {
        return Plt_Err(ARGUMENT_ERROR, "Two arguments needed!");

    }
    float radius = 0;
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != circleclass)
    {
        return Plt_Err(TYPE_ERROR, "self must be an instance of circle class!");

    }
    if (args[1].type != PLT_INT && args[1].type != PLT_INT64)
    {
        return Plt_Err(TYPE_ERROR, "Point count must be an integer!");

    }

    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::CircleShape* c = (sf::CircleShape*)k->members[".handle"].ptr;
    if (args[1].type == PLT_INT)
        c->setPointCount(args[1].i);
    else
        c->setPointCount(args[1].l);
    return nil;
}
PltObject Circle__setfillcolor(PltObject* args, int n)
{
    if (n != 2)
        return Plt_Err(ARGUMENT_ERROR, "Two arguments needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != circleclass)
        return Plt_Err(TYPE_ERROR, "Argument 1(self) must be an instance of circle class!");
    if (args[1].type != PLT_OBJ || ((KlassInstance*)args[1].ptr)->klass != colorclass)
        return Plt_Err(TYPE_ERROR, "Argument 2 must be an instance of class Color!");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    KlassInstance* j = (KlassInstance*)args[1].ptr;
    sf::CircleShape* c = (sf::CircleShape*)k->members[".handle"].ptr;
    sf::Color* color = (sf::Color*)j->members[".handle"].ptr;
    c->setFillColor(*color);
    return nil;

}
PltObject Circle__del(PltObject* args, int n)
{
    if (n != 1)
        return nil;
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != circleclass)
        return nil;
    KlassInstance* ki = (KlassInstance*)args[0].ptr;
    if (ki->members[".handle"].type == PLT_NIL)
        return nil;
    sf::CircleShape* circle = (sf::CircleShape*)ki->members[".handle"].ptr;
    delete circle;
    ki->members[".handle"] = nil;
    return nil;
}
//Rectangle
PltObject Rect__construct(PltObject* args, int n)
{
    if (n != 3)
    {
        return Plt_Err(ARGUMENT_ERROR, "3 arguments needed!");

    }
    float width = 0;
    float height = 0;
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != rectclass)
        return Plt_Err(TYPE_ERROR, "self must be an instance of Rectangle class!");
    if (args[1].type != PLT_FLOAT || args[2].type != PLT_FLOAT)
        return Plt_Err(TYPE_ERROR, "Width and height must be floats!");

    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RectangleShape* c = new sf::RectangleShape(sf::Vector2f(args[1].f, args[2].f));
    k->members.emplace(".handle", PObjFromPtr(c));
    return nil;
}
PltObject Rect__setpos(PltObject* args, int n)
{
    if (n != 3)
    {
        return Plt_Err(ARGUMENT_ERROR, "Three arguments needed!");

    }
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != rectclass)
    {
        return Plt_Err(TYPE_ERROR, "self must be an instance of Rectangle class!");

    }
    if (args[1].type != PLT_FLOAT || args[2].type != PLT_FLOAT)
    {
        return Plt_Err(TYPE_ERROR, "Position coordinates must be floats!");

    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RectangleShape* c = (sf::RectangleShape*)k->members[".handle"].ptr;
    c->setPosition(args[1].f, args[2].f);
    return nil;
}
PltObject Rect__setSize(PltObject* args, int n)
{
    if (n != 3)
    {
        return Plt_Err(ARGUMENT_ERROR, "Three arguments needed!");

    }
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != rectclass)
    {
        return Plt_Err(TYPE_ERROR, "self must be an instance of Rectangle class!");

    }
    if (args[1].type != PLT_FLOAT || args[2].type != PLT_FLOAT)
    {
        return Plt_Err(TYPE_ERROR, "Size values must be floats!");

    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RectangleShape* c = (sf::RectangleShape*)k->members[".handle"].ptr;
    c->setSize(sf::Vector2f(args[1].f, args[2].f));
    return nil;
}
PltObject Rect__getPosition(PltObject* args, int n)
{
    if (n != 1)
        return Plt_Err(ARGUMENT_ERROR, "1 argument needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != rectclass)
        return Plt_Err(TYPE_ERROR, "self must be an instance of Rectangle class!");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RectangleShape* c = (sf::RectangleShape*)k->members[".handle"].ptr;
    KlassInstance* ki = vm_allocKlassInstance();
    ki->klass = vector2fclass;
    ki->members = vector2fclass->members;
    sf::Vector2f v = c->getPosition();
    ki->members["x"] = PObjFromDouble(v.x);
    ki->members["y"] = PObjFromDouble(v.y);
    return PObjFromKlassInst(ki);
}
PltObject Rect__getGlobalBounds(PltObject* args, int n)
{
    if (n != 1)
        return Plt_Err(ARGUMENT_ERROR, "1 argument needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != rectclass)
        return Plt_Err(TYPE_ERROR, "self must be an instance of Rectangle class!");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RectangleShape* c = (sf::RectangleShape*)k->members[".handle"].ptr;
    KlassInstance* ki = vm_allocKlassInstance();
    ki->klass = floatrectclass;
    ki->members = floatrectclass->members;
    sf::FloatRect v = c->getGlobalBounds();
    ki->members["width"] = PObjFromDouble(v.width);
    ki->members["height"] = PObjFromDouble(v.height);
    ki->members["left"] = PObjFromDouble(v.left);
    ki->members["top"] = PObjFromDouble(v.top);
    return PObjFromKlassInst(ki);
}
PltObject Rect__setOutlineThickness(PltObject* args, int n)
{
    if (n != 2)
    {
        return Plt_Err(ARGUMENT_ERROR, "Three arguments needed!");

    }
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != rectclass)
    {
        return Plt_Err(TYPE_ERROR, "self must be an instance of Rectangle class!");

    }
    if (args[1].type != PLT_FLOAT)
    {
        return Plt_Err(TYPE_ERROR, "Argument 1 must be a float!");

    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::RectangleShape* c = (sf::RectangleShape*)k->members[".handle"].ptr;
    c->setOutlineThickness(args[1].f);
    return nil;
}
PltObject Rect__setfillcolor(PltObject* args, int n)
{
    if (n != 2)
        return Plt_Err(ARGUMENT_ERROR, "Two arguments needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != rectclass)
        return Plt_Err(TYPE_ERROR, "Argument 1(self) must be an instance of Rectangle class!");
    if (args[1].type != PLT_OBJ || ((KlassInstance*)args[1].ptr)->klass != colorclass)
        return Plt_Err(TYPE_ERROR, "Argument 2 must be an instance of class Color!");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    KlassInstance* j = (KlassInstance*)args[1].ptr;
    sf::RectangleShape* c = (sf::RectangleShape*)k->members[".handle"].ptr;
    sf::Color* color = (sf::Color*)j->members[".handle"].ptr;
    c->setFillColor(*color);
    return nil;
}
PltObject Rect__setOutlineColor(PltObject* args, int n)
{
    if (n != 2)
        return Plt_Err(ARGUMENT_ERROR, "Two arguments needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != rectclass)
        return Plt_Err(TYPE_ERROR, "Argument 1(self) must be an instance of Rectangle class!");
    if (args[1].type != PLT_OBJ || ((KlassInstance*)args[1].ptr)->klass != colorclass)
        return Plt_Err(TYPE_ERROR, "Argument 2 must be an instance of class Color!");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    KlassInstance* j = (KlassInstance*)args[1].ptr;
    sf::RectangleShape* c = (sf::RectangleShape*)k->members[".handle"].ptr;
    sf::Color* color = (sf::Color*)j->members[".handle"].ptr;
    c->setOutlineColor(*color);
    return nil;
}
PltObject Rect__del(PltObject* args, int n)
{
    if (n != 1)
        return nil;
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != rectclass)
        return nil;
    KlassInstance* ki = (KlassInstance*)args[0].ptr;
    if (ki->members[".handle"].type == PLT_NIL)
        return nil;
    sf::RectangleShape* rect = (sf::RectangleShape*)ki->members[".handle"].ptr;
    delete rect;
    ki->members[".handle"] = nil;
    return nil;
}
//Color
PltObject Color__construct(PltObject* args, int n)
{
    if (n != 4)
    {
        return Plt_Err(ARGUMENT_ERROR, "4 arguments needed!");

    }
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != colorclass)
    {
        return Plt_Err(TYPE_ERROR, "self must be an instance of Color class!");

    }
    if (args[1].type != PLT_INT || args[2].type != PLT_INT || args[3].type != PLT_INT)
    {
        return Plt_Err(TYPE_ERROR, "RGB values must be integers!");

    }
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::Color* c = new sf::Color(args[1].i, args[2].i, args[3].i);
    k->members.emplace(".handle", PObjFromPtr(c));
    return nil;
}
PltObject Color__del(PltObject* args, int n)
{
    if (n != 1)
        return nil;
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != colorclass)
        return nil;
    KlassInstance* ki = (KlassInstance*)args[0].ptr;
    if (ki->members[".handle"].type == PLT_NIL)
        return nil;
    sf::Color* color = (sf::Color*)ki->members[".handle"].ptr;
    delete color;
    ki->members[".handle"] = nil;
    return nil;
}
//Clock
PltObject Clock__construct(PltObject* args, int n)
{
    if (n != 1 || args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != clockclass)
        return Plt_Err(ARGUMENT_ERROR, "1 argument self needed which must be instance of Clock");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::Clock* e = new sf::Clock;
    k->members.emplace(".handle", PObjFromPtr(e));
    return nil; //values returned by consructors are ignored anyway
}
PltObject Clock__restart(PltObject* args, int n)
{
    if (n != 1 || args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != clockclass)
        return Plt_Err(ARGUMENT_ERROR, "1 argument self needed which must be instance of Clock");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::Clock* e = (sf::Clock*)k->members[".handle"].ptr;
    sf::Time* t = new sf::Time(e->restart());
    KlassInstance* ki = vm_allocKlassInstance();
    ki->klass = timeclass;
    ki->members = timeclass->members;
    ki->members.emplace(".handle", PObjFromPtr(t));
    return PObjFromKlassInst(ki);
}
PltObject Clock__del(PltObject* args, int n)
{
    if (n != 1 || args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != clockclass)
        return nil;
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    if (k->members[".handle"].type == PLT_NIL)
        return nil;
    sf::Clock* e = (sf::Clock*)k->members[".handle"].ptr;
    delete e;
    k->members[".handle"] = nil;
    return nil;
}

//Time
PltObject Time__asSeconds(PltObject* args, int n)
{
    if (n != 1 || args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != timeclass)
        return Plt_Err(ARGUMENT_ERROR, "1 argument self needed which must be instance of Time");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::Time* t = (sf::Time*)k->members[".handle"].ptr;

    return PObjFromDouble(t->asSeconds());
}
PltObject Time__del(PltObject* args, int n)
{
    if (n != 1 || args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != timeclass)
        return nil;
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    if (k->members[".handle"].type == PLT_NIL)
        return nil;
    sf::Time* t = (sf::Time*)k->members[".handle"].ptr;
    delete t;
    k->members[".handle"] = nil;
    return nil;
}
//Texture
PltObject Texture__construct(PltObject* args, int n)
{
    if (n != 1 || args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != textureclass)
        return Plt_Err(ARGUMENT_ERROR, "1 argument self needed which must be instance of Texture");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::Texture* e = new sf::Texture;
    k->members.emplace(".handle", PObjFromPtr(e));
    return nil; //values returned by consructors are ignored anyway
}
PltObject Texture__loadFromFile(PltObject* args, int n)
{
    if (n != 2)
        return Plt_Err(ARGUMENT_ERROR, "2 arguments needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != textureclass)
        return Plt_Err(TYPE_ERROR, "Argument 1 must be instance of Texture");
    if (args[1].type != PLT_STR)
        return Plt_Err(TYPE_ERROR, "Argument 2 must be a string!");
    string& fname = *(string*)args[1].ptr;
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::Texture* f = (sf::Texture*)k->members[".handle"].ptr;
    f->loadFromFile(fname);
    return nil;
}
PltObject Texture__del(PltObject* args, int n)
{
    if (n != 1 || args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != textureclass)
        return nil;
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    if (k->members[".handle"].type == PLT_NIL)
        return nil;
    sf::Texture* e = (sf::Texture*)k->members[".handle"].ptr;
    // delete e;
    return nil; //values returned by consructors/destructors are ignored anyway
}
//VertexArray
PltObject VertexArray__construct(PltObject* args, int n)
{
    if (n != 1 || args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != vaclass)
        return Plt_Err(ARGUMENT_ERROR, "1 argument self needed which must be instance of VertexArray");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::VertexArray* e = new sf::VertexArray;
    k->members.emplace(".handle", PObjFromPtr(e));
    return nil; //values returned by consructors are ignored anyway
}
PltObject VertexArray__setPrimType(PltObject* args, int n)
{
    if (n != 2)
        return Plt_Err(ARGUMENT_ERROR, "2 arguments needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != vaclass)
        return Plt_Err(TYPE_ERROR, "Argument 1  must be instance of VertexArray");
    if (args[1].type != PLT_INT)
        return Plt_Err(TYPE_ERROR, "Argument 2 must be an integer!");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::VertexArray* va = (sf::VertexArray*)k->members[".handle"].ptr;
    va->setPrimitiveType((sf::PrimitiveType)args[1].i);
    return nil;
}
PltObject VertexArray__resize(PltObject* args, int n)
{
    if (n != 2)
        return Plt_Err(ARGUMENT_ERROR, "2 arguments needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != vaclass)
        return Plt_Err(TYPE_ERROR, "Argument 1  must be instance of VertexArray");
    if (args[1].type != PLT_INT)
        return Plt_Err(TYPE_ERROR, "Argument 2 must be an integer!");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::VertexArray* va = (sf::VertexArray*)k->members[".handle"].ptr;
    va->resize(args[1].i);
    return nil;
}
PltObject VertexArray__setKth(PltObject* args, int n)
{
    if (n != 4)
        return Plt_Err(ARGUMENT_ERROR, "3 arguments needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != vaclass)
        return Plt_Err(TYPE_ERROR, "Argument 1  must be instance of VertexArray");
    if (args[1].type != PLT_INT)
        return Plt_Err(TYPE_ERROR, "Argument 1 must be an integer!");
    if (args[2].type != PLT_FLOAT || args[3].type != PLT_FLOAT)
        return Plt_Err(TYPE_ERROR, "Argument 3 and 4 must be floats!");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::VertexArray* va = (sf::VertexArray*)k->members[".handle"].ptr;
    (*va)[args[1].i].position = sf::Vector2f(args[2].f, args[3].f);
    return nil;
}
PltObject VertexArray__del(PltObject* args, int n)
{
    if (n != 1 || args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != vaclass)
        return nil;
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    if (k->members["handle"].type == PLT_NIL)
        return nil;
    sf::VertexArray* e = (sf::VertexArray*)k->members[".handle"].ptr;
    delete e;
}
//Font
PltObject Font__construct(PltObject* args, int n)
{
    if (n != 1 || args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != fontclass)
        return Plt_Err(ARGUMENT_ERROR, "1 argument self needed which must be instance of Font");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::Font* e = new sf::Font;
    k->members.emplace(".handle", PObjFromPtr(e));
    return nil; //values returned by consructors are ignored anyway
}
PltObject Font__loadFromFile(PltObject* args, int n)
{
    if (n != 2)
        return Plt_Err(ARGUMENT_ERROR, "2 arguments needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != fontclass)
        return Plt_Err(TYPE_ERROR, "Argument 1 must be instance of Font");
    if (args[1].type != PLT_STR)
        return Plt_Err(TYPE_ERROR, "Argument 2 must be a string!");
    string& fname = *(string*)args[1].ptr;
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::Font* f = (sf::Font*)k->members[".handle"].ptr;
    f->loadFromFile(fname);
    return nil;
}
PltObject Font__del(PltObject* args, int n)
{
    if (n != 1 || args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != fontclass)
        return nil;
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    if (k->members[".handle"].type == PLT_NIL)
        return nil;
    sf::Font* e = (sf::Font*)k->members[".handle"].ptr;
    // delete e; //Deleting this was causing SegFault
    //even tho no illegal memory access was made by Plutonium
    //Prolly a SFML thing
    return nil; //values returned by consructors are ignored anyway
}
//Text
PltObject Text__construct(PltObject* args, int n)
{
    if (n != 1 || args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != textclass)
        return Plt_Err(ARGUMENT_ERROR, "1 argument self needed which must be instance of Text");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    auto e = new sf::Text;
    k->members.emplace(".handle", PObjFromPtr(e));
    return nil; //values returned by consructors are ignored anyway
}
PltObject Text__setCharacterSize(PltObject* args, int n)
{
    if (n != 2)
        return Plt_Err(ARGUMENT_ERROR, "2 arguments needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != textclass)
        return Plt_Err(TYPE_ERROR, "Argument 1 must be instance of Text");
    if (args[1].type != PLT_INT)
        return Plt_Err(TYPE_ERROR, "Argument 2 must be an integer!");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::Text* t = (sf::Text*)k->members[".handle"].ptr;
    t->setCharacterSize(args[1].i);
    return nil;
}
PltObject Text__setPostion(PltObject* args, int n)
{
    if (n != 3)
        return Plt_Err(ARGUMENT_ERROR, "2 arguments needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != textclass)
        return Plt_Err(TYPE_ERROR, "Argument 1 must be instance of Text");
    if (args[1].type != PLT_FLOAT || args[2].type != PLT_FLOAT)
        return Plt_Err(TYPE_ERROR, "Argument 2 and 3 must be an floats!");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::Text* t = (sf::Text*)k->members[".handle"].ptr;
    t->setPosition(sf::Vector2f(args[1].f, args[2].f));
    return nil;
}
PltObject Text__setString(PltObject* args, int n)
{
    if (n != 2)
        return Plt_Err(ARGUMENT_ERROR, "2 arguments needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != textclass)
        return Plt_Err(TYPE_ERROR, "Argument 1 must be instance of Text");
    if (args[1].type != PLT_STR)
        return Plt_Err(TYPE_ERROR, "Argument 2 must be a string!");
    string& str = *(string*)args[1].ptr;
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::Text* t = (sf::Text*)k->members[".handle"].ptr;
    t->setString(str);
    return nil;
}
PltObject Text__setFont(PltObject* args, int n)
{
    if (n != 2)
        return Plt_Err(ARGUMENT_ERROR, "2 arguments needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != textclass)
        return Plt_Err(TYPE_ERROR, "Argument 1 must be instance of Text");
    if (args[1].type != PLT_OBJ || ((KlassInstance*)args[1].ptr)->klass != fontclass)
        return Plt_Err(TYPE_ERROR, "Argument 2 must be an instance of Font!");
    KlassInstance* k1 = (KlassInstance*)args[1].ptr;
    sf::Font* f = (sf::Font*)k1->members[".handle"].ptr;
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::Text* t = (sf::Text*)k->members[".handle"].ptr;
    t->setFont(*(sf::Font*)k1->members[".handle"].ptr);
    vm_markImportant(k1);
    return nil;
}
PltObject Text__setFillColor(PltObject* args, int n)
{
    if (n != 2)
        return Plt_Err(ARGUMENT_ERROR, "2 arguments needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != textclass)
        return Plt_Err(TYPE_ERROR, "Argument 1 must be instance of Text");
    if (args[1].type != PLT_OBJ || ((KlassInstance*)args[1].ptr)->klass != colorclass)
        return Plt_Err(TYPE_ERROR, "Argument 2 must be an instance of Color!");
    KlassInstance* k1 = (KlassInstance*)args[1].ptr;
    sf::Color* f = (sf::Color*)k1->members[".handle"].ptr;
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::Text* t = (sf::Text*)k->members[".handle"].ptr;
    t->setFillColor(*f);
    vm_markImportant(k1);
    return nil;
}
PltObject Text__del(PltObject* args, int n)
{
    if (n != 1 || args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != textclass)
        return nil;
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    if (k->members[".handle"].type == PLT_NIL)
        return nil;
    sf::Text* e = (sf::Text*)k->members[".handle"].ptr;
    delete e;
    return nil;
}

//Sprite
PltObject Sprite__construct(PltObject* args, int n)
{
    if (n != 1 || args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != spriteclass)
        return Plt_Err(ARGUMENT_ERROR, "1 argument self needed which must be instance of Sprite");
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    auto e = new sf::Sprite;
    k->members.emplace(".handle", PObjFromPtr(e));
    return nil; //values returned by consructors are ignored anyway
}
PltObject Sprite__setTexture(PltObject* args, int n)
{
    if (n != 2)
        return Plt_Err(ARGUMENT_ERROR, "2 arguments needed!");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != spriteclass)
        return Plt_Err(TYPE_ERROR, "Argument 1 must be instance of Sprite");
    if (args[1].type != PLT_OBJ || ((KlassInstance*)args[1].ptr)->klass != textureclass)
        return Plt_Err(TYPE_ERROR, "Argument 2 must be an instance of Texture!");
    KlassInstance* k1 = (KlassInstance*)args[1].ptr;
    sf::Texture* f = (sf::Texture*)k1->members[".handle"].ptr;
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    sf::Sprite* t = (sf::Sprite*)k->members[".handle"].ptr;
    t->setTexture(*(sf::Texture*)k1->members[".handle"].ptr);
    vm_markImportant(k1);
    return nil;
}
PltObject Sprite__del(PltObject* args, int n)
{
    if (n != 1 || args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != spriteclass)
        return nil;
    KlassInstance* k = (KlassInstance*)args[0].ptr;
    if (k->members[".handle"].type == PLT_NIL)
        return nil;
    sf::Sprite* e = (sf::Sprite*)k->members[".handle"].ptr;
    delete e;
    return nil;
}
//FloatRect
PltObject FloatRect__intersects(PltObject* args, int n)
{
    if (n != 2)
        return Plt_Err(ARGUMENT_ERROR, "2 arguments required");
    if (args[0].type != PLT_OBJ || ((KlassInstance*)args[0].ptr)->klass != floatrectclass)
        return Plt_Err(TYPE_ERROR, "Argument 1 must be an instance of FloatRect");
    if (args[1].type != PLT_OBJ || ((KlassInstance*)args[1].ptr)->klass != floatrectclass)
        return Plt_Err(TYPE_ERROR, "Argument 2 must be an instance of FloatRect");
    KlassInstance* k1 = (KlassInstance*)args[0].ptr;
    KlassInstance* k2 = (KlassInstance*)args[1].ptr;
    sf::FloatRect v1;
    sf::FloatRect v2;
    v1.width = (float)k1->members["width"].f;
    v1.height = (float)k1->members["height"].f;
    v1.left = (float)k1->members["left"].f;
    v1.top = (float)k1->members["top"].f;
    v2.width = (float)k2->members["width"].f;
    v2.height = (float)k2->members["height"].f;
    v2.left = (float)k2->members["left"].f;
    v2.top = (float)k2->members["top"].f;
    return PObjFromBool(v1.intersects(v2));
}
