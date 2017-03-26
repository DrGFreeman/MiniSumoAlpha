#include <PID.h>

// Constructor
PID::PID(float Kp, float Ki, float Kd)
{
  setGains(Kp, Ki, Kd);
  reset();
  _boundRange = false;
}

// Bound the command within the command range
int PID::boundCmd(int cmdIn)
{
  int cmdOut = cmdIn;

  if (_boundRange)
  {
    if (cmdIn < _cmdMin)
    {
      cmdOut = _cmdMin;
    }
    else if (cmdIn > _cmdMax)
    {
      cmdOut = _cmdMax;
    }
  }
  return cmdOut;
}

// Get command without time step
int PID::getCmd(int setPoint, int procVar)
{
  // Calculate error terms
  int error = setPoint - procVar;
  _errorIntegral += error;
  int errorDerivative = error - _errorPrevious;

  // Set last error to current error
  _errorPrevious = error;

  // Calculate command
  int cmd = _Kp * error + _Ki * _errorIntegral + _Kd * errorDerivative;

  // return bound command
  return boundCmd(cmd);
}

// Get command with auto time step calculation
int PID::getCmdAutoStep(int setPoint, int procVar)
{
  // Calculate time step from last time method was called
  unsigned long currentTime = millis();
  unsigned int timeStep = currentTime - _lastCmdTime;

  // Set last time method was called to current time
  _lastCmdTime = currentTime;

  // Get command
  return getCmdStep(setPoint, procVar, timeStep);
}

// Get command with specified time step
int PID::getCmdStep(int setPoint, int procVar, unsigned int timeStep)
{
  // Calculate error terms
  int error = setPoint - procVar;
  _errorIntegral += (error + _errorPrevious) / 2 * timeStep;
  float errorDerivative = (error - _errorPrevious) / float(timeStep);

  // Set last error to current error
  _errorPrevious = error;

  // Calculate command
  int cmd = _Kp * error + _Ki * _errorIntegral + _Kd * errorDerivative;

  // return bound command
  return boundCmd(cmd);
}

// Reset the PID error terms
void PID::reset()
{
  _errorPrevious = 0;
  _errorIntegral = 0;

  _lastCmdTime = millis();
}

// Set the maximum command range
void PID::setCmdRange(int cmdMin, int cmdMax)
{
  _cmdMin = cmdMin;
  _cmdMax = cmdMax;
  _boundRange = true;
}

// Set the PID gains
void PID::setGains(float Kp, float Ki, float Kd)
{
  _Kp = Kp;
  _Ki = Ki;
  _Kd = Kd;
}
