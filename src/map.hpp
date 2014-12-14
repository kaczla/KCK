#ifndef MAP_HPP_
#define MAP_HPP_
#include <vector>
#include "include_SDL.hpp"
#include "img.hpp"
#include "anim.hpp"
#include "log_game.hpp"
#include <cstdlib>
#include <cmath>

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
	std::string Operation( std::string text );
	void TurnOnAnimation( bool value );
private:
	class Podloze{
	public:
		Podloze(){
			this->LocalName = "NULL";
			this->ImageID = -1;
		}
		int ReturnImageID(){
			return this->ImageID;
		}
		std::string ReturnLocalName(){
			return this->LocalName;
		}
		void SetLocalName( std::string value ){
			this->LocalName = value;
		}
		void SetImageID( unsigned int value ){
				this->ImageID = (int)value;
			}
		void SetImageID( int value ){
			this->ImageID = value;
		}
	private:
		std::string LocalName;
		int ImageID;
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
	std::vector <Podloze> Drzewo;
	std::vector <Podloze> Ognisko;
	std::vector <Podloze> Kamien;
	std::string Error_Map;
	bool Success, SuccessVarMap;
	bool Animation;
};

#endif
