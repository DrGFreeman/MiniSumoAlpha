#ifndef MiniSumoCore_h
#define MiniSumoCore_h

#include <Arduino.h>
#include <AStar32U4.h>
#include <QTRSensors.h>

class MiniSumoCore
{
public:
    // Motors
  AStar32U4Motors motors;

  // Constructor
  MiniSumoCore(const bool flipLeft = false, const bool flipRight = false,
    unsigned int trimLeft = 40, unsigned int trimRight = 40);

  // Check border sensors & update state variables
  void checkBorder();

  // Access to border state variables
  bool isOverBorder();
  bool isOverBorderL();
  bool isOverBorderR();

  // Set motor speeds from fwdSpeed & turnSpeed
  void move(int fwdSpeed, int turnSpeed);

  // Set border detection threshold for QTR sensors
  void setBorderThreshold(unsigned int threshold);

  // Set motor trims in 1 / 40 fraction
  void setMotorTrims(unsigned int trimLeft, unsigned int trimRight);

  // Stop motors
  void stop();

private:
  // QTR sensors
  unsigned int _qtrThreshold;
  unsigned int _qtrValues[2];
  QTRSensorsRC _qtrRC;

  // Border state variables
  bool _overBorderL;
  bool _overBorderR;

  // Motor trims in 1 / 40 fraction
  int _trimLeft;
  int _trimRight;
};

#endif
