#include "MusicAlbumTOC.h"
//#include <iostream>


MusicAlbumTOC::MusicAlbumTOC() {}

MusicAlbumTOC::MusicAlbumTOC(String title) : title(title) {}

unsigned int
MusicAlbumTOC::nameAlbum(String _title) { title = _title; return 0; }

void
MusicAlbumTOC::clearToc() { tracks.clear(); title = ""; }

unsigned int
MusicAlbumTOC::addTrack(String title, unsigned int duration) {
  tracks.push_back(MusicTrack(title, duration));
  return 0;
}

unsigned int
MusicAlbumTOC::renameTrack(String title, unsigned int duration, int pos) {
  tracks.at(pos) = MusicTrack(title, duration);
  return 0;
}

std::vector<MusicTrack>
MusicAlbumTOC::getTracks() const { return tracks; }

unsigned int
MusicAlbumTOC::size() const { return tracks.size(); }

String
MusicAlbumTOC::getTitle() const { return title; }

unsigned int
MusicAlbumTOC::getBlocks() const { 
  unsigned int totalBlocks = (title.length()+6)/7;

  for (unsigned int i=0; i<tracks.size(); i++) {
    totalBlocks += tracks[i].getBlocks();
  }
  return totalBlocks;
}

String
MusicAlbumTOC::getTrackName(unsigned int index) const {
  return tracks.at(index).getName();
}

unsigned int
MusicAlbumTOC::getTrackDuration(unsigned int index) const {
  return tracks.at(index).getDuration();
}

