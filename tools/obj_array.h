#include<iostream>
#include<cmath>
#include"qsort.h"

//class to store objects (or primative types) in a dynamic array.
//array is initalized with a capacity of 32. As the number of
//elements in the array (size) grows capacity is adjusted new capcity = old capacity ^ 2

namespace jel {
	template<typename T>
	class obj_array {
	private:
		double _capacity;
		long _size;
		T* _base;
		void resize() {
			_capacity = std::powl(_capacity,2.0);
			T* temp = new T[_capacity];
			for (long i = 0; i < _size; i++) {
				temp[i] = _base[i];
			}
			delete[] _base;
			_base = temp;
		}
		void print_function(std::ostream& s) const {
			for (long i = 0; i < _size-1; i++) {
				s << _base[i] << ' ';
			}
			s << _base[_size-1];
		}
	public:
		//constructor
		obj_array() : _capacity(32), _size(0), _base(nullptr) {
			_base = new T[_capacity];
		}

		//destructor
		~obj_array() {
			delete[] _base;
		}

		//getters
		double capacity() const { return _capacity; }
		long size() const { return _size; }

		//methods
		void shrink_to_fit() {
			T* temp = new T[_size];
			for (long i = 0; i < _size; i++) {
				temp[i] = _base[i];
			}
			delete[] _base;
			_base = temp;
		}
		void sort() {
			jel::quicksort<T>(_base,0L,_size-1);
		}
		void push_back(const T& element) {
			if (_size >= _capacity) {
				resize();
			}
			_base[_size] = element;
			_size++;
		}

		T& operator[](long index) {
			return _base[index];
		}

		friend std::ostream& operator<<(std::ostream& s, const obj_array& a) {
			a.print_function(s);
			return s;
		}
	};
}
