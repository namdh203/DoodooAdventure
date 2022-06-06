#include "Enemy.h"
#include "Texture.h"
#include "Engine.h"
#include "Input.h"
#include "Collision.h"
#include "Sound.h"
#include "SDL.h"

using namespace std;

Enemy::Enemy(Properties* props, Transform p) : Character(props) {
  HitBox = new Hitting();

  m_Flip = SDL_FLIP_NONE;
  m_Animation = new Animation();
  position = p;

  startDie = false;

  HP = initHP = 2;
  dir = 0;
  GetHitDelay = GET_HIT_DELAY_ENEMY;
  IdleTime = IDLE_TIME;

  HitBox->SetBuffer(0, 0, 0, 0);
  HitBox->Set(position.X, position.Y + 18, 48, 30);

}

void Enemy::Draw() {
//  SDL_Log("%d %d", m_Animation->m_SpriteFrame, m_Animation->m_FrameCount);

  if (HP == 0) {
    if (!startDie) {
      m_Animation->SetProps("enemy_walk", 1, 4, 150, m_Flip);
      m_Animation->Update();
    }
    if (m_Animation->m_SpriteFrame == 0) startDie = true;
    if (m_Animation->m_SpriteFrame == 3 && startDie) {
      Sound::GetGo()->play("assets/sound/menuSelect.wav", 0);
      HP = -1;
    }
  } else {
    m_Animation->SetProps("enemy_walk", 1, 4, 150, m_Flip);
    m_Animation->Update();
  }

  m_Animation->Draw(position.X, position.Y, 48, 48, m_Flip);

}

void Enemy::Clean() {

}

void Enemy::Update(float dt) {
//  SDL_Log("%d", HP);
  HitBox->Set(position.X, position.Y + 18, 48, 30);

  m_Animation ->SetProps("enemy_idle", 1, 4, 150, m_Flip);

  if (idle) {
    IdleTime -= dt;
    if (IdleTime < 0) {
      IdleTime = IDLE_TIME;
      idle = false;
    }
  } else if (dir) {
    m_Flip = SDL_FLIP_HORIZONTAL;
    position.X += 2.0f;
  } else {
    m_Flip = SDL_FLIP_NONE;
    position.X -= 2.0f;
  }
  m_Animation->SetProps("enemy_walk", 1, 4, 100, m_Flip);

  int i = (position.Y + 28) / 32, j = (position.X + 28) / 32;
//  SDL_Log("%d %d", i, j);
  if (dir && (MapCode::GetGo()->base[i][j + 1] || !MapCode::GetGo()->base[i + 1][j + 1]) ) {
    idle = 1; dir = 0;
  }
  if (!dir && (MapCode::GetGo()->base[i][j - 1] || !MapCode::GetGo()->base[i + 1][j - 1]) ) {
    idle = 1; dir = 1;
  }

  if (HP == 0) {
    m_Animation->SetProps("enemy_death", 1, 4, 80, m_Flip);
  }
  m_Animation->Update();
}

void Enemy::get_hit(float dt) {
  if (GetHitDelay == GET_HIT_DELAY_ENEMY) {
    --HP;
    gethit = true;
  }
  GetHitDelay -= dt;
  if (GetHitDelay < 0) {
    GetHitDelay = GET_HIT_DELAY_ENEMY;
  }
}
