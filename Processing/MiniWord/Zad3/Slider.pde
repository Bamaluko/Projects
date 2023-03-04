class Slider extends Button
{
  
  Slider(int x, int y, int w, int h, PFont font, String givenFontname)
  {
    super(x, y, w, h, font, givenFontname);
  }

  void draw()
  {
    fill(100, 100, 100);
    rect(200, super.y, 500, super.h);
    fill(100, 100, 0);
    rect(super.x, super.y, super.w, super.h);
    
    textFont(super.font);
    text(fontSize, 700, 880);
    
    fill(255, 255, 255);
  }
  
  void isClicked(float mouseX, float mouseY)
  {
    if (mouseX >= super.x && mouseX <= super.x + super.w && mouseY >= super.y && mouseY <= super.h + super.y) 
    {
      if(int(mouseX) - 25 < super.x && super.x >= 200)
      {
        super.x = int(mouseX) - 25;
        this.draw();
        fontSize = round((mouseX - 100) / 20) + 20;
      }
      
      else if(int(mouseX) - 25 > super.x && super.x <= 650)
      {
        super.x = int(mouseX) - 25;
        this.draw();
        fontSize = round((mouseX - 100) / 20) + 20;
      }

    }
  }
}
