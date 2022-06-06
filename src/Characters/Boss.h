#ifndef BOSS_H
#define BOSS_H

#include "Character.h"
#include "Animation.h"
#include "Hitting.h"
#include "vector2d.h"
#include "transform.h"

#include <string>

#define DELAY 10.0f
#define GET_HIT_DELAY_BOSS 40.0f

class Boss : public Character {
  public:
    Boss(Properties* props, Transform p);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(float dt);

    void DrawIdle();
    void DrawAttack();
    void DrawDeath();
    void get_hit(float dt);

  public:
    bool spawn;
    Animation* m_Animation;

  public:
    int LastFrame, AnimationSpeed, FrameCount, CurrentFrame;
    int Frame = 1;
    float Delay, GetHitDelay;
    bool hit, endHit, startHit;
    bool startDie;
    std::string id;
    Hitting* HitBox;
    Hitting* HitBoxAttack;
    Transform position;
    int width, height;
    bool start;
    bool gethit;
    bool dame;
};

#endif // BOSS_H
