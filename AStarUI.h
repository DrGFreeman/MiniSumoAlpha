#ifndef AStarUI_h
#define AStarUI_h

#include <Arduino.h>
#include <AStar32U4.h>

class AStarUI
{
public:
    // Buttons
  AStar32U4ButtonA btnA;
  AStar32U4ButtonB btnB;
  AStar32U4ButtonC btnC;

  // Buzzer
  PololuBuzzer buzzer;

  // Buzzer modes
  enum buzzerModes
  {
    BUZZER_ENABLED,
    BUZZER_DISABLED
  };

  // Pre-defined notes sequences to play with buzzer
  enum buzzerNotes
  {
    NOTES_BOOT,
    NOTES_VALUE_UP,
    NOTES_VALUE_DOWN,
    NOTES_BEEP_SHORT,
    NOTES_BEEP_LONG,
    NOTES_BEEP_MED_SHORT,
    NOTES_SELECT,
    NOTES_END_SELECT
  };

  // Constructor
  AStarUI(byte buzzerMode);

  /* Check battery level and return mode (0-7). This is used to turn-on
   * or flash the LEDs using ledsOnMode or flashLedsMode functions to indicate
   * battery level.
   * Red LED is always on,
   * Yellow LED is on above BATTERY_LOW level
   * Green LED is on above BATTERY_MED level.
   */
  byte battLevelMode();

  // Flash leds according to defined mode as 3 bit integer (0-7)
  void flashLedsMode(byte mode, unsigned int duration);

  // Turn all LEDs off
  void ledsOff();

  /* Turn LEDs on according to defined mode as 3 bit integer (0-7)
   * 1st bit: Yellow LED
   * 2nd bit: Green LED
   * 3rd bit: Red LED
   */
  void ledsOnMode(byte mode);

  // Play Pre-defined notes sequence with buzzer
  void play(byte notes);

  // Use buttons to select mode as 3 bit integer (0-7)
  byte selectMode(unsigned int waitTime);

private:

  // Buzzer mode
  int _buzzerMode;
};

#endif
