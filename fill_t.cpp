#include "color_t.cpp"
#include "point_t.cpp"
#include "line_t.cpp"
#include <vector>
#include <cstdlib>
#ifndef FILL_T
#define FILL_T

class fill_t{
	private:
	color_t solid_fill_color;    //defualt green
	color_t checker_fill_color1; //default green
	color_t checker_fill_color2; //default red
	bool checker_fill_mode;      //default false
	public:
	color_t get_sfc(){return solid_fill_color;}
	color_t get_cfc1(){return checker_fill_color1;}
	color_t get_cfc2(){return checker_fill_color2;}
	bool get_cfm(){return checker_fill_mode;}
	void set_sfc(color_t c){solid_fill_color=c;}
	void set_cfc1(color_t c){checker_fill_color1=c;}
	void set_cfc2(color_t c){checker_fill_color2=c;}
	void set_cfm(bool cfm){checker_fill_mode=cfm;}
	
	fill_t(color_t sfc=*(new color_t(0,255,0)),color_t cfc1=*(new color_t(0,255,0)),color_t cfc2=*(new color_t(255,0,0)),bool cfm=false):solid_fill_color(sfc),checker_fill_color1(cfc1),checker_fill_color2(cfc2),checker_fill_mode(cfm){};
	
		void draw(std::vector< std::vector<color_t> >& p_a, int x, int y , int w, int h){
		int done=1;
		color_t target=p_a[x][y];
		std::vector<int> X;
		std::vector<int> Y;
		X.push_back(x);Y.push_back(y);
		if(same(p_a[x+1][y],target)){X.push_back(x+1);Y.push_back(y);}
		if(same(p_a[x-1][y],target)){X.push_back(x-1);Y.push_back(y);}
		if(same(p_a[x][y+1],target)){X.push_back(x);Y.push_back(y+1);}
		if(same(p_a[x][y-1],target)){X.push_back(x);Y.push_back(y-1);}
		while(X.size()!=0){
			p_a[X[X.size()-1]][Y[Y.size()-1]]=solid_fill_color;
			if(checker_fill_mode&&done%2==0){p_a[X[X.size()-1]][Y[Y.size()-1]]=checker_fill_color1;done++;}
			else if(checker_fill_mode&&done%2!=0){p_a[X[X.size()-1]][Y[Y.size()-1]]=checker_fill_color2;done++;}
			int a = X[X.size()-1]; int b=Y[Y.size()-1];
			X.pop_back();Y.pop_back();
			if(a+1<w&&same(p_a[a+1][b],target)){X.push_back(a+1);Y.push_back(b);}
			if(a-1>0&&same(p_a[a-1][b],target)){X.push_back(a-1);Y.push_back(b);}
			if(b+1<h&&same(p_a[a][b+1],target)){X.push_back(a);Y.push_back(b+1);}
			if(b-1>0&&same(p_a[a][b-1],target)){X.push_back(a);Y.push_back(b-1);}
		}
		//return p_a;
	}
	
	bool same(color_t c, color_t c1){
		if(c.getRed()==c1.getRed() && c.getGreen()==c1.getGreen() && c.getBlue()==c1.getBlue()){return true;}
		return false;
	}
	
};

#endif
