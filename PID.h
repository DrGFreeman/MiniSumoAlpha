#ifndef PID_h
#define PID_h

#include <Arduino.h>

class PID
{
public:
  // Constructor
  PID(float Kp = 1.0, float Ki = 0.0, float Kd = 0.0);

  /* Get command without time step
   * setPoint it the desired process set point
   * procVar is the currrent value of the process variable to be controlled
   * No time step is used (assumed = 1)
  */
  int getCmd(int setPoint, int procVar);

  /* Get command with auto time step calculation
   * setPoint it the desired process set point
   * procVar is the currrent value of the process variable to be controlled
   * The time step is calculated from the last call to the method
  */
  int getCmdAutoStep(int setPoint, int procVar);

  /* Get command with specified time step
   * setPoint it the desired process set point
   * procVar is the currrent value of the process variable to be controlled
   * timeStep is the timeStep to be used for integration / derivation
  */
  int getCmdStep(int setPoint, int procVar, unsigned int timeStep);

  // Reset the PID error terms
  void reset();

  /* Set the maximum command range. Commands calculated outside the cmdMin and
   * cmdMax range will be set to cmdMin or cmdMax respectively.
  */
  void setCmdRange(int cmdMin, int cmdMax);

  // Set the PID gains
  void setGains(float Kp, float Ki, float Kd);

private:
  // Command range
  int _cmdMin;
  int _cmdMax;
  bool _boundRange;

  // Error terms
  int _errorPrevious;
  long _errorIntegral;

  // Gains
  float _Kp, _Ki, _Kd;

  // Last time the getCmd method was called
  unsigned long _lastCmdTime;

  // Bound the command within command range
  int boundCmd(int cmdIn);
};

#endif
