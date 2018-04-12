#include "../src/rsdl.hpp"
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

#define width 640
#define heigth 480
#define MAX_STRING_LENGTH 10
#define WINDOW_TITLE "RSDL Tutorial"
#define BACK_SPACE 8
#define RETURN 13

#define TICK_DURATION 10
#define CURSOR_AGE 50

#define IMG_SQUARE "examples/assets/square.png"
#define IMG_BACKGROUND "examples/assets/background.jpeg"
#define FONT_FREESANS "examples/assets/OpenSans.ttf"

//An example of use cases of RSDL functions.
void drawDynamicBackground(Window* win)
{
  win->draw_bg(IMG_BACKGROUND, 0, 0);
  win->fill_rect(100, 100, (400 - 1), (50 - 1), RED);
}



class MyString{
public:
  string prepareOutputText()
  {
    return "  Your name: " + inputString;
  }

  void eraseLastChar()
  {
    if(inputString.size() > 0)
        inputString.erase(inputString.size() - 1);
  }

  void addChar(char c)
  {
    if(inputString.size() < MAX_STRING_LENGTH)
      inputString += c;
  }
  //A simple function to draw a string on screen.
  void drawString(Window* win)
  {
    win->show_text(prepareOutputText(), 100, 100, WHITE, FONT_FREESANS, 30);
  }

  string getString(){
    return inputString;
  }
private:
  string inputString;
};

class TextInput {
private:
  Window* win;
  MyString inputString;
public:
  TextInput(){
    win = new Window(width, heigth, "Text Input");
  }
  void getInput(){
    bool quitFlag = false;

    //Main loop
    while(!quitFlag) {

      //Handle input
      quitFlag = processInput();

      //Draw Section
      draw();

      //Delay your program for specific amount time.
      Delay(TICK_DURATION);
    }
  }
  string getInputString(){
    getInput();
    return inputString.getString();
  }
  void draw()
  {
    win->clear();
    drawDynamicBackground(win);
    inputString.drawString(win);
    //Update the current Window.
    win->update_screen();
  }
  bool processInput(){
    Event event = win->pollForEvent();
    return processRsdlEvent(event);
  }
  bool processRsdlEvent(Event event) {
    bool quitFlag = false;
    //When working with RSDL you first poll for the latest event.
    //Then you can work with the event.
    //List of these events are availabe in rsdl.hpp .
    if(event.type() == KEY_PRESS) {
      if(event.pressedKey() == BACK_SPACE)
        inputString.eraseLastChar();
      else {
        if(event.pressedKey() == RETURN)
        	quitFlag = true;
        else
          inputString.addChar(event.pressedKey());
      }
    }
    return quitFlag;
  }
};

int main()
{
  TextInput textInput;
  cout<<textInput.getInputString()<<endl;
}
