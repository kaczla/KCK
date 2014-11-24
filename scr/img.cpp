#include "img.hpp"

Img::Img(){
	this->ImageID = 0;
	this->Width = 0;
	this->Height =  0;
	this->id = -1;
	this->Name = " ";
	this->File_Name = " ";
	this->Success = 0;
	this->Delete = false;
	//std::cout<<SDL_GetTicks()<<": Konstruktor Img()\n";
}

Img::Img( int tmp_id, std::string tmp_name, std::string tmp_name_file ){
	this->ImageID = 0;
	this->Width = 0;
	this->Height =  0;
	this->id = tmp_id;
	this->Name = tmp_name;
	this->File_Name = tmp_name_file;
	this->Success = 0;
	this->Delete = false;
	this->Load();
	//std::cout<<SDL_GetTicks()<<": Konstruktor Img( int tmp_id, std::string tmp_name, std::string tmp_name_file )\n";
}

Img::Img( int tmp_id ){
	this->ImageID = 0;
	this->Width = 0;
	this->Height =  0;
	this->id = tmp_id;
	this->Success = 0;
	this->Delete = false;
	//std::cout<<SDL_GetTicks()<<": Konstruktor Img( int tmp_id )\n";
}

Img::~Img(){
	this->Clear();
}

bool Img::LoadFile(){
	ilGenImages( 1, &this->ImageID );
	ilBindImage( this->ImageID );
	this->Success = ilLoadImage( this->File_Name.c_str() );
	if( this->Success == IL_TRUE ){
		this->Width = ilGetInteger(IL_IMAGE_WIDTH);
		this->Height = ilGetInteger(IL_IMAGE_HEIGHT);
		this->Success = ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE );
		if( this->Success == IL_TRUE ){
			glGenTextures( 1, &this->ImageID );
			glBindTexture( GL_TEXTURE_2D, this->ImageID );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexImage2D( GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), this->Width, this->Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLuint*)ilGetData() );
			GLenum error = glGetError();
			if( error != GL_NO_ERROR ){
				std::cerr<<SDL_GetTicks()<<": Nie przetworzono grafiki: "<<this->File_Name<<" "<<error<<"\n";
				return false;
			}
		}
		else{
			std::cerr<<SDL_GetTicks()<<": Nie przekształcono grafiki: "<<this->File_Name<<"\n";
			return false;
		}
	}
	else{
		std::cerr<<SDL_GetTicks()<<": Nie załadowano grafiki: "<<this->File_Name<<" (PLIK NIE ISTNIEJE)\n";
		return false;
	}
	return true;
}

void Img::Load(){
	if( ! this->Success == IL_TRUE ){
		if( this->id != -1 ){
			if( ! this->LoadFile() ){
				this->Clear();
			}
		}
		else{
			std::cerr<<SDL_GetTicks()<<": Brakuje niezbędnych danych do załadawania obrazka!\n Zawartość obiektu: ";
			this->ReturnAllText_to_Error();
		}
	}
	//this->ReturnAllText();
}

void Img::Clear(){
	if( ! this->Delete and this->ImageID != 0 ){
		ilDeleteImages( 1, &this->ImageID );
		this->Delete = true;
		//std::cout<<SDL_GetTicks()<<": Usunięto grafike o nazwie pliku \""<<this->File_Name<<"\" z pamięci\n";
	}
}

bool Img::ReturnSuccess(){
	if( this->Success == IL_TRUE ){
		return true;
	}
	else{
		return false;
	}
}

void Img::ReturnAllText(){
	std::cout<<SDL_GetTicks()
		<<": id="<<this->id
		<<" name="<<this->Name
		<<" file_name="<<this->File_Name
		<<" imageID="<<this->ImageID
		<<" width="<<this->Width
		<<" height="<<this->Height
		<<" Success="<<(int)this->Success
		<<" Delete="<<this->Delete
		<<"\n";
}

void Img::ReturnAllText_to_Error(){
	std::cerr<<SDL_GetTicks()
		<<": id="<<this->id
		<<" name="<<this->Name
		<<" file_name="<<this->File_Name
		<<" imageID="<<this->ImageID
		<<" width="<<this->Width
		<<" height="<<this->Height
		<<" Success="<<(int)this->Success
		<<" Delete="<<this->Delete
		<<"\n";
}


void Img::Status(){
	this->ReturnAllText();
}

ILuint Img::ReturnImageID(){
	return this->ImageID;
}

ILuint Img::ReturnWidth(){
	return this->Width;
}

ILuint Img::ReturnHeight(){
	return this->Height;
}

std::string Img::ReturnName(){
	return this->Name;
}

int Img::ReturnSize(){
	return 1;
}

