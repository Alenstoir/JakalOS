#pragma once

#include "IMG.cpp"
#include "IOfuncs.cpp"

class Textarea : public IOfuncs{
	private:
		int x, y, dimX, dimY, scale;
		char* text;
		bool transparent;
		char* alphabet; //TODO оформить покрасивше
		bool hidden;
		static const int TOLEFT = 0, TORIGHT = 1, TOTOP = 2, TOBOTOM = 3, MID = 5;
	public:
		Textarea(){
			//drawRect(10, 10, 0xFFFF00, 20, 0);
			hidden = true;
		}
		Textarea(char* alphabet, char* text, int x, int y, int dimX, int dimY, int scale, bool transparent){
			this->text = text;
			this->alphabet = alphabet;
			this->x = x;
			this->y = y;
			this->dimY = dimY;
			this->dimX = dimX;
			this->scale = scale;
			this->transparent = transparent;
			//drawRect(500,500,0xFFFF00, 20);
			hidden = true;
		}

		void initialize(char* alphabet, char* text, int x, int y, int dimX, int dimY, int scale, bool transparent){
			this->text = text;
			this->alphabet = alphabet;
			this->x = x;
			this->y = y;
			this->dimY = dimY;
			this->dimX = dimX;
			this->scale = scale;
			this->transparent = transparent;
			hidden = true;
		}

		void invalidate(IMG link, const int param){
			switch(param){
				case TOLEFT: this->x = link.getX()-4;break;
				case TORIGHT: this->x = link.getX() + link.getW() + 7;break;
				case MID: this->y = link.getY() + link.getH()/2 -9*scale;break;
				case TOBOTOM: this->y = link.getY() + link.getH()+9;break;
			}
			this->scale = link.getScale();
		}
/**---------------------------------------------------------------------------------------*/
		void show(){
			this->hidden = false;
		}
		void hide(){
			this->hidden = true;
		}
		bool isHidden(){
			return !hidden;
		}
/**---------------------------------------------------------------------------------------*/
		void setText(char* text){
			this->text = text;			
		}
		void setText(int text){
			this->text = (char*)text;			
		}
		void setScale(int scale){
			this->scale = scale;
		};
		void setXY(int x, int y){
			this->x = x;
			this->y = y;
		}
		int getX(){
			return this->x;
		}
		int getY(){
			return this->y;
		}
		void setSize(int dimX, int dimY){
			this->dimY = dimY;
			this->dimX = dimX;
		}
/**---------------------------------------------------------------------------------------*/

		void rawPrint(bool f){
			char* tempTxt = this->text;
			char buff = (char)tempTxt[0];
			asm("mov ax, [ebp-0x9]");
			asm("mov [0x1a00020], ax");
			int z=1, row = 0;
			int offset = 0;
			while(*tempTxt){
				for(int p = 0; p < 2; p++){

					buff = (char)tempTxt[0];
					asm("mov ax, [ebp-0x5]");

					if(p == 1){
						asm("shr ax, 4");
						asm("mov [ebp-0x5], al");
					} else {
						char buff = (char)tempTxt[0];
						asm("mov ax, [ebp-0x5]");
						asm("shl ax, 4");
						asm("mov ah, 0");
						asm("shr ax, 4");
						asm("mov [ebp-0x5], al");
					}

					
					char *ptr = this->alphabet + 64*(buff);
					ptr+=2; //когда 2 без косяков идёт. Хотя по идее 1 дожно быть
						for(int i = 0; i < 9; i++){
						for (int j = 0; j < 7; j++)
						{
							
							if (*ptr != 00)
								{
									if (f)
									{
										drawRectC(x+scale*(j+7*z), y+(scale*(i+(row*9))), 0xFFFFFF, scale, 0);
									} else {
										drawRectC(x+scale*(j+7*z), y+(scale*(i+(row*9))), 0xFFFFFF, scale, 1);
									}
									//setPoint(lfb, x+j+7*z, y+i,0xFFFFFF);
								} 
								else{
									if (!transparent)
									{
										if (f)
										{
											drawRectC(x+scale*(j+7*z), y+(scale*(i+(row*9))), 0xFFFFFF, scale, 0);
										} else {
											drawRectC(x+scale*(j+7*z), y+(scale*(i+(row*9))), 0x000000, scale, 1);
										}
									}
									//setPoint(lfb, x+j+7*z, y+i,0x000000);
								}
							ptr+=1;
						}
					}
					z++; //Если делать контроль текстбокса, добавить id строки
					if (z >= this->dimX)
					{
						z = 0;
						row++;
						if (row >= this-> dimY)
						{
							//TODO придумать что с этим делать
						}
					}
					tempTxt++;
				}
			}
		}

		void print(bool f) //Вывод текст блока TODO решить что с текстбоксами
		{
			char* tempTxt = this->text;
			int z=1, row = 0;
			int offset = 0;
			while(*tempTxt){
				if (*tempTxt == ' ')
				{
					z++;
					tempTxt++;
					continue;
				} else if (*tempTxt > 47 && *tempTxt < 58) //Цифры
				{
					offset = 48;
				} else if (*tempTxt > 96 && *tempTxt < 120) //Прописные
				{
					offset = 87;
				} else if (*tempTxt > 64 && *tempTxt < 91) //Заглавные
				{
					offset = 55;
				}
				char *ptr = this->alphabet + 64*(*tempTxt-offset);
				ptr+=2; //когда 2 без косяков идёт. Хотя по идее 1 дожно быть
					for(int i = 0; i < 9; i++){
					for (int j = 0; j < 7; j++)
					{
						
						if (*ptr != 00)
						 	{
						 		if (f)
						 		{
						 			drawRectC(x+scale*(j+7*z), y+(scale*(i+(row*9))), 0xFFFFFF, scale, 0);
						 		} else {
						 			drawRectC(x+scale*(j+7*z), y+(scale*(i+(row*9))), 0xFFFFFF, scale, 1);
						 		}
						 		//setPoint(lfb, x+j+7*z, y+i,0xFFFFFF);
							} 
							else{
								if (!transparent)
								{
									if (f)
						 			{
						 				drawRectC(x+scale*(j+7*z), y+(scale*(i+(row*9))), 0xFFFFFF, scale, 0);
						 			} else {
						 				drawRectC(x+scale*(j+7*z), y+(scale*(i+(row*9))), 0x000000, scale, 1);
						 			}
								}
								//setPoint(lfb, x+j+7*z, y+i,0x000000);
							}
						ptr+=1;
					}
				}
				z++; //Если делать контроль текстбокса, добавить id строки
				if (z >= this->dimX)
				{
					z = 0;
					row++;
					if (row >= this-> dimY)
					{
						//TODO придумать что с этим делать
					}
				}
				tempTxt++;
			}
		}
};