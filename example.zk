import sfml

var win = sfml.RenderWindow(640,480,"My Game")
var running = true
var ev = sfml.Event()
var color = sfml.Color(0,0,255)
var circle = sfml.Circle(80.0)
circle.setPosition(230.0,150.0)
circle.setPointCount(3)
circle.setFillColor(color)
while(running)
{
    while(win.pollEvent(ev))
    {
        if(ev.type == sfml.EventClosed)
          running = false
    }
    win.clear()
    win.draw(circle)
    win.display()
}
