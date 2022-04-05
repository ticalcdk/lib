
#ifndef TI_H
#define TI_H

unsigned char tiKeypad[8];
unsigned char tiPrevKeypad[8];

#define TI_JUST_PRESSED(group) (tiKeypad[group] & (tiKeypad[group] ^ tiPrevKeypad[group]))
#define TI_JUST_RELEASED(group) ((~tiKeypad[group]) & (tiKeypad[group] ^ tiPrevKeypad[group]))

void tiRect(int x, int y, int w, int h, unsigned int c);
void tiRefreshKeys();

#ifdef TI84PCSE

#define TI_SCREEN_W ((unsigned int)320)
#define TI_SCREEN_H ((unsigned int)240)

#define TI_COLOR_BLACK 0x0000
#define TI_COLOR_WHITE 0xFFFF

#define TI_GLOBAL_START 0x987C

#endif

void memcpy(char* dst, char* src, int size);

#define bool char
#define true 1
#define false 0

unsigned int rngSeed = 1;
unsigned int rand();

#endif
