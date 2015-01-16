#ifndef LOG_GAME_HPP_
#define LOG_GAME_HPP_
#include <fstream>
#include <vector>

class LogGame{
public:
	LogGame();
	~LogGame();
	static void Write( std::string text );
	static void Write( char text );
	static void Write( int text );
	static void Write( unsigned int text );
	static void Write( double text );
#if __GNUC__
	#if __x86_64__ || __ppc64__
	#define Vector_size_x64
		static void Write( std::vector<std::basic_string<char> >::size_type text );
	#endif
#endif
	static void NewLine();
	bool ReturnLogGame();
	static void ClearLogGame();
private:
	static void InitLogGame();
	static bool IsInit;
	static std::fstream file;
};


#endif
