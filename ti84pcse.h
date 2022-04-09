
#define TI_SCREEN_W ((unsigned int)320)
#define TI_SCREEN_H ((unsigned int)240)

#define TI_COLOR_BLACK 0x0000
#define TI_COLOR_WHITE 0xFFFF

#define TI_GLOBAL_START 0x987C

unsigned char tiKeypad[8];
unsigned char tiPrevKeypad[8];

unsigned char tiBuffer[16];

#define TI_JUST_PRESSED(group) (tiKeypad[group] & (tiKeypad[group] ^ tiPrevKeypad[group]))
#define TI_JUST_RELEASED(group) ((~tiKeypad[group]) & (tiKeypad[group] ^ tiPrevKeypad[group]))

void tiWriteLCDRegAddr(unsigned char addr);
void tiWriteLCDVal(unsigned int val);

void tiLCDMoveCursor(unsigned int x, unsigned int y);

void tiLCDSetWinLeft(unsigned int left);
void tiLCDSetWinRight(unsigned int right);
void tiLCDSetWinTop(unsigned int top);
void tiLCDSetWinBottom(unsigned int bottom);