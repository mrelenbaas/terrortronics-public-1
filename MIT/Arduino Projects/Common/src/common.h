#ifndef Common_h
#define Common_h

////////////////////////////////////////////////////////////////////////
// Function Stubs //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void interruptFunction();
void startButtonFunctionPress();
void startButtonFunctionRelease();
void resetButtonFunctionPress();
void resetButtonFunctionRelease();

////////////////////////////////////////////////////////////////////////
// Pins ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Serial //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   The serial baud rate.
*/
const int BAUD_RATE = 9600;

////////////////////////////////////////////////////////////////////////
// Time ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
   Time (in milliseconds) of a single second.
*/
const unsigned long TIME_ONE_SECOND = 1000L;

////////////////////////////////////////////////////////////////////////
// Undocumented ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// Untested Functions //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////
// Buttons /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

class Button {
  public:
    Button(int,
           Timer,
           unsigned long,
           unsigned long,
           void (*)(),
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
    void (*delegateFunctionPress)();
    void (*delegateFunctionRelease)();
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
              void (*)(),
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
              void (*)(),
              void (*)());
};

class Proximity : public Button {
  public:
    Proximity(int,
              Timer,
              unsigned long,
              unsigned long,
              void (*)(),
              void (*)());
};

////////////////////////////////////////////////////////////////////////
// Lights //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

class Light {
  public:
    Light(int);
    void turnOn();
    void turnOff();
  private:
    int pin;
};

////////////////////////////////////////////////////////////////////////
// State ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

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
