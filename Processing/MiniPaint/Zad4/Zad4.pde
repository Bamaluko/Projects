 String fontname1 = "SimpleMelody";

 String message = "";
 int fontSize = 32;
 
 ButtonPaint paintToolButton;
 ButtonErase eraseToolButton;
 
 ButtonColor buttonColor1;
 ButtonColor buttonColor2;
 ButtonColor buttonColor3;
 ButtonColor buttonColor4;
 
 Slider slider;
 
 boolean isErasing = false;
 
 PFont font1;
 
 float toolSize = 10;

 Container container = new Container();
 int r = 0;
 int g = 0;
 int b = 0;
 
void setup()
{
  font1 = createFont(fontname1 + ".ttf", 30);
  paintToolButton = new ButtonPaint(100, 800, 200, 50, font1, "Paint Tool");
  eraseToolButton = new ButtonErase(600, 800, 200, 50, font1, "Erase Tool");
  
  buttonColor1 = new ButtonColor(350, 700, 50, 50, font1, "", 255, 0, 0);
  buttonColor2 = new ButtonColor(400, 700, 50, 50, font1, "", 0, 255, 0);
  buttonColor3 = new ButtonColor(450, 700, 50, 50, font1, "", 0, 0, 255);
  buttonColor4 = new ButtonColor(500, 700, 50, 50, font1, "", 0, 0, 0);
  
  slider = new Slider(500, 860, 50, 25, font1, "");
  
  size(900, 900);
  textFont(font1);
}

void draw()
{
  background(200, 200, 200);
  push();
    paintToolButton.draw();
    eraseToolButton.draw();
    buttonColor1.draw();
    buttonColor2.draw();
    buttonColor3.draw();
    buttonColor4.draw();
    slider.draw();
  pop();
  
  stroke(0);
  strokeWeight(3);
  line(0, 0.75 * height, width, 0.75 * height);
  
  pushMatrix();
    noStroke();
    container.redraw();
  popMatrix();
  
  pushMatrix();
    fill(r,g,b);
    noStroke();
    circle(mouseX, mouseY, toolSize);
  popMatrix();
}

void mousePressed() 
{
  paintToolButton.isClicked(mouseX, mouseY);
  eraseToolButton.isClicked(mouseX, mouseY);
  if(!isErasing)
  {
    buttonColor1.isClicked(mouseX, mouseY);
    buttonColor2.isClicked(mouseX, mouseY);
    buttonColor3.isClicked(mouseX, mouseY);
    buttonColor4.isClicked(mouseX, mouseY);
  }
}

void mouseDragged()
{
  if(mouseY >=0 && mouseY < 0.75 * height - toolSize)
  {
    container.addElement(mouseX, mouseY, toolSize, r, g, b); 
  }
  
  slider.isClicked(mouseX, mouseY);
}


//Container will store info about what we have drawn
class Container
{
  private ArrayList<Element> elements;
  
  Container()
  {
    elements = new ArrayList<Element>();
  }
  
  void redraw()
  {
    for(Element element : elements)
    {
      element.draw();
    }
  }
  
  void addElement(int x, int y, float radius, int r, int g, int b)
  {
    elements.add(new Element(x, y, radius, r, g, b));
  }
}


class Element
{
  private int x, y, r, g, b;
  private float radius;
  
  Element(int x, int y, float radius, int r, int g, int b) 
  {
     this.x = x;
     this.y = y;
     this.radius = radius;
     
     this.r = r;
     this.g = g;
     this.b = b;
  }
  
  void draw()
  {
    fill(r, g, b);
    circle(x, y, radius);
  }
}


//Button Class
abstract class Button
{
  private int x, y, w, h;
  private PFont font;
  private String fontname;
  
  Button(int x, int y, int w, int h, PFont font, String givenFontname)
  {
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    this.font = font;
    this.fontname = givenFontname;
  }
  
  void draw()
  {
    fill(255, 255, 0);
    rect(this.x, this.y, this.w, this.h);
    textFont(this.font);
    fill(0, 0, 0);
    text(fontname ,this.x + 30, this.y + 35);
  }
}

//Button Paint
class ButtonPaint extends Button
{
  
  ButtonPaint(int x, int y, int w, int h, PFont font, String givenFontname)
  {
    super(x, y, w, h, font, givenFontname);
  }

  void isClicked(float mouseX, float mouseY)
  {
    if (mouseX >= super.x && mouseX <= super.x + super.w && mouseY >= super.y && mouseY <= super.y + super.h) 
    {
      print("Paint mode");
      print("\n");
      r = 0;
      g = 0;
      b = 0;
      isErasing = false;
    }
  }
}

//Button Erase
class ButtonErase extends Button
{
  ButtonErase(int x, int y, int w, int h, PFont font, String givenFontname)
  {
    super(x, y, w, h, font, givenFontname);
  }

    void isClicked(float mouseX, float mouseY)
    {
    if (mouseX >= super.x && mouseX <= super.x + super.w && mouseY >= super.y && mouseY <= super.h + super.y) 
    {
      print("Erase mode");
      print("\n");
      r = 200;
      g = 200;
      b = 200;
      isErasing = true;
    }
  }
}

//Button color
class ButtonColor extends Button
{
  private int color_r, color_g, color_b;
  
  ButtonColor(int x, int y, int w, int h, PFont font, String givenFontname, int given_r, int given_g, int given_b)
  {
    super(x, y, w, h, font, givenFontname);
    this.color_r = given_r;
    this.color_g = given_g;
    this.color_b = given_b;
  }

  void draw()
  {
    fill(color_r, color_g, color_b);
    rect(super.x, super.y, super.w, super.h);
  }
  
  void isClicked(float mouseX, float mouseY)
  {
    if (mouseX >= super.x && mouseX <= super.x + super.w && mouseY >= super.y && mouseY <= super.h + super.y) 
    {
      print("Color Changed");
      print("\n");
      r = color_r;
      g = color_g;
      b = color_b;
    }
  }
}


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
  }
  
  void isClicked(float mouseX, float mouseY)
  {
    if (mouseX >= super.x && mouseX <= super.x + super.w && mouseY >= super.y && mouseY <= super.h + super.y) 
    {
      if(int(mouseX) - 25 < super.x && super.x >= 200)
      {
        super.x = int(mouseX) - 25;
        this.draw();
        toolSize = (mouseX - 100) / 50;
      }
      
      else if(int(mouseX) - 25 > super.x && super.x <= 650)
      {
        super.x = int(mouseX) - 25;
        this.draw();
        toolSize = (mouseX - 100) / 50;
      }

    }
  }
}
