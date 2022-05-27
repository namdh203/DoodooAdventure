#ifndef Engine_H
#define Engine_H

#include "transform.h"

#include "SDL.h"
#include "SDL_image.h"
const int SCREEN_WIDTH = 736;
const int SCREEN_HEIGHT = 480;

class Engine {

  public:
    static Engine* GetGo() {
      return s_Go = (s_Go != nullptr) ? s_Go : new Engine();
    }

    bool Init();
    bool Clean();
    void Quit();

    void Update();
    void Render();
    void Events();

    inline bool IsRunning(){return m_IsRunning;}
    inline SDL_Renderer* GetRenderer(){return m_Renderer;}

  private:
    Engine();
    bool m_IsRunning;
    bool isPlaying;
    bool resume;
    Transform* arrow;
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    static Engine* s_Go;
};

#endif // Engine_H
