#ifndef DOODOO_H
#define DOODOO_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"

class Doodoo : public Character {
  public:
    Doodoo(Properties* props);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(float dt);
    void ChangeStage(int id);
    void SetSize(int w, int h);
    void GetHit(float dt);
    bool Alive();
    int stage;
    int last_stage;
    bool frozen;
  private:
    bool Jumping;
    bool Grounded;

    Animation* m_Animation;
    RigidBody* m_RigidBody;

};

#endif // DOODOO_H
