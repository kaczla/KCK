#ifndef MAP_HPP_
#define MAP_HPP_
#include <vector>
#include <iostream>
#include <SDL\SDL.h>
//using std::vector;

class Map{
public:
	Map();
	Map(int height, int width);
	~Map();
	void SetValue(int height, int width);
	int ReturnValueMap(int x, int y);
	int ReturnValueMapObj(int x, int y);
	void SaveToFile();
	bool ReturnSuccess();
private:
	inline void SetVector();
	int PlayerX, PlayerY;
	std::vector < std::vector <int> > Map2D;
	std::vector < std::vector <int> > Map2D_obj;
	int Width, Height;
	bool Success;
};



#endif
