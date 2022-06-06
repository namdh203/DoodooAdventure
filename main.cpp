#include "Engine.h"
#include "Timer.h"
#include "Sound.h"

int main(int argc, char** argv) {

  Engine::GetGo() -> Init();
//  Sound::GetGo()->play("assets/bgm/bgm.wav", 10);
  while (Engine::GetGo() -> IsRunning()) {
    Engine::GetGo()->Events();
    Engine::GetGo()->Update();
    Engine::GetGo()->Render();
    Timer::GetGo()->Tick();
  }

  Engine::GetGo()->Clean();

  return 0;
}
