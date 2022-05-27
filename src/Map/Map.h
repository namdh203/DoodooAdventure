#ifndef MAP_H
#define MAP_H


class Map {
  public:
    static Map* GetGo() {
      return s_Go = (s_Go != nullptr) ? s_Go : new Map();
    }

    void Update(float dt, int stage);
    void GetBase(int stage);
  public:
    int base[35][35];
    int stage;

  private
    Map() {}
    Map* s_Go;
};

#endif // MAP_H
