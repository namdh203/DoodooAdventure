#ifndef HITTING_H
#define HITTING_H

#include "SDL.h"

class Hitting {
  public:
    inline SDL_Rect Get() {
      return Box;
    }

    inline void SetBuffer(int x, int y, int w, int h) {
      Buffer = {x, y, w, h};
    }

    void Set(int x, int y, int w, int h) {
      Box = {x - Buffer.x, y - Buffer.y, w - Buffer.w, h - Buffer.h};
    }

  private:
    SDL_Rect Box;
    SDL_Rect Buffer;
};

#endif // HITTING_H
