#include "text.hpp"

bool Text::IsInit = false;
TTF_Font *Text::Font = NULL;
SDL_Color Text::TextColorBlack = { 0, 0, 0 };
SDL_Color Text::TextColorWhite = { 255, 255, 255 };
SDL_Color Text::TextColorRed = { 255, 0, 0 };
SDL_Color Text::TextColorGreen = { 0, 255, 0 };
SDL_Color Text::TextColorBlue = { 0, 0, 255 };
int Text::FontSize = 14;

Text::Text(){
	this->SetColor( 255, 255, 255 );
	this->ImageID.clear();
	this->Width.clear();
	this->Height.clear();
	this->MaxLength = 17;
	this->NextLine = 17.0;
}

Text::~Text(){
	for( unsigned int i=0; i<ImageID.size(); i++ ){
		glDeleteTextures( 1, &this->ImageID[i] );
	}
	this->ImageID.clear();
	this->Height.clear();
	this->Width.clear();

}

bool Text::InitText(){
	if( ! Text::IsInit ){
		LogGame::Write( "[LOG] " );
		LogGame::Write( SDL_GetTicks() );
		LogGame::Write( ": Freetype - Inicjalizowanie\n" );
		if( TTF_Init() == -1 ){
			LogGame::Write( "[ERR] " );
			LogGame::Write( SDL_GetTicks() );
			LogGame::Write( ": FreeType - Błąd: Niepowodzenie TTF_Init !\n" );
			return false;
		}
		if( Text::FontSize < 14 or Text::FontSize > 18 ){
			Text::FontSize = 14;
		}
		Text::Font = TTF_OpenFont( "bin/font.ttf", Text::FontSize );
		if( Text::Font == NULL ){
			LogGame::Write( "[ERR] " );
			LogGame::Write( SDL_GetTicks() );
			LogGame::Write( ": FreeType - Błąd: Niepowodzenie TTF_OpenFont !\n" );
			return false;
		}
		TTF_SetFontStyle( Text::Font, TTF_STYLE_BOLD );
		Text::IsInit = true;
		LogGame::Write( "[LOG] " );
		LogGame::Write( SDL_GetTicks() );
		LogGame::Write( ": Freetype - Inicjalizacja przebiegła pomyślnie\n" );
	}
	return true;
}

void Text::Clear(){
	if( Text::IsInit ){
		TTF_Quit();
	}
}

void Text::SetColor( Uint8 r, Uint8 g, Uint8 b){
	this->TextColor.r = r;
	this->TextColor.g = g;
	this->TextColor.b = b;
}

void Text::RenderText( std::string text ){
	if( ! Text::IsInit ){
		TTF_CloseFont( Text::Font );
		Text::InitText();
	}
	for( unsigned int i=0; i<ImageID.size(); i++ ){
		glDeleteTextures( 1, &this->ImageID[i] );
	}
	this->ImageID.clear();
	this->Height.clear();
	this->Width.clear();

	//Podzial na lancuchy
	unsigned int tmp = 1;
	for(unsigned int i=1; i<text.size()-1; i++){
		if( text[i] == ' ' ){
			tmp++;
		}
	}
	std::string Word[tmp];
	unsigned int NumberWord = 0;
	if( tmp == 1 ){
		Word[0] = text;
	}
	else{
		for(unsigned int i=0; i<text.size(); i++){
			if( text[i] != ' ' ){
				Word[NumberWord] += text[i];
			}
			else{
				NumberWord++;
			}
		}
	}
	std::string Word2[tmp];
	unsigned int NumberString = 0;
	Word2[0]=Word[0];
	for( unsigned int i=1; i<tmp; i++ ){
		//std::cout<<"i="<<i<<"; NumberString="<<NumberString<<";\nWord2[NumberString].size()="<<Word2[NumberString].size()<<"; Word[i].size()="<<Word[i].size()<<"; suma="<<Word2[NumberString].size() + Word[i].size()<<"; Text::MaxLength="<<Text::MaxLength<<"\n";
		if( ( Word2[NumberString].size() + Word[i].size() ) <= this->MaxLength ){
			Word2[NumberString] += ' ' + Word[i];
		}
		else{
			NumberString++;
			Word2[NumberString] = Word[i];
		}

	}

	this->ImageID.resize( NumberString+1 );
	this->Height.resize( NumberString+1 );
	this->Width.resize( NumberString+1 );

	for( unsigned int i=0; i<=NumberString; i++ ){
		SDL_Surface *Message = TTF_RenderUTF8_Blended( Text::Font, Word2[i].c_str(), Text::TextColorBlack );
		this->Width[i] = Message->w;
		this->Height[i] = Message->h;
		glGenTextures( 1, &this->ImageID[i] );
		glBindTexture( GL_TEXTURE_2D, this->ImageID[i] );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Message->w, Message->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, Message->pixels );
		SDL_FreeSurface(Message);
	}
}

void Text::RenderText( u16string text ){
	if( ! Text::IsInit ){
		TTF_CloseFont( Text::Font );
		Text::InitText();
	}
	for( unsigned int i=0; i<ImageID.size(); i++ ){
		glDeleteTextures( 1, &this->ImageID[i] );
	}
	this->ImageID.clear();
	this->Height.clear();
	this->Width.clear();

	//Podzial na lancuchy
	unsigned int tmp = 1;
	for(unsigned int i=1; i<text.size()-1; i++){
		if( text[i] == ' ' ){
			tmp++;
		}
	}
	u16string Word[tmp];
	unsigned int NumberWord = 0;
	if( tmp == 1 ){
		Word[0] = text;
	}
	else{
		for(unsigned int i=0; i<text.size(); i++){
			if( text[i] != ' ' ){
				Word[NumberWord] += text[i];
			}
			else{
				NumberWord++;
			}
		}
	}
	u16string Word2[tmp];
	unsigned int NumberString = 0;
	Word2[0]=Word[0];
	for( unsigned int i=1; i<tmp; i++ ){
		//std::cout<<"i="<<i<<"; NumberString="<<NumberString<<";\nWord2[NumberString].size()="<<Word2[NumberString].size()<<"; Word[i].size()="<<Word[i].size()<<"; suma="<<Word2[NumberString].size() + Word[i].size()<<"; Text::MaxLength="<<Text::MaxLength<<"\n";
		if( ( Word2[NumberString].size() + Word[i].size() ) <= this->MaxLength ){
			Word2[NumberString] += ' ';
			Word2[NumberString] += Word[i];
		}
		else{
			NumberString++;
			Word2[NumberString] = Word[i];
		}

	}

	this->ImageID.resize( NumberString+1 );
	this->Height.resize( NumberString+1 );
	this->Width.resize( NumberString+1 );

	for( unsigned int i=0; i<=NumberString; i++ ){
		SDL_Surface *Message = TTF_RenderUNICODE_Blended( Text::Font, Word2[i].c_str(), Text::TextColorBlack );
		this->Width[i] = Message->w;
		this->Height[i] = Message->h;
		glGenTextures( 1, &this->ImageID[i] );
		glBindTexture( GL_TEXTURE_2D, this->ImageID[i] );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Message->w, Message->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, Message->pixels );
		SDL_FreeSurface(Message);
	}
}

void Text::SetMaxLength( float max ){
	if( max<17.0 or max>100 ){
		max = 17.0;
	}
	this->MaxLength = (unsigned int)max;
}

void Text::Draw(){
	for( unsigned int i=0; i<ImageID.size(); i++ ){
		glBindTexture( GL_TEXTURE_2D, this->ImageID[i] );
		//LogGame::Write("\nDraw\n");		//LogGame::Write( Height[i] );		//LogGame::Write("+" );
		//LogGame::Write( Width[i] );		//LogGame::Write(" ;\n");
		glBegin( GL_QUADS );
			glTexCoord2d( 0.0, 0.0 ); glVertex2d( 0.0, 0.0 );
			glTexCoord2d( 1.0, 0.0 ); glVertex2d( this->Width[i], 0.0 );
			glTexCoord2d( 1.0, 1.0 ); glVertex2d( this->Width[i], this->Height[i] );
			glTexCoord2d( 0.0, 1.0 ); glVertex2d( 0.0, this->Height[i] );
		glEnd();
		glTranslatef( 0.0, this->NextLine, 0.0 );
	}
}

void Text::DrawPlusAngle(){
	glRotatef( -5.0, 0.0, 0.0, 1.0 );
	for( unsigned int i=0; i<ImageID.size(); i++ ){
		glBindTexture( GL_TEXTURE_2D, this->ImageID[i] );
		glBegin( GL_QUADS );
			glTexCoord2d( 0.0, 0.0 ); glVertex2d( 0.0, 0.0 );
			glTexCoord2d( 1.0, 0.0 ); glVertex2d( this->Width[i], 0.0 );
			glTexCoord2d( 1.0, 1.0 ); glVertex2d( this->Width[i], this->Height[i] );
			glTexCoord2d( 0.0, 1.0 ); glVertex2d( 0.0, this->Height[i] );
		glEnd();
		glTranslatef( 0.0, this->NextLine, 0.0 );
	}
}

void Text::SetNextLine( float line ){
	if( line<17.0 or line>100 ){
		line = 17.0;
	}
	this->NextLine = line;
}
