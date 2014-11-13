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
	//std::cout<<SDL_GetTicks()<<": Konstruktor Anim()\n";
}

Anim::Anim( int tmp_id, int tmp_size, Uint32 tmp_time, std::vector <std::string> tmp_name, std::vector <std::string> tmp_name_file )
{
	this->id = tmp_id;
	this->Width = 0;
	this->Height =  0;
	this->StartTime = 0;
	this->StopEnd = 0;
	this->DiffTime = tmp_time;
	this->for_int_i = 0;

	if( tmp_size < (int)tmp_name.size() ){
		tmp_size = (int)tmp_name.size();
	}
	if( tmp_size < (int)tmp_name_file.size() ){
		tmp_size = (int)tmp_name_file.size();
	}
	this->Size = tmp_size;
	this->CurrentImg = tmp_size -1;

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
	//std::cout<<SDL_GetTicks()<<": Konstruktor Anim( int tmp_id, int tmp_size, Uint32 tmp_time, std::vector <std::string> tmp_name, std::vector <std::string> tmp_name_file )\n";
}

Anim::~Anim(){
	//std::cout<<"Dek!\n";
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
					std::cerr<<SDL_GetTicks()<<": Nie przetworzono grafiki: "<<this->File_Name[for_int_i]<<" "<<error<<"\n";
					return false;
				}
			}
			else{
				std::cerr<<SDL_GetTicks()<<": Nie przekształcono grafiki: "<<this->File_Name[for_int_i]<<"\n";
				return false;
			}
		}
		else{
			std::cerr<<SDL_GetTicks()<<": Nie załadowano grafiki: "<<this->File_Name[for_int_i]<<"\n";
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
			std::cerr<<SDL_GetTicks()<<": Brakuje niezbędnych danych do załadawania obrazka!\n Zawartość obiektu: ";
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
				//std::cout<<SDL_GetTicks()<<":  Anim()\n";
			}
		}
		this->Delete = true;
	}
}

void Anim::ReturnAllText(){
	std::cout<<SDL_GetTicks()
		<<": id="<<this->id
		<<" ImageID.size()="<<this->ImageID.size()
		<<" File_Name.size()="<<this->File_Name.size()
		<<" Name.size()="<<this->Name.size();
	for( this->for_int_i=0; this->for_int_i<this->Size; this->for_int_i++){
		std::cout<<" name_"<<for_int_i<<"="<<this->Name[this->for_int_i]
		   <<" file_name_"<<for_int_i<<"="<<this->File_Name[this->for_int_i]
		   <<" imageID_"<<for_int_i<<"="<<this->ImageID[this->for_int_i];
	}
	std::cout<<" size="<<this->Size
		<<" time="<<this->DiffTime
		<<" width="<<this->Width
		<<" height="<<this->Height
		<<" Success="<<(int)this->Success
		<<" Delete="<<this->Delete
		<<"\n";
}

void Anim::ReturnAllText_to_Error(){
	std::cerr<<SDL_GetTicks()
		<<": id="<<this->id
		<<" ImageID.size()="<<this->ImageID.size()
		<<" File_Name.size()="<<this->File_Name.size()
		<<" Name.size()="<<this->Name.size();
	for( this->for_int_i=0; this->for_int_i<this->Size; this->for_int_i++){
		std::cerr<<" name_"<<for_int_i<<"="<<this->Name[this->for_int_i]
		   <<" file_name_"<<for_int_i<<"="<<this->File_Name[this->for_int_i]
		   <<" imageID_"<<for_int_i<<"="<<this->ImageID[this->for_int_i];
	}
	std::cerr<<" size="<<this->Size
		<<" time="<<this->DiffTime
		<<" width="<<this->Width
		<<" height="<<this->Height
		<<" Success="<<(int)this->Success
		<<" Delete="<<this->Delete
		<<"\n";
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
		else{
			this->CurrentImg++;
		}
	}
}

