#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"

class Input {
  public:
    static Input* GetGo() {
      return s_Go = (s_Go != nullptr) ? s_Go : new Input();
    }
    void Listen();
    bool GetKeyDown(SDL_Scancode key);
    bool GetKeyMenu(SDL_Scancode key);

  private:
    Input();
    void KeyUp();
    void KeyDown();
    bool press;
    const Uint8* m_KeyStates; // array storing keyboard
    static Input* s_Go;
};

#endif // INPUT_H
