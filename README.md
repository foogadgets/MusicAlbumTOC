# MusicAlbumTOC

**Arduino MusicAlbumTOC library **


(C) foogadgets, 2021, CC-BY-SA 4.0
https://creativecommons.org/licenses/by-sa/4.0/

-------------------------------------------------------------------------------------------------------------------

# Installation
Create a new folder called "MusicAlbumTOC" under the folder named "libraries" in your Arduino sketchbook folder.
Create the folder "libraries" in case it does not exist yet. Place all the files in the "MusicAlbumTOC" folder.

# Usage
To use the library in your own sketch, select it from *Sketch > Import Library*.

# Example

Simplest example of using this library:

```c++
#include <MusicAlbumTOC.h>

MusicAlbumTOC minidiscTOC;

void setup() {
  minidiscTOC.nameAlbum("Imagine Dragons - Evolve");
  minidiscTOC.addTrack("Next To Me", 34523);
  minidiscTOC.addTrack("I Don't Know Why", 64738);
  minidiscTOC.addTrack("Whatever It Takes", 78994);
  minidiscTOC.addTrack("Never gonna give you up", 2666475);
  minidiscTOC.addTrack("Walking with the wire", 2666475);

  minidiscTOC.renameTrack("Beliver", 4847738, 4);

  Serial.println(minidiscTOC.getTitle());

  for (const MusicTrack& track : minidiscTOC.getTracks()) {
    Serial.print(track.getName());
    Serial.print(", duration: ");
    Serial.print(track.getDuration());
    Serial.println("ms");
  }
}

void loop() {
}
```

  Feel free to share this source code, but include explicit mention to the author.
  Licensed under creative commons - see http://creativecommons.org/licenses/by-sa/4.0/
