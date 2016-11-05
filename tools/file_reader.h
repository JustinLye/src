#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdexcept>

#if !defined(__JEL_FILE_READER_HEADER__)
#define __JEL_FILE_READER_HEADER__

namespace jel {

	class file {
	public:
		file(const char* file_path) : _path(file_path) {}
		inline const char* path() const { return _path.c_str(); }
		inline void path(const char* file_path) { _path = file_path; }
		std::vector<std::string> content() const { return _content; }
	
	private:
		file() {}
		file(const file& s) {}
		file(file&& s) {}
		
		/*_read_fileInternal Flag
		Usage: Operations should set flag to TRUE if some action could 
		affect the intended file that the jel::file class obj. represents.
		For example, if the private member _path is set to some other value
		then _read_file should be set to true in the same function in which
		the value of _path is being changed.
		Only the _get_content() operation should set flag to FALSE.*/
		bool _read_file;
		bool _content_available;
		std::string _path;
		std::ofstream _file;
		std::vector<std::string> _content;
		void _get_content();

		
		bool _init_read();
	};
}


#endif