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
}

Img::Img( int tmp_id ){
	this->ImageID = 0;
	this->Width = 0;
	this->Height =  0;
	this->id = tmp_id;
	this->Success = 0;
	this->Delete = false;
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
				LogGame::Write( "[ERR] " );
				LogGame::Write( SDL_GetTicks() );
				LogGame::Write( ": Nie przetworzono grafiki: " );
				LogGame::Write( this->File_Name );
				LogGame::Write( " Błąd: " );
				LogGame::Write( error );
				LogGame::NewLine();
				return false;
			}
		}
		else{
			LogGame::Write( "[ERR] " );
			LogGame::Write( SDL_GetTicks() );
			LogGame::Write( ": Nie przekształcono grafiki: " );
			LogGame::Write( this->File_Name );
			LogGame::NewLine();
			return false;
		}
	}
	else{
		LogGame::Write( "[ERR] " );
		LogGame::Write( SDL_GetTicks() );
		LogGame::Write( ": Nie załadowano grafiki: " );
		LogGame::Write( this->File_Name );
		LogGame::Write( " (PLIK NIE ISTNIEJE)\n" );
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
			LogGame::Write( "[ERR] " );
			LogGame::Write( SDL_GetTicks() );
			LogGame::Write( ": Brakuje niezbędnych danych do załadawania obrazka!\n Zawartość obiektu:\n" );
			this->ReturnAllText_to_Error();
		}
	}
	//this->ReturnAllText();
}

void Img::Clear(){
	if( ! this->Delete and this->ImageID != 0 ){
		ilDeleteImages( 1, &this->ImageID );
		this->Delete = true;
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
	LogGame::Write( "[LOG] " );
	LogGame::Write( ": id=" );
	LogGame::Write( this->id );

	LogGame::Write( " name=" );
	LogGame::Write( this->Name );

	LogGame::Write( " file_name=" );
	LogGame::Write( this->File_Name );

	LogGame::Write( " imageID=" );
	LogGame::Write( this->ImageID );

	LogGame::Write( " width=" );
	LogGame::Write( this->Width );

	LogGame::Write( " height=" );
	LogGame::Write( this->Height );

	LogGame::Write( " Success=" );
	LogGame::Write( (int)this->Success );

	LogGame::Write( " Delete=" );
	LogGame::Write( this->Delete );

	LogGame::NewLine();
}

void Img::ReturnAllText_to_Error(){
	LogGame::Write( "[ERR] " );
	LogGame::Write( ": id=" );
	LogGame::Write( this->id );

	LogGame::Write( " name=" );
	LogGame::Write( this->Name );

	LogGame::Write( " file_name=" );
	LogGame::Write( this->File_Name );

	LogGame::Write( " imageID=" );
	LogGame::Write( this->ImageID );

	LogGame::Write( " width=" );
	LogGame::Write( this->Width );

	LogGame::Write( " height=" );
	LogGame::Write( this->Height );

	LogGame::Write( " Success=" );
	LogGame::Write( (int)this->Success );

	LogGame::Write( " Delete=" );
	LogGame::Write( this->Delete );

	LogGame::NewLine();
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

