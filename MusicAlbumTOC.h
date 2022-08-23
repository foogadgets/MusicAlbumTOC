#ifndef MUSICALBUMTOC_H
#define MUSICALBUMTOC_H

#include <stdint.h>
#include <cstddef>

#define MAXTRACKNO  100

class MusicAlbumTOC
{
  public:
    MusicAlbumTOC(void);
    MusicAlbumTOC(const char* albumName);
    ~MusicAlbumTOC(void);

    bool    addTrack(const char *trackName);
    bool    setAlbumName(const char *albumName);
    bool    setTrackName(const uint8_t trackNo, const char *trackName);
    bool    setTrackDuration(const uint8_t trackNo, const uint32_t duration);
    uint32_t getTrackDuration(const uint8_t trackNo);
    uint8_t getNoTracks(void);
    char*   getAlbumName(void);
    char*   getTrackName(const uint8_t trackNo);
    void    clearTOC(void);
  private:
    uint8_t _getUsedBlocks(void);
    char   *_albumName = NULL;
    char   *_trackName[MAXTRACKNO] = { NULL };
    uint32_t *_trackDuration_ms[MAXTRACKNO] = { NULL };
    uint8_t _numberOfTracks = 0;
};

#endif // MUSICALBUMTOC_H
