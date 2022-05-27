#include "Boss.h"
#include "Texture.h"
#include "Engine.h"
#include "Input.h"
#include "Collision.h"

#include "SDL.h"

using namespace std;

Boss::Boss(Properties* props, Transform p) : Character(props) {
  HitBox = new Hitting();
  HitBoxAttack = new Hitting();

  m_Flip = SDL_FLIP_HORIZONTAL;
  m_Animation = new Animation();
  position = p;

  spawn = start = hit = startHit = startDie = false;
  endHit = true;

  HP = initHP = 20;
  GetHitDelay = GET_HIT_DELAY_BOSS;
  Delay = DELAY;

  HitBox->SetBuffer(-170, -20, 0, 0);
  HitBox->Set(position.X, position.Y, 120, 130);
  HitBoxAttack->SetBuffer(0, 0, 0, 0);
  HitBoxAttack ->Set(430, 400, 150, 10);
}

void Boss::Draw() {
  if (HP == 0) {
    if (startDie)
      m_Animation->DrawFrame(position.X, position.Y, 450, 150, m_Flip);
    else {
      m_Animation->SetProps("boss_idle", 1, 8, 150, SDL_FLIP_HORIZONTAL);
      m_Animation->Update();
      m_Animation->DrawFrame(position.X, position.Y, 450, 150, m_Flip);
    }
    if (m_Animation->m_SpriteFrame == 0) startDie = true;
    if (m_Animation->m_SpriteFrame == 9 && startDie) HP = -1;
  } else {
    if (m_Animation->m_SpriteFrame == 0) {
      startHit = true;
    }
    if (m_Animation->m_SpriteFrame == 13 && startHit) {
      endHit = true;
    }
    if ((startHit && !endHit))
      m_Animation->DrawFrame(position.X, position.Y, 450, 150, m_Flip);
    else {
      m_Animation->SetProps("boss_idle", 1, 8, 150, m_Flip);
      m_Animation->Update();
      m_Animation->DrawFrame(position.X, position.Y, 450, 150, m_Flip);
    }
  }

//  SDL_Rect hit_box = HitBox ->Get();
//  SDL_RenderDrawRect (Engine::GetGo() ->GetRenderer(), &hit_box);
//  hit_box = HitBoxAttack ->Get();
//  if (dame) SDL_RenderDrawRect (Engine::GetGo() ->GetRenderer(), &hit_box);

}

void Boss::Clean() {

}

void Boss::Update(float dt) {
  HitBoxAttack ->Set(0, 0, 0, 0);

  HitBox->Set(position.X, position.Y, 120, 130);

  m_Animation ->SetProps("boss_idle", 1, 6, 150, SDL_FLIP_HORIZONTAL);

  if (hit) {

    m_Animation ->SetProps("boss_attack", 1, 15, 150, SDL_FLIP_HORIZONTAL);
  }
  if (hit && endHit) {
    hit = 0, startHit = 0;
  }
  if (!hit && endHit) {
    if (Delay <= 0) {
      hit = 1, startHit = 0, endHit = 0;
      Delay = DELAY;
    }
    else {
      Delay -= dt;
    }
  }

	if (HP == 0) {
		m_Animation ->SetProps("boss_die", 1, 10, 100, SDL_FLIP_HORIZONTAL);
	}

	m_Animation ->Update();

	dame = 0;
	if (hit && startHit && !endHit && 4 < m_Animation->m_SpriteFrame && m_Animation->m_SpriteFrame < 7) {
		HitBoxAttack ->Set(430, 360, 150, 80);
		dame = 1;
	}

}

void Boss::get_hit(float dt) {
  if (GetHitDelay == GET_HIT_DELAY_BOSS) {
    --HP;
    gethit = true;
  }
  GetHitDelay -= dt;
  if (GetHitDelay < 0) {
    GetHitDelay = GET_HIT_DELAY_BOSS;
  }
}
