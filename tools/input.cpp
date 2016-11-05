#if !defined(__JEL_INPUT_CPP__)
#define __JEL_INPUT_CPP__

#if !defined(__JEL_INPUT_HEADER__)
#include"input.h"
#endif

//reads characters from std input until max_len - 1 characters are read or delim is read.
//delim is not included in the string.
//THROWS: runtime error if problem is encountered.
__declspec(dllexport) void jel::get_console_input(char* A, int max_len, char delim) {
	std::cout << "another wasted day\n";
	int curr_idx = 0;
	char curr_char = '\0';

	try {
		curr_char = std::cin.get();
		while ((curr_idx < max_len - 1) && (curr_char != delim)) {
			A[curr_idx] = curr_char;
			curr_char = std::cin.get();
			curr_idx++;
		}
		A[curr_idx] = '\0';
	} catch (std::exception& e) {
		std::cerr << "Exception occurred: " << e.what() << '\n';
		std::cerr << "Error Thrown @: " << __FILE__ << " Line(" << __LINE__ << ")\n";
		throw e;
	} catch (...) {
		std::cerr << "Error Thrown @: " << __FILE__ << " Line(" << __LINE__ << ")\n";
		throw;
	}

}

#endif
