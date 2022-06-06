#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "MapCode.h"
#include "Texture.h"
#include "SDL.h"
#include <bits/stdc++.h>
using namespace std;

#include "Sound.h"

MapCode* MapCode::s_Go = nullptr;

void MapCode::GetBase(int stage) {
  string path = "assets/Maps_Code/" + to_string(stage) + ".txt";

  ifstream inp(path.c_str());

  for (int i = 0; i < 15; ++i)
    for (int j = 0; j < 23; ++j) {
      inp >> base[i][j];
    }
}

void MapCode::initEnemy() {
  int cnt = 3;
  ene.clear(); ene_death.clear();
  for (int i = 0; i < 15; ++i)
    cnt_ene[i] = 0;

  int count_row = 0;
  for (int i = 0; i < 15; ++i) {
    for (int j = 0; j < 23; ++j) {
      if (base[i][j] == 2) {
        ++count_row; break;
      }
    }
  }

  while (cnt--) {
    while (true) {
      int i = SDL_GetTicks() % 15;
      int j = SDL_GetTicks() % 23;
      // available spawn
      if (base[i][j] == 2 && (count_row == 1 || cnt_ene[i] < 2) ) {
        ++cnt_ene[i];
        base[i][j] = 0;
        Enemy* cur = new Enemy(new Properties("enemy_idle", 0, 0, 48, 48),
                               Transform(j * 32 - 48, i * 32 - 48) );
        ene.push_back(cur);
        ene_death.push_back(0);
        break;
      }
    }
  }
}

void MapCode::Update(float dt, int cur_stage) {
  if (stage != cur_stage) return;
  for (int i = 0; i < (int)ene.size(); ++i) {
    ene[i]->Update(dt);

//    SDL_Log("%d %d %d", i, ene[i]->HP,
//                ene_death[i]);

    if (ene[i]->HP <= -1 && ene_death[i] == 0) {
      ene_death[i] = 1;
//      SDL_Log("%d %d %d lmao", i, ene[i]->HP,
//                ene_death[i]);
    }
  }
  if (stage == 6) {
    boss->Update(dt);
  }
}



void MapCode::DrawEnemy() {
  for (int i = 0; i < (int)ene.size(); ++i)
    if (ene[i]->HP >= 0) ene[i]->Draw();
  if (stage == 6 && boss->HP >= 0) boss->Draw();
}


void MapCode::Reset() {
  ene.clear();
  for (int i = 0; i < 10; ++i) completed[i] = 0;

  for (int i = 0; i < 30; ++i)
    for (int j = 0; j < 30; ++j)
    base[i][j] = 0;
}



