#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "Animation.h"
#include "Hitting.h"
#include "vector2d.h"
#include "transform.h"

#define IDLE_TIME 30.0f
#define GET_HIT_DELAY_ENEMY 20.0f

class Enemy : public Character {
  public:
    Enemy(Properties* props, Transform p);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(float dt);

    void get_hit(float dt);

  public:
    float IdleTime, GetHitDelay;
    Animation* m_Animation;
    Hitting* HitBox;
    Transform position;
    bool idle, gethit;
    bool startDie;
    bool dir; // dir = 0 if turnleft, = 1 if turnright
};

#endif // ENEMY_H
