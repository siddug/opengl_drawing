#ifndef COLOR_T
#define COLOR_T

class color_t{
	private:
	int Red; //default 0
	int Blue;//default 0
	int Green;//default 0
	public:
	int getRed(){return Red;}
	int getBlue(){return Blue;}
	int getGreen(){return Green;}
	void setRed(int r){Red=r;}
	void setBlue(int b){Blue=b;}
	void setGreen(int g){Green=g;}
	void setColor(int r,int g,int b){Red=r;Blue=b;Green=g;}
	color_t(int r=0,int g=0,int b=0):Red(r),Blue(b),Green(g){};
};

#endif
