#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_
#include <fstream>
#include <iostream>

class Settings{
public:
	Settings();
	~Settings();
	void init_Settings();
	void SaveSettings();
	bool ReturnFullscreen();
	int ReturnWidth();
	int ReturnHeight();
	int ReturnBpp();
private:
	//std::string name_imgages[5];
	bool fullscreen;
	int width;
	int height;
	int bpp;
	void SetValue(std::string name, int value);
};

#endif
