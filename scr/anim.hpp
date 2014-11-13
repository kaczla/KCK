#ifndef ANIM_HPP_
#define ANIM_HPP_
#include "img.hpp"
#include <vector>

class Anim : public Img{
public:
	Anim();
	Anim( int tmp_id, int tmp_size, Uint32 time, std::vector <std::string> tmp_name, std::vector <std::string> tmp_name_file );
	~Anim();
	ILuint ReturnImageID();
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

};




#endif
