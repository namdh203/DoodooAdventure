#ifndef SOUND_H
#define SOUND_H

#include "SDL_mixer.h"
#include <string>
class Sound {
  public:
    static Sound* GetGo() {
      return s_Go = (s_Go != nullptr ? s_Go : new Sound() );
    }
    void play(std::string path, int loop);
  private:
    static Sound* s_Go;
};

#endif // SOUND_H
