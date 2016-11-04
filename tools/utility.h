#include<iostream>
#include<string>
#include<stdexcept>

#if !defined(__JEL_UTILITY_HEADER__)
#define __JEL_UTILITY_HEADER__

namespace jel {

#define JEL_STATUS_NOT_OKAY 0x1010
#define JEL_STATUS_OKAY 0x1011
#define JEL_STATUS_UNKNOWN 0X1012

#define JEL_PRINT_PYTHON_LIKE_FORMAT 0X1020

	/*udty - short for utility, this class is intented to function as my programming swiss army pocket-knife.
	         Misc. type functions that are trival, but fequently used will be added to this class.
			 All functions and members are public and static.
			 Also, a singleton approach is implemented be making the constructors inaccessible.
	*/
	class uty {
	public:

		//returns true if val is low_bound <= val <= high_bound
		template<typename Type>
		inline static bool InRange(Type val, Type low_bound, Type high_bound) { return (val >= low_bound && val <= high_bound && low_bound <= high_bound); }

		//handles input from console. Files char array up to max_len chars. optional end of input sential and prompt (default values are '\n' and "" repectively)
		static void ConsoleRFI(char* A, int max_len, char eoi_sential = '\n', const char* prompt = nullptr);

		//prints array with optional formating
	private:
		uty() {}
		uty(const uty& j) {}
		uty(uty&& j) {}
	};



	class base_status {
	public:
		base_status() : _state(JEL_STATUS_UNKNOWN) {}
		base_status(const base_status& s) : _state(s._state) {}
		base_status(base_status&& s) : _state(std::move(s._state)) {}

		virtual inline int operator()() const { return _state; }
		//virtual inline void operator()(int new_state) { _state = 
	private:
		int _state;

	};
}

#endif