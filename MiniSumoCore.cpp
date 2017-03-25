#include <MiniSumoCore.h>

unsigned char qtrPins[] = {7, 5}; // Left, Right
unsigned int qtrNumSensors = 2;
unsigned int qtrTimeout = 2500;

// Constructor
MiniSumoCore::MiniSumoCore(const bool flipLeft, const bool flipRight,
  unsigned int trimLeft, unsigned int trimRight) :
  _qtrRC(qtrPins, qtrNumSensors, qtrTimeout, QTR_NO_EMITTER_PIN)

{
  motors.flipM1(flipLeft);
  motors.flipM2(flipRight);
  setMotorTrims(trimLeft, trimRight);
  _qtrThreshold = 550;
}

// Check border sensors & update state variables
void MiniSumoCore::checkBorder()
{
  // Read QTR sensors
  _qtrRC.read(_qtrValues);
  //Serial.print(_qtrValues[0]);
  //Serial.print("\t");
  //Serial.println(_qtrValues[1]);

  // Reset state variables
  _overBorderL = false;
  _overBorderR = false;

  if (_qtrValues[0] < _qtrThreshold)
  {
    // Left sensor is over border
    _overBorderL = true;
  }
  if (_qtrValues[1] < _qtrThreshold)
  {
    // Right sensor is over border
    _overBorderR = true;
  }
}

// Access to border state variables
bool MiniSumoCore::isOverBorder()
{
  if (_overBorderL || _overBorderR)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool MiniSumoCore::isOverBorderL()
{
  if (_overBorderL)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool MiniSumoCore::isOverBorderR()
{
  if (_overBorderR)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// Set motor speeds from fwdSpeed & turnSpeed
void MiniSumoCore::move(int fwdSpeed, int turnSpeed)
{
  motors.setM1Speed((fwdSpeed - turnSpeed) * _trimLeft / 40);
  motors.setM2Speed((fwdSpeed + turnSpeed) * _trimRight / 40);
}

// Set motor trims in 1 / 40 fraction
void MiniSumoCore::setMotorTrims(unsigned int trimLeft, unsigned int trimRight)
{
  _trimLeft = trimLeft;
  _trimRight = trimRight;
}
