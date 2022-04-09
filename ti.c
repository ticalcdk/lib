
#include "ti.h"

void memcpy(char* dst, char* src, int size) {
    for(int i = 0; i < size; i++)
        dst[i] = src[i];
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void tiPoint(int x, int y, unsigned int c) {
    tiRect(x, y, 1, 1, c);
}

void tiRect(int x, int y, int w, int h, unsigned int c) {
    
    *((int*)(0x8100)) = c;
    *((int*)(0x8102)) = max(y, 0);
    *((int*)(0x8104)) = min(y + h - 1, TI_SCREEN_H);
    *((int*)(0x8106)) = max(x, 0);
    *((int*)(0x8108)) = min(x + w - 1, TI_SCREEN_W);
    __asm
        ld hl, (0x8100) ; set color
        ld (0xA5F4), hl
        ld hl, (0x8102) ; set top
        ld b, l
        ld hl, (0x8104) ; set bottom
        ld c, l
        ld hl, (0x8106) ; set left
        ld de, (0x8108) ; set right
        rst 0x28
        .dw 0x4D4A
    __endasm;
}

void tiRefreshKeys() {
    memcpy(tiPrevKeypad, tiKeypad, 8);

    __asm
        ld a, #0xFF ; group 0
        out (1), a
        ex (sp),hl
        ex (sp),hl
        ld a, #0xFE
        out (1), a
        in a, (1)
        ld (_tiKeypad), a

        ld a, #0xFF ; group 1
        out (1), a
        ex (sp),hl
        ex (sp),hl
        ld a, #0xFD
        out (1), a
        in a, (1)
        ld (_tiKeypad+1), a

        ld a, #0xFF ; group 2
        out (1), a
        ex (sp),hl
        ex (sp),hl
        ld a, #0xFB
        out (1), a
        in a, (1)
        ld (_tiKeypad+2), a

        ld a, #0xFF ; group 3
        out (1), a
        ex (sp),hl
        ex (sp),hl
        ld a, #0xF7
        out (1), a
        in a, (1)
        ld (_tiKeypad+3), a

        ld a, #0xFF ; group 4
        out (1), a
        ex (sp),hl
        ex (sp),hl
        ld a, #0xEF
        out (1), a
        in a, (1)
        ld (_tiKeypad+4), a

        ld a, #0xFF ; group 5
        out (1), a
        ex (sp),hl
        ex (sp),hl
        ld a, #0xDF
        out (1), a
        in a, (1)
        ld (_tiKeypad+5), a

        ld a, #0xFF ; group 6
        out (1), a
        ex (sp),hl
        ex (sp),hl
        ld a, #0xBF
        out (1), a
        in a, (1)
        ld (_tiKeypad+6), a

    __endasm;

    tiKeypad[0] = ~tiKeypad[0];
    tiKeypad[1] = ~tiKeypad[1];
    tiKeypad[2] = ~tiKeypad[2];
    tiKeypad[3] = ~tiKeypad[3];
    tiKeypad[4] = ~tiKeypad[4];
    tiKeypad[5] = ~tiKeypad[5];
    tiKeypad[6] = ~tiKeypad[6];
    tiKeypad[7] = ~tiKeypad[7];
}

unsigned int rand() {
    rngSeed ^= rngSeed << (unsigned int)7;
    rngSeed ^= rngSeed >> (unsigned int)9;
    rngSeed ^= rngSeed << (unsigned int)8;
    return rngSeed;
}

void tiWriteLCDRegAddr(unsigned char addr) { // these use some nasty sdcc abi stuff
    __asm
        out (0x10), a
        out (0x10), a
    __endasm;
}

void tiWriteLCDVal(unsigned int val) {
    __asm
        ld a, h
        out (0x11), a
        ld a, l
        out (0x11), a
    __endasm;
}

void tiLCDMoveCursor(unsigned int x, unsigned int y) {
    tiWriteLCDRegAddr(0x20);
    tiWriteLCDVal(x);
    tiWriteLCDRegAddr(0x21);
    tiWriteLCDVal(y);
}

void tiLCDSetWinLeft(unsigned int left) {
    tiWriteLCDRegAddr(0x52);
    tiWriteLCDVal(left);
}

void tiLCDSetWinRight(unsigned int right) {
    tiWriteLCDRegAddr(0x53);
    tiWriteLCDVal(right);
}

void tiLCDSetWinTop(unsigned int top) {
    tiWriteLCDRegAddr(0x50);
    tiWriteLCDVal(top);
}

void tiLCDSetWinBottom(unsigned int bottom) {
    tiWriteLCDRegAddr(0x51);
    tiWriteLCDVal(bottom);
}