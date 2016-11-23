#include<iostream>
#include<limits>
#include<cmath>
#if !defined(__DS_HASH_HEADER__)
#define __DS_HASH_HEADER__
namespace ds {
	//namespace of hash functions for CS4343
	namespace hash_table {
		//forward declaration
		class element;
/*-------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*      Hash Tables                                                        */
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*-------------------------------------------------------------------------*/

		/////////////////////////////////////////////////////////////////////
		// Base Hash Table (pure virtual)                                  //
		/////////////////////////////////////////////////////////////////////
		class base_hash_table {
		public:
			base_hash_table(int init_size, int(*hash_function)(int, int));
			virtual int hash_insert(int k) = 0;
			friend std::ostream& operator<<(std::ostream& s, const base_hash_table& h);
		protected:
			int _size;
			int (*_h)(int,int);
			virtual int h(int k, int i) = 0;
			virtual int insert(int k) = 0;
			virtual int insert(int k, std::ostream& s) = 0;
			virtual void clear() {}
			virtual void print(std::ostream& s) const = 0;
		};//base_hash_table

/*-------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*      Hash Tables Derived from base_hash_table                           */
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*-------------------------------------------------------------------------*/

		/////////////////////////////////////////////////////////////////////
		// Open Address Hash Table (pure virtual)                          //
		/////////////////////////////////////////////////////////////////////
		class open_address : public base_hash_table {
		public:
			//constructors
			open_address(int init_size);
			open_address(int init_size, int(*hash_function)(int, int));

			//destructor
			~open_address();

			//public member methods
			int hash_insert(int k) = 0;

		protected:
			//protected members
			int* _table;
			int _nil;

			// protected member methods
			virtual int h(int k, int i);
			int insert(int k);
			int insert(int k, std::ostream& s);
			void clear();
			void print(std::ostream& s) const;
		}; //open_address

		/////////////////////////////////////////////////////////////////////
		// Base Chained Hash Table (pure virtual)                          //
		/////////////////////////////////////////////////////////////////////
		class base_chained : public base_hash_table {
		public:
			base_chained(int init_size, int(*hash_function)(int, int));
			~base_chained();
			virtual int hash_insert(int k) = 0;
			virtual int hash_insert(int k, std::ostream& s) = 0;
		protected:
			element** _table;
			virtual int h(int k, int i);
			int insert(int k);
			int insert(int k, std::ostream& s);
			void clear();
			void print(std::ostream& s) const;
		}; //base_chained


/*-------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*      Hash Tables Derived from open_address                              */
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*-------------------------------------------------------------------------*/

		/////////////////////////////////////////////////////////////////////
		// Linear Probe Hash Table                                         //
		/////////////////////////////////////////////////////////////////////
		class linear_probe : public open_address {
		public:
			linear_probe(int init_size);
			int hash_insert(int k);
			int hash_insert(int k, std::ostream& s);
		protected:
			virtual int h(int k, int i);
		}; //linear_probe


		/////////////////////////////////////////////////////////////////////
		// Double Hashing Hash Table                                      //
		/////////////////////////////////////////////////////////////////////
		class double_hash : public open_address {
		public:
			double_hash(int init_size);
			double_hash(int init_size, int mprime);
			int hash_insert(int k);
		protected:
			int _mprime;
			int h(int k, int i);
			int h1(int k);
			int h2(int k);
		}; //double_hash

/*-------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*      Hash Tables Derived from base_chained                              */
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*-------------------------------------------------------------------------*/

		/////////////////////////////////////////////////////////////////////
		// Chained Hash Table                                              //
		/////////////////////////////////////////////////////////////////////
		class chained : public base_chained {
		public:
			chained(int init_size);
			int hash_insert(int k);
			int hash_insert(int k, std::ostream& s);
		protected:
			int h(int k, int i);
		}; //chained
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*      Utility Structures for Hash Tables                                 */
/*|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*-------------------------------------------------------------------------*/

		/////////////////////////////////////////////////////////////////////
		// Lesser Power Of (number < val that is a power of power)         //
		/////////////////////////////////////////////////////////////////////
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

		/////////////////////////////////////////////////////////////////////
		// Element (used by chaining hash tables                           //
		/////////////////////////////////////////////////////////////////////
		class element {
		public:
			int value;
			element* next;
			element* prev;
			element(int val) : value(val), next(nullptr), prev(nullptr) {}
			friend std::ostream& operator<<(std::ostream& s, const element& e) {
				e.print(s);
				return s;
			}
		protected:
			void print(std::ostream& s) const {
				s << value;
			}
		};//element

		  /////////////////////////////////////////////////////////////////////
		  // Default NIL Value (used by open addressing hash tables          //
		  /////////////////////////////////////////////////////////////////////
		static struct {
			int operator()() { return std::numeric_limits<int>::max(); }
		}default_nil;
	}; //hash
}; //ds

#endif
