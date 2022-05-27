#include "Collision.h"

#include "Engine.h"
#include "SDL.h"
#include <iostream>

using namespace std;

Collision* Collision::s_Go = nullptr;

bool Collision::valid(SDL_Rect a, SDL_Rect b) {
  return (a.x < b.x + b.w) && (a.x + a.w > b.x) && (a.y < b.y + b.h) && (a.y + a.h > b.y);
}

bool Collision::MapCollision(SDL_Rect a) {
  int tileSize = 32;
  int RowCount = 15;
  int ColCount = 23;

  int top_tile = (a.y - 1) / tileSize;
  int bottom_tile = (a.y + a.h - 1) / tileSize;

  int left_tile = (a.x - 1) / tileSize;
  int right_tile = (a.x + a.w - 1) / tileSize;

  top_tile = std::max(top_tile, 0);
  bottom_tile = std::min(bottom_tile, 14);

  left_tile = std::max(left_tile, 0);
  right_tile = std::min(right_tile, 22);

  for (int i = top_tile; i <= bottom_tile; ++i) {
    for (int j = left_tile; j <= right_tile; ++j) {
      if (base[i][j] > 0) return true;
    }
  }

  return false;
}

void Collision::GetMapCode() {
	for (int i = 0; i < 15; ++i)
    for (int j = 0; j < 23; ++j) {
      base[i][j] = MapCode::GetGo()->base[i][j];
    }
}


