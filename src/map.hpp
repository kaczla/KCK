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
	void Operation( std::string text );
	void TurnOnAnimation( bool value );
	void Update();
	std::string ReturnAnswer();
	bool ReturnBusy();
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
	char PlayerDirection;
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
	unsigned int LastOperation,NextOperation;
	std::string TextOperation, Answer;
	bool ToDeleteAnswer, Busy;
	bool MovePlayerTo( int x, int y );
	inline void OperationGo();
	inline void OperationTurn();
};

//TEXT MESSAGE
const std::string text_dont_know = "Nie wiem co mam zrobić!";
const std::string text_turn_up = "Obróciłem się w kierunku północnym";
const std::string text_turn_down = "Obróciłem się w kierunku południowym";
const std::string text_turn_left = "Obróciłem się w kierunku zachodnim";
const std::string text_turn_right = "Obróciłem się w kierunku wschodnim";
const std::string text_on_place = "Jestem na miejscu";
const std::string text_go_up = "Poruszam się w kierunku północnym";
const std::string text_go_down = "Poruszam się w kierunku południowym";
const std::string text_go_left = "Poruszam się w kierunku zachodnim";
const std::string text_go_right = "Poruszam się w kierunku wschodnim";
const std::string text_cant_move = "Nie jestem w stanie dość do wyznaczonego miejsca!";
const std::string text_builds = "Buduje";

//TIME NEXT MOVE
const unsigned int time_move = 750;
const unsigned int time_turn = 500;

#endif
