#define TI84PCSE

#ifndef TI_H
#define TI_H

void main();

int entry() {
    main();
    return 0;
}

int max(int a, int b);
int min(int a, int b);

void tiPoint(int x, int y, unsigned int c);
void tiRect(int x, int y, int w, int h, unsigned int c);
void tiRefreshKeys();

#ifdef TI84PCSE
#include "ti84pcse.h"
#endif

void memcpy(char* dst, char* src, int size);

#define bool char
#define true 1
#define false 0

unsigned int rngSeed = 1;
unsigned int rand();

#endif
