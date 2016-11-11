#include<iostream>
#include<stdexcept>
#include<sstream>

#if !defined(__JEL_ERROR_HEADER__)
#define __JEL_ERROR_HEADER__

namespace jel {

	class error : public std::runtime_error {
	public:
		error(const char* filename, int linenum, const char* info = nullptr) :
			_filename(filename),
			_linenum(linenum),
			_info(info) {
			std::ostringstream ss;
			ss << _filename << " (" << _linenum << "):\t " << _info;
			_error_msg = ss.str().c_str();
		}
			
		friend std::ostream& operator<<(std::ostream& s, const jel::error& e) {
			e.print(s);
			return s;
		}
	private:
		const char* _filename;
		int _linenum;
		const char* _info;
		const char* _error_msg;
		virtual void print(std::ostream& s) const {
			s << _error_msg << std::endl;
		}
	};

}


#endif