#ifndef Opponent_h
#define Opponent_h

#include <Arduino.h>
#include <SharpDistSensor.h>

class Opponent
{
public:
  enum directions
  {
    DIR_LEFT,
    DIR_RIGHT
  };

  /* Constructor
   * maxDist is the max distance to look for the opponent
   * mfSize is the window size for the sensors median filter
  */
  Opponent(unsigned int maxDist, const byte mfSize);

  // Check for opponent and update state variables
  void check();

  // Return opponent direction
  byte direction();

  // Return true if opponent is in sight
  bool isInSight();

  /* Return the position of the opponent
   * The position is defined as the difference between the right and left sensor
   * distances. A positive number means the opponent is to the left.
  */
  int position();

  // Return time when opponent was last seen (in ms)
  unsigned long timeLastSeen();

  // Return time since opponent was last seen (in ms)
  unsigned long timeSinceLastSeen();

private:
  // Opponent direction
  byte _direction;

  // Opponent is in sight
  bool _inSight;

  // Last time opponent was seen
  unsigned long _timeLastSeen;

  // Max distance to look for opponent
  unsigned int _maxDist;

  // Opponent position
  int _position;

  // Sharp distance sensors
  SharpDistSensor _sensL;
  SharpDistSensor _sensR;
};

#endif
