#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "Layer.h"
#include<vector>

class GameMap {
  public:
    GameMap() {}
//    void Render() {
//      for (int i = 0; i < (int)m_MapLayers.size(); ++i) {
//        m_MapLayers[i].Render();
//      }
//    }
//
//    void Update() {
//      for (int i = 0; i < (int)m_MapLayers.size(); ++i) {
//        m_MapLayers[i].Update();
//      }
//    }

    std::vector<Layer*> GetMap() {return m_MapLayers;}

  private:
    std::vector<Layer*> m_MapLayers;
};

#endif // GAMEMAP_H
