#include "bot.hpp"

void cTestAppCallbacks::onAimlLoad(const std::string& filename) {
	LogGame::Write( "[LOG] " );
	LogGame::Write( "AIML - Załadowano: " );
	LogGame::Write( filename );
	LogGame::NewLine();
}

Bot::Bot(){
	this->Init = false;
	this->interpreter = NULL;
	this->Answer.clear();
}

Bot::~Bot(){
	delete interpreter;
}

bool Bot::InitBot(){
	this->interpreter = cInterpreter::newInterpreter();
	cTestAppCallbacks myCallbacks;
	this->interpreter->registerCallbacks( &myCallbacks );
	LogGame::Write( "[LOG] " );
	LogGame::Write( "AIML - Inicjalizowanie\n" );
	if ( ! interpreter->initialize( "libaiml.xml" ) ){
		LogGame::Write( "[ERR] " );
		LogGame::Write( "AIML - Brak plików potrzebych do inicjalizacji!\n" );
	}
	else{
		LogGame::Write( "[LOG] " );
		LogGame::Write( "AIML - Inicjalizacja przebiegła pomyślnie\n" );
		Init = true;
	}
	return true;
}


std::string Bot::ReturnAnswer( std::string text ){
	if( ! interpreter->respond( text, "localhost", this->Answer ) ){
		LogGame::Write( "[ERR] " );
		LogGame::Write( "AIML - Błąd: interpreter->respond( text, \"localhost\", this->Answer )\n" );
	}
	return this->Answer;
}

std::string Bot::ReturnAnswer( u16string text ){
	for( unsigned int i=0; i<text.size(); i++ ){
		switch( text[i] ){
		case 0x104:
			text[i] = 'A';
			break;
		case 0x15A:
			text[i] = 'S';
			break;
		case 0x106:
			text[i] = 'C';
			break;
		case 0x118:
			text[i] = 'E';
			break;
		case 0xD3:
			text[i] = 'O';
			break;
		case 0x141:
			text[i] = 'L';
			break;
		case 0x143:
			text[i] = 'N';
			break;
		case 0x17B:
			text[i] = 'Z';
			break;
		case 0x179:
			text[i] = 'Z';
			break;
		case 0x105:
			text[i] = 'a';
			break;
		case 0x15B:
			text[i] = 's';
			break;
		case 0x107:
			text[i] = 'c';
			break;
		case 0x119:
			text[i] = 'e';
			break;
		case 0xF3:
			text[i] = 'o';
			break;
		case 0x142:
			text[i] = 'l';
			break;
		case 0x144:
			text[i] = 'n';
			break;
		case 0x17C:
			text[i] = 'z';
			break;
		case 0x17A:
			text[i] = 'z';
			break;
		default:
			break;
		}
	}
	std::string tmp_text ( text.begin(), text.end() );
	return this->ReturnAnswer( tmp_text );
}

