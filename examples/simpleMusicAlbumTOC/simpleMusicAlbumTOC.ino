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

