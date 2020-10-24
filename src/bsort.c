#include <atari-xl.h>
#include "counter.h"
#include "gr.h"

void runBsort() {
	memset(lms, 0, 0x1ff0);
	prepareCounter("Bubble Sort: 255 elements");
	counterOn(1);
	benchmarkBsort();
	counterOn(0);
	waitFrames(5);
	counterPrint();
}

void benchmarkBsort() {
	char align(0x100) sortTable[255];
	for (char i: 0..254) {
		sortTable[i] = 0xff - i;
	}
	
	for (char i: 253..0) {
		for (char j: 0..253) {
			char n1 = sortTable[j];
			char n2 = sortTable[j+1];
			if (n1 > n2) {
				sortTable[j]   = n2;
				sortTable[j+1] = n1;
			}
		}
	}
}