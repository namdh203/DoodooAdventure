#ifndef TIMER_H
#define TIMER_H

#define TARGET_FPS 60
const float TARGET_DELTATIME = 2.0f;

class Timer {
  public:
    void Tick();
    inline float GetDeltaTime() {
      return m_DeltaTime;
    }
    inline static Timer* GetGo() {
      return s_Go = (s_Go != nullptr) ? s_Go : new Timer();
    }
  private:
    Timer() {};
    static Timer* s_Go;
    float m_DeltaTime, m_LastTime;
};

#endif // TIMER_H
