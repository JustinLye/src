
#include"dshash.h"
using namespace ds::hash_table;

/*-------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*      Hash Tables                                                        */
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*-------------------------------------------------------------------------*/

		/////////////////////////////////////////////////////////////////////
		// Base Hash Table (pure virtual)                                  //
		/////////////////////////////////////////////////////////////////////
		base_hash_table::base_hash_table(int init_size, int(*hash_function)(int, int)) : _size(init_size), _h(hash_function) {}
		std::ostream& ds::hash_table::operator<<(std::ostream& s, const base_hash_table& h) {
			h.print(s);
			return s;
		}

/*-------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*      Hash Tables Derived from base_hash_table                           */
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*-------------------------------------------------------------------------*/

		/////////////////////////////////////////////////////////////////////
		// Open Address Hash Table (pure virtual)                          //
		/////////////////////////////////////////////////////////////////////
		open_address::open_address(int init_size) : base_hash_table(init_size, nullptr), _table(nullptr), _nil(default_nil()) { clear(); }
		open_address::open_address(int init_size, int(*hash_function)(int, int)) : base_hash_table(init_size, hash_function), _table(nullptr), _nil(default_nil()) { clear(); }
		open_address::~open_address() {
			if (_table != nullptr)
				delete[] _table;
		}
		int open_address::h(int k, int i) {
			return _h(k, i);
		}
		int open_address::insert(int k) {
			int j = _nil;
			for (int i = 0; i < _size; i++) {
				j = h(k, i);
				if (_table[j] == _nil) {
					_table[j] = k;
					return j;
				}
			}
			return _nil;
		}
		int open_address::insert(int k, std::ostream& s) {
			int j = _nil;
			for (int i = 0; i < _size; i++) {
				j = h(k, i);
				s << "h(" << k << "," << i << ") = " << j;
				if (_table[j] == _nil) {
					s << " T[" << j << "] = NIL ==> T[" << j << "] = " << k << std::endl;
					_table[j] = k;
					return j;
				} else {
					s << " T[" << j << "] is occupied." << std::endl;
				}
			}
			s << "Error hash table is full. Could not insert key " << k << std::endl;
			return _nil;
		}
		void open_address::clear() {
			if (_table != nullptr)
				delete[] _table;
			_table = new int[_size];
			for (int i = 0; i < _size; i++)
				_table[i] = _nil;
		}
		void open_address::print(std::ostream& s) const {
			for (int i = 0; i < _size; i++) {
				s << "T[" << i << "] = ";
				(_table[i] == _nil) ? s << "NIL" : s << _table[i];
				s << std::endl;
			}
		}

		/////////////////////////////////////////////////////////////////////
		// Chained Hash Table (pure virtual)                               //
		/////////////////////////////////////////////////////////////////////
		base_chained::base_chained(int init_size, int(*hash_function)(int, int)) : base_hash_table(init_size, hash_function), _table(nullptr) { clear(); }
		base_chained::~base_chained() {
			clear();
			if (_table != nullptr)
				delete[] _table;
		}
		int base_chained::h(int k, int i) { return _h(k, i); }
		int base_chained::insert(int k) {
			int j = h(k, _size);
			element* val = new element(k);
			element* temp = _table[j];
			val->next = temp;
			if (temp != nullptr)
				temp->prev = val;
			_table[j] = val;
			return j;
		}
		int base_chained::insert(int k, std::ostream& s) {
			int j = h(k, _size);
			s << "h(" << k << "," << _size << ") = " << j;
			element* val = new element(k);
			element* temp = _table[j];
			val->next = temp;
			if (temp != nullptr) {
				s << " T[" << j << "] is occuppied => chain " << *val << std::endl;
				temp->prev = val;
			} else {
				s << " T[" << j << "] = NIL => " << "T[" << j << "] = " << *val << std::endl;
			}
			_table[j] = val;
			return j;
		}
		void base_chained::clear() {
			if (_table != nullptr) {
				element* temp = nullptr;
				for (int i = 0; i < _size; i++) {
					while (_table[i] != nullptr) {
						temp = _table[i];
						_table[i] = _table[i]->next;
						delete temp;
					}
				}
			}
			_table = new element*[_size];
			for (int i = 0; i < _size; i++) {
				_table[i] = nullptr;
			}
		}
		void base_chained::print(std::ostream& s) const {
			element* temp = nullptr;
			if (_table != nullptr) {
				for (int i = 0; i < _size; i++) {
					temp = _table[i];
					s << "T[" << i << "] = ";
					while (temp != nullptr) {
						s << *temp << " --> ";
						temp = temp->next;
					}
					s << "NIL" << std::endl;
				}
			}
		}
/*-------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*      Hash Tables Derived from open_address                              */
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*-------------------------------------------------------------------------*/

		/////////////////////////////////////////////////////////////////////
		// Linear Probe Hash Table                                         //
		/////////////////////////////////////////////////////////////////////
		linear_probe::linear_probe(int init_size) : open_address(init_size) {}
		int linear_probe::hash_insert(int k) { return insert(k); }
		int linear_probe::hash_insert(int k, std::ostream& s) { return insert(k, s); }
		int linear_probe::h(int k, int i) { return ((k + i) % _size); }

		/////////////////////////////////////////////////////////////////////
		// Double Hashing Hash Table                                      //
		/////////////////////////////////////////////////////////////////////
		double_hash::double_hash(int init_size) : open_address(init_size), _mprime(int(lesser_power_of(init_size, 2))) {}
		double_hash::double_hash(int init_size, int mprime) : open_address(init_size), _mprime(mprime) {}
		int double_hash::hash_insert(int k) { return insert(k); }
		int double_hash::h(int k, int i) { return ((h1(k) + i * h2(k)) % _size); }
		int double_hash::h1(int k) { return k; }
		int double_hash::h2(int k) { return (1 + (k % _mprime)); }


/*-------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*      Hash Tables Derived from base_chained                              */
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*-------------------------------------------------------------------------*/

		/////////////////////////////////////////////////////////////////////
		// Chained Hash Table                                              //
		/////////////////////////////////////////////////////////////////////
		chained::chained(int init_size) : base_chained(init_size, nullptr) {}
		int chained::hash_insert(int k) { return insert(k); }
		int chained::hash_insert(int k, std::ostream& s) { return insert(k, s); }
		int chained::h(int k, int i) { return (k % _size); }