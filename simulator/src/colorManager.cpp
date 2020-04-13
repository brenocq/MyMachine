#include "colorManager.h"

vector<string> ColorManager::color;

ColorManager::ColorManager()
{
	init();
}

ColorManager::~ColorManager()
{

}

void ColorManager::init(void)
{
	if(color.size()>0)
		return;

	putColor("black", 0, 0, 0);
	putColor("lgray", 400, 400, 400);
	putColor("dgray", 200, 200, 200);
	putColor("white", 1000, 1000, 1000);
	putColor("red", 1000, 0, 0);
	putColor("green", 600, 1000, 300);
	putColor("blue", 0, 0, 1000);
	putColor("cyan", 0, 1000, 1000);
	putColor("pink", 1000, 500, 800);
	putColor("orange", 1000, 500, 0);
	putColor("magenta", 1000, 0, 1000);
	putColor("yellow", 1000, 1000, 0);
}

void ColorManager::putColor(string name, int r, int g, int b)
{
	int nextId = color.size();
	init_color(nextId, r, g, b);
	color.push_back(name);
	updatePairs();
}

void ColorManager::updatePairs()
{
	int currColor = color.size()-1;
	for(int i=0;i<int(color.size());i++)
	{
		// TODO use extended
		//init_extended_pair(currColor*MAX_PAIRS+i, currColor, i);
		//init_extended_pair(i*MAX_PAIRS+currColor, i, currColor);
		init_pair(currColor*MAX_PAIRS+i, currColor, i);
		init_pair(i*MAX_PAIRS+currColor, i, currColor);
	}
}

int ColorManager::getColor(string name)
{
	for(int i=0;i<int(color.size());i++)
	{
		if(color[i]==name)
			return i;
	}
	return 0;
}

int ColorManager::getPair(string name)
{
	size_t split = name.find("-");
	if(split == string::npos || split > 100)
		return 0;

	string textColor = name.substr(0,split);
	string bgColor = name.substr(split+1,name.size()-1);
	int textColorId = getColor(textColor);
	int bgColorId = getColor(bgColor);

	//move(4,0);
	//printw("%s %s %d %d", textColor.c_str(), bgColor.c_str(), textColorId, textColorId*256+bgColorId);
	//refresh();

	return textColorId*MAX_PAIRS+bgColorId;
}

