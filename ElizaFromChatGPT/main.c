static void orgit() __naked {
  __asm
  org     0x140D
    nop
    nop
    nop
    __endasm;
}

void main2();

void main() {

  main2();
}

#include "../NABULIB/NABU-LIB.h"

void main2() {

  // Set the text mode to foreground color white, bg black
  vdp_initTextMode(0xf, 0x0, 0x1);

  // init the audio because we'll play some funky music!
  initAudio();

  // This is our intro song
  // col 0: note
  // col 1: length of note (ms)
  const uint8_t song[] = {
       26, 150,
       38, 50,
       36, 100,
       22, 50,
  };

  // Play the music from the little intro cause we be so funky
  for (uint8_t i = 0; i < sizeof(song); i += 2) {

    playNoteDelay(0, song[i], song[i + 1]);

    z80_delay_ms(song[i + 1]);
  }

  // Let's ask the user for their name
  vdp_setCursor2(0, 0);

  char input[256];
  int count = 0;

  // greet the user
  vdp_print("Hello! I am Eliza-Nabu, a chatbot.");
  vdp_newLine();
  vdp_print("What is on your mind tonight?");


  while (1) {
    vdp_newLine();
    count = count + 1;
    vdp_print("> ");
    uint8_t read = readLine(input, 16);
       
    if (count == 4) {
        vdp_newLine();
        vdp_print("Sorry, I have another appointment. TTFN");
        z80_delay_ms(3000);
        break;
    }

    // otherwise, generate a response
    vdp_newLine();
    if ((count % 2) == 0)
        {
            // even
            vdp_print("I see, tell me more about ");
        }
        else
        {
            // odd
              vdp_print("Hummm, go on about ");
        }
     vdp_printPart(input, 0, read);
  }

  return ;

}
