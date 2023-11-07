#include <Arduino.h>

/*! Counts FPS. */
class Timer {
public:
  const int ANALOG_PIN = 10;            ///< Pin for FPS display.
  const float ANALOG_STEP_MAX = 255.0f; ///< Analog range max.
  const float ANALOG_VOLT_MAX = 5.0f;   ///< Analog volt max.
  const float FPS_MAX = 40000.0f;       ///< Estimated FPS max.
  const long PERIOD = 1000L;            ///< Milliseconds in a second.
  void updater();
private:
  long count;    ///< Frames counted during current second.
  long current;  ///< Time (milliseconds) since start of second.
  long fps;      ///< Frames counted during previous second.
  long now;      ///< Time (milliseconds) since start of Arduino.
  long previous; ///< Time (milliseconds) at previous update.
  float fps_to_percentage();
};

/**
 * Counts frames for 1 second, then resets.
 */
void Timer::updater() {
  now = millis();
  current += now - previous;
  previous = now;
  ++count;
  if(current > PERIOD) {
    fps = count;
    count = 0L;
    current = 0L;
    analogWrite(ANALOG_PIN, fps_to_percentage());
  }
}

/**
 * Converts FPS to percentage (for analog output).
 */
float Timer::fps_to_percentage() {
  float percentage;
  percentage = (float)fps / FPS_MAX;
  percentage = ANALOG_STEP_MAX * percentage;
  percentage = (ANALOG_STEP_MAX - percentage) / ANALOG_VOLT_MAX;
  return percentage;
}
