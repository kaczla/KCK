#ifndef IMG_HPP_
#define IMG_HPP_
#include "include_SDL.hpp"
#include "include_SDL_opengl.hpp"
#include "include_IL.hpp"
#include "log_game.hpp"

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
