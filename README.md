# MusicAlbumTOC

**Arduino MusicAlbumTOC library **


-------------------------------------------------------------------------------------------------------------------

# Installation
Create a new folder called "MusicAlbumTOC" under the folder named "libraries" in your Arduino sketchbook folder.
Create the folder "libraries" in case it does not exist yet. Place all the files in the "MusicAlbumTOC" folder.

# Usage
To use the library in your own sketch, select it from *Sketch > Import Library*.

# Example

Simplest example of using this library:

```c++
#include "MusicAlbumTOC.h"
MusicAlbumTOC minidiscTOC;
MusicAlbumTOC anotherMinidiscTOC("Deep Purple-Machine Head");

void setup() {
  minidiscTOC.setAlbumName("Imagine Dragons-Evolve");
  minidiscTOC.addTrack("Next to me");
  minidiscTOC.addTrack("I Don't know why");
  minidiscTOC.addTrack("Whatever it takes");
  minidiscTOC.addTrack("Walking with the wire");
  minidiscTOC.setTrackName(4, "Beliver");
}

void loop() {
  uint8_t noOfTracks = minidiscTOC.getNoTracks();
  for (uint8_t i=0; i<noOfTracks) {
    Serial.println(minidiscTOC.getTrackName(i+1);
  }
}
```
