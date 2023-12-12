#ifndef Common_h
#define Common_h

void interruptFunction();

class Timer {
  public:
    //Timer(int);
    void pseudoConstructor(unsigned long, unsigned long);
    int updateStart(bool, int *);
    int updateStop(bool, int *);
    void reset();
  private:
    unsigned long previous;
    unsigned long current;
    unsigned long delta;
    unsigned long count;
    unsigned long periodStart;
    unsigned long periodStop;
};

class SoundDigital {
  public:
    SoundDigital(int);
    int printDefinitions();
    void updateHotState();
  private:
    int pin;
    bool stateHot;
};

class SoundAnalog {
  public:
    SoundAnalog(int);
    int printDefinitions();
    void updateHotState();
  private:
    int pin;
    float stateHot;
};

class Proximity {
  public:
    Proximity(int);
    int printDefinitions();
    void updateHotState();
  private:
    int pin;
    bool stateHot;
};

class Water {
  public:
    Water(int);
    int printDefinitions();
    void updateHotState();
  private:
    int pin;
    float stateHot;
};

class ThumbStick {
  public:
    ThumbStick(int, int);
    int printDefinitions();
    void updateHotState();
  private:
    int pinHorizontal;
    int pinVertical;
    float stateHotHorizontal;
    float stateHotVertical;
};

class Button {
  public:
    Button(int,
           Timer,
           unsigned long,
           unsigned long,
           void (*)());
    int printDefinitions();
    int updateHotState();
    int debounceByBlockPress();
    int debounceByBlockRelease();
    int debounceByPositionPress();
    int debounceByPositionRelease();
    int debounceByTargetPress();
    int debounceByTargetRelease();
    int debounceByTimePress();
    int debounceByTimeRelease();
    void startTargeting();
    void stopTargeting();
    void reset();
    void (*delegateFunction)();
  //protected:
    int pin;
    bool stateHot;
    int stateDebouncedByTime;
    int statePositionPrevious;
    bool statePositionCurrent;
    bool isTarget;
    int isBlocked;
    int * hotButtons;
    int index;
    Timer timer;
  private:
    static Button thisButton;
};

class ButtonARM : public Button {
  public:
    ButtonARM(int,
              Timer,
              unsigned long,
              unsigned long,
              void (*)());
  private:
    static void interruptFunction();
};

class ButtonAVR : public Button {
  public:
    ButtonAVR(int,
              Timer,
              unsigned long,
              unsigned long,
              void (*)());
};

class State {
  public:
    void startRunning();
    void startWaiting();
    int isRunning();
    int isWaiting();
  private:
    int state = -1;
};

//int state = -1;
enum stateEnum {
  stateRunning,
  stateWaiting
};

#endif
