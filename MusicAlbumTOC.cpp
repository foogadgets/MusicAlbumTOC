#include "MusicAlbumTOC.h"
#include <string.h>
#include <stdlib.h>


MusicAlbumTOC::MusicAlbumTOC(void)
{
  clearToc();
}

MusicAlbumTOC::MusicAlbumTOC(const char* albumName)
{
  clearToc();

  this->_albumName = (char*)calloc(1, (1+strlen(albumName))*sizeof(char));
  strncpy(this->_albumName, albumName, strlen(albumName));
}

MusicAlbumTOC::~MusicAlbumTOC(void)
{
  clearToc();
}


bool
MusicAlbumTOC::setAlbumName(const char *albumName)
{
  this->_albumName = (char*)calloc(1, (1+strlen(albumName))*sizeof(char));
  if (this->_albumName == NULL) return false;

  strncpy(this->_albumName, albumName, strlen(albumName));

  return true;
}

   /* track number start from 1 ... 
   duration is stored in milliseconds
   */
bool
MusicAlbumTOC::setTrackDuration(const uint8_t trackNo, const uint32_t duration)
{
  if (trackNo == 0 || trackNo > this->_numberOfTracks) return false;

  this->_trackDuration_ms[trackNo-1] = (uint32_t*)malloc(sizeof(uint32_t));
  if (this->_trackDuration_ms[trackNo-1] == NULL) return false;

  *this->_trackDuration_ms[trackNo-1] = duration;

  return true;
}

   /* track number start from 1 ... 
   Return value in milliseconds
   */
uint32_t
MusicAlbumTOC::getTrackDuration(const uint8_t trackNo)
{
  if (trackNo == 0 || trackNo > this->_numberOfTracks) return 0UL;
  return *(this->_trackDuration_ms[trackNo-1]);
}


bool
MusicAlbumTOC::addTrack(const char *trackName)
{
  if (this->_numberOfTracks >= MAXTRACKNO) return false;

  this->_trackName[this->_numberOfTracks] = (char*)calloc(1, (1+strlen(trackName))*sizeof(char));
  if (this->_trackName[this->_numberOfTracks] == NULL) return false;

  strncpy(this->_trackName[this->_numberOfTracks], trackName, strlen(trackName));
  this->_numberOfTracks++;

  return true;
}

bool
MusicAlbumTOC::setTrackName(const uint8_t trackNo, const char *trackName)
{
  if (trackNo == 0 || trackNo > this->_numberOfTracks) return false;

  free(this->_trackName[trackNo-1]);

  this->_trackName[trackNo-1] = (char*)calloc(1, (1+strlen(trackName))*sizeof(char));
  if (this->_trackName[trackNo-1] == NULL) return false;

  strncpy(this->_trackName[trackNo-1], trackName, strlen(trackName));

  return true;
}

uint8_t
MusicAlbumTOC::getNoTracks(void)
{
  return this->_numberOfTracks;
}

char*
MusicAlbumTOC::getAlbumName(void)
{
  return this->_albumName;
}

char*
MusicAlbumTOC::getTrackName(const uint8_t trackNo)
{
  if (trackNo == 0 || trackNo > MAXTRACKNO) return NULL;

  return this->_trackName[(trackNo - 1)];
}

void
MusicAlbumTOC::clearToc(void) {
  if (this->_numberOfTracks > 0) {
    free(this->_albumName);
    this->_albumName = NULL;

    for (uint8_t i = 0; i < this->_numberOfTracks; i++) {
      free(this->_trackName[i]);
      this->_trackName[i] = NULL;
      free(this->_trackDuration_ms[i]);
      this->_trackDuration_ms[i] = NULL;
    }
    this->_numberOfTracks = NULL;
  }
}

uint8_t
MusicAlbumTOC::_getUsedBlocks(void)
{
  uint8_t usedChars = 0;
  usedChars += strlen(this->_albumName);
  for(uint8_t i=0; i<this->_numberOfTracks; i++)
    usedChars += strlen(this->_trackName[i]);

  return (usedChars+6)/7;
}
