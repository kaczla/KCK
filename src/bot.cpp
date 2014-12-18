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
	std::string tmp_text ( text.begin(), text.end() );
	return this->ReturnAnswer( tmp_text );
}

