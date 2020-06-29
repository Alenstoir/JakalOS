#pragma once

#include "Textarea.cpp"
#include "IMG.cpp"
#include "IOfuncs.cpp"
#include "../settings.h"
#include "../struct/ArrayList.cpp"
// Отрисовка фсего


#define	CENTER_X (SCREEN_X-dimX*scale)/2
#define	CENTER_Y (SCREEN_Y-dimY*scale)/2	
 

class Drawer : public IOfuncs 
{
	private:
		//char * lfb; //TODO юзать тут или нет?
		ArrayList<Textarea> * text_screen_1;
		ArrayList<IMG> * img_screen_1;

		//int layers[]; 
		char* text; //TODO на будущее заделать текстбоксы
	public:
		Drawer()
		{
			//this->lfb = lfb;
			//int layers[] = {0,0,0,0,0,0,0,0};
			Textarea *filler;
			IMG *filer;
			this->img_screen_1->set(filer);
			this->text_screen_1->set(filler);
		};

		Textarea printText(char* alphabet, char* text, int x, int y, int dimX, int dimY, int scale, bool transparent){
			Textarea* txt;
			txt->initialize(alphabet, text, x, y, dimX, dimY, scale, transparent);
			txt->print();
			this->text_screen_1->add(txt);
			return* txt;
		};

		IMG printIMG(int x, int y, int dimX, int dimY, char* img, int scale){
			IMG * image;
			image->initialize(x,y,dimX,dimY,img,scale);
			image->print();
			this->img_screen_1->add(image);
			return * image;
		}


		

		fill(int color){
			for (int i = 0; i < SCREEN_X*SCREEN_Y; ++i)
			{
				setPointAsm(i, 0, color);
			}
			//drawRect(500,500,0xFFFF00, 20);
		}		
};