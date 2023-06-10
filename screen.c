#define ROWS      25 // Кол-во строк на экране
#define COLUMNS   80 // Кол-во столбцов на экране
#define SYM_BYTES 2  // Кол-во байтов на один символ
#define SIZE ROWS*COLUMNS*SYM_BYTES // Общее кол-во байт

#define DEF_COLOR 0x07 // Стандартный цвет
#define CUR_COLOR 0x70 // Цвет курсора

#define BLANK_SYM 0x00 // Символ-заполнитель

char* vidmem = (char*)0x000B8000; // Указатель на начало видео памяти
unsigned long curloc = 0;         // Позиция курсора

// Полная очистка экрана
void clear(void)
{
    while(curloc<=SIZE) {
        vidmem[curloc]   = BLANK_SYM;
        vidmem[curloc+1] = DEF_COLOR;
        curloc += SYM_BYTES;
    }
    curloc = 0;
    vidmem[curloc+1] = CUR_COLOR;
    return;
}

// Печать строки на экране с позиции курсора
void printStr(char* str)
{
    unsigned long j = 0;
    while(str[j] != '\0') {
        if (curloc == SIZE) return;
        vidmem[curloc]   = str[j];
        vidmem[curloc+1] = DEF_COLOR;
        curloc += SYM_BYTES;
        j += 1;
    }
    vidmem[curloc+1] = CUR_COLOR;
    return;
}

// Печать символа на экране с позиции курсора
void printSym(char sym)
{
    if (curloc == SIZE) return;
    vidmem[curloc]   = sym;
    vidmem[curloc+1] = DEF_COLOR;
    curloc += SYM_BYTES;
    vidmem[curloc+1] = CUR_COLOR;
    return;
}

// Перенос курсора на новую строку
void newLine(void)
{
    if (curloc >= (ROWS-1)*COLUMNS*SYM_BYTES) return;
    vidmem[curloc+1] = DEF_COLOR;
    curloc += (COLUMNS*SYM_BYTES - curloc % (COLUMNS*SYM_BYTES));
    vidmem[curloc+1] = CUR_COLOR;
    return;
}

// Удаление символа слева и перемещение курсора на его место
void backDelete(void)
{
    if (curloc == 0) return;
    if ((curloc / SYM_BYTES) % COLUMNS == 0) {
        unsigned char i = COLUMNS*SYM_BYTES;
        while (i>0) {
            if (vidmem[curloc-(COLUMNS*SYM_BYTES-i)] != BLANK_SYM) break;
            i -= SYM_BYTES;
        }
        vidmem[curloc+1] = DEF_COLOR;
        curloc -= (COLUMNS-1)*SYM_BYTES-i;
        vidmem[curloc+1] = CUR_COLOR;
        return;
    }
    vidmem[curloc-2] = BLANK_SYM;
    vidmem[curloc-1] = CUR_COLOR;
    vidmem[curloc+1] = DEF_COLOR;
    curloc -= SYM_BYTES;
    return;
}

// Удаление символа справа
void delete(void)
{
    vidmem[curloc+2] = BLANK_SYM;
    return;
}

// Перемещение курсора влево
void moveLeft(void)
{
    if (curloc == 0) return;
    vidmem[curloc-1] = CUR_COLOR;
    vidmem[curloc+1] = DEF_COLOR;
    curloc -= SYM_BYTES;
    return;
}

// Перемещение курсора вверх
void moveUp(void)
{
    if (curloc / (COLUMNS*SYM_BYTES) == 0) return;
    vidmem[curloc-159] = CUR_COLOR;
    vidmem[curloc+1]   = DEF_COLOR;
    curloc -= COLUMNS*SYM_BYTES;
    return;
}

// Перемещение курсора вправо
void moveRight(void)
{
    if (curloc == SIZE) return;
    vidmem[curloc+3] = CUR_COLOR;
    vidmem[curloc+1] = DEF_COLOR;
    curloc += SYM_BYTES;
    return;
}

// Перемещение курсора вниз
void moveDown(void)
{
    if (curloc / (COLUMNS*SYM_BYTES) == 24) return;
    vidmem[curloc+161] = CUR_COLOR;
    vidmem[curloc+1]   = DEF_COLOR;
    curloc += COLUMNS*SYM_BYTES;
    return;
}