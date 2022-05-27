#include "Warrior.h"
#include "Texture.h"
#include "Engine.h"
#include "Input.h"
#include "Collision.h"
#include "MapCode.h"
#include "SDL.h"

#include "Sound.h"

Warrior::Warrior(Properties* props) : Character(props) {
  IsRunning = IsJumping = IsFalling = IsAttack = IsSlide = false;

  m_Flip = SDL_FLIP_NONE;
  JumpTime = jump_time;
  JumpForce = jump_force;
  AttackTime = attack_time;

  m_Hitting = new Hitting();
  m_Hitting->SetBuffer(-47, -45, 0, 0);
  HitBoxAttack = new Hitting();
  HitBoxAttack->SetBuffer(0, 0, 0, 0);

  m_RigidBody = new RigidBody();
  m_RigidBody->SetGravity(4.0f);

  m_Animation = new Animation();
  m_Animation->SetProps(m_TextureID, 1, 10, 80);

	IsGrounded = true;
	IsJumping = false;

	position = new Transform(45, 200);

	HP = initHP = 10;
	stage = 0; last_stage = -1;
  MapCode::GetGo()->completed[0] = 1;

	GetHitDelay = GET_HIT_DELAY_WARRIOR;
	ChangeStageDelay = CHANGE_STAGE_DELAY;

	save_point = vector2d(position->X, position->Y);
}

void Warrior::Draw() {

  m_Animation->Draw(position->X, position->Y, m_Width, m_Height, m_Flip);


//  SDL_Rect hit_box = m_Hitting->Get();
//	SDL_RenderDrawRect (Engine::GetGo()->GetRenderer(), &hit_box);
//  hit_box = HitBoxAttack->Get();
//  SDL_RenderDrawRect (Engine::GetGo()->GetRenderer(), &hit_box);

  // ve rect cua nhan vat va don danh
}

void Warrior::Clean() {
  Texture::GetGo()->Drop(m_TextureID);
}

void Warrior::Update(float dt) {
//	SDL_Log("%d\n", HP);
//	SDL_Log ("%d\n",stage);
//	SDL_Log ("%f %f\n",position ->X, position ->Y);
  if (stage != last_stage) {
//    SDL_Log("pos %f %f", position->X, position->Y);
    for (int j = 14; j >= 0; --j) {
      if (j > 0 && MapCode::GetGo()->base[j][1] > 0 && !MapCode::GetGo()->base[j - 1][1]) {
        position = new Transform(32, (j - 1) * 32 - 48);
        break;
      }
    }
    last_stage = stage;
    return;
  }
  m_RigidBody->UnSetForce();

  IsRunning = false; IsSlide = false; IsAttack = false;
  // move

  if (Input::GetGo()->GetKeyDown(SDL_SCANCODE_D) && !IsAttack) {
    m_RigidBody->ApplyForceX(FORWARD * run_force);
    m_Flip = SDL_FLIP_NONE;
    IsRunning = true;
  }

  if (Input::GetGo()->GetKeyDown(SDL_SCANCODE_A) && !IsAttack) {
    m_RigidBody->ApplyForceX(BACKWARD * run_force);
    m_Flip = SDL_FLIP_HORIZONTAL;
    IsRunning = true;
  }

  // jump
  if (Input::GetGo()->GetKeyDown(SDL_SCANCODE_K) && IsGrounded && !IsJumping) {
    IsJumping = true;
    IsGrounded = false;
    m_RigidBody->ApplyForceY(UPWARD * JumpForce);
  } else
  if (Input::GetGo()->GetKeyDown(SDL_SCANCODE_K) && IsJumping && JumpTime > 0) {
    JumpTime -= dt;
    m_RigidBody->ApplyForceY(UPWARD * JumpForce);
  } else {
    IsJumping = false;
    JumpTime = jump_time;
  }

  // slide

  if (Input::GetGo()->GetKeyDown(SDL_SCANCODE_L) && IsRunning && m_Flip == SDL_FLIP_NONE) {
    m_RigidBody->ApplyForceX(FORWARD * 6);
    IsSlide = true;
  }

  if (Input::GetGo()->GetKeyDown(SDL_SCANCODE_L) && IsRunning && m_Flip != SDL_FLIP_NONE) {
    m_RigidBody->ApplyForceX(BACKWARD * 6);
    IsSlide = true;
  }


  // attack
  if (Input::GetGo()->GetKeyDown(SDL_SCANCODE_J)) {
    m_RigidBody->UnSetForce();
    IsAttack = true;
  }

  // fall
  if (m_RigidBody->Velocity().Y > 0 && !IsGrounded) {
    IsFalling = true;
  } else
    IsFalling = false;

  // attack timer
  if (IsAttack && AttackTime > 0) {
    AttackTime -= dt;
  } else {
    IsAttack = false;
    AttackTime = attack_time;
  }

  // move on X axis
  m_RigidBody->Update(dt);
  save_point.X = position->X;
  position->X += m_RigidBody->Position().X;
  m_Hitting->Set(position->X, position->Y, 18, 32);

  if (Collision::GetGo()->MapCollision(m_Hitting->Get())) {
    position->X = save_point.X;
  }

  // move on Y axis
  m_RigidBody->Update(dt);
  save_point.Y = position->Y;
  position->Y += m_RigidBody->Position().Y;
  m_Hitting->Set(position->X, position->Y, 18, 32);

  if (Collision::GetGo()->MapCollision(m_Hitting->Get())) {
    IsGrounded = true;
    position->Y = save_point.Y;
    if (IsJumping && JumpTime) {
      JumpTime = 0;
    }
  } else
    IsGrounded = false;

  // animation state
  m_Animation->SetProps("player", 1, 10, 100);

  if (IsRunning)
    m_Animation->SetProps("player_run", 1, 10, 100);

  if (IsSlide) {
//    Sound::GetGo()->play("assets/sound/slide.wav", 0);
    m_Animation->SetProps("player_slide", 1, 4, 100);
  }

  if (IsJumping) {
    Sound::GetGo()->play("assets/sound/jump.wav", 0);
    m_Animation->SetProps("player_jump", 1, 3, 100);
  }

  if (IsFalling)
    m_Animation->SetProps("player_fall", 1, 2, 300);

  if (IsAttack) {
    Sound::GetGo()->play("assets/sound/attack.wav", 0);
    m_Animation->SetProps("player_attack", 1, 4, 100);

    if (m_Flip != SDL_FLIP_HORIZONTAL) {
      HitBoxAttack->Set(m_Hitting->Get().x + 20, m_Hitting->Get().y, 50, 32);
    } else {
      HitBoxAttack->Set(m_Hitting->Get().x - 38, m_Hitting->Get().y, 50, 32);
    }
  } else {
    HitBoxAttack->Set(0, 0, 0, 0);
  }

  // change stage
  if (position->X > 670) {
    if (!MapCode::GetGo()->completed[stage]) {
//      SDL_Log("debug");
      position = new Transform(save_point.X, save_point.Y);
    } else {
      ++stage;
    }
  }

  m_Animation->Update();
}

void Warrior::get_hit(float dt) {
  if (GetHitDelay == GET_HIT_DELAY_WARRIOR) {
    --HP;
  }
  GetHitDelay -= dt;
  if (GetHitDelay < 0)
    GetHitDelay = GET_HIT_DELAY_WARRIOR;
}

bool Warrior::Alive() {
  return (HP > 0);
}

void Warrior::changestage(int id) {
  stage = id;
}

