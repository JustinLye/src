#include<iostream>
#include<limits>
#include<cmath>
#if !defined(__DS_HASH_HEADER__)
#define __DS_HASH_HEADER__
namespace ds {
	//namespace of hash functions for CS4343
	namespace hash {
		static struct {
			double operator()(int val, int power) {
				int exponent = std::floor(std::log(val) / std::log(power));
				double residue = exponent - (std::log(val) / std::log(power));
				if (std::abs(residue) <= std::numeric_limits<double>::epsilon()) {
					return std::pow(power, exponent - 1);
				} else {
					return std::pow(power, exponent);
				}
			}
		}lesser_power_of;

		class hash_table_base {
		public:
			hash_table_base(int init_size) : _table(nullptr), _size(init_size) {

			}
			~hash_table_base() {
				if (_table != nullptr) { delete[] _table; }
			}
			inline virtual int hash_insert(int) = 0;
		protected:
			int* _table;
			int _size;
			inline virtual int h(int,int) const = 0;
			virtual void print(std::ostream& s) const {
				for (int i = 0; i < _size; i++) {
					s << _table[i] << ' ';
				}
			}
		};

		namespace open_addressing {
			static struct {
				int operator()() { return std::numeric_limits<int>::max(); }
			}default_nil;
			class open_addressing_base : public hash_table_base {
			public:
				open_addressing_base(int init_size) : hash_table_base(init_size), _nil(open_addressing::default_nil()) { clear(); }
				open_addressing_base(int init_size, int nil_value) : hash_table_base(init_size), _nil(nil_value) { clear(); }
				inline virtual int hash_insert(int k) {
					return insert(k);
				}
				inline virtual int hash_insert(int k, std::ostream* s) {
					return insert(k, *s);
				}
				inline virtual int nil() const { return _nil; }
				virtual inline void clear() {
					if (_table != nullptr)
						delete[] _table;
					_table = new int[_size];
					for(int i = 0; i < _size; i++)
						_table[i] = _nil;
				}
				friend inline std::ostream& operator<<(std::ostream& s, const open_addressing_base& h) {
					h.print(s);
					return s;
				}
			protected:
				int _nil;
				inline virtual int insert(int k) {
					int j = _nil;
					for (int i = 0; i < _size; i++) {
						j = h(k, i);
						if (_table[j] == _nil) {
							_table[j] = k;
							return j;
						}
					}
					std::cerr << "Failed to insert key " << k << "! All slots are occupied" << std::endl;
					return j;
				}
				inline virtual int insert(int k, std::ostream& s) {
					int j = _nil;
					for (int i = 0; i < _size; i++) {
						j = h(k, i);
						s << "j = h(" << k << "," << i << ") = " << j << ' ';
						if (_table[j] == _nil) {
							_table[j] = k;
							s << "T[" << j << "] = " << k << std::endl;
							return j;
						} else {
							s << "T[" << j << "] is occupied." << std::endl;
						}
					}
					std::cerr << "Failed to insert key " << k << "! All slots are occupied" << std::endl;
					s << "Failed to insert key " << k << "! All slots are occupied" << std::endl;
					return j;
				}
				virtual void print(std::ostream& s) const {
					for (int i = 0; i < _size; i++) {
						if (_table[i] == _nil) {
							s << "T[" << i << "] = NIL" << std::endl;
						} else {
							s << "T[" << i << "] = " << _table[i] << std::endl;
						}
					}
				}
			};

			class linear_probe : public open_addressing_base {
			public:
				linear_probe(int init_size) : open_addressing_base(init_size, open_addressing::default_nil()) {}
				linear_probe(int init_size, int nil_value) : open_addressing_base(init_size, nil_value) {}
			protected:
				inline virtual int h(int k, int i) const {
					return (k + i) % _size;
				}
			};
			//does not rehash if constants are changed after construction.
			class quadratic_probe : public open_addressing_base {
			public:
				quadratic_probe(int init_size, int nil_val) : open_addressing_base(init_size, nil_val), _c1(0), _c2(0) {}
				quadratic_probe(int init_size, int nil_val, int init_c1, int init_c2) : open_addressing_base(init_size, nil_val), _c1(init_c1), _c2(init_c2) {}
			protected:
				inline virtual int h(int k, int i) const {
					return ((k + _c1 * i + _c2 * (i*i)) % _size);
				}
				int _c1;
				int _c2;
			};

			class double_hash : public open_addressing_base {
			public:
				double_hash(int init_size, int nil_val) : open_addressing_base(init_size, nil_val), _mprime(int(lesser_power_of(init_size, 2))) {}
				double_hash(int init_size, int nil_val, int init_mprime) : open_addressing_base(init_size, nil_val), _mprime(init_mprime) {}
			protected:
				inline virtual int h(int k, int i) const {
					return ((h1(k) + i * h2(k)) % _size);
				}
				inline virtual int h1(int k) const {
					return k;
				}
				inline virtual int h2(int k) const {
					return (1 + (k % _mprime));
				}
				int _mprime;

			};
		};

		namespace chaining {
			class element {
			public:
				int value;
				element* next;
				element* prev;
				element() : value(0), next(nullptr), prev(nullptr) {}
				element(int val) : value(val), next(nullptr), prev(nullptr) {}
				inline friend std::ostream& operator<<(std::ostream& s, const element& e) {
					e.print(s);
					return s;
				}
			protected:
				inline virtual void print(std::ostream& s) const {
					s << value;
				}
			};
			
			class hash_table {
			public:
				static int default_h(int k) { return k % 1; }
				
				hash_table(int init_size, int(*f)(int)) : _table(nullptr), _size(init_size),  h_ptr(f) {
					clear();
				}
				inline int hash_insert(int k) { return _insert(k); }
				inline void clear() {
					element* temp = nullptr;
					if (_table != nullptr) {
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
				inline friend std::ostream& operator<<(std::ostream& s, const hash_table& h) {
					h.print(s);
					return s;
				}
			protected:
				element** _table;
				int _size;
				int(*h_ptr)(int);
				int h(int k) {
					return h_ptr(k);
				}
				inline int _insert(int k) {
					
					int j = h(k);
					element* val = new element(k);
					element* temp = _table[j];
					val->next = temp;
					if(temp != nullptr)
						temp->prev = val;
					_table[j] = val;
					return j;
				}

				inline void print(std::ostream& s) const {
					element* temp = nullptr;
					if (_table != nullptr) {
						for (int i = 0; i < _size; i++) {
							temp = _table[i];
							s << "T[" << i << "] = ";
							while (temp != nullptr) {
								s << *temp << " ---> ";
								temp = temp->next;
							}
							s << "NIL" << std::endl;
						}
					}
				}
			};
		};
	};
};

#endif
