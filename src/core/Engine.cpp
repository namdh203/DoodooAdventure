#include "Engine.h"
#include "Texture.h"
#include "Warrior.h"
#include "Input.h"
#include "Timer.h"
#include "MapCode.h"
#include "Collision.h"
#include "MenuGame.h"
#include "Sound.h"

// testing
//#include "Boss.h"
//#include "Enemy.h"
//

#include<iostream>
#include<string>

using namespace std;

Engine* Engine::s_Go = nullptr;
Warrior* player = nullptr;
//Boss* boss = nullptr;
//Enemy* enemy = nullptr;

bool Engine::Init() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0 ) {
    SDL_Log("false to initialize SDL: %s", SDL_GetError());
    return false;
  }

  SDL_WindowFlags wf = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

  m_Window = SDL_CreateWindow("Doodoo Adventure", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, wf);
  if (m_Window == nullptr) {
    SDL_Log("false to create Window : %s", SDL_GetError());
    return false;
  }

  m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (m_Renderer == nullptr) {
    SDL_Log("false to create Renderer: %s", SDL_GetError());
    return false;
  }

  Texture::GetGo()->Load("player", "assets/Animation/Idle.png");
  Texture::GetGo()->Load("player_run", "assets/Animation/Run.png");
  Texture::GetGo()->Load("player_jump", "assets/Animation/Jump.png");
  Texture::GetGo()->Load("player_fall", "assets/Animation/Fall.png");
  Texture::GetGo()->Load("player_attack", "assets/Animation/Attack2.png");
  Texture::GetGo()->Load("player_slide", "assets/Animation/Slide.png");
  Texture::GetGo()->Load("HP", "assets/Health Points/heart_icon.png");
  Texture::GetGo()->Load("boss_bhp", "assets/Health Points/boss_bhp.png");
  Texture::GetGo()->Load("boss_hp", "assets/Health Points/boss_hp.png");
  Texture::GetGo()->Load("gameover", "assets/other/gameover.png");
  Texture::GetGo()->Load("menu", "assets/Menu/menu.png");
  Texture::GetGo()->Load("arrow", "assets/Menu/arrow.png");
  Texture::GetGo()->Load("arrow_w", "assets/Menu/arrowW.png");
  Texture::GetGo()->Load("resume", "assets/Menu/resume.png");
  Texture::GetGo()->Load("tutorial", "assets/Menu/tutorial.png");

  for (int i = 0; i <= 6; ++i)
  Texture::GetGo()->Load("map" + to_string(i), "assets/Maps_png/map_" + to_string(i) + ".png");

  Texture::GetGo()->Load("enemy_idle", "assets/Enemy/Scorpio_idle.png");
  Texture::GetGo()->Load("enemy_death", "assets/Enemy/Scorpio_death.png");
  Texture::GetGo()->Load("enemy_walk", "assets/Enemy/Scorpio_walk.png");

  for (int i = 1; i <= 14; ++i)
  Texture::GetGo()->Load("boss_attack" + to_string(i), "assets/Boss/attack/attack" + to_string(i) + ".png");

  for (int i = 1; i <= 10; ++i)
  Texture::GetGo()->Load("boss_die" + to_string(i), "assets/Boss/die/die" + to_string(i) + ".png");

  for (int i = 1; i <= 8; ++i)
  Texture::GetGo()->Load("boss_idle" + to_string(i), "assets/Boss/idle/idle" + to_string(i) + ".png");

  player = new Warrior(new Properties("player", 50, 100, 120, 80));
  MapCode::GetGo()->boss = new Boss(new Properties("boss_idle", 400, 300, 96, 32), Transform(400, 300));

  isPlaying = true;
  resume = true;
  arrow = new Transform(235, 190);

  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

  return m_IsRunning = true;
}

bool Engine::Clean() {
  Texture::GetGo()->Clean();
  SDL_DestroyRenderer(m_Renderer);
  SDL_DestroyWindow(m_Window);
  IMG_Quit();
  SDL_Quit();
}

void Engine::Quit() {
  m_IsRunning = false;
}

void Engine::Events() {
  Input::GetGo()->Listen();
}

void Engine::Update() {
  float dt = Timer::GetGo()->GetDeltaTime();

  if (MenuGame::GetGo()->isRunning() == 2) {
    MenuGame::GetGo()->Update();
    return;
  }
  if (MenuGame::GetGo()->isRunning() == 1) {
    MapCode::GetGo()->Reset();
    player = new Warrior(new Properties("player", 50, 100, 120, 80));
    MapCode::GetGo()->boss = new Boss(new Properties("boss_idle", 400, 300, 96, 32),
                                        Transform(400, 300));
    MenuGame::GetGo()->Change(0);
  }

	if (Input::GetGo() ->GetKeyDown(SDL_SCANCODE_ESCAPE) && isPlaying) {
		isPlaying = 0;
		return;
	}
	if (!isPlaying) {
		if (Input::GetGo() ->GetKeyDown(SDL_SCANCODE_W)) {
			resume = 1;
			arrow = new Transform(235, 190);
		}
		if (Input::GetGo() ->GetKeyDown(SDL_SCANCODE_S)) {
			resume = 0;
			arrow = new Transform(235, 270);
		}
		if (Input::GetGo() ->GetKeyMenu(SDL_SCANCODE_J)) {
				if (resume) isPlaying = 1;
				else {
					isPlaying = 1;
					MenuGame::GetGo()->Change(2);
				}
		}
	}

  if (player->Alive() && isPlaying) {
//    SDL_Log("%d", player->HP);
    player->Update(dt);
    MapCode::GetGo()->GetBase(player->stage);
    MapCode::GetGo()->stage = player->stage;

    if (player->stage == 6) {
      Collision::GetGo()->GetMapCode();
      MapCode::GetGo()->Update(dt, player->stage);

      // Collision giua nhan vat va boss
      if (MapCode::GetGo()->boss->HP > -1) {
        SDL_Rect boss_hb = MapCode::GetGo()->boss->HitBox->Get();
        SDL_Rect boss_hba = MapCode::GetGo()->boss->HitBoxAttack->Get();
        SDL_Rect player_hb = player->m_Hitting->Get();
        SDL_Rect player_hba = player->HitBoxAttack->Get();

        bool getdmg = Collision::GetGo()->valid(player_hb, boss_hba);
        if (getdmg) player->get_hit(dt);
        getdmg = 0;

        getdmg = Collision::GetGo()->valid(boss_hb, player_hba);
        if (getdmg) MapCode::GetGo()->boss->get_hit(dt);
        getdmg = 0;

        getdmg = Collision::GetGo()->valid(player_hb, boss_hb);
        if (getdmg) player->get_hit(dt);
        getdmg = 0;
      } else {
        if (!MapCode::GetGo()->completed[player->stage]) {
          Sound::GetGo()->play("assets/sound/levelComplete.wav", 0);
          MapCode::GetGo()->completed[player->stage] = 1;
        }
      }


//      SDL_Log("%d %d", player->HP, boss->HP);
      /*-----------------------------------------------------------*/
    } else {
      if (MapCode::GetGo()->stage != player->last_stage && !MapCode::GetGo()->completed[player->stage]) {
        MapCode::GetGo()->initEnemy();
      }

      Collision::GetGo()->GetMapCode();
      MapCode::GetGo()->Update(dt, player->stage);

      int cnt = 0;
      for (int i = 0; i < (int)MapCode::GetGo()->ene.size(); ++i) {
        if (MapCode::GetGo()->ene_death[i]) continue;
        ++cnt;
        SDL_Rect enemy_hb = MapCode::GetGo()->ene[i]->HitBox->Get();
        SDL_Rect player_hb = player->m_Hitting->Get();
        SDL_Rect player_hba = player->HitBoxAttack->Get();
//        SDL_Log("%d %d %d", i, MapCode::GetGo()->ene[i]->HP,
//                MapCode::GetGo()->ene_death[i]);
        if (!MapCode::GetGo()->ene_death[i]) {
          // Collision giua nhan vat va bon creep
          bool getdmg = Collision::GetGo()->valid(enemy_hb, player_hba);
          if (getdmg) MapCode::GetGo()->ene[i]->get_hit(dt);
          getdmg = 0;

          getdmg = Collision::GetGo()->valid(player_hb, enemy_hb);
          if (getdmg) player->get_hit(dt);
          getdmg = 0;
        }
      }
      if (!cnt) {
        if (!MapCode::GetGo()->completed[player->stage]) {
          MapCode::GetGo()->completed[player->stage] = 1;
        }
      }
    }

    if (player->HP <= 0)
      Sound::GetGo()->play("assets/sound/gameOver.wav", 0);
  } else {
    if (Input::GetGo()->GetKeyMenu(SDL_SCANCODE_J)) {
      MenuGame::GetGo() ->Change(2);
    }
  }

  if (player->stage == 6 && MapCode::GetGo()->completed[6]) {
    if (Input::GetGo()->GetKeyMenu(SDL_SCANCODE_J)) {
      MenuGame::GetGo() ->Change(2);
    }
  }
}

void Engine::Render() {
  SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
  SDL_RenderClear(m_Renderer);

  if (MenuGame::GetGo()->isRunning() == 2) {
    MenuGame::GetGo()->Draw();
    SDL_RenderPresent(m_Renderer);
    return;
  }

  if (player->Alive()) {
//    SDL_Log("%d", player->stage);
    Texture::GetGo()->Draw("map" + to_string(player->stage), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    player->Draw();
    MapCode::GetGo()->DrawEnemy();

    for (int i = 0; i < player->HP; ++i) {
      Texture::GetGo()->Draw("HP", i * 32, 0, 32, 32);
    }

    if (player->stage == 6) {
      if (MapCode::GetGo()->boss->HP > 0)
      for (int i = 0; i < MapCode::GetGo()->boss->initHP; ++i) {
        Texture::GetGo()->Draw("boss_bhp", 570 + i * 6, 320, 6, 9);
      }
      for (int i = 0; i < MapCode::GetGo()->boss->HP; ++i) {
        Texture::GetGo()->Draw("boss_hp", 570 + i * 6, 320, 6, 9);
      }
    }

    if (!isPlaying) {
      Texture::GetGo()->Draw("resume", 125, 0, 500, 498);
      Texture::GetGo()->Draw("arrow_w", arrow ->X, arrow ->Y, 22, 21);
    }

    SDL_RenderPresent(m_Renderer);
  } else {
    Texture::GetGo()->Draw("gameover", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderPresent(m_Renderer);
  }
}

Engine::Engine() {

}
