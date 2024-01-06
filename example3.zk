import sfml
var win = sfml.RenderWindow(640,480,"My Game")
var running = true
var ev = sfml.Event()
var color = sfml.Color(0,0,255)
var x = 230.0
var y = 150.0
var ball = sfml.Rectangle(30.0,30.0)
ball.setPosition(x,y)
ball.setFillColor(color)
var vx = -0.2
var vy = -0.2
while(running)
{
    while(win.pollEvent(ev))
    {
        if(ev.type == sfml.EventClosed)
          running = false
    }
    ball.setPosition(x,y)
    x+=vx
    y+=vy
    if(x<0 or x>610)
      vx*=(-1)
    if(y<0 or y>450)
      vy*=(-1)
    win.clear()
    win.draw(ball)
    win.display()
}
