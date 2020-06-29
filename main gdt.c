//#include "./drawer/Drawer.cpp"
#include "./drawer/Textarea.cpp"
#include "./drawer/IMG.cpp"
#include "./kb/KBInput.cpp"
#include "./settings.h"
#include "./drawer/IOfuncs.cpp"
//#include "./struct/ArrayList.cpp"
#include "./drawer/Cursor.cpp"
#include "./drawer/Filler.cpp"










int start(){
	//char qq = scancodes[0][0];//bdc0
	int curX = SCREEN_X/2, curY = SCREEN_Y/2; 
	char txt[] = "JAKAL 05"; // название
	asm("mov dword ptr [0xa00000], esi"); // фреймбуфер
	asm("mov dword ptr [0xa00010], 0xa10000"); // буфер

	

	char * img =(char*) 0x1300B00; // иконка
	char * imgB =(char*) 0x1303C00; // нормальная картинка
	char *alpha =(char*) 0x1300000; // алфавит
	char key[] = "WASD to move  SPC to select  ESC to exit  Keylogger  "; // для считывания клавы

	int rand = 100; // сид для рандома
	Filler p;
	 // отрисовщик
	KBInput k;

	p.disk(64, 5, (uint16_t*)alpha);
	p.disk(69, 24, (uint16_t*)img);
	p.disk(94, 24, (uint16_t*)imgB);
	//p.disk(86, 24, (uint16_t*)0x1a00000);


	p.fill(0x00AAFF); // 0x00AAFF
	p.buffd();
	//*lfb = buffer[0];

	IMG jakal(350,200,64, 64, imgB, 5); // лого
	Textarea truearea(alpha, txt, 400, 550, 10, 2, 3, 1); // название
	Textarea tempo(alpha, key, SCREEN_X-1000, SCREEN_Y-(75/2+9*3), 41, 2, 3, 1); // название

	p.initialize(truearea,jakal, rand); // заставка на rand*100 миллисекунд (железовлияемо)
	p.drawBounds(jakal, truearea); // отрисовка верхней/нижней панелек

	//	test.switchGlitch(); 
	//p.line(50, 300, 500, 50, 0xFFFFFF, 1);
	//p.line(0, 0, SCREEN_X, SCREEN_Y, 0xFFFFFF, 1);
	//p.line(0, SCREEN_Y, SCREEN_X, 0, 0xFFFFFF, 1);
	//p.buffd();

		//p.disk(32, 5);
		asm("mov dword ptr [0x1d00020], 0x1a000"); // буфер

	while(1){		
		p.bg();
		//p.line(0, 75, SCREEN_X, SCREEN_Y-75, 0xAA00AA, 2);
		//p.line(0, SCREEN_Y-75, SCREEN_X, 75, 0xAA00AA, 2);
		key[52] = k.getc();
		tempo.setText(key);
		tempo.print(1);
		//test.switchGlitch(); 
		//p.wait(10);
		p.listen(k.getc());
		p.mouse(k.getc());
		//if (k.getc() == '!')
		//{
		//	p.bg();
		//}
		p.buffd();
		if (k.getc() == '!')
		{
			goto exit;
		}
	};

/**------------------------------------------------*/
	exit:
	p.fill(0x000000);
	Textarea final(alpha, (char*)"You may now turn off the PC", SCREEN_X/2-26*7, SCREEN_Y/2-9, 30, 1, 2, 1);
	final.print(1);
	p.buffd();
	p.wait(100);	
	while(1){
	}
/**------------------------------------------------*/

return 0;
};


