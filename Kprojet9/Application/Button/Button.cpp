#include "Button.h" 
bool Button::WasPressed()
  {
     if(!pin.IsSet())
     {
       while(!pin.IsSet());
       return true;
     }
    return false;
  }
Button::Button(IButtonPin& pin): pin(pin){};

void Button::Enable()
{
  pin.Enable();
  pin.SelectInputMode();
}