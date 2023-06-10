#include "MapKB.h"

#define PIC1_CP 0x20  // PIC1 control Port
#define KB_CP   0x64  // Keyboard Control Port
#define KB_DP   0x60  // Keyboard Data Port

#define CODE_BS  0x0E // Скан-код Backspace'а
#define CODE_ENT 0x1C // Скан-код Enter'а
#define CODE_DEL 0x53 // Скан-код Delete'а
#define CODE_LA  0x4B // Скан-код стрелки влево
#define CODE_UA  0x48 // Скан-код стрелки вверх
#define CODE_RA  0x4D // Скан-код стрелки вправо
#define CODE_DA  0x50 // Скан-код стрелки вниз

#define EOI_CODE 0x20 // End Of Interrupt Code

extern void writePort(unsigned short, unsigned char); // ports.asm
extern unsigned char readPort(unsigned short);        // ports.asm

extern void clear(void);      // screen.c
extern void printStr(char*);  // screen.c
extern void printSym(char);   // screen.c
extern void newLine(void);    // screen.c
extern void backDelete(void); // screen.c
extern void delete(void);     // screen.c
extern void moveLeft(void);   // screen.c
extern void moveUp(void);     // screen.c
extern void moveRight(void);  // screen.c
extern void moveDown(void);   // screen.c

// Драйвер клавиатуры
void HandlerKB(void)
{
    unsigned char status;
    char keycode;

    writePort(PIC1_CP, EOI_CODE);
    status = readPort(KB_CP);

    if(status & 0x01) {
        keycode = readPort(KB_DP);
        if (keycode < 0) return;
        if (keycode == CODE_BS) {backDelete();return;}
        if (keycode == CODE_ENT){   newLine();return;}
        if (keycode == CODE_DEL){    delete();return;}
        if (keycode == CODE_LA) {  moveLeft();return;}
        if (keycode == CODE_UA) {    moveUp();return;}
        if (keycode == CODE_RA) { moveRight();return;}
        if (keycode == CODE_DA) {  moveDown();return;}

        printSym(MapKB[keycode]);
    }
    return;
}