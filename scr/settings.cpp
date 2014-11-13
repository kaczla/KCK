#include "settings.hpp"

Settings::Settings(){
	this->fullscreen = false;
	this->width = 640;
	this->height = 480;
	this->bpp = 32;
}

Settings::~Settings(){

}

bool Settings::ReturnFullscreen(){
	return this->fullscreen;
}

int Settings::ReturnBpp(){
	return this->bpp;
}

int Settings::ReturnWidth(){
	return this->width;
}

int Settings::ReturnHeight(){
	return this->height;
}

void Settings::SaveSettings(){
	std::fstream file;
	file.open("settings.ini", std::ios::out);
	file<<"fullscreen= "<<this->ReturnFullscreen()<<"\n"
		<<"width= "<<this->ReturnWidth()<<"\n"
		<<"height= "<<this->ReturnHeight()<<"\n"
		<<"bpp= "<<this->ReturnBpp()<<"\n"
		<<"";
	file.close();
}

void Settings::init_Settings(){
	std::fstream file;
	file.open("settings.ini", std::ios::in);
	if(file.good()){
		std::string tmp1;
		int tmp2;
		for(unsigned i=0;i<4;i++){
			file>>tmp1;
			file>>tmp2;
			SetValue(tmp1,tmp2);
		}
		file.close();
		//Set value
		if( this->width < 640 ){
			this->width = 640;
			std::cerr<<"Zmieniono szerokość okna na 640\n";
		}
		if( this->height < 480 ){
			this->height = 480;
			std::cerr<<"Zmieniono wysokość okna na 480\n";
		}
		if( this->bpp > 32 or this->bpp < 8){
			this->bpp = 32;
			std::cerr<<"Zmieniono głębie kolorów dla okna na 32 (2^32)\n";
		}

		std::cout<<"0: Wczytano ustawienia z pliku settings.ini: ";
		std::cout<<"fullscreen="<<this->ReturnFullscreen()<<";width="<<this->ReturnWidth()
				<<";height="<<this->ReturnHeight()<<";bpp="<<this->ReturnBpp()<<";\n";

	}
	else{
		file.open("settings.ini", std::ios::out);
		file<<"fullscreen= 0\n"
			<<"width= 640\n"
			<<"height= 480\n"
			<<"bpp= 32\n"
			<<"";
		file.close();
		std::cout<<"0: Stworzono ustawienia w pliku settings.ini: ";
		std::cout<<"fullscreen="<<this->ReturnFullscreen()<<";width="<<this->ReturnWidth()
						<<";height="<<this->ReturnHeight()<<";bpp="<<this->ReturnBpp()<<";\n";
	}
}

void Settings::SetValue(std::string name, int value){
	if( name == "fullscreen=" ){
		this->fullscreen=value;
	}
	else if( name == "width=" ){
		this->width=value;
	}
	else if( name == "height=" ){
		this->height=value;
	}
	else if( name == "bpp=" ){
		this->bpp=value;
	}
	else{

	}
}
