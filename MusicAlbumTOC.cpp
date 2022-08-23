#include "MusicAlbumTOC.h"
#include <string.h>
#include <stdlib.h>


MusicAlbumTOC::MusicAlbumTOC(void)
{
  this->_numberOfTracks = 0;
  this->_albumName = NULL;
}

MusicAlbumTOC::MusicAlbumTOC(const char* albumName)
{
  _numberOfTracks = 0;
  clearTOC();

  this->_albumName = (char*)calloc((strlen(albumName)+1), sizeof(char));
  strncpy(this->_albumName, albumName, strlen(albumName));
}

MusicAlbumTOC::~MusicAlbumTOC(void)
{
  clearTOC();
}


bool
MusicAlbumTOC::setAlbumName(const char *albumName)
{
  if(this->_albumName != NULL) { free(this->_albumName); }

  this->_albumName = (char*)calloc((strlen(albumName)+1), sizeof(char));
  if (this->_albumName == NULL) { return false; }
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
  
  if(this->_trackDuration_ms[trackNo-1] == NULL) {
    this->_trackDuration_ms[trackNo-1] = (uint32_t*)malloc(sizeof(uint32_t));
    if(this->_trackDuration_ms[trackNo-1] == NULL) { return false; }
  }

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

  if (this->_trackName[this->_numberOfTracks] != NULL) {
    free(this->_trackName[this->_numberOfTracks]);
  }

  this->_trackName[this->_numberOfTracks] = (char*)calloc((strlen(trackName)+1), sizeof(char));
  if (this->_trackName[this->_numberOfTracks] == NULL) return false;

  strncpy(this->_trackName[this->_numberOfTracks], trackName, strlen(trackName));

  this->_numberOfTracks++;

  return true;
}

bool
MusicAlbumTOC::setTrackName(const uint8_t trackNo, const char *trackName)
{
  if (trackNo == 0 || trackNo > this->_numberOfTracks) return false;

  if (this->_trackName[trackNo-1] != NULL) {
    free(this->_trackName[trackNo-1]);
  }

  this->_trackName[trackNo-1] = (char*)calloc((1+strlen(trackName)), sizeof(char));
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
  if (trackNo == 0 || trackNo > this->_numberOfTracks) return NULL;

  return this->_trackName[(trackNo - 1)];
}

void
MusicAlbumTOC::clearTOC(void) {
  if(this->_albumName != NULL) {
    free(this->_albumName);
    this->_albumName = NULL;
  }

  for (uint8_t i = 0; i < this->_numberOfTracks; i++) {
    free(this->_trackName[i]);
    this->_trackName[i] = NULL;
    free(this->_trackDuration_ms[i]);
    this->_trackDuration_ms[i] = NULL;
  }

  this->_numberOfTracks = 0;
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
