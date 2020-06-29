#pragma once

#include "IOfuncs.cpp"

class IMG : public IOfuncs
{
private:
		int x, y, dimX, dimY, scale, iter, W, H;
		bool hidden;
		char * img;
		int size, toolTipInt;
		bool glitch;
public:
	IMG(){
		hidden = true;
			glitch = false;
			iter = 0;
	};

	IMG(int x, int y, int W, int H, char* img, int scale){
			this->x = x;
			this->y = y;
			this->W = W;
			this->H = H;
			this->scale = scale;
			this->img = img;
			iter = 0;
			hidden = true;
			glitch = false;
			dimX = 0;
			dimY = 0;
	};

	void initialize(int x, int y, int W, int H, char* img, int scale){
		this->x = x;
		this->y = y;
		this->W = W;
		this->H = H;
		this->scale = scale;
		this->img = img;
		hidden = true;
			iter = 0;
			glitch = false;
		dimX = 0;
		dimY = 0;
	};
/**---------------------------------------------------------------------------------------*/

	void show(){
		this->hidden = false;
	};
	void hide(){
		this->hidden = true;
	};
	bool isHidden(){
		return !hidden;
	};
	void switchGlitch(){
		glitch = !glitch;
		iter++;
		if (iter == 50)
		{
			iter = 4;
		};
	};
/**---------------------------------------------------------------------------------------*/
	void setXY(int xn, int yn){
		x = xn;
		y = yn;
	};
	void setScale(int scale){
		this->scale = scale;
	};

	int getScale(){
		return this->scale;
	};

	int getY(){
		return this->y;
	};

	int getX(){
		return this->x;
	};

	void setX(int x){
		this->x = x;
	};

	void setY(int y){
		this->y = y;
	};

	int getW(){
		return W-dimX;
	};


	int getH(){
		return H-dimY;
	};

	int setDim(int W, int H){
		this->W = W;
		this->H = H;
	}

	void setSize(int dimX, int dimY){
		this->dimY = dimY;
		this->dimX = dimX;
	};

	void setIMG(char* img){
		this->img = img;			
	};

	char* getIMG(){
		return img;
	}

	int getToolTipInt(){
		return toolTipInt;
	}

	void setToolTipInt(int n){
		this->toolTipInt = n;
	}

	int getSectors(){
		return W*H*3/512;
	}
/**---------------------------------------------------------------------------------------*/

	void print(){ //печать картинки
		char* temp = img;
		int shift = 0;
		int ind = 0;
		int kX = 1, kY = 1;
		if(dimX != 0 && dimY != 0){
			kX = W/dimX;
			kY = H/dimY;
		}
		for (int i = H/kY; i > 0; i--)
		{
			if(i%kY != 0) temp+= (3*W) * kY;
			int tmpY = y, tmpX = x;
			if (glitch && (((i+3) > iter && (i-3) < iter) || ((i%2+5) > iter && (i%2-5) < iter))){
				shift = i-iter;
				if (shift > 0)
				{
					tmpX = x - shift*4;
				} else if (shift < 0)
				{
					tmpX = x + shift*4;
				} else {
					tmpX = x + 4*4;
				}
			}
			for (int j = 0; j < W/kX; j++)
			{
				if (glitch && ((ind%iter) == 0) ||((ind%(iter+1)) == 0)||((ind%(iter+2)) == 0))
				{
					char* temptemp = temp;
					if ((ind%iter) == 0)
					{	
						temptemp+=7;
					} else {
						temptemp-=7;
					}
					drawRect(scale*j+tmpX, scale*i+y, temptemp, scale, 0);
				} else {
					drawRect(scale*j+tmpX, scale*i+y, temp, scale, 0);
				}		
				temp+=(3*kX); //24 бита, сую 32 бита. Могут быть артефакты на 1 скейле
				ind++;
			
			}
		}
	};

	void print(bool f){ //печать картинки
		char* temp = img;
		int kX = 1, kY = 1;
		if(dimX != 0 && dimY != 0){
			kX = W/dimX;
			kY = H/dimY;
		}
		//char* temp = (char*)0x10800;
		for (int i = H/kY; i > 0; i--)
		{
			if(i%kY != 0)temp+= (3*W) * kY;
			for (int j = 0; j < W/kX; j++)
			{
				if (f)
				{
					drawRect(scale*j+x, scale*i+y, temp, scale, 0);	
				}	else {
					drawRect(scale*j+x, scale*i+y, temp, scale, 1);	
				}
				temp+=(3*kX); //24 бита, сую 32 бита. Могут быть артефакты на 1 скейле			
			}
			//temp+=((3*W)*kY-1);
		}
	};

	void printDirect(){ //печать картинки
		char* temp = img;
		int kX = 1, kY = 1;
		if(dimX != 0 && dimY != 0){
			kX = W/dimX;
			kY = H/dimY;
		}
		//char* temp = (char*)0x10800;
		for (int i = H/kY; i > 0; i--)
		{
			if(i%kY != 0)temp+= (3*W) * kY;
			for (int j = 0; j < W/kX; j++)
			{
				drawRectDirect(scale*j+x, scale*i+y, temp, scale);	
				temp+=(3*kX); //24 бита, сую 32 бита. Могут быть артефакты на 1 скейле			
			}
			//temp+=((3*W)*);
		}
	};
};