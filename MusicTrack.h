#ifndef __MUSICTRACK_H__
#define __MUSICTRACK_H__

#include "Arduino.h" // for delayMicroseconds, digitalPinToBitMask, etc

class MusicTrack {
private:
  String name;
  unsigned int duration;
  unsigned int blocks;

public:
  MusicTrack(String, int);
  unsigned int getDuration() const;
  unsigned int getBlocks() const;
  String getName() const;
};
#endif /* __MUSICTRACK_H__ */
