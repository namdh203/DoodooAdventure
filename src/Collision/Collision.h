#ifndef COLLISION_H
#define COLLISION_H

#include "SDL.h"
#include <vector>
#include "MapCode.h"
#include "Warrior.h"

class Collision {
  public:
    bool valid(SDL_Rect a, SDL_Rect b);
    bool MapCollision(SDL_Rect a);

    void GetMapCode();

    inline static Collision* GetGo() {
      return s_Go = (s_Go != nullptr) ? s_Go : new Collision();
    }

  private:
    Collision() {};
    int base[32][32];
    static Collision* s_Go;
};

#endif // COLLISION_H
