#include "MusicAlbumTOC.h"
#include <string.h>
#include <stdlib.h>


MusicAlbumTOC::MusicAlbumTOC(void)
{
  this->_albumName = (char*)calloc(1, sizeof(char));
  strncpy(this->_albumName, "\0", 1);

  for (uint8_t i = 0; i < MAXTRACKNO; i++) {
    this->_trackName[i] = (char*)calloc(1, sizeof(char));
    strncpy(this->_trackName[i], "\0", 1);

    this->_trackDuration_ms[i] = (uint32_t*)malloc(sizeof(uint32_t));
    *this->_trackDuration_ms[i] = 0;
  }

  this->_numberOfTracks = 0;
  this->_usedBlocks = 0;
}


MusicAlbumTOC::~MusicAlbumTOC(void)
{
  if(this->_albumName != NULL) {
    free(this->_albumName);
    this->_albumName = NULL;
  }

  for (uint8_t i = 0; i < MAXTRACKNO; i++) {
    if (this->_trackName[i] != NULL) {
      free(this->_trackName[i]);
      this->_trackName[i] = NULL;
    }
    if (this->_trackDuration_ms[i] != NULL) {
      free(this->_trackDuration_ms[i]);
    }
  }
}


uint8_t
MusicAlbumTOC::setAlbumName(const char *albumName)
{
  // Check how many blocks will be consumed after album Name change
  if ((this->_usedBlocks - (strlen(this->_albumName)+6)/7 + (strlen(albumName)+6)/7) > MAXBLOCKS) { return 1; }

  // Remove old album name
  this->_usedBlocks -= (strlen(this->_albumName)+6)/7;
  free(this->_albumName);

  // Add new album name
  this->_albumName = (char*)calloc((strlen(albumName)+1), sizeof(char));
  strncpy(this->_albumName, albumName, strlen(albumName));

  this->_usedBlocks += (strlen(albumName)+6)/7;

  return 0;
}


   /* track number start from 1 ... 
   duration is stored in milliseconds
   */
uint8_t
MusicAlbumTOC::setTrackDuration(const uint8_t trackNo, const uint32_t duration)
{
  if (trackNo == 0 || trackNo > this->_numberOfTracks) { return 1; }
  
  *this->_trackDuration_ms[trackNo-1] = duration;

  return 0;
}


   /* track number start from 1 ... 
   Return value in milliseconds
   */
uint32_t
MusicAlbumTOC::getTrackDuration(const uint8_t trackNo)
{
  if (trackNo == 0 || trackNo > this->_numberOfTracks) { return 0; }

  return *this->_trackDuration_ms[trackNo-1];
}


uint8_t
MusicAlbumTOC::addTrack(const char *trackName)
{
  if (this->_numberOfTracks >= MAXTRACKNO) { return 1; }
  if ((this->_usedBlocks + (strlen(trackName)+6)/7) > MAXBLOCKS) { return 2; }

  free(this->_trackName[this->_numberOfTracks]);


  this->_trackName[this->_numberOfTracks] = (char*)calloc((strlen(trackName)+1), sizeof(char));
  strncpy(this->_trackName[this->_numberOfTracks], trackName, strlen(trackName));

  this->_usedBlocks += (strlen(trackName)+6)/7;
  this->_numberOfTracks++;

  return 0;
}


uint8_t
MusicAlbumTOC::setTrackName(const uint8_t trackNo, const char *trackName)
{
  if (trackNo == 0 || trackNo > this->_numberOfTracks) { return 1; }

  // Check how many blocks will be consumed after track name change
  if ((this->_usedBlocks - (strlen(this->_trackName[trackNo-1])+6)/7 + (strlen(trackName)+6)/7) > MAXBLOCKS) { return 2; }

  this->_usedBlocks -= (strlen(this->_trackName[trackNo-1])+6)/7;
  free(this->_trackName[trackNo-1]);

  this->_trackName[trackNo-1] = (char*)calloc((strlen(trackName)+1), sizeof(char));
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


uint8_t
MusicAlbumTOC::getUsedBlocks(void)
{
  return this->_usedBlocks;
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
    this->_albumName = (char*)calloc(1, sizeof(char));
    strncpy(this->_albumName, "\0", 1);
  }

  for (uint8_t i = 0; i < MAXTRACKNO; i++) {
    free(this->_trackName[i]);
    this->_trackName[i] = (char*)calloc(1, sizeof(char));
    strncpy(this->_trackName[i], "\0", 1);

    *this->_trackDuration_ms[i] = 0;
  }

  this->_numberOfTracks = 0;
  this->_usedBlocks = 0;
}
