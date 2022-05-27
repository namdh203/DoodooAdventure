#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Hitting.h"
#include "vector2d.h"

#define jump_time 20.0f
#define jump_force 10.5f

#define run_force 5.0f
#define attack_time 15.0f

#define GET_HIT_DELAY_WARRIOR 18.0f
#define CHANGE_STAGE_DELAY 100.0f

class Warrior : public Character {
  public:
    Warrior(Properties* props);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(float dt);

  public:
    void get_hit(float dt);
    bool Alive();
    int stage, last_stage;
    void changestage(int id);
    float ChangeStageDelay;
    float GetHitDelay;
    Hitting* m_Hitting;
    Hitting* HitBoxAttack;

  private:
    bool IsJumping, IsGrounded, IsFalling, IsAttack, IsSlide, IsRunning;
    float JumpTime, JumpForce, AttackTime;

    Animation* m_Animation;
    RigidBody* m_RigidBody;
    vector2d save_point;

};

#endif // WARRIOR_H
