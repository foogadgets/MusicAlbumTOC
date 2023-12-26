#include "MusicAlbumTOC.h"
#include <string.h>
#include <stdlib.h>


MusicAlbumTOC::MusicAlbumTOC(void)
{
}


MusicAlbumTOC::~MusicAlbumTOC(void)
{
  clearTOC();
}


uint8_t
MusicAlbumTOC::setAlbumName(const char *albumName)
{
  if(albumName == NULL) { return 4; }	// album a Nullstring is not allowed

  if(this->_albumName != NULL) { this->_usedBlocks -= (strlen(this->_albumName)+6)/7; free(this->_albumName); }

  this->_albumName = (char*)calloc((strlen(albumName)+1), sizeof(char));
  if (this->_albumName == NULL) { return 3; }
  strncpy(this->_albumName, albumName, strlen(albumName));

  this->_usedBlocks += (strlen(albumName)+6)/7;
  if (this->_usedBlocks > MAXBLOCKS) { return 2; }

  return 0;
}

   /* track number start from 1 ... 
   duration is stored in milliseconds
   */
uint8_t
MusicAlbumTOC::setTrackDuration(const uint8_t trackNo, const uint32_t duration)
{
  if (trackNo == 0 || trackNo > this->_numberOfTracks) { return 1; }
  
  if(this->_trackDuration_ms[trackNo-1] == NULL) {
    this->_trackDuration_ms[trackNo-1] = (uint32_t*)malloc(sizeof(uint32_t));
    if(this->_trackDuration_ms[trackNo-1] == NULL) { return 3; }
  }

  *this->_trackDuration_ms[trackNo-1] = duration;

  return 0;
}

   /* track number start from 1 ... 
   Return value in milliseconds
   */
uint32_t
MusicAlbumTOC::getTrackDuration(const uint8_t trackNo)
{
  if (trackNo == 0 || trackNo > this->_numberOfTracks) { return 0UL; }
  return *(this->_trackDuration_ms[trackNo-1]);
}


uint8_t
MusicAlbumTOC::addTrack(const char *trackName)
{
  if (this->_numberOfTracks >= MAXTRACKNO) { return 1; }

  if (this->_trackName[this->_numberOfTracks] != NULL) {
    free(this->_trackName[this->_numberOfTracks]);
  }

  if ((this->_usedBlocks+(strlen(trackName)+6)/7) > MAXBLOCKS) { return 2; }

  this->_trackName[this->_numberOfTracks] = (char*)calloc((strlen(trackName)+1), sizeof(char));
  if (this->_trackName[this->_numberOfTracks] == NULL) { return 3; }

  strncpy(this->_trackName[this->_numberOfTracks], trackName, strlen(trackName));

  this->_usedBlocks += (strlen(trackName)+6)/7;
  this->_numberOfTracks++;

  return 0;
}

uint8_t
MusicAlbumTOC::setTrackName(const uint8_t trackNo, const char *trackName)
{
  if (trackNo == 0 || trackNo > this->_numberOfTracks) { return 1; }

  if (this->_trackName[trackNo-1] != NULL) {
    uint16_t tmpBlocks = _usedBlocks - (strlen(this->_trackName[trackNo-1])+6)/7;
    if ((tmpBlocks + (strlen(trackName)+6)/7) > MAXBLOCKS) { return 2; }

    this->_usedBlocks -= (strlen(this->_trackName[trackNo-1])+6)/7;
    free(this->_trackName[trackNo-1]);
  }

  this->_trackName[trackNo-1] = (char*)calloc((1+strlen(trackName)), sizeof(char));
  if (this->_trackName[trackNo-1] == NULL) { return 3; }

  strncpy(this->_trackName[trackNo-1], trackName, strlen(trackName));

  this->_usedBlocks += (strlen(trackName)+6)/7;

  return 0;
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
  if (trackNo == 0 || trackNo > this->_numberOfTracks) { return NULL; }

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
  this->_usedBlocks = 0;
}
