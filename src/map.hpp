#ifndef MAP_HPP_
#define MAP_HPP_
#include <vector>
#include "include_SDL.hpp"
#include "img.hpp"
#include "anim.hpp"
#include "log_game.hpp"
#include <cstdlib>
#include <cmath>
#include <iostream>

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
	void StopOperation();

	unsigned int ReturnFood();
	unsigned int ReturnWood();
	unsigned int ReturnStone();
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
	class Object{
	public:
		Object(){
			this->X = 0;
			this->Y = 0;
			this->TMP = 0;
		}
		Object( int x, int y ){
			this->X = x;
			this->Y = y;
			this->TMP = 0;
		}
		Object( unsigned int x, unsigned int y ){
			this->X = (int)x;
			this->Y = (int)y;
			this->TMP = 0;
		}
		Object( int x, int y, int tmp ){
			this->X = x;
			this->Y = y;
			this->TMP = abs( x ) + abs( y ) - abs( tmp );
		}
		Object( const Object & object ){
			this->X = object.X;
			this->Y = object.Y;
			this->TMP = object.TMP;
		}
		Object operator=( const Object &object ){
			this->X = object.X;
			this->Y = object.Y;
			this->TMP = object.TMP;
			return *this;
		}
		int ReturnX(){
			return this->X;
		}
		int ReturnY(){
			return this->Y;
		}
		int ReturnTMP(){
			return this->TMP;
		}
		void SetX( int x ){
			this->X = x;
		}
		void SetY( int y ){
			this->Y = y;
		}
		void SetTMP( int tmp ){
			this->TMP = tmp;
		}
		void SetTMP( int x, int y ){
			this->TMP = abs( this->X ) + abs( this->Y );
			this->TMP -= abs( x ) + abs( y );
			this->TMP = abs( this->TMP );
		}
	private:
		int X, Y;
		int TMP;
	};
	inline void SetVector();
	//Koordynaty Gracza
	int PlayerX, PlayerY;
	char PlayerDirection;
	//Mapa
	std::vector < std::vector <int> > Map2D;
	//Mapa Objektów
	std::vector < std::vector <int> > Map2D_obj;
	//Szerokość i wysokość mapy
	int Width, Height;
	//Identyfikatory grafik ( wody, trawy, pisku, drzew ... )
	std::vector <Podloze> Player;
	std::vector <Podloze> Pelne;
	std::vector <Podloze> TrawaPiach;
	std::vector <Podloze> WodaPiach;
	std::vector <Podloze> WodaTrawa;
	std::vector <Podloze> Drzewo;
	std::vector <Podloze> Ognisko;
	std::vector <Podloze> Kamien;
	std::vector <Podloze> Przedmioty;
	//Błędy
	std::string Error_Map;
	bool Success, SuccessVarMap;
	bool Animation;
	//Czas akcji
	unsigned int LastOperation,NextOperation;
	//Tekst
	std::string TextOperation, Answer;
	//Sprawdzanie akcji
	bool ToDeleteAnswer, Busy;
	//Poruszanie się
	bool MovePlayerTo( int x, int y );
	inline void OperationGo();
	//Obrót
	inline void OperationTurn();
	//Budowanie
	bool Builds;
	inline void OperationBuildFire();
	inline void OperationDelete();
	inline void CutTree();
	unsigned int MaxRange;
	std::vector <std::string> Path;
	inline void FindPath( std::vector < std::vector <char> > &In );
	inline void StartPath();

	//Zasoby gracza
	unsigned int Food, Wood, Stone;

	//CHEATS
	bool Cheats;
};

//Tekst gotowych odpowiedzi
const std::string text_dont_know = "Nie wiem co mam zrobić!";
const std::string text_turn_up = "Obróciłem się w kierunku północnym";
const std::string text_turn_down = "Obróciłem się w kierunku południowym";
const std::string text_turn_left = "Obróciłem się w kierunku zachodnim";
const std::string text_turn_right = "Obróciłem się w kierunku wschodnim";
const std::string text_turn_ok = "No przeciesz stoję w tym kierunku!";
const std::string text_on_place = "Jestem na miejscu";
const std::string text_go_up = "Poruszam się w kierunku północnym";
const std::string text_go_down = "Poruszam się w kierunku południowym";
const std::string text_go_left = "Poruszam się w kierunku zachodnim";
const std::string text_go_right = "Poruszam się w kierunku wschodnim";
const std::string text_cant_move = "Nie jestem w stanie dość do wyznaczonego miejsca!";
const std::string text_builds = "Buduje";
const std::string text_build_fire = "Zbudowałem ognisko";
const std::string text_build_no_items = "Nie posiadam wystarczającą ilość przedmoiotów niezbędnych do budowy!";
const std::string text_build_is_item = "Nie mogę zbudować, ponieważ przedmiot w miejscu docelowym istnieje!";
const std::string text_build_wrong_place = "Nie mogę zbudować na takim terenie!";
const std::string text_non = "Jestem gotów do pracy";
const std::string text_delete = "Niszczę obiekt znajdujący się przede mną";
const std::string text_delete_not = "Nie ma nic przede mną do zniszczenia!";
const std::string text_delete_end = "Zniszczyłem obiekt znajdujący się przede mną";
const std::string text_path = "Jestem w drodze do celu";
const std::string text_path_error = "Niemożliwe do wykonania!";

const std::string text_stop = "Przerywam akcje!";
const std::string text_cheats_on = "Nie ładnie oszukiwać! :<";

//Czas wykonywanych akcji
const unsigned int time_move = 750;
const unsigned int time_turn = 500;
const unsigned int time_build_fire = 6000;
const unsigned int time_delete = 5000;

#endif
