#include "utility.h"

//handles input from console. Files char array up to max_len chars. optional end of input sential and prompt (default values are '\n' and "" repectively)
void jel::uty::ConsoleRFI(char* A, int max_len, char eoi_sential, const char* prompt) {
	if (prompt != nullptr) {
		std::cout << prompt;
	}

	int curr_idx = 0;
	char curr_char = '\0';

	try {
		curr_char = std::cin.get();
		while ((curr_idx < max_len - 1) && (curr_char != eoi_sential)) {
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