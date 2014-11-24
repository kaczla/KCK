#ifndef MAP_HPP_
#define MAP_HPP_
#include <vector>
#include <iostream>
#include <SDL\SDL.h>
#include "img.hpp"
#include "anim.hpp"

class Map{
public:
	Map();
	Map(int height, int width);
	~Map();
	void SetValue(int height, int width);
	void SetVarMap( std::vector <Img> img, std::vector <Anim> anim);
	int ReturnValueMap(int x, int y);
	int ReturnValueMapObj(int x, int y);
	int ReturnPlayer();
	std::string ReturnError();
	void SaveToFile();
	bool ReturnSuccess();
	int ReturnWidth();
	int ReturnHeight();
	int ReturnPlayerX();
	int ReturnPlayerY();
private:
	class Podloze{
	public:
		Podloze(){
			this->LocalName = "NULL";
			this->ImageID = 0;
		}
		unsigned int ReturnImageID(){
			return this->ImageID;
		}
		std::string ReturnLocalName(){
			return this->LocalName;
		}
		void SetLocalName( std::string value ){
			this->LocalName = value;
		}
		void SetImageID( unsigned int value ){
			this->ImageID = value;
		}
	private:
		std::string LocalName;
		unsigned int ImageID;
	};
	inline void SetVector();
	int PlayerX, PlayerY;
	std::vector < std::vector <int> > Map2D;
	std::vector < std::vector <int> > Map2D_obj;
	int Width, Height;
	std::vector <Podloze> Player;
	std::vector <Podloze> Pelne;
	std::vector <Podloze> TrawaPiach;
	std::vector <Podloze> WodaPiach;
	std::vector <Podloze> WodaTrawa;
	std::string Error_Map;
	bool Success, SuccessVarMap;
};



#endif
