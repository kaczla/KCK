#include "log_game.hpp"

std::fstream LogGame::file ("log.txt", std::fstream::out );
bool LogGame::IsInit = true;

LogGame::LogGame(){

}

LogGame::~LogGame(){
	LogGame::ClearLogGame();
}

void LogGame::ClearLogGame(){
	LogGame::file.close();
}

bool LogGame::ReturnLogGame(){
	return LogGame::IsInit;
}

void LogGame::Write( std::string text ){
	LogGame::file<<text;
}

void LogGame::Write( int text ){
	LogGame::file<<text;
}

void LogGame::Write( unsigned int text ){
	LogGame::file<<text;
}

void LogGame::Write( double text ){
	LogGame::file<<text;
}

void LogGame::NewLine(){
	LogGame::file<<"\n";
}
