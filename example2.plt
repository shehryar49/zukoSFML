import sfml
var win = sfml.RenderWindow(640,480,"My Game")
var running = true
var ev = sfml.Event()
var color = sfml.Color(0,0,255)
var x = 230.0
var y = 150.0
var rect = sfml.Rectangle(80.0,80.0)
rect.setPosition(x,y)
rect.setFillColor(color)
while(running)
{
    while(win.pollEvent(ev))
    {
        if(ev.type == sfml.EventClosed)
          running = false
        else if(ev.type == sfml.EventKeyPressed)
        {
            if(ev.keycode == sfml.KeyboardA and x>0)
              x-=10
            else if(ev.keycode == sfml.KeyboardD and x<560)
              x+=10
            else if(ev.keycode == sfml.KeyboardW and y>0)
              y-=10
            else if(ev.keycode == sfml.KeyboardS and y<400)
              y+=10 
            rect.setPosition(x,y)
        }
    }
    win.clear()
    win.draw(rect)
    win.display()
}
