#include<stdexcept>
#if !defined(__DS_ARRAY_HEADER__)
#define __DS_ARRAY_HEADER__
namespace ds {
	//Simple array class
	template<typename T>
	class Array {
	public:
		//constructor: allocates space from array of init_length
		Array(int init_length) : _length(init_length), _array(nullptr) { _array = new T[_length]; }
		//constructor: accepts initialization list
		Array(std::initializer_list<T> l) : _length(l.size()) {
			_array = new T[_length];
			int count = 0;
			for (auto i = l.begin(); i != l.end(); ++i) {
				_array[count] = *i;
				count++;
			}
		}
		//destructor: release memory
		~Array() { delete[] _array; }
		//getter: returns length of array
		inline int length() const { return _length; }
		//getter: return maximum value found in array in O(n) time
		inline T Max() const {
			T result = _array[0];
			for (int i = 1; i < _length; i++) {
				if (result < _array[i])
					result = _array[i];
			}
			return result;
		}

		//resets array to array_length. All existing elements are lost
		inline void resize(int array_length) {
			if (_array != nullptr) {
				delete[] _array;
			}
			_array = new T[array_length];
			_length = array_length;
		}
		//fill array with some constant value. All existing elements are replaced
		inline void fill(const T& val) { for (int i = 0; i < _length; i++) { _array[i] = val; } }
		//operator: random access operator
		inline T& operator[](int idx) { if (idx >= 0 && idx < _length) { return _array[idx]; } else { std::string msg = std::string("Index out of bounds ") + std::to_string(idx); throw std::runtime_error(msg.c_str()); } }
		//operator: standard output operator
		friend inline std::ostream& operator<<(std::ostream& s, const Array& a) {
			a.print(s);
			return s;
		}
	protected:
		//member: stores current length of array
		int _length;
		//base pointer to array
		int* _array;
		//method to print array to given output s
		void print(std::ostream& s) const {
			s << "[";
			for (int i = 0; i < _length - 1; i++) {
				s << _array[i] << ',';
			}
			s << _array[_length - 1] << "]";
		}
	private:
		int_array() {}
		int_array(const Array& a) {}
		int_array(Array&& a) {}
	};
};
#endif