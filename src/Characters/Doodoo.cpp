#include "Doodoo.h"
#include "Texture.h"
#include "Input.h"
#include "Collision.h"
#include "MapCode.h"
#include "SDL.h"

Doodoo::Doodoo(Properties* props) : Character(props) {
  m_RigidBody = new RigidBody();
  m_Animation = new Animation();
//  m_Animation->SetProps(m_TextureID, 1, 8, 80, SDL_FLIP_HORIZONTAL);
  m_Animation->SetProps(m_TextureID, 1, 8, 80);
}

void Doodoo::Draw() {
  m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Doodoo::Clean() {
  Texture::GetGo()->Clean();
}

void Doodoo::Update(float dt) {

}
