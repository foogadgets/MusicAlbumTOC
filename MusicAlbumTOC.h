#ifndef MUSICALBUMTOC_H
#define MUSICALBUMTOC_H

#include <stdint.h>
#include <cstddef>

#define MAXTRACKNO  100
#define MAXBLOCKS	255

class MusicAlbumTOC
{
  public:
    MusicAlbumTOC(void);
    ~MusicAlbumTOC(void);

    uint8_t addTrack(const char *trackName);
    uint8_t setAlbumName(const char *albumName);
    uint8_t setTrackName(const uint8_t trackNo, const char *trackName);
    uint8_t setTrackDuration(const uint8_t trackNo, const uint32_t duration);
    uint32_t getTrackDuration(const uint8_t trackNo);
    uint8_t getNoTracks(void);
    char*   getAlbumName(void);
    char*   getTrackName(const uint8_t trackNo);
    void    clearTOC(void);
  private:
    uint16_t _usedBlocks = 0;
    char   *_albumName = NULL;
    char   *_trackName[MAXTRACKNO] = { NULL };
    uint32_t *_trackDuration_ms[MAXTRACKNO] = { NULL };
    uint8_t _numberOfTracks = 0;
};

#endif // MUSICALBUMTOC_H
