#ifndef IMG_HPP_
#define IMG_HPP_
#include <SDL\SDL.h>
#include <SDL\SDL_opengl.h>
#include <IL\il.h>
#include <iostream>

class Img{
public:
	Img();
	Img( int tmp_id, std::string tmp_name, std::string tmp_name_file );
	~Img();
	ILuint ReturnWidth();
	ILuint ReturnHeight();
	ILuint ReturnImageID();
	std::string ReturnName();
	int ReturnSize();
	void Status();
	bool ReturnSuccess();
protected:
	void Load();
	bool LoadFile();
	void Clear();
	void ReturnAllText();
	inline void ReturnAllText_to_Error();
	ILuint ImageID, Width, Height;
	ILboolean Success;
	bool Delete;
	int id;
	Img( int tmp_id );
private:
	std::string Name,File_Name;
};


#endif
