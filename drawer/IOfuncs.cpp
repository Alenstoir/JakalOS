#pragma once

#include "../settings.h"

class IOfuncs
{
public:
	IOfuncs(){};


/**----------Работа с адресами---------------------*/
void setPointAsm(int x, int y, int color) //вывод пикселя на асме
{	
	 asm("mov esi, dword ptr [0xa00000] /*0xfd000000*/"); //lfb
	 asm("mov eax, [ebp+0x8]"); //x
	 asm("mov ebx, [ebp+0xc]"); //y
	 asm("mov edx, [ebp+0x10] /*[ebp-0x24]*/"); //color
	 asm("imul ebx, 1024"); //shift
	 asm("add eax, ebx"); //shift
	 asm("imul eax, 3"); //shift
	 asm("xor ebx, ebx"); //toNull
	 asm("mov ebx, eax"); //cur shift
	 asm("mov [esi+ebx], edx"); //print
}

void setPointBuffer(int x, int y, int color) // буферизация
{	
	 asm("mov esi, 0xa10000"); //lfb
	 asm("mov eax, [ebp+0x8]"); //x
	 asm("mov ebx, [ebp+0xc]"); //y
	 asm("mov edx, [ebp+0x10]"); //color
	 asm("imul ebx, 1024"); //shift
	 asm("add eax, ebx"); //shift
	 asm("imul eax, 3"); //shift
	 asm("xor ebx, ebx"); //toNull
	 asm("mov ebx, eax"); //cur shift
	 asm("mov [esi+ebx], edx"); //print
}

void setPoint(int x, int y, int color, int addr) //вывод пикселя в адрес
{	
	 asm("mov esi, [ebp+0x14]"); //addr
	 asm("mov eax, [ebp+0x8]"); //x
	 asm("mov ebx, [ebp+0xc]"); //y
	 asm("mov edx, [ebp+0x10]"); //color
	 asm("imul ebx, 1024"); //shift
	 asm("add eax, ebx"); //shift
	 asm("imul eax, 3"); //shift
	 asm("xor ebx, ebx"); //toNull
	 asm("mov ebx, eax"); //cur shift
	 asm("mov [esi+ebx], edx"); //print
}

int getPoint(int x, int y) //получить пиксель
{	
	asm("mov esi, 0x1000000"); //lfb
	 asm("mov eax, [ebp+0x8]"); //x
	 asm("mov ebx, [ebp+0xc]"); //y
	 asm("imul ebx, 1024"); //shift
	 asm("add eax, ebx"); //shift
	 asm("imul eax, 3"); //shift
	 asm("xor ebx, ebx"); //toNull
	 asm("mov ebx, eax"); //cur shift
	 asm("mov eax, [esi+ebx]"); //print
}

/**-------------Утилити-------------*/


void swapBuffer(){
	MMX();
}

void BG(){
	MMX_addr(0xa10000, 0x1000000);
}

/**------------MMX----------------*/
void MMX(){ // Перенос из буфера на экран
    int i;
    asm("mov edi, dword ptr [0xa00000]");
    asm("mov esi, 0xa10000");
	for(i = 0; i < 147456*2 ;i++){
	    asm("movq mm0, [esi]");
	    asm("movq [edi], mm0");
	    asm("add esi, 8");
	    asm("add edi, 8");
    }
}

void MMX_addr(int a, int b){ // Перенос из адреса в адрес. Размер экрана
    int i;
    asm("mov edi, [ebp+0x8]");
    asm("mov esi, [ebp+0xc]");
	for(i = 0; i < 147456*2 ;i++){
	    asm("movq mm0, [esi]");
	    asm("movq [edi], mm0");
	    asm("add esi, 8");
	    asm("add edi, 8");
    }
}

void MMX_fill(int color, int addr){ //Заливка по размеру экрана
    int i;
    asm("mov edi, [ebp+0xc]");
    asm("mov esi, [ebp+0x8]");
    asm("mov dword ptr [0xa00020], esi");
    asm("mov dword ptr [0xa00023], esi");
    asm("mov esi, 0xa00020");
	for(i = 0; i < 147456*3 ;i++){
	    asm("movq mm0, [esi]");
	    asm("movq [edi], mm0");
	    asm("add edi, 6");
    }
}

void MMX_fill(int color, int addr, int start, int end){ // Заливка блока по адресу
    int i;
    start*=3;
    asm("mov edi, [ebp+0xc]");
    asm("mov esi, [ebp+0x8]");
	asm("add edi, [ebp+0x10]");
    asm("mov dword ptr [0xa00020], esi");
    asm("mov dword ptr [0xa00023], esi");
    asm("mov esi, 0xa00020");
	for(i = start/3; i < (start/3+end)/2 ;i++){
	    asm("movq mm0, [esi]");
	    asm("movq [edi], mm0");
	    asm("add edi, 6");
    }
}

/**--------------Примитивы----------------*/

void drawRect(int x, int y, char * img, int scale, bool bg){ // квадрат в буфер/бекграунд из адреса
	for (int i = 0; i < scale; ++i)
	{
		for (int j = 0; j < scale; ++j)
		{
			if (bg)
			{
				setPoint(j+x, i+y, *(long*)img,0x1000000);
			} else {
				setPointBuffer( j+x, i+y, *(long*)img);
			}
		}
	}
}

void drawRectDirect(int x, int y, char * img, int scale){ // квадрат напрямую на экран из адреса
	for (int i = 0; i < scale; ++i)
	{
		for (int j = 0; j < scale; ++j)
		{
			setPointAsm( j+x, i+y, *(long*)img);
		}
	}
}

void drawRectC(int x, int y, int color, int scale, bool bg){ // квадрат в буфер/бекграунд цветом
	for (int i = 0; i < scale; ++i)
	{
		for (int j = 0; j < scale; ++j)
		{
			if (bg)
			{
				setPoint(j+x, i+y, color,0x1000000);
			} else {
				setPointBuffer(j+x, i+y, color);
			}
		}
	}
}

void drawLine(int aX, int aY, int bX, int bY, int color, int scale, bool bg){ // Алгоритм Брезенхэма для отрисовки растровой линии через 2 точки
	int x0, x1, y0, y1, dX, dY, err, ystep; 
	bool step;

	step = (bY-aY) > (bX-aX);
	if (step)
	{
		x0 = aY;
		y0 = aX;

		x1 = bY;
		y1 = bX;
	} else {
		x0 = aX;
		y0 = aY;

		x1 = bX;
		y1 = bY;
	};
	if (x0 > x1)
	{
		int buf = x0;
		x0 = x1;
		x1 = buf;

		buf = y0;
		y0 = y1;
		y1 = buf;
	};

	dX = x1-x0;
	dY = y1-y0;
	if (dY < 0)
	{
		dY *= -1;
	}
	err = dX/2;
	if (y0 < y1)
	{
		ystep = 1*scale;
	} else {
		ystep = -1*scale;
	}

	for (int i = x0; i <= x1; i+=scale)
	{
		if (step)
		{
			drawRectC(y0, i, color, scale, bg);
		} else {
			drawRectC(i, y0, color, scale, bg);
		}
		err -= dY; 
		if (err < 0)
		{
			y0 += ystep;
			err += dX; 
		}
	}
};



/**--------------Диск----------------*/

int LBA_read(uint32_t LBA, uint8_t sectorCount,uint16_t* dest){ //Чтение секторов
    uint32_t still_going=-1;
    asm("and    eax, 0x0FFFFFFF \n"
        "mov    eax,[ebp+8]     \n"
        "mov    cl,[ebp+12]     \n"
        "mov    edi,[ebp+16]    \n");

    asm("mov    ebx,eax         \n");

    asm("mov    edx,0x1F6       \n"
        "shr    eax,24          \n"
        "or     al,0b11100000   \n"
        "out    dx,al           \n");

    asm("mov    edx,0x1F2       \n"
        "mov    al,cl           \n"
        "out    dx,al           \n");

    asm("mov    edx,0x1F3       \n"
        "mov    eax,ebx         \n"
        "out    dx,al           \n");

    asm("mov    edx,0x1F4       \n"
        "mov    eax,ebx         \n"
        "shr    eax,8           \n"
        "out    dx,al           \n");

    asm("mov    edx,0x1F5       \n"
        "mov    eax,ebx         \n"
        "shr    eax,16          \n"
        "out    dx,al           \n");

    asm("mov    edx,0x01F7      \n"
        "mov    al,0x20         \n"
        "out    dx,al           \n");
   do{
        asm("in   al,dx         \n"
            "mov  [ebp-4],al    \n");
    } while((still_going&0x80));

    asm("mov    eax,256         \n"
        "xor    bx,bx           \n"
        "mov    bl,cl           \n"
        "mul    bx              \n"
        "mov    ecx,eax         \n"
        "mov    edx,0x01F0      \n"
        "rep    insw            \n");

    return 1;
	}
};