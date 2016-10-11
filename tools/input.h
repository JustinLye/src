#include<iostream>
#include<stdexcept>
#if !defined(__JEL_INPUT_HEADER__)
#define __JEL_INPUT_HEADER__

namespace jel {
	__declspec(dllexport) void get_console_input(char* A, int max_len = 255, char delim = '\n');
}

#endif