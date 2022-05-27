#include "Texture.h"
#include "Engine.h"

#include "SDL.h"

Texture* Texture::s_Go= nullptr;

bool Texture::Load(std::string id, std::string filename) {
  SDL_Surface* surface = IMG_Load(filename.c_str());
  if (surface == nullptr) {
    SDL_Log("Failed to load texture: %s, %s", filename.c_str(), SDL_GetError());
    return false;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetGo()->GetRenderer(), surface);
  if (texture == nullptr) {
    SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
  }

  m_TextureMap[id] = texture;
  return true;
}

void Texture::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip) {
  SDL_Rect srcRect = {0, 0, width, height};
  SDL_Rect dstRect = {x, y, width, height};
  SDL_RenderCopyEx(Engine::GetGo()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void Texture::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip) {
  SDL_Rect srcRect = {width * frame, height * (row - 1), width, height};
  SDL_Rect dstRect = {x, y, width, height};
  SDL_RenderCopyEx(Engine::GetGo()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}



void Texture::Drop(std::string id) {
  SDL_DestroyTexture(m_TextureMap[id]);
  m_TextureMap.erase(id);
}

void Texture::Clean() {
  for (auto it = m_TextureMap.begin(); it != m_TextureMap.end(); ++it) {
    SDL_DestroyTexture(it->second);
  }

  m_TextureMap.clear();

  SDL_Log("Texture Map Clean! ^o^");
}
