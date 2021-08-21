#ifndef MUSICALBUMTOC_H
#define MUSICALBUMTOC_H

#include <stdint.h>


#define MAXTRACKNO  100

class MusicAlbumTOC
{
  public:
    MusicAlbumTOC(void);
    MusicAlbumTOC(const char* albumName);
    ~MusicAlbumTOC(void);

    bool    setAlbumName(const char *albumName);
    bool    addTrack(const char *trackName);
    bool    setTrackName(const uint8_t trackNo, const char *trackName);
    bool    setTrackDuration(const uint8_t trackNo, const uint32_t duration);
    uint32_t getTrackDuration(const uint8_t trackNo);
    uint8_t getNoTracks(void);
    char*   getAlbumName(void);
    char*   getTrackName(const uint8_t trackNo);
    void    clearToc(void);
  private:
    uint8_t _getUsedBlocks(void);
    char   *_albumName;
    char   *_trackName[MAXTRACKNO];
    uint32_t *_trackDuration_ms[MAXTRACKNO];
    uint8_t _numberOfTracks;
};

#endif // MUSICALBUMTOC_H
