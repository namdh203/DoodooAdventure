#ifndef ANIMATION_H
#define ANIMATION_H

#include "SDL.h"
#include<string>

class Animation {
  public:
    Animation() {};
    void Update();

    void Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawFrame(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
    SDL_RendererFlip GetFlip();

  public:
    int m_SpriteRow, m_SpriteFrame;
    int m_AnimSpeed, m_FrameCount;
    std::string m_TextureID;
    SDL_RendererFlip m_Flip;

};

#endif // ANIMATION_H
