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

/**
 * Mapa gry, na której przetwarzane są wszystkie operacje.
 */
class Map{
public:
	Map();
	/**
	 * Generuje i zmienia ustawienia dotyczące mapy
	 * @param height - wysokość mapy
	 * @param width - szerokość mapy
	 */
	Map( int height, int width );

	~Map();
	/**
	 * Ustawia wartości dla mapy i ustawień gry
	 * @param height - wysokość mapy
	 * @param width - szerokość mapy
	 */
	void SetValue( int height, int width );
	/**
	 * Ustawia wartości zmiennych odpowiedzialnych za wyświetlanie, generowanie mapy.
	 * @param img - wektor wszystkich grafik
	 * @param anim - wektor wszystkich animacji
	 */
	void SetVarMap( std::vector <Img> &img, std::vector <Anim> &anim);
	/**
	 * @param x - współrzędne x
	 * @param y - współrzędne y
	 * @return wartość mapy dla podanego x,y
	 */
	int ReturnValueMap( int x, int y );
	/**
	 * @param x - współrzędne x
	 * @param y - współrzędne y
	 * @return wartość objektu mapy dla podanego x,y
	 */
	int ReturnValueMapObj( int x, int y );
	/**
	 * @return kierunek, w którym jest aktualnie obrócony gracz
	 * - u - północ
	 * - d - południe
	 * - l - zachód
	 * - r - wschód
	 */
	int ReturnPlayer();
	/**
	 *
	 * @return teskt błędu
	 */
	std::string ReturnError();
	/**
	 * Zapis do pliku
	 */
	void SaveToFile();
	/**
	 *
	 * @return wartość poprawności wykonania operacji
	 */
	bool ReturnSuccess();
	/**
	 *
	 * @return szerokość aktualnej mapy
	 */
	int ReturnWidth();
	/**
	 *
	 * @return wysokość aktualnej mapy
	 */
	int ReturnHeight();
	/**
	 *
	 * @return współrzędne X położenia gracza
	 */
	int ReturnPlayerX();
	/**
	 *
	 * @return współrzędne Y położenia gracza
	 */
	int ReturnPlayerY();
	/**
	 * Dodaje operacje do wykonania
	 * @param text - tekst komendy do wykonania
	 */
	void Operation( std::string &text );
	/**
	 * Włącza lub wyłącza animacje
	 * @param value - wartość uruchomienia animacji
	 */
	void TurnOnAnimation( bool value );
	/**
	 * Aktualizacja operacji, gracza, mapy
	 */
	void Update();
	/**
	 *
	 * @return tekst odpowiedzi
	 */
	std::string ReturnAnswer();
	/**
	 *
	 * @return wartość zajętości gracza
	 */
	bool ReturnBusy();
	/**
	 * Zatrzymuje aktualnie przetwarzaną operacji
	 */
	void StopOperation();
	/**
	 * Zatrzymuje aktualnie przetwarzane operacje
	 */
	void StopOperationAll();
	/**
	 *
	 * @return wartość posiadanej żywności
	 */
	unsigned int ReturnFood();
	/**
	 *
	 * @return wartość posiadanego drewna
	 */
	unsigned int ReturnWood();
	/**
	 *
	 * @return wartość posiadanego kamienia
	 */
	unsigned int ReturnStone();
	/**
	 *
	 * @return wartość głodu
	 */
	unsigned int ReturnHungry();
	/**
	 * Zmniejsza poziom głodu gracza
	 */
	void MinusHungry();
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
			this->TMP = (double)tmp;
		}
		Object( int x, int y, float tmp ){
			this->X = x;
			this->Y = y;
			this->TMP = (double)tmp;
		}
		Object( int x, int y, double tmp ){
			this->X = x;
			this->Y = y;
			this->TMP = tmp;
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
		double ReturnTMP(){
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
		void SetTMP( double tmp){
			this->TMP = tmp;
		}
		void SetTMP( float tmp){
			this->TMP = (double)tmp;
		}
	private:
		int X, Y;
		double TMP;
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
	std::vector <Podloze> Jedzenie;
	std::vector <Podloze> Przedmioty;
	//Błędy
	std::string Error_Map;
	bool Success, SuccessVarMap;
	bool Animation;
	//Czas akcji
	unsigned int LastOperation,NextOperation;
	//Tekst
	std::string TextOperation, Answer;
	std::vector < std::string > Other;
	bool OtherBool;
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
	inline void StartFire();
	inline void StopFire();
	inline void OperationDelete();
	inline void DeleteObject( int x, int y );
	inline void CutTree();
	inline void DestroyStone();
	inline void DestoryFood();
	inline void FindFire();
	inline void FindTree();
	inline void FindStone();
	inline void FindFood();
	unsigned int MaxRange;
	//PATH
	std::vector <std::string> Path;
	inline void FindObject( std::vector <Podloze> &target );
	inline void FindPath( std::vector < std::vector <char> > &In );
	bool PathBool, PathBoolEnd;

	//Zasoby gracza
	unsigned int Food, Wood, Stone;
	unsigned int Hungry;
	void Eat();

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
const std::string text_build_no_items = "Nie posiadam wystarczającej ilości przedmoiotów niezbędnych do budowy!";
const std::string text_build_is_item = "Nie mogę zbudować, ponieważ przedmiot w miejscu docelowym istnieje!";
const std::string text_build_wrong_place = "Nie mogę zbudować na takim terenie!";
const std::string text_non = "Jestem gotów do pracy";
const std::string text_delete = "Niszczę obiekt znajdujący się przede mną";
const std::string text_delete_not = "Nie ma nic przede mną do zniszczenia!";
const std::string text_delete_end = "Zniszczyłem obiekt znajdujący się przede mną";
const std::string text_path = "Jestem w drodze do celu";
const std::string text_path_error = "Niemożliwe do wykonania!";
const std::string text_path_end = "Cel osiągnięty";
const std::string text_path_working = "Pracuje nad tym";
const std::string text_done = "Zrobione";
const std::string text_stop = "Przerywam akcje!";
const std::string text_cheats_on = "Nie ładnie oszukiwać! :<";
const std::string text_hungry_full = "Nie jestem głody";
const std::string text_hungry_eat = "Od razu lepiej";
const std::string text_hungry_not = "Nie mam co zjeść";

//Czas wykonywanych akcji
const unsigned int time_move = 1000;
const unsigned int time_turn = 500;
const unsigned int time_build_fire = 6000;
const unsigned int time_delete = 5000;

#endif
