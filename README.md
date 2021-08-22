# MusicAlbumTOC
[![License](https://img.shields.io/badge/License-GPLv3-blue.svg)](./LICENSE)

Arduino MusicAlbumTOC library to make album handling easier.

# Installation
```
cd Arduino/libraries/
git clone https://github.com/foogadgets/MusicAlbumTOC.git
```

# Usage example

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
  for (uint8_t i=0; i < minidiscTOC.getNoTracks(); i++) {
    Serial.println(minidiscTOC.getTrackName(i+1);
  }
  for(;;);
}
```
