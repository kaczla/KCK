#ifndef LOG_GAME_HPP_
#define LOG_GAME_HPP_
//#include <iostream>
#include <fstream>

class LogGame{
public:
	LogGame();
	~LogGame();
	static void Write( std::string text );
	static void Write( int text );
	static void Write( unsigned int text );
	static void Write( double text );
	static void NewLine();
	bool ReturnLogGame();
	static void ClearLogGame();
private:
	static void InitLogGame();
	static bool IsInit;
	static std::fstream file;
};


#endif
