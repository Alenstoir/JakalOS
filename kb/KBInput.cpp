#include "../settings.h"

#pragma once
// Ввод с клавиатуры

class KBInput
{
private:
	int key, stats;
public:
	KBInput(){
		key = 0;
		stats = 0;
	};

	int getchar(){
		asm("mov eax, 0");
		asm("in al, 0x60");
	}

	int getcharS(){
		asm("mov eax, 0");
		asm("in al, 0x64");
	}

	int resetKB(int val){
		asm("mov eax, 0");
		asm("mov al, [ebp-8]");
		asm("out 0x64, al");
	}

	char getc(){
		while(1){
			key = getchar();
			stats = getcharS();
			if ((stats&0b10000000) != 0b10000000)
			{
				return scancodes[key][1];
			}
		};
		return 0;
	}
};





