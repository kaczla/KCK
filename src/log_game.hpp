#ifndef LOG_GAME_HPP_
#define LOG_GAME_HPP_
#include <fstream>
#include <vector>

/**
 * Zapisywanie logów do pliku tekstowego: log.txt
 */
class LogGame{
public:
	LogGame();
	~LogGame();
	/**
	 * Zapis logów do pliku
	 * @param text - tekst
	 */
	static void Write( std::string text );
	/**
	 * Zapis logów do pliku
	 * @param text - znak
	 */
	static void Write( char text );
	/**
	 * Zapis logów do pliku
	 * @param text - liczba całkowita
	 */
	static void Write( int text );
	/**
	 * Zapis logów do pliku
	 * @param text - liczba całkowita bez znaku
	 */
	static void Write( unsigned int text );
	/**
	 * Zapis logów do pliku
	 * @param text - liczba zmiennoprzecinkowa
	 */
	static void Write( double text );
#if __GNUC__
	#if __x86_64__ || __ppc64__
	#define Vector_size_x64
		static void Write( std::vector<std::basic_string<char> >::size_type text );
	#endif
#endif
	/**
	 * Dodanie nowej lini do pliku log.txt
	 */
	static void NewLine();
	/**
	 *
	 * @return kod błędu
	 */
	bool ReturnLogGame();
	/**
	 * Zamknięcie pliku log.txt
	 */
	static void ClearLogGame();
private:
	static void InitLogGame();
	static bool IsInit;
	static std::fstream file;
};


#endif
