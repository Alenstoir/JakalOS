#include "./Textarea.cpp"
#include "./IMG.cpp"
#include "./IOfuncs.cpp"
#include "./Cursor.cpp"

#include "../kb/KBInput.cpp"

#include "../settings.h"


class Filler : public IOfuncs {
	private:
			int offset;
			Cursor cur;
			IMG ico1, jakal, icoCenter, sample;
			char *alpha;
			int pix, wh, hw, WH, HW,tooltip;
			Textarea tempo, label, lbl1, debug;
			bool self, p1;
			uint16_t * sml_img;

	public:
		Filler(){
			offset = 5;
			self = 1;
			p1 = 0;
			sml_img = (uint16_t*) 0x1d00000;
			char * img =(char*) 0x1300B00; // иконка
			alpha =(char*) 0x1300000; // алфавит
			Cursor cur;
			ico1 = IMG(15,90,64, 64, img, 1);
			icoCenter = IMG(SCREEN_X/2-32,SCREEN_Y/2-32, 64, 64, (char*)sml_img, 1);
			sample = IMG(0,0, 0, 0, img, 1);
			lbl1 = Textarea(alpha, (char*)"PICTURES", 0, 0, 10, 2, 3, 1);
			lbl1.invalidate(ico1,3);
			lbl1.invalidate(ico1,0);
		}

	/** работа с буффером и бекграундом **/
	void bg(){
		BG();
		
	};
	void buffd(){
		swapBuffer();
	};
	/** работа с буффером и бекграундом **/
	
	/** отрисовка **/
	void fill(int color, int addr){
	
		MMX_fill(color, addr);
	};

	void fill(int color){
		MMX_fill(color, 0xa10000);
	};

	void fill(int color, int start, int end){
	
		MMX_fill(color, 0x1000000, start, end);
	};
	
	void line(int aX, int aY, int bX, int bY, int color, int scale){
		drawLine(aX, aY, bX, bY, color, scale, 0);

	}
	/** отрисовка **/


	/** перемещение мыши **/
	void mouse(char c){
		
		switch(c){
			case 'W': cur.up(); break;
			case 'A': cur.left(); break;
			case 'S': cur.down(); break;
			case 'D': cur.right(); break;
			//default:  break;
		}
		cur.print();
		if (c == '+')
		{
			cur.scrUp();
		} else if( c == '-'){
			cur.scrDwn();
		}
	};
	/** перемещение мыши **/

	/** работа с диском **/
	void disk(int lba){
		uint16_t* addr = (uint16_t*)0x1a00000;
			int a = LBA_read(1, 1, addr);
	};
	void disk(int lba, int amount){
		uint16_t* addr = (uint16_t*)0x1a00000;
		for (int i = 0; i < amount; i ++){
			int a = LBA_read(lba+i, 1, addr);
			addr+=0x100;
		}
	};
	void disk(int lba, int amount, uint16_t* addr){
		for (int i = 0; i < amount; i ++){
			int a = LBA_read(lba+i, 1, addr);
			addr+=0x100;
		}
	};

	int pow(int c, int s){ //Утилитарные функции
		int d = c;
		for(int i = 0; i < s-1; i++){
			d = d * c;
		}
		if(s == 0)
		return 1;
		return d;
	}

	int valFromHex(char* hex){ //Утилитарные функции
		int x = 0x0;
		int cnt = 0;
		for(int c = 0; c < 5; c++){
			if(hex[c] != 0x00){ 
				cnt++;
			}
		}
		for(int c = 0; c < cnt; c++){
			int d = (hex[c]-0x30) * pow(0xA,cnt - (c+1));	
			x += d;
		}
		return x;
	}

	int searchImgPrefs(int n, char* lfName, IMG * sample){ // Поиск картинки по названию
		if(n == 0){
			n = 118;
		}
		bool eq = true;
		uint16_t * addr = (uint16_t*) 0x1a00000;
		uint16_t * sizeX = (uint16_t*) 0x1a00010;
		uint16_t * sizeY = (uint16_t*) 0x1a00020;
		disk(n, 1, addr);
		
		int tr = 1;
		
		int x = valFromHex((char*)sizeX);
		int y = valFromHex((char*)sizeY);

			

		for(int c = 0; c < 5; c++){
			if (dbg[c] != lfName[c]){
				eq = false;
			}
		}
		n++;

		if(eq){
			sample->setDim(x, y);
			return n;
		} else {
			n += (x*y*0x3)/0x200;
			
			if(n > 200) n++;
			return searchImgPrefs(n, lfName, sample);
		}
	}
	/** работа с диском **/

	/** рабочий стол **/
	void drawBounds(IMG jakal, Textarea label){
		this->label = label;
		this->jakal = jakal;
		fill(0x00AAFF, 0x1000000);
		int h = 75;
		int color = 0xDDDDDD;
		for (int i = 0; i < h; ++i)
		{
			for (int j = 0; j < SCREEN_X; ++j)
			{
				drawRectC(j, i, color, 1, 1);
			}
			if (i < h/2)
			{
				color-= 0x020202;
			} else {
				color+= 0x020202;
			}
		}
		color = 0xDDDDDD;
		for (int i = 0; i < h; ++i)
		{
			for (int j = 0; j < SCREEN_X; ++j)
			{
				drawRectC(j, SCREEN_Y-i, color, 1 ,1);
			}
			if (i < h/2)
			{
				color-= 0x020202;
			} else {
				color+= 0x020202;
			}
		}
		jakal.setScale(1);
		jakal.setXY(5,5);
		label.invalidate(jakal, 1);
		label.invalidate(jakal, 5);
		label.setScale(2);
		jakal.print(0);
		label.print(0);
		ico1.print(0);
		lbl1.print(0);
		BG();
		buffd();
	}
	/** рабочий стол **/

	/** задержка **/
	void wait(int millis){
	int feedle = 0;
	for (int i = 0; i < 65536; ++i)
		{
			for (int j = 0; j < millis; ++j)
			{
					feedle++;
					feedle--;
			};
		};
	};
	/** задержка **/

	/** заставка **/
	void initialize(Textarea osname,IMG jakal, int rand){
		int i = 50;
			jakal.switchGlitch();  
		while(i > 0){
			fill(0x00AAFF);
			jakal.print();
			jakal.switchGlitch();
			osname.print(1);
			buffd();
			i--;
		}
		fill(0x00AAFF, 0x1000000);
		fill(0x00AAFF);
		cur.print();	
	};
	/** заставка **/

	/** главный листенер **/
	void listen(char c){
		if (self)
		{
			if(check(ico1, c)){
				char name[] = "PICTURES";
				window(name);
				prog1();
				self = !self;
				p1 = !p1;
			}
		} else if(c == '!'){
			drawBounds(jakal, label);	
			self = !self;
			p1 = !p1;		
		} else if(check(SCREEN_X-25, 80, 15, c)){
			drawBounds(jakal, label);	
			self = !self;
			p1 = !p1;				
		}

		if (p1)
		{
			bool checked = false;
			int n = 0, nx = 0, ny = 0;
			prog1();
			if(check(10, SCREEN_Y/2-25, 50,  c)){
				if(tooltip == 0){
					tooltip = 4;
				} else {
					tooltip--;
				}
				if(tooltip == 0){
					n = searchImgPrefs(0, (char*)"pln01", &sample);		
				} else if(tooltip == 1){
					n = searchImgPrefs(0, (char*)"jak00", &sample);
				} else if(tooltip == 2){
					n = searchImgPrefs(0, (char*)"pln00", &sample);
				} else if(tooltip == 3){
					n = searchImgPrefs(0, (char*)"puls0", &sample);
				} else if(tooltip == 4){
					n = searchImgPrefs(0, (char*)"fox00", &sample);
					nx = 450;
					ny = 300;
				}  		 		
				checked = true;					
			}
			if(check(SCREEN_X-60, SCREEN_Y/2-25, 50,  c)){
				if(tooltip == 4){
					tooltip = 0;
				} else {
					tooltip++;
				}
				if(tooltip == 0){
					n = searchImgPrefs(0, (char*)"pln01", &sample);
				} else if(tooltip == 1){
					n = searchImgPrefs(0, (char*)"jak00", &sample);
				} else if(tooltip == 2){
					n = searchImgPrefs(0, (char*)"pln00", &sample);
				} else if(tooltip == 3){
					n = searchImgPrefs(0, (char*)"puls0", &sample);
				} else if(tooltip == 4){
					n = searchImgPrefs(0, (char*)"fox00", &sample);
					
				}  	
					checked = true;
			}
			if(checked){
					WH = sample.getH();
					HW = sample.getW();
					disk(n, sample.getSectors(), sml_img);

					icoCenter.setSize(nx, ny);

					icoCenter.setDim(HW, WH);

					wh = icoCenter.getH()/2;
					hw = icoCenter.getW()/2;
					icoCenter.setXY(1024/2- hw,768/2 - wh);
					p1_fill();
					icoCenter.print(0);
			}
		}
	}
	/** главный листенер **/

	/** проверка курсора по координатам / картинке **/
	bool check(int x, int y, int size, char c){
		int color = 0x00FF00;
		if(cur.getX() >= x && cur.getX() <= x+size){
			if (cur.getY() >= y && cur.getY() <= y+size)
			{
				drawLine(x-1, y-1, x+size+1, y-1, color, 1, 0); // верх
				drawLine(x-1, y+size+1, x+size+1, y+size+1, color, 1, 0); // низ
				drawLine(x-1, y-1, x-1, y+size+1, color, 1, 0); // лево
				drawLine(x+size+1, y-1, x+size+1, y+size+1, color, 1, 0); // право
				if (c == ' ')
				{
					tempo.print(1);
					return 1;
				}
			}
		}
		return 0;
	};
	
	bool check(IMG ico, char c){
		int color = 0x00FF00;
		if(cur.getX() >= ico.getX() && cur.getX() <= ico.getX()+ico.getW()){
			if (cur.getY() >= ico.getY() && cur.getY() <= ico.getY()+ico.getH())
			{
				drawLine(ico.getX()-offset, ico.getY()-offset, ico.getX()+ico.getW()+offset, ico.getY()-offset, color, 1, 0); // верх
				drawLine(ico.getX()-offset, ico.getY()+ico.getH()+4*offset, ico.getX()+ico.getW()+offset, ico.getY()+ico.getH()+4*offset, color, 1, 0); // низ
				drawLine(ico.getX()-offset, ico.getY()-offset, ico.getX()-offset, ico.getY()+ico.getH()+4*offset, color, 1, 0); // лево
				drawLine(ico.getX()+ico.getW()+offset, ico.getY()-offset, ico.getX()+ico.getW()+offset, ico.getY()+ico.getH()+4*offset, color, 1, 0); // право
				if (c == ' ')
				{
					tempo.print(1);
					return 1;
				}
			}
		}
		return 0;
	}
	/** проверка курсора по координатам / картинке **/

	/** отрисовка окна **/
	void window(char * lbl){
		int h = 25;
		int color = 0xDDDDDD;

		fill(0xAAAAFF, SCREEN_X*75, SCREEN_X*SCREEN_Y-SCREEN_X*75);

		drawLine(0, 75, 0, SCREEN_Y-75, color, 5, 1); // лево	
		drawLine(SCREEN_X-5, 75, SCREEN_X-5, SCREEN_Y-75, color, 5, 1); // право
		drawLine(0, 75, SCREEN_X, 75, color, 5, 0); // верх
		drawLine(0, SCREEN_Y-75, SCREEN_X, SCREEN_Y-75, color, 5, 1); // низ


		color = 0xDDDDDD;
		for (int i = 75+h; i >= 75; --i)
		{
			for (int j = 0; j < SCREEN_X; j++)
			{
				drawRectC(j, i, color, 1, 1);
			}
				color-= 0x020202;
		}

		Textarea name = Textarea(alpha, lbl, 0, 80, 25, 1, 2, 1);
		name.print(0);
		int m = 26, s = 10;
		color = 0x500A0A;
		for (int i = s; i < m; ++i)
		{
			for (int j = 80; j < 96; ++j)
			{
				if (j >= 88)
				{
					color -= 0x0A0000;
				} else {
					color += 0x0A0000;
				}
				drawRectC(SCREEN_X-i, j, color, 1, 1);
			}
			if (i >= 18)
			{
				color -= 0x0A0000;
			} else {
				color += 0x0A0000;				
			}
		}
		drawLine(SCREEN_X-25, 80, SCREEN_X-10, 95, 0x000000, 1, 1);
		drawLine(SCREEN_X-25, 95, SCREEN_X-10, 80, 0x000000, 1, 1);
	}

	
	/** отрисовка окна **/

	/** просмотр изображений **/
	void prog1(){
		if (!p1)
		{
			int n = searchImgPrefs(0, (char*)"jak00", &sample);
            disk(n, sample.getSectors(), sml_img);
			p1_fill();
			tooltip = 1;
			icoCenter.print(0);
		}
	}

	void p1_fill(){ 
            window((char*)"PICTURES");
			drawRectC(SCREEN_X-60, SCREEN_Y/2-12, 0x4411AA, 25, 1);
			drawRectC(SCREEN_X-35, SCREEN_Y/2-12, 0x4411AA, 25, 1);
			drawLine(SCREEN_X-50, SCREEN_Y/2, SCREEN_X-10, SCREEN_Y/2, 0x00FF00, 1, 1);
			drawLine(SCREEN_X-25, SCREEN_Y/2-10, SCREEN_X-10, SCREEN_Y/2, 0x00FF00, 1, 1);
			drawLine(SCREEN_X-25, SCREEN_Y/2+10, SCREEN_X-10, SCREEN_Y/2, 0x00FF00, 1, 1);

			drawRectC(10, SCREEN_Y/2-12, 0x4411AA, 25, 1);
			drawRectC(35, SCREEN_Y/2-12, 0x4411AA, 25, 1);
			drawLine(10, SCREEN_Y/2, 50, SCREEN_Y/2, 0x00FF00, 1, 1);
			drawLine(10, SCREEN_Y/2, 25, SCREEN_Y/2-10, 0x00FF00, 1, 1);
			drawLine(10, SCREEN_Y/2, 25, SCREEN_Y/2+10, 0x00FF00, 1, 1);
	}
	/** просмотр изображений **/
};