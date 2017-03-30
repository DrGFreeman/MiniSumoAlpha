#include <Opponent.h>

// Constructor
Opponent::Opponent(unsigned int maxDist, const byte mfSize = 7) :
  _sensL(A0, mfSize), _sensR(A2, mfSize)
{
  _maxDist = maxDist;

  // Set Sharp sensors parameters
  _sensL.setModel(SharpDistSensor::GP2Y0A60SZLF_5V);
  _sensR.setModel(SharpDistSensor::GP2Y0A60SZLF_5V);
  _sensL.setValMinMax(134, 875);
  _sensR.setValMinMax(134, 875);
}

// Check for opponent and update state variables
void Opponent::check()
{
  // Reset state variable
  _inSight = false;

  // Get distance from sensors
  unsigned int distL = _sensL.getDist();
  unsigned int distR = _sensR.getDist();

  // Check if opponent is visible
  if (distL < _maxDist)
  {
    // Opponent is visible to the left sensor
    _inSight = true;
  }
  else
  {
    // Opponent is not visible to the left sensor
    distL = _maxDist;
  }
  if (distR < _maxDist)
  {
    // Opponent is visible to the right sensor
    _inSight = true;
  }
  else
  {
    // Opponent is not visible to the right sensor
    distR = _maxDist;
  }

  // Determine opponent position; positive = to the left
  _position = distR - distL;

  if (_inSight)
  {
    // Note current time
    _timeLastSeen = millis();

    if (_position > 0)
    {
      _direction = DIR_LEFT;
    }
    else
    {
      _direction = DIR_RIGHT;
    }
  }
}

// Return opponent direction
byte Opponent::direction()
{
  return _direction;
}

// Return true if opponent is in sight
bool Opponent::isInSight()
{
  if (_inSight)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// Return the position of the opponent
int Opponent::position()
{
  return _position;
}

// Return time when opponent was last seen (in ms)
unsigned long Opponent::timeLastSeen()
{
  return _timeLastSeen;
}

// Return time since opponent was last seen (in ms)
unsigned long Opponent::timeSinceLastSeen()
{
  return millis() - _timeLastSeen;
}
