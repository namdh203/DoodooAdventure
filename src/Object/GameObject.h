#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Object.h"
#include "Transform.h"
#include "SDL.h"

struct Properties {
  public:
    std::string TextureID;
    int Width, Height;
    float X, Y;
    SDL_RendererFlip Flip;

  public:
		Properties(std::string ID, int x, int y, int w, int h, SDL_RendererFlip flip = SDL_FLIP_NONE) {
			X = x; Y = y;
			Flip = flip;
			Width = w;
      Height = h;
			TextureID = ID;
		}
};

class GameObject : public Object {
  public:
    GameObject(Properties* prop) :
      m_Width(prop->Width),
      m_Height(prop->Height),
      m_TextureID(prop->TextureID),
      m_Flip(prop->Flip) {
      position = new Transform(prop->X, prop->Y);
    }

    virtual void Draw() = 0;
    virtual void Update(float dt) = 0;
    virtual void Clean() = 0;

  protected:
    Transform* position;
    int m_Width, m_Height;
    std::string m_TextureID;
    SDL_RendererFlip m_Flip;
};

#endif // GAMEOBJECT_H

