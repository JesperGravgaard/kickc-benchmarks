
#include <atari-xl.h>
#include "atari-system.h"
#include "counter.h"
#include "gr.h"

void runQR1d() {
	memset(lms, 0, 0x1ff0);
	prepareCounter("QR 1D Array 200 frames");
	counterOn(1);
	benchmarkQR1d();
	counterOn(0);
	waitFrames(10);
	counterOverwrite();
	counterPrint();
}

char align(0x100) qr[] = kickasm {{
   .byte %11111111,%11111111,%11111111,%11111111,%11100000
   .byte %10000000,%10001010,%01111111,%00100000,%00100000
   .byte %10111110,%10001101,%00000111,%11101111,%10100000
   .byte %10100010,%10100100,%01001110,%01101000,%10100000
   .byte %10100010,%10010100,%01101101,%01101000,%10100000
   .byte %10100010,%11111100,%11101101,%00101000,%10100000
   .byte %10111110,%10110010,%01000010,%01101111,%10100000
   .byte %10000000,%10101010,%10101010,%10100000,%00100000
   .byte %11111111,%11011001,%10001111,%00111111,%11100000
   .byte %10011000,%11110100,%11010101,%00110100,%00100000
   .byte %10011001,%01001011,%00100111,%11011001,%10100000
   .byte %10100010,%10110011,%10011100,%11111010,%01100000
   .byte %10101111,%01100101,%01001111,%01011111,%00100000
   .byte %11101000,%00101000,%00010010,%10111100,%11100000
   .byte %10100011,%10011111,%10001011,%00000001,%10100000
   .byte %10110000,%10101100,%00001110,%01110010,%01100000
   .byte %10011001,%00101011,%10011110,%10100001,%00100000
   .byte %10110110,%00110010,%01000001,%11011011,%11100000
   .byte %10110111,%01011000,%11101010,%10111101,%10100000
   .byte %10111100,%00100111,%01011100,%11111010,%01100000
   .byte %10010001,%01111011,%01011000,%11110001,%11100000
   .byte %11100010,%10010101,%11010001,%00001011,%11100000
   .byte %10010101,%01001011,%00101101,%11011011,%10100000
   .byte %11101100,%10011110,%00111000,%11111011,%01100000
   .byte %11110111,%10100101,%10011101,%01111101,%11100000
   .byte %10001010,%11000111,%11010001,%10000010,%01100000
   .byte %11111111,%10011000,%10011111,%10111011,%01100000
   .byte %10000000,%11011101,%01011000,%10101000,%11100000
   .byte %10111110,%10111101,%01001000,%00111001,%00100000
   .byte %10100010,%10001000,%11001001,%10000011,%10100000
   .byte %10100010,%11010101,%00100111,%10111111,%00100000
   .byte %10100010,%11101010,%00011100,%10111101,%01100000
   .byte %10111110,%10010000,%01011100,%11000001,%11100000
   .byte %10000000,%10100010,%10110001,%11101111,%10100000
   .byte %11111111,%11111111,%11111111,%11111111,%11100000
}};

void benchmarkQR1d() {
	mode4();
	clearAltScore();
	*(RTCLOK + 2) = 0;
	char y = 0;
	while (*(RTCLOK + 2) < 200) {
		char *p = lms;
		for (char x: 0..174) {
			*(p + y++) = *(qr + x);
			if (y == 5) {
				// mode 4 has 10 bytes per line?
				p += 10;
				y = 0;
			}
		}
		(*scoreA4)++;
		if (*scoreA4 == 10) { *scoreA4 = 0; (*scoreA3)++; }
		if (*scoreA3 == 10) { *scoreA3 = 0; (*scoreA2)++; }
		if (*scoreA2 == 10) { *scoreA2 = 0; (*scoreA1)++; }
	}
}
