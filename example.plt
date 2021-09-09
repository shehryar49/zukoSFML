import sfml
var win = sfml.RenderWindow(640,480,"Game")
var bg = sfml.Color(0,0,0)
var rcolor = sfml.Color(0,0,235)
var event = sfml.Event()
var circle = sfml.Circle(100)
circle.setPointCount(3)
circle.setPosition(320,240)
circle.setOrigin(100,100)
circle.setFillColor(rcolor)
while(win.isOpen())
{
  while(win.pollEvent(event))
  {
    var i = event.type()
    #println(i)
    if(i==0)
        win.close()
  }
  win.clear(bg)
  win.draw(circle)
  win.display()
  circle.rotate(40)
  sleep(200)
}
