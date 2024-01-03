#ifndef __MUSICALBUMTOC_H__
#define __MUSICALBUMTOC_H__

#include <vector>
#include "MusicTrack.h"


class MusicAlbumTOC {
private:
  String title;
  std::vector<MusicTrack> tracks;

public:
  MusicAlbumTOC();
  MusicAlbumTOC(String);
  void clearToc();
  unsigned int size() const;
  unsigned int getBlocks() const;
  unsigned int nameAlbum(String);
  unsigned int addTrack(String, unsigned int);
  unsigned int getTrackDuration(unsigned int) const;
  unsigned int renameTrack(String, unsigned int, int);
  String getTitle() const;
  String getTrackName(unsigned int) const;
  std::vector<MusicTrack> getTracks() const;
};
#endif /* __MUSICALBUMTOC_H__ */
