#ifndef IMG_HPP_
#define IMG_HPP_
#include "include_SDL.hpp"
#include "include_SDL_opengl.hpp"
#include "include_IL.hpp"
#include "log_game.hpp"

/**
Plik **img.hpp**:

Umożliwia ładowanie grafiki do pamięci.

* Załadowanie grafiki możliwe jest przez wywołanie konstruktora:

Img( int **tmp_id**, std::string **tmp_name**, std::string **tmp_name_file** )

gdzie:

_tmp_id_ - identyfikator grafiki

_tmp_name_ - lokalizacja grafiki

_tmp_name_file_ - nazwa grafiki
 */
class Img{
public:
	Img();
	/**
	 * Wczytanie grafiki do pamięci.
	 * @param tmp_id - identyfikator grafiki
	 * @param tmp_name - lokalizacja grafiki
	 * @param tmp_name_file - nazwa grafiki
	 */
	Img( int tmp_id, std::string tmp_name, std::string tmp_name_file );
	~Img();
	/**
	 *
	 * @return szerokość grafiki
	 */
	ILuint ReturnWidth();
	/**
	 *
	 * @return wysokość grafiki
	 */
	ILuint ReturnHeight();
	/**
	 *
	 * @return identyfikator grafiki w pamięci
	 */
	ILuint ReturnImageID();
	/**
	 *
	 * @return nazwę grafiki
	 */
	std::string ReturnName();
	/**
	 *
	 * @return ilość klater grafiki
	 */
	int ReturnSize();
	/**
	 * Zapisuje grafikę do pliku log.txt
	 */
	void Status();
	/**
	 *
	 * @return kod błędu
	 */
	bool ReturnSuccess();
protected:
	/**
	 * Inicjalizacja wczytywania grafkiki
	 */
	void Load();
	/**
	 * Wczytanie grafiki o wcześniej podanych informacjach
	 * @return kod błędu
	 */
	bool LoadFile();
	/**
	 * Usunięcie grafiki
	 */
	void Clear();
	/**
	 * Zapisuje grafikę do pliku log.txt
	 */
	void ReturnAllText();
	/**
	 * Zapisuje grafikę do pliku log.txt
	 */
	inline void ReturnAllText_to_Error();
	/**
	 * Identyfikator grafiki w pamięci
	 */
	ILuint ImageID;
	/**
	 * Szerokość grafiki
	 */
	ILuint Width;
	/**
	 * Wysokość grafiki
	 */
	ILuint Height;
	/**
	 * Success Kod błedu
	 */
	ILboolean Success;
	/**
	 * Kod usunięcia grafiki
	 */
	bool Delete;
	/**
	 * Tymczasowy identyfikator grafiki
	 */
	int id;
	/**
	 * Inicjalizacja grafiki
	 * @param tmp_id - identyfikator grafiki w pamięci
	 */
	Img( int tmp_id );
private:
	std::string Name,File_Name;
};


#endif
