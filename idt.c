#define IDT_SIZE 256

#define CS_SELECTOR 0x08 // Code Segment Selector
#define IG_CODE 	0x8E // Interrupt Gate Code

#define PIC1_CP 0x20 // PIC1 Control Port
#define PIC1_DP 0x21 // PIC1 Data Port
#define PIC2_CP 0xA0 // PIC2 Control Port
#define PIC2_DP 0xA1 // PIC2 Data Port

// Gate Descriptor
struct GD {
    unsigned short offsetLow;
	unsigned short selector;
	unsigned char  zero;
	unsigned char  type_attr;
	unsigned short offsetHigh;
} __attribute__((packed));

// Table Register
struct TR {
	unsigned short limit;
	unsigned long  base;
} __attribute__((packed));

struct GD IDT[IDT_SIZE];
struct TR IDTR;

extern void HandlerCallerKB(void); // handlers.asm
extern void loadIDT(struct TR*);   // ports.asm

// Создание и загрузка IDT
void initIDT(void)
{
    unsigned long AddressKB = (unsigned long)HandlerCallerKB;

	// Keyboard Descriptor
    IDT[0x21].offsetLow  = AddressKB & 0x0000FFFF;
	IDT[0x21].selector   = CS_SELECTOR;
	IDT[0x21].zero       = 0x00;
	IDT[0x21].type_attr  = IG_CODE;
	IDT[0x21].offsetHigh = (AddressKB & 0xFFFF0000) >> 16;

    IDTR.limit = sizeof(IDT);
	IDTR.base = (unsigned long)IDT;

    loadIDT(&IDTR);
}

extern void writePort(unsigned short, unsigned char); // ports.asm

// Настройка PIC
void initPIC(void)
{
	// ICW1
    writePort(PIC1_CP, 0x11);
	writePort(PIC2_CP, 0x11);

	// ICW2
	writePort(PIC1_DP, 0x20);
	writePort(PIC2_DP, 0x28);

	// ICW3
	writePort(PIC1_DP, 0x00);
	writePort(PIC2_DP, 0x00);

	// ICW4
	writePort(PIC1_DP, 0x01);
	writePort(PIC2_DP, 0x01);
	
	// OCW1
	writePort(PIC1_DP, 0xFD);
	writePort(PIC2_DP, 0xFF);
}