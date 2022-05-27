#include "Animation.h"
#include "Texture.h"

void Animation::Update() {
  m_SpriteFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
}

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip) {
  Texture::GetGo()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, flip);
}

void Animation::DrawFrame(float x, float y, int width, int height, SDL_RendererFlip flip) {
	std::string id = m_TextureID + std::to_string(m_SpriteFrame + 1);
	Texture::GetGo()->Draw(id, x, y, width, height, flip);
}

void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip) {
  m_TextureID = textureID;
  m_SpriteRow = spriteRow;
  m_FrameCount = frameCount;
  m_AnimSpeed = animSpeed;
  m_Flip = flip;
}

SDL_RendererFlip Animation::GetFlip() {
	return m_Flip;
}
