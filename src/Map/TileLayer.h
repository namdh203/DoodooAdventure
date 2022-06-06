#ifndef TILELAYER_H
#define TILELAYER_H

#include<string>
#include<vector>
#include "Layer.h"

struct batoncute {
  int First, LastId;
  int RowCount, ColCount;
  int TileCount, TileSize;
  std::string Name, Source;
};

using TilesetList = std::vector<batoncute>;
using TileMap = std::vector< std::vector<int> >;

class TileLayer : public Layer {
  public:
    TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tileset) ;
    virtual void Render();
    virtual void Update();
    inline TileMap GetTileMap() {return m_TileMap;}

  private:
    int m_TileSize, m_RowCount, m_ColCount;
    TileMap m_TileMap;
    TilesetList m_Tilesets;
};

#endif // TILELAYER_H
