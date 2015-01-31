#ifndef ANIM_HPP_
#define ANIM_HPP_
#include "img.hpp"
#include <vector>

/**
 *

Plik anim.h:

Umożliwia ładowanie animacji do pamięci.

Załadowanie animacji możliwe jest przez wywołanie konstruktora

Anim( int tmp_id, std::string tmp_global_name, int tmp_size, Uint32 time, std::vector std::string tmp_name, std::vector std::string tmp_name )

gdzie:

tmp_id - identyfikator animacji

tmp_global_name - nazwa animacji

tmp_size - ilość klatek

time - czas odświeżania

tmp_name - kontener zawierający lokalizację wszystkich klatek

tmp_name_ - kontener zawierający nazwy wszystkich klatek

 */
class Anim : public Img{
public:
	Anim();
	/**
	 * Załadownie animacji
	 * @param tmp_id - identyfikator animacji
	 * @param tmp_global_name - nazwa animacji
	 * @param tmp_size - ilość klatek
	 * @param time - czas odświeżania
	 * @param tmp_name - kontener zawierający lokalizację wszystkich klatek
	 * @param tmp_name_file - kontener zawierający nazwy wszystkich klatek
	 */
	Anim( int tmp_id, std::string tmp_global_name, int tmp_size, Uint32 time, std::vector <std::string> tmp_name, std::vector <std::string> tmp_name_file );
	~Anim();
	/**
	 *
	 * @return numer animacji w pamięci
	 */
	ILuint ReturnImageID();
	/**
	 *
	 * @return nazwę animacji
	 */
	std::string ReturnName();
	/**
	 *
	 * @return ilość klatek animacji
	 */
	int ReturnSize();
	/**
	 * Zapis do pliku
	 */
	void Status();
private:
	void Load();
	bool LoadFile();
	void Update();
	void Clear();
	inline void ReturnAllText();
	inline void ReturnAllText_to_Error();
	Uint32 StartTime, StopEnd, DiffTime;
	int Size,CurrentImg,for_int_i;
	std::vector <std::string> Name,File_Name;
	std::vector <ILuint> ImageID;
	std::string GlobalName;
};




#endif
