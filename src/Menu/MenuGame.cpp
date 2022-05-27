#include "MenuGame.h"
#include "Texture.h"
#include "Input.h"
#include "Engine.h"
#include "Sound.h"

MenuGame* MenuGame::s_Go = nullptr;

void MenuGame::Update() {
	if (type == "menu") {
		if (Input::GetGo() ->GetKeyMenu(SDL_SCANCODE_W) && order > 1) {
      Sound::GetGo()->play("assets/sound/menuSelect.wav", 0);
			arrow = new Transform(arrow ->X, arrow ->Y - 75);
			order --;
		}
		if (Input::GetGo() ->GetKeyMenu(SDL_SCANCODE_S) && order < 3) {
      Sound::GetGo()->play("assets/sound/menuSelect.wav", 0);
			arrow = new Transform(arrow ->X, arrow ->Y + 75);
			order ++;
		}
		if (Input::GetGo() ->GetKeyMenu(SDL_SCANCODE_J)) {
		  Sound::GetGo()->play("assets/sound/menuSelect.wav", 0);
			if (order == 1) is_running = 1;
			else if (order == 2) type = "tutorial";
			else Engine::GetGo() ->Quit();
		}
		return;
	}

	if (Input::GetGo() ->GetKeyMenu(SDL_SCANCODE_L)) {
		type = "menu";
	}

}

void MenuGame::Draw() {
	if (type == "menu") {
		Texture::GetGo() ->Draw("menu", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		Texture::GetGo() ->Draw("arrow", arrow->X, arrow ->Y, 32, 32);
		return;
	}
	else {
		Texture::GetGo() ->Draw("tutorial", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		m_Animation = new Animation();
		m_Animation->SetProps("player_run", 1, 10, 100);
		m_Animation->Update();
		m_Animation->Draw(300, 40, 120, 80);
		m_Animation = new Animation();
		m_Animation->SetProps("player_attack", 1, 4, 100);
		m_Animation->Update();
		m_Animation ->Draw(300, 130, 120, 80);
		m_Animation = new Animation();
		m_Animation->SetProps("player_jump", 1, 3, 100);
		m_Animation->Update();
		m_Animation ->Draw(300, 220, 120, 80);
		m_Animation = new Animation();
		m_Animation->SetProps("player_slide", 1, 4, 100);
		m_Animation->Update();
		m_Animation ->Draw(300, 310, 120, 80);
	}
}
