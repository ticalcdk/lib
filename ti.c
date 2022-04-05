
#include "ti.h"

void memcpy(char* dst, char* src, int size) {
    for(int i = 0; i < size; i++)
        dst[i] = src[i];
}

void tiRect(int x, int y, int w, int h, unsigned int c) { // TODO: make this use a buffer instead of 0x8100
    *((int*)(0x8100)) = c;
    *((int*)(0x8102)) = y;
    *((int*)(0x8104)) = y + h - 1;
    *((int*)(0x8106)) = x;
    *((int*)(0x8108)) = x + w - 1;
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