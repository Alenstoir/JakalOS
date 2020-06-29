#pragma once


#define CMD_READ 0x20
#define BSY_FLAG 0x80

typedef int size_t;
typedef unsigned long uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef signed long int32_t;
typedef signed short int16_t;
typedef signed char int8_t;

#define NULL 0

enum SCREEN_RES{
	SCREEN_X = 1024,
	SCREEN_Y = 768
};

enum IOport{
	BASE = 			0x1f0,
	SEC_SELECT = 	0x1F2,
	LBA07 = 		0x1F3,
	LBA815 = 		0x1F4,
	LBA1623 = 		0x1F5,
	DEVICE_SELECT = 0x1F6,
	CMD = 			0x1F7,
	BLOCK = 		0x3F6,

};

char scancodes[][2] = {
		{ '0' , '0' },
		{ '1', '!' }, /* escape (ESC) */
		{ '2', '1' },
		{ '3', '2' },
		{ '4', '3' },
		{ '5', '4' },
		{ '6', '5' },
		{ '7', '6' },
		{ '8', '7' },
		{ '9', '8' },
		{ '0', '9' },
		{ '0', '0' },
		{ '-', '-' },
		{ '+', '+' },
		{ '\b', '0'  }, /* FIXME: VGA backspace support */
		{ '\t', '0'  }, /* FIXME: VGA tab support */
		{ 'q', 'Q' },
		{ 'w', 'W' },
		{ 'e', 'E' },
		{ 'r', 'R' },
		{ 't', 'T' },
		{ 'y', 'Y' },
		{ 'u', 'U' },
		{ 'i', 'I' },
		{ 'o', 'O' },
		{ 'p', 'P' },
		{ '[', '{' },
		{ ']', '}' },
		{ '\n', 0  }, /* Enter */
		{ 0 , 0  }, /* Ctrl; good old days position */
		{ 'a', 'A' },
		{ 's', 'S' },
		{ 'd', 'D' },
		{ 'f', 'F' },
		{ 'g', 'G' },
		{ 'h', 'H' },
		{ 'j', 'J' },
		{ 'k', 'K' },
		{ 'l', 'L' },
		{ ';', ':' }, /* Semicolon; colon */
		{ '\'', '"' }, /* Quote; doubelquote */
		{ '`', '~' }, /* Backquote; tilde */
		{ 0, 0 }, /* Left shift */
		{ '\\', '|' }, /* Backslash; pipe */
		{ 'z', 'Z' },
		{ 'x', 'X' }, 
		{ 'c', 'C' },
		{ 'v', 'V' },
		{ 'b', 'B' },
		{ 'n', 'N' },
		{ 'm', 'M' },
		{ ',', '<' },
		{ '.', '>' },
		{ '/', '?' },
		{ 0 , 0  }, /* Right shift */
		{ '*', '*' },
		{ 0 , 0  }, /* Left Alt */
		{ ' ', ' ' }, /* Space */
		{ 0 , 0  }, /* Caps Lock */
		{ 0 , 0  }, /* F1 */
		{ 0 , 0  }, /* F2 */
		{ 0 , 0  }, /* F3 */
		{ 0 , 0  }, /* F4 */
		{ 0 , 0  }, /* F5 */
		{ 0 , 0  }, /* F6 */
		{ 0 , 0  }, /* F7 */
		{ 0 , 0  }, /* F8 */
		{ 0 , 0  }, /* F9 */
		{ 0 , 0  }, /* F10 */
		{ 0 , 0  }, /* Num Lock */
		{ 0 , 0  }, /* Scroll Lock */
		{ '7', '7' },
		{ '8', '8' },
		{ '9', '9' },
		{ '-', '-' },
		{ '4', '4' },
		{ '5', '5' },
		{ '6', '6' },
		{ '+', '+' },
		{ '1', '1' },
		{ '2', '2' },
		{ '3', '3' },
		{ '0', '0' },
		{ '.', '.' }
	};

// typedef struct regs
// {
// 	uint32 gs, fs, es, ds;
// 	uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
// 	uint32 int_no, err_code;
// 	uint32 eip, cs, eflags, useresp, ss;
// } regs_t;

