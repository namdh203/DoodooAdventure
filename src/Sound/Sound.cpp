#include "Sound.h"

Sound* Sound::s_Go = nullptr;

using namespace std;

void Sound::play(string path, int loops)
{
	Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
  Mix_PlayChannel(-1, chunk, loops);
}
