import sfml
var win = sfml.RenderWindow(640,480,"Game")
var bg = sfml.Color(0,0,0)
var rcolor = sfml.Color(0,0,235)
var event = sfml.Event()
var circle = sfml.Circle(100)
sfml.setPointCount(circle,3)
sfml.setPosition(circle,320,240)
sfml.setOrigin(circle,100,100)
sfml.setFillColor(circle,rcolor)
while(sfml.isOpen(win))
{
  while(sfml.pollEvent(win,event))
  {
    var i = sfml.eventType(event)
    #println(i)
    if(i==0)
        sfml.close(win)
  }
  sfml.clear(win,bg)
  sfml.draw(circle,win)
  sfml.display(win)
  sfml.rotate(circle,40)
  sleep(1)
}
