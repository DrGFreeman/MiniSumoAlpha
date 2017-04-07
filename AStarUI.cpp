#include <AStarUI.h>

// Constructor
AStarUI::AStarUI(byte buzzerMode)
{
  _buzzerMode = buzzerMode;
}

/*
 * Check battery level and return mode (0-7). This is used to turn-on
 * or flash the LEDs using ledsOnMode or flashLedsMode functions to indicate
 * battery level.
 * Red LED is always on,
 * Yellow LED is on above BATTERY_LOW level
 * Green LED is on above BATTERY_MED level.
 */
byte AStarUI::battLevelMode()
{
  unsigned int batteryMV = readBatteryMillivoltsLV();

  const unsigned int BATTERY_LOW = 6400;
  const unsigned int BATTERY_MED = 7000;

  // Red LED always on
  byte mode = 4;

  if (batteryMV > 0)
  {
    if (batteryMV > BATTERY_LOW)
    {
      // Turns Yellow LED on
      mode += 1;
    }
    if (batteryMV > BATTERY_MED)
    {
      // Turns Green LED on
      mode += 2;
    }
  }
  else
  {
    // Power switch is turned off; return 7.
    mode = 7;
  }
  return mode;
}

// Perform countdown
void AStarUI::countdown(unsigned int delay)
{
  unsigned long endTime = millis() + delay;

  // turn LEDs off
  ledsOff();

  // Do nothing until last five seconds
  while (millis() < endTime - 5000)
  {}

  // Last five seconds; turn on red LED
  ledRed(1);

  // Do nothing until last three seconds
  while (millis() < endTime - 3000)
  {}

  // Last three seconds start playing beeps
  play(NOTES_BEEP_SHORT);

  // Do nothing until last two seconds
  while (millis() < endTime - 2000)
  {}
  play(NOTES_BEEP_SHORT);

  // Do nothing until last seconds
  while (millis() < endTime - 1000)
  {}
  // Last second; play beep and turn on yellow LED
  play(NOTES_BEEP_SHORT);
  ledRed(0);
  ledYellow(1);



  // Do nothing until end of countdown
  while (millis() < endTime)
  {}
  // End of countdown; play long beep and turn on green LED
  play(NOTES_BEEP_LONG);
  ledYellow(0);
  ledGreen(1);
}

// Flash leds according to defined mode as 3 bit integer
void AStarUI::flashLedsMode(byte mode, unsigned int duration)
{
  unsigned long startTime = millis();

  while (millis() - startTime < duration)
  {
    // Turn LEDs on
    ledsOnMode(mode);
    delay(125);

    // Turn LEDs off
    ledsOff();
    delay(125);
  }
  ledsOff();
}

// Turn all LEDs off
void AStarUI::ledsOff()
{
  ledYellow(0);
  ledGreen(0);
  ledRed(0);
}

/* Turn LEDs on according to defined mode as 3 bit integer
 * 1st bit: Yellow LED
 * 2nd bit: Green LED
 * 3rd bit: Red LED
*/
void AStarUI::ledsOnMode(byte mode)
{
  ledsOff();

  if (bitRead(mode, 0)) {ledYellow(1);}
  if (bitRead(mode, 1)) {ledGreen(1);}
  if (bitRead(mode, 2)) {ledRed(1);}
}

// Play pre-defined notes sequences with buzzer
void AStarUI::play(byte notes)
{
  if (_buzzerMode == BUZZER_ENABLED)
  {
    //char notes[24];
    switch (notes) {
      case NOTES_BOOT:
        buzzer.play("L16 V10 >c>e>g>>c");
        break;

      case NOTES_VALUE_UP:
        buzzer.play("L16 V10 >c>>c");
        break;

      case NOTES_VALUE_DOWN:
        buzzer.play("L16 V10 >>c>c");
        break;

      case NOTES_BEEP_SHORT:
        buzzer.play("L16 V10 >>c");
        break;

      case NOTES_BEEP_LONG:
        buzzer.play("L2 V10 >>c");
        break;

      case NOTES_BEEP_MED_SHORT:
        buzzer.play("L16 V10 >c");
        break;

      case NOTES_SELECT:
        buzzer.play("L16 V10 >>cR>>cR>>c");
        break;

      case NOTES_END_SELECT:
        buzzer.play("L16 V10 >cR>cR>c");
        break;
    }
  }
}

// Use buttons to select mode as 3 bit integer (0-7)
byte AStarUI::selectMode(unsigned int waitTime)
{
  byte mode = 0;

  unsigned long waitStartTime = millis();

  ledsOff();

  if (_buzzerMode == BUZZER_ENABLED)
  {
    play(NOTES_SELECT);
  }

  while (millis() - waitStartTime < waitTime)
  {
    if (btnA.getSingleDebouncedPress())
    {
      // Button A is pressed
      if (bitRead(mode, 0))
      {
        // Bit 0 (1) is high, set it to low and turn yellow LED off
        mode -= 1;
        ledYellow(0);
        if (_buzzerMode == BUZZER_ENABLED)
        {
          play(NOTES_VALUE_DOWN);
        }
      }
      else
      {
        // Bit 0 (1) is low, set it to high and turn yellow LED on
        mode += 1;
        ledYellow(1);
        if (_buzzerMode == BUZZER_ENABLED)
        {
          play(NOTES_VALUE_UP);
        }
      }
    }
    if (btnB.getSingleDebouncedPress())
    {
      // Button B is pressed
      if (bitRead(mode, 1))
      {
        // Bit 1 (2) is high, set it to low and turn green LED off
        mode -= 2;
        ledGreen(0);
        if (_buzzerMode == BUZZER_ENABLED)
        {
          play(NOTES_VALUE_DOWN);
        }
      }
      else
      {
        // Bit 1 (2) is low, set it to high and turn Green LED on
        mode += 2;
        ledGreen(1);
        if (_buzzerMode == BUZZER_ENABLED)
        {
          play(NOTES_VALUE_UP);
        }
      }
    }
    if (btnC.getSingleDebouncedPress())
    {
      // Button C is pressed
      if (bitRead(mode, 2))
      {
        // Bit 2 (4) is high, set it to low and turn red LED off
        mode -= 4;
        ledRed(0);
        if (_buzzerMode == BUZZER_ENABLED)
        {
          play(NOTES_VALUE_DOWN);
        }
      }
      else
      {
        // Bit 2 (4) is low, set it to high and turn red LED on
        mode += 4;
        ledRed(1);
        if (_buzzerMode == BUZZER_ENABLED)
        {
          play(NOTES_VALUE_UP);
        }
      }
    }
  }
  if (_buzzerMode == BUZZER_ENABLED)
  {
    play(NOTES_END_SELECT);
  }
  ledsOff();
  return mode;
}
