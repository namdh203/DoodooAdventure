#include "Input.h"
#include "Engine.h"

Input* Input::s_Go = nullptr;

Input::Input() {
  m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::Listen() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_QUIT:
        Engine::GetGo()->Quit();
        break;

      case SDL_KEYDOWN:
        KeyDown();
        break;

      case SDL_KEYUP:
        KeyUp();
        break;
    }
  }
}

bool Input::GetKeyDown(SDL_Scancode key) {
  return (m_KeyStates[key] == true);
}

bool Input::GetKeyMenu(SDL_Scancode key) {
  if (m_KeyStates[key] == true && !press) {
    press = 1;
    return true;
  }
  return false;
}

void Input::KeyUp() {
  m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown() {
  m_KeyStates = SDL_GetKeyboardState(nullptr);
  press = 0;
}
