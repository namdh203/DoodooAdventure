#ifndef MAPCODE_H
#define MAPCODE_H

#include <iostream>
#include <string>
#include <vector>
#include "Warrior.h"
#include "Boss.h"
#include "Enemy.h"

using namespace std;

class MapCode {
	public:
	  static MapCode* GetGo() {
      return s_Go = (s_Go != nullptr) ? s_Go : new MapCode();
	  }
		void GetBase(int stage);
		void Update(float dt, int stage);
		void initEnemy();
		void DrawEnemy();
		void Reset();

  public:
		int base[30][30];
		int cnt_ene[30]; // count enemy of a row
		int stage = 0;
	  bool completed[10];
    Boss* boss;
    vector<Enemy*> ene;
    vector<int> ene_death;
	private:
	  MapCode() {}
	  static MapCode* s_Go;
};

#endif // MAPCODE_H
