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
    renderwinclass->members.emplace("__construct__", ZObjFromMethod("__construct__", &RenderWindow__construct, renderwinclass));
    renderwinclass->members.emplace("clear", ZObjFromMethod("clear", &RenderWindow__clear, renderwinclass));
    renderwinclass->members.emplace("draw", ZObjFromMethod("draw", &RenderWindow__draw, renderwinclass));
    renderwinclass->members.emplace("display", ZObjFromMethod("display", &RenderWindow__display, renderwinclass));
    renderwinclass->members.emplace("pollEvent", ZObjFromMethod("pollEvent", &RenderWindow__pollevent, renderwinclass));
    renderwinclass->members.emplace("setFramerateLimit", ZObjFromMethod("setFramerateLimit", &RenderWindow__setFrameRateLimit, renderwinclass));
    renderwinclass->members.emplace("close", ZObjFromMethod("close", &RenderWindow__close, renderwinclass));

    circleclass = vm_allocKlass();
    circleclass->name = "Circle";
    circleclass->members.emplace("__construct__", ZObjFromMethod("__construct__", &Circle__construct, circleclass));
    circleclass->members.emplace("setPosition", ZObjFromMethod("setPosition", &Circle__setpos, circleclass));
    circleclass->members.emplace("setFillColor", ZObjFromMethod("setFillColor", &Circle__setfillcolor, circleclass));
    circleclass->members.emplace("setPointCount", ZObjFromMethod("setPointCount", &Circle__setpointcount, circleclass));
    circleclass->members.emplace("__del__", ZObjFromMethod("__del__", &Circle__del, circleclass));
    colorclass = vm_allocKlass();
    colorclass->name = "Color";
    colorclass->members.emplace("__construct__", ZObjFromMethod("__construct__", &Color__construct, colorclass));
    colorclass->members.emplace("__del__", ZObjFromMethod("__del__", &Color__del, colorclass));

    rectclass = vm_allocKlass();
    rectclass->name = "Rectangle";
    rectclass->members.emplace("__construct__", ZObjFromMethod("__construct__", &Rect__construct, rectclass));
    rectclass->members.emplace("setPosition", ZObjFromMethod("setPosition", &Rect__setpos, rectclass));
    rectclass->members.emplace("setFillColor", ZObjFromMethod("setFillColor", &Rect__setfillcolor, rectclass));
    rectclass->members.emplace("setOutlineColor", ZObjFromMethod("setOutlineColor", &Rect__setOutlineColor, rectclass));
    rectclass->members.emplace("setOutlineThickness", ZObjFromMethod("setOutlineThickness", &Rect__setOutlineThickness, rectclass));
    rectclass->members.emplace("setPosition", ZObjFromMethod("setPosition", &Rect__setpos, rectclass));
    rectclass->members.emplace("getPosition", ZObjFromMethod("getPosition", &Rect__getPosition, rectclass));
    rectclass->members.emplace("getGlobalBounds", ZObjFromMethod("getGlobalBounds", &Rect__getGlobalBounds, rectclass));
    rectclass->members.emplace("setSize", ZObjFromMethod("setSize", &Rect__setSize, rectclass));

    evclass = vm_allocKlass();
    evclass->name = "Event";
    evclass->members.emplace("__construct__", ZObjFromMethod("__construct__", &Event__construct, evclass));
    evclass->members.emplace("__del__", ZObjFromMethod("__del__", &Event__del, evclass));
    evclass->members.emplace("type", nil);
    evclass->members.emplace("keycode", nil);

    textureclass = vm_allocKlass();
    textureclass->name = "Texture";
    textureclass->members.emplace("__construct__", ZObjFromMethod("__construct__", &Texture__construct, textureclass));
    textureclass->members.emplace("loadFromFile", ZObjFromMethod("loadFromFile", &Texture__loadFromFile, textureclass));
    textureclass->members.emplace("__del__", ZObjFromMethod("__del__", &Texture__del, textureclass));

    clockclass = vm_allocKlass();
    clockclass->name = "Clock";
    clockclass->members.emplace("__construct__", ZObjFromMethod("__construct__", &Clock__construct, clockclass));
    clockclass->members.emplace("restart", ZObjFromMethod("restart", &Clock__restart, clockclass));
    clockclass->members.emplace("__del__", ZObjFromMethod("__del__", &Clock__del, clockclass));

    vaclass = vm_allocKlass();
    vaclass->name = "VertexArray";
    vaclass->members.emplace("__construct__", ZObjFromMethod("__construct__", &VertexArray__construct, vaclass));
    vaclass->members.emplace("resize", ZObjFromMethod("resize", &VertexArray__resize, vaclass));
    vaclass->members.emplace("setPrimitiveType", ZObjFromMethod("setPrimitiveType", &VertexArray__setPrimType, vaclass));
    vaclass->members.emplace("setKth", ZObjFromMethod("setKth", &VertexArray__setKth, vaclass));
    vaclass->members.emplace("__del__", ZObjFromMethod("__del__", &VertexArray__del, vaclass));

    fontclass = vm_allocKlass();
    fontclass->name = "Font";
    fontclass->members.emplace("__construct__", ZObjFromMethod("__construct__", &Font__construct, fontclass));
    fontclass->members.emplace("loadFromFile", ZObjFromMethod("loadFromFile", &Font__loadFromFile, fontclass));
    fontclass->members.emplace("__del__", ZObjFromMethod("__del__", &Font__del, fontclass));

    spriteclass = vm_allocKlass();
    spriteclass->name = "Sprite";
    spriteclass->members.emplace("__construct__", ZObjFromMethod("__construct__", &Sprite__construct, spriteclass));
    spriteclass->members.emplace("setTexture", ZObjFromMethod("setTexture", &Sprite__setTexture, spriteclass));
    spriteclass->members.emplace("__del__", ZObjFromMethod("__del__", &Sprite__del, spriteclass));

    textclass = vm_allocKlass();
    textclass->name = "Text";
    textclass->members.emplace("__construct__", ZObjFromMethod("__construct__", &Text__construct, textclass));
    textclass->members.emplace("setCharacterSize", ZObjFromMethod("setCharacterSize", &Text__setCharacterSize, textclass));
    textclass->members.emplace("setString", ZObjFromMethod("setString", &Text__setString, textclass));
    textclass->members.emplace("setPosition", ZObjFromMethod("setPosition", &Text__setPostion, textclass));
    textclass->members.emplace("setFont", ZObjFromMethod("setFont", &Text__setFont, textclass));
    textclass->members.emplace("setFillColor", ZObjFromMethod("setFillColor", &Text__setFillColor, textclass));
    textclass->members.emplace("__del__", ZObjFromMethod("__del__", &Text__del, textclass));

    timeclass = vm_allocKlass();
    timeclass->name = "Time";
    timeclass->members.emplace("asSeconds", ZObjFromMethod("asSeconds", &Time__asSeconds, timeclass));
    timeclass->members.emplace("__del__", ZObjFromMethod("__del__", &Time__del, timeclass));

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
    floatrectclass->members.emplace("intersects", ZObjFromMethod("intersects", &FloatRect__intersects, floatrectclass));

    vm_markImportant(timeclass);
    vm_markImportant(vector2fclass);
    vm_markImportant(floatrectclass);

    // Add classes to module
    Module *sfml = vm_allocModule();
    sfml->name = "sfml";
    sfml->members.emplace("RenderWindow", ZObjFromKlass(renderwinclass));
    sfml->members.emplace("Circle", ZObjFromKlass(circleclass));
    sfml->members.emplace("Color", ZObjFromKlass(colorclass));
    sfml->members.emplace("Rectangle", ZObjFromKlass(rectclass));
    sfml->members.emplace("Event", ZObjFromKlass(evclass));
    sfml->members.emplace("Clock", ZObjFromKlass(clockclass));
    sfml->members.emplace("VertexArray", ZObjFromKlass(vaclass));
    sfml->members.emplace("Font", ZObjFromKlass(fontclass));
    sfml->members.emplace("Text", ZObjFromKlass(textclass));
    sfml->members.emplace("Texture", ZObjFromKlass(textureclass));
    sfml->members.emplace("Sprite", ZObjFromKlass(spriteclass));
    sfml->members.emplace("Vector2f", ZObjFromKlass(vector2fclass));

    sfml->members.emplace("getMousePosition", ZObjFromFunction("getMousePosition", &getMousePosition));

    sfml->members.emplace("EventClosed", ZObjFromInt(sf::Event::Closed));
    sfml->members.emplace("EventKeyPressed", ZObjFromInt(sf::Event::KeyPressed));
    sfml->members.emplace("EventMouseButtonPressed", ZObjFromInt(sf::Event::MouseButtonPressed));
    sfml->members.emplace("EventMouseMoved", ZObjFromInt(sf::Event::MouseMoved));
    sfml->members.emplace("KeyboardA", ZObjFromInt(sf::Keyboard::A));
    sfml->members.emplace("KeyboardS", ZObjFromInt(sf::Keyboard::S));
    sfml->members.emplace("KeyboardD", ZObjFromInt(sf::Keyboard::D));
    sfml->members.emplace("KeyboardW", ZObjFromInt(sf::Keyboard::W));
    sfml->members.emplace("KeyboardUp", ZObjFromInt(sf::Keyboard::Up));
    sfml->members.emplace("KeyboardDown", ZObjFromInt(sf::Keyboard::Down));
    sfml->members.emplace("KeyboardLeft", ZObjFromInt(sf::Keyboard::Left));
    sfml->members.emplace("KeyboardRight", ZObjFromInt(sf::Keyboard::Right));
    sfml->members.emplace("KeyboardEsc", ZObjFromInt(sf::Keyboard::Escape));
    sfml->members.emplace("KeyboardEnter", ZObjFromInt(sf::Keyboard::Enter));
    // More keymappings to be added later

    sfml->members.emplace("LinesStrip", ZObjFromInt(sf::LinesStrip));
    sfml->members.emplace("MouseLeft", ZObjFromInt(sf::Mouse::Left));

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
    sf::RenderWindow *w = (sf::RenderWindow *)k->members[".handle"].ptr;
    KlassObject *ki = vm_allocKlassObject();
    ki->klass = vector2fclass;
    ki->members = vector2fclass->members;
    sf::Vector2i v = sf::Mouse::getPosition(*w);
    ki->members["x"] = ZObjFromDouble(v.x);
    ki->members["y"] = ZObjFromDouble(v.y);
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
    string &title = *((string *)args[3].ptr);
    sf::RenderWindow *w = new sf::RenderWindow(sf::VideoMode(args[1].i, args[2].i), title);
    KlassObject *k = (KlassObject *)args[0].ptr;
    k->members.emplace(".handle", ZObjFromPtr((void *)w)); // we use .handle so that user can't change it's value
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
        sf::Color *color = (sf::Color *)ki->members[".handle"].ptr;
        c = *color;
    }
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::RenderWindow *w = (sf::RenderWindow *)k->members[".handle"].ptr;
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
    sf::RenderWindow *w = (sf::RenderWindow *)k->members[".handle"].ptr;
    w->close();
    delete w;
    k->members[".handle"] = nil;
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
    sf::RenderWindow *w = (sf::RenderWindow *)k->members[".handle"].ptr;
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
    sf::RenderWindow *w = (sf::RenderWindow *)k->members[".handle"].ptr;
    if (obj->klass == circleclass)
    {
        sf::CircleShape *d = (sf::CircleShape *)obj->members[".handle"].ptr;
        w->draw(*d);
    }
    else if (obj->klass == rectclass)
    {
        sf::RectangleShape *d = (sf::RectangleShape *)obj->members[".handle"].ptr;
        w->draw(*d);
    }
    else if (obj->klass == spriteclass)
    {
        sf::Sprite *d = (sf::Sprite *)obj->members[".handle"].ptr;
        w->draw(*d);
    }
    else if (obj->klass == textclass)
    {
        sf::Text *d = (sf::Text *)obj->members[".handle"].ptr;
        w->draw(*d);
    }
    else if (obj->klass == vaclass)
    {
        sf::VertexArray *d = (sf::VertexArray *)obj->members[".handle"].ptr;
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
    sf::RenderWindow *w = (sf::RenderWindow *)k->members[".handle"].ptr;
    sf::Event *e = (sf::Event *)obj->members[".handle"].ptr;
    bool b = w->pollEvent(*e);
    if (b)
    {
        obj->members["type"] = ZObjFromInt(e->type);
        if (e->type == sf::Event::KeyPressed)
            obj->members["keycode"] = ZObjFromInt(e->key.code);
        if (e->type == sf::Event::MouseButtonPressed)
            obj->members.emplace("mouseButton", ZObjFromInt(e->mouseButton.button));
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
    sf::RenderWindow *w = (sf::RenderWindow *)k->members[".handle"].ptr;
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
    k->members.emplace(".handle", ZObjFromPtr(e));
    return nil;
}
ZObject Event__del(ZObject *args, int n)
{
    if (n != 1)
        return nil;
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != evclass)
        return nil;
    KlassObject *ki = (KlassObject *)args[0].ptr;
    if (ki->members[".handle"].type == Z_NIL)
        return nil;
    sf::Event *ev = (sf::Event *)ki->members[".handle"].ptr;
    delete ev;
    ki->members[".handle"] = nil;
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
    k->members.emplace(".handle", ZObjFromPtr(c));
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
    sf::CircleShape *c = (sf::CircleShape *)k->members[".handle"].ptr;
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
    sf::CircleShape *c = (sf::CircleShape *)k->members[".handle"].ptr;
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
    sf::CircleShape *c = (sf::CircleShape *)k->members[".handle"].ptr;
    sf::Color *color = (sf::Color *)j->members[".handle"].ptr;
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
    if (ki->members[".handle"].type == Z_NIL)
        return nil;
    sf::CircleShape *circle = (sf::CircleShape *)ki->members[".handle"].ptr;
    delete circle;
    ki->members[".handle"] = nil;
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
    k->members.emplace(".handle", ZObjFromPtr(c));
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
    sf::RectangleShape *c = (sf::RectangleShape *)k->members[".handle"].ptr;
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
    sf::RectangleShape *c = (sf::RectangleShape *)k->members[".handle"].ptr;
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
    sf::RectangleShape *c = (sf::RectangleShape *)k->members[".handle"].ptr;
    KlassObject *ki = vm_allocKlassObject();
    ki->klass = vector2fclass;
    ki->members = vector2fclass->members;
    sf::Vector2f v = c->getPosition();
    ki->members["x"] = ZObjFromDouble(v.x);
    ki->members["y"] = ZObjFromDouble(v.y);
    return ZObjFromKlassObj(ki);
}
ZObject Rect__getGlobalBounds(ZObject *args, int n)
{
    if (n != 1)
        return Z_Err(ArgumentError, "1 argument needed!");
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != rectclass)
        return Z_Err(TypeError, "self must be an instance of Rectangle class!");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::RectangleShape *c = (sf::RectangleShape *)k->members[".handle"].ptr;
    KlassObject *ki = vm_allocKlassObject();
    ki->klass = floatrectclass;
    ki->members = floatrectclass->members;
    sf::FloatRect v = c->getGlobalBounds();
    ki->members["width"] = ZObjFromDouble(v.width);
    ki->members["height"] = ZObjFromDouble(v.height);
    ki->members["left"] = ZObjFromDouble(v.left);
    ki->members["top"] = ZObjFromDouble(v.top);
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
    sf::RectangleShape *c = (sf::RectangleShape *)k->members[".handle"].ptr;
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
    sf::RectangleShape *c = (sf::RectangleShape *)k->members[".handle"].ptr;
    sf::Color *color = (sf::Color *)j->members[".handle"].ptr;
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
    sf::RectangleShape *c = (sf::RectangleShape *)k->members[".handle"].ptr;
    sf::Color *color = (sf::Color *)j->members[".handle"].ptr;
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
    if (ki->members[".handle"].type == Z_NIL)
        return nil;
    sf::RectangleShape *rect = (sf::RectangleShape *)ki->members[".handle"].ptr;
    delete rect;
    ki->members[".handle"] = nil;
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
    k->members.emplace(".handle", ZObjFromPtr(c));
    return nil;
}
ZObject Color__del(ZObject *args, int n)
{
    if (n != 1)
        return nil;
    if (args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != colorclass)
        return nil;
    KlassObject *ki = (KlassObject *)args[0].ptr;
    if (ki->members[".handle"].type == Z_NIL)
        return nil;
    sf::Color *color = (sf::Color *)ki->members[".handle"].ptr;
    delete color;
    ki->members[".handle"] = nil;
    return nil;
}
// Clock
ZObject Clock__construct(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != clockclass)
        return Z_Err(ArgumentError, "1 argument self needed which must be instance of Clock");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Clock *e = new sf::Clock;
    k->members.emplace(".handle", ZObjFromPtr(e));
    return nil; // values returned by consructors are ignored anyway
}
ZObject Clock__restart(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != clockclass)
        return Z_Err(ArgumentError, "1 argument self needed which must be instance of Clock");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Clock *e = (sf::Clock *)k->members[".handle"].ptr;
    sf::Time *t = new sf::Time(e->restart());
    KlassObject *ki = vm_allocKlassObject();
    ki->klass = timeclass;
    ki->members = timeclass->members;
    ki->members.emplace(".handle", ZObjFromPtr(t));
    return ZObjFromKlassObj(ki);
}
ZObject Clock__del(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != clockclass)
        return nil;
    KlassObject *k = (KlassObject *)args[0].ptr;
    if (k->members[".handle"].type == Z_NIL)
        return nil;
    sf::Clock *e = (sf::Clock *)k->members[".handle"].ptr;
    delete e;
    k->members[".handle"] = nil;
    return nil;
}

// Time
ZObject Time__asSeconds(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != timeclass)
        return Z_Err(ArgumentError, "1 argument self needed which must be instance of Time");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Time *t = (sf::Time *)k->members[".handle"].ptr;

    return ZObjFromDouble(t->asSeconds());
}
ZObject Time__del(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != timeclass)
        return nil;
    KlassObject *k = (KlassObject *)args[0].ptr;
    if (k->members[".handle"].type == Z_NIL)
        return nil;
    sf::Time *t = (sf::Time *)k->members[".handle"].ptr;
    delete t;
    k->members[".handle"] = nil;
    return nil;
}
// Texture
ZObject Texture__construct(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != textureclass)
        return Z_Err(ArgumentError, "1 argument self needed which must be instance of Texture");
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Texture *e = new sf::Texture;
    k->members.emplace(".handle", ZObjFromPtr(e));
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
    string &fname = *(string *)args[1].ptr;
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Texture *f = (sf::Texture *)k->members[".handle"].ptr;
    f->loadFromFile(fname);
    return nil;
}
ZObject Texture__del(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != textureclass)
        return nil;
    KlassObject *k = (KlassObject *)args[0].ptr;
    if (k->members[".handle"].type == Z_NIL)
        return nil;
    sf::Texture *e = (sf::Texture *)k->members[".handle"].ptr;
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
    k->members.emplace(".handle", ZObjFromPtr(e));
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
    sf::VertexArray *va = (sf::VertexArray *)k->members[".handle"].ptr;
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
    sf::VertexArray *va = (sf::VertexArray *)k->members[".handle"].ptr;
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
    sf::VertexArray *va = (sf::VertexArray *)k->members[".handle"].ptr;
    (*va)[args[1].i].position = sf::Vector2f(args[2].f, args[3].f);
    return nil;
}
ZObject VertexArray__del(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != vaclass)
        return nil;
    KlassObject *k = (KlassObject *)args[0].ptr;
    if (k->members["handle"].type == Z_NIL)
        return nil;
    sf::VertexArray *e = (sf::VertexArray *)k->members[".handle"].ptr;
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
    k->members.emplace(".handle", ZObjFromPtr(e));
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
    string &fname = *(string *)args[1].ptr;
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Font *f = (sf::Font *)k->members[".handle"].ptr;
    f->loadFromFile(fname);
    return nil;
}
ZObject Font__del(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != fontclass)
        return nil;
    KlassObject *k = (KlassObject *)args[0].ptr;
    if (k->members[".handle"].type == Z_NIL)
        return nil;
    sf::Font *e = (sf::Font *)k->members[".handle"].ptr;
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
    k->members.emplace(".handle", ZObjFromPtr(e));
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
    sf::Text *t = (sf::Text *)k->members[".handle"].ptr;
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
    sf::Text *t = (sf::Text *)k->members[".handle"].ptr;
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
    string &str = *(string *)args[1].ptr;
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Text *t = (sf::Text *)k->members[".handle"].ptr;
    t->setString(str);
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
    sf::Font *f = (sf::Font *)k1->members[".handle"].ptr;
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Text *t = (sf::Text *)k->members[".handle"].ptr;
    t->setFont(*(sf::Font *)k1->members[".handle"].ptr);
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
    sf::Color *f = (sf::Color *)k1->members[".handle"].ptr;
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Text *t = (sf::Text *)k->members[".handle"].ptr;
    t->setFillColor(*f);
    vm_markImportant(k1);
    return nil;
}
ZObject Text__del(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != textclass)
        return nil;
    KlassObject *k = (KlassObject *)args[0].ptr;
    if (k->members[".handle"].type == Z_NIL)
        return nil;
    sf::Text *e = (sf::Text *)k->members[".handle"].ptr;
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
    k->members.emplace(".handle", ZObjFromPtr(e));
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
    sf::Texture *f = (sf::Texture *)k1->members[".handle"].ptr;
    KlassObject *k = (KlassObject *)args[0].ptr;
    sf::Sprite *t = (sf::Sprite *)k->members[".handle"].ptr;
    t->setTexture(*(sf::Texture *)k1->members[".handle"].ptr);
    vm_markImportant(k1);
    return nil;
}
ZObject Sprite__del(ZObject *args, int n)
{
    if (n != 1 || args[0].type != Z_OBJ || ((KlassObject *)args[0].ptr)->klass != spriteclass)
        return nil;
    KlassObject *k = (KlassObject *)args[0].ptr;
    if (k->members[".handle"].type == Z_NIL)
        return nil;
    sf::Sprite *e = (sf::Sprite *)k->members[".handle"].ptr;
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
    v1.width = (float)k1->members["width"].f;
    v1.height = (float)k1->members["height"].f;
    v1.left = (float)k1->members["left"].f;
    v1.top = (float)k1->members["top"].f;
    v2.width = (float)k2->members["width"].f;
    v2.height = (float)k2->members["height"].f;
    v2.left = (float)k2->members["left"].f;
    v2.top = (float)k2->members["top"].f;
    return ZObjFromBool(v1.intersects(v2));
}
