#include "MusicTrack.h"


MusicTrack::MusicTrack(String name, int duration) : name(name), duration(duration) {
  blocks = (name.length()+6)/7;
}

String
MusicTrack::getName() const { return name; }

unsigned int
MusicTrack::getDuration() const { return duration; }

unsigned int
MusicTrack::getBlocks() const { return blocks; }
