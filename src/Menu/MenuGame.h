#ifndef MENUGAME_H
#define MENUGAME_H
#include "Animation.h"
#include "transform.h"
#include <string>

class MenuGame {
  public:
    static MenuGame* GetGo() {
      return s_Go = (s_Go != nullptr) ? s_Go : new MenuGame();
    }

  void Update();
  void Draw();

  int isRunning() {
    return is_running;
  }
  void Change(int change) {
    is_running = change;
  }
  private:
    MenuGame() {}
    static MenuGame* s_Go;
    int is_running = 2;
    std::string type = "menu";
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    Animation* m_Animation;
    Transform* arrow = new Transform(200, 117);
    int order = 1;
};

#endif // MENUGAME_H
