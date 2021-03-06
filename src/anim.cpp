#include "anim.hpp"

Anim::Anim(){
	this->Width = 0;
	this->Height =  0;
	this->id = -1;

	this->StartTime = 0;
	this->StopEnd = 0;
	this->DiffTime = 0;
	this->Size = 0;
	this->CurrentImg = 0;

	this->Success = 0;
	this->Delete = false;
	this->for_int_i = 0;

	this->GlobalName = "0";
}

Anim::Anim( int tmp_id, std::string tmp_global_name, int tmp_size, Uint32 tmp_time, std::vector <std::string> tmp_name, std::vector <std::string> tmp_name_file )
{
	this->id = tmp_id;
	this->Width = 0;
	this->Height =  0;
	this->StartTime = 0;
	this->StopEnd = 0;
	this->DiffTime = tmp_time;
	this->for_int_i = 0;
	this->GlobalName = tmp_global_name;

	if( tmp_size < (int)tmp_name.size() ){
		tmp_size = (int)tmp_name.size();
	}
	if( tmp_size < (int)tmp_name_file.size() ){
		tmp_size = (int)tmp_name_file.size();
	}
	this->Size = tmp_size;
	this->CurrentImg = tmp_size - 1;

	this->Name.resize( tmp_size );
	this->Name.clear();
	this->Name = tmp_name;
	this->File_Name.resize( tmp_size );
	this->File_Name.clear();
	this->File_Name = tmp_name_file;
	this->ImageID.resize( tmp_size );
	this->ImageID.clear();
	for( this->for_int_i=0; this->for_int_i<this->Size; this->for_int_i++){
		this->ImageID.push_back( 0 );
	}

	this->Success = 0;
	this->Delete = false;
	this->Load();
}

Anim::~Anim(){
	this->Clear();
}

bool Anim::LoadFile(){
	for( this->for_int_i=0; this->for_int_i<this->Size; this->for_int_i++){
		ilGenImages( 1, &this->ImageID[for_int_i] );
		ilBindImage( this->ImageID[for_int_i] );
		this->Success = ilLoadImage( this->File_Name[for_int_i].c_str() );
		if( this->Success == IL_TRUE ){
			this->Width = ilGetInteger(IL_IMAGE_WIDTH);
			this->Height = ilGetInteger(IL_IMAGE_HEIGHT);
			this->Success = ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE );
			if( this->Success == IL_TRUE ){
				glGenTextures( 1, &this->ImageID[for_int_i] );
				glBindTexture( GL_TEXTURE_2D, this->ImageID[for_int_i] );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
				glTexImage2D( GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), this->Width, this->Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLuint*)ilGetData() );
				GLenum error = glGetError();
				if( error != GL_NO_ERROR ){
					LogGame::Write( "[ERR] " );
					LogGame::Write( SDL_GetTicks() );
					LogGame::Write( ": Nie przetworzono grafiki: " );
					LogGame::Write( this->File_Name[for_int_i] );
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
				LogGame::Write( this->File_Name[for_int_i] );
				LogGame::NewLine();
				return false;
			}
		}
		else{
			LogGame::Write( "[ERR] " );
			LogGame::Write( SDL_GetTicks() );
			LogGame::Write( ": Nie załadowano grafiki: " );
			LogGame::Write( this->File_Name[for_int_i] );
			LogGame::Write( " (PLIK NIE ISTNIEJE)\n" );
			return false;
		}
	}
	return true;

}

void Anim::Load(){
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

void Anim::Clear(){
	if( ! this->Delete  ){
		for( int i=0; i<this->Size; i++){

			if( this->ImageID[i] != 0){
				ilDeleteImages( 1, &this->ImageID[i] );
			}
		}
		this->Delete = true;
	}
}

void Anim::ReturnAllText(){
	LogGame::Write( "[LOG] " );
	LogGame::Write( SDL_GetTicks() );

	LogGame::Write( ": id=" );
	LogGame::Write( this->id );

	LogGame::Write( ": ImageID.size()=" );
	LogGame::Write( this->ImageID.size() );

	LogGame::Write( ": File_Name.size()=" );
	LogGame::Write( this->File_Name.size() );

	LogGame::Write( ": Name.size()=" );
	LogGame::Write( this->Name.size() );
	for( this->for_int_i=0; this->for_int_i<this->Size; this->for_int_i++){
		LogGame::Write( "[LOG] " );
		LogGame::Write( " name_" );
		LogGame::Write( for_int_i );
		LogGame::Write( "=" );
		LogGame::Write( this->Name[this->for_int_i] );

		LogGame::Write( " file_name_" );
		LogGame::Write( for_int_i );
		LogGame::Write( "=" );
		LogGame::Write( this->File_Name[this->for_int_i] );

		LogGame::Write( " imageID_" );
		LogGame::Write( for_int_i );
		LogGame::Write( "=" );
		LogGame::Write( this->ImageID[this->for_int_i] );
	}

	LogGame::Write( "\n[LOG] " );
	LogGame::Write( " size=" );
	LogGame::Write( this->Size );

	LogGame::Write( " time=" );
	LogGame::Write( this->DiffTime );

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

void Anim::ReturnAllText_to_Error(){
	LogGame::Write( "[ERR] " );
	LogGame::Write( SDL_GetTicks() );

	LogGame::Write( ": id=" );
	LogGame::Write( this->id );

	LogGame::Write( ": ImageID.size()=" );
	LogGame::Write( this->ImageID.size() );

	LogGame::Write( ": File_Name.size()=" );
	LogGame::Write( this->File_Name.size() );

	LogGame::Write( ": Name.size()=" );
	LogGame::Write( this->Name.size() );
	for( this->for_int_i=0; this->for_int_i<this->Size; this->for_int_i++){
		LogGame::Write( "[ERR] " );
		LogGame::Write( " name_" );
		LogGame::Write( for_int_i );
		LogGame::Write( "=" );
		LogGame::Write( this->Name[this->for_int_i] );

		LogGame::Write( " file_name_" );
		LogGame::Write( for_int_i );
		LogGame::Write( "=" );
		LogGame::Write( this->File_Name[this->for_int_i] );

		LogGame::Write( " imageID_" );
		LogGame::Write( for_int_i );
		LogGame::Write( "=" );
		LogGame::Write( this->ImageID[this->for_int_i] );
	}

	LogGame::Write( "\n[ERR] " );
	LogGame::Write( " size=" );
	LogGame::Write( this->Size );

	LogGame::Write( " time=" );
	LogGame::Write( this->DiffTime );

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

void Anim::Status(){
	this->ReturnAllText();
}

ILuint Anim::ReturnImageID(){
	this->Update();
	return this->ImageID[this->CurrentImg];
}


void Anim::Update(){
	this->StartTime = SDL_GetTicks();
	if( this->StartTime >= this->StopEnd ){
		this->StopEnd = this->StartTime + this->DiffTime;
		this->CurrentImg++;
		if( this->CurrentImg > this->Size-1 or this->CurrentImg < 0 ){
			this->CurrentImg = 0;
		}
	}
}

int Anim::ReturnSize(){
	return this->ImageID.size();
}


std::string Anim::ReturnName(){
	return this->GlobalName;
}

