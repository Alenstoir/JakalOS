#pragma once

#include "IOfuncs.cpp"
#include "../settings.h"

class Cursor : public IOfuncs
{
private:
	int x, y, step, color, size, iter;
	bool way;
public:
	Cursor(){
		iter = 10;
		way = true;
		x = SCREEN_X/2;
		y = SCREEN_Y/2;
		step = 5;
		color = 0x454545;
		size = 1;
	};
	int getX(){
		return x;
	};
	int getY(){
		return y;
	};
	void print(){
		int under = getPoint(x, y);
		under >>=8;
		under&=0x00ffffff;
			if (under >= 0x777777)
			{
				color = 0x000000;
			} else {
				color = 0xFFFFFF;
			}
		//if (way)
		//{
			drawRectC(x, y, color, 1, 0);
			drawLine(x, y-6, x, y-3, color, size, 0);
			drawLine(x-5, y, x-3, y, color, size, 0);
			drawLine(x, y+3, x, y+6, color, size, 0);
			drawLine(x+3, y, x+6, y, color, size, 0);
		//} else {
		//	drawLine(x-5, y-5, x+5, y+5, color, size, 0);
		//	drawLine(x-5, y+5, x+5, y-5, color, size, 0);
		//}
		
	};

	void up(){
		if (y > 75)
		{
			y -= step;
		}
			print();
	}
	void down(){
		if (y < SCREEN_Y - 75)
		{
			y += step;
		}
			print();
	}
	void left(){
		if (x > 2)
		{
			x -= step;
		}
			print();
	}
	void right(){
		if (x < SCREEN_X - 2)
		{
			x += step;
		}
			print();
	}

	void scrUp(){
		step++;
	}

	void scrDwn(){
		step--;
	}
};