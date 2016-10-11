#if !defined(__JEL_RANDOM_HEADER__)
#define __JEL_RANDOM_HEADER__
#include<iostream>
#include<random>
#include<ctime>
namespace jel {
	
	static struct {
		template<class TypeName>
		void operator()(TypeName seed) { srand(seed); }
	} random_seed;

	static struct {
		template<class TypeName>
		TypeName operator()(TypeName low, TypeName high) { return (rand() % (high - low)) + low; }
	} random;

	//WARNING: caller is responsible for TypeName* resource management!!
	static struct {
		template<class TypeName>
		TypeName* operator()(TypeName size, TypeName low, TypeName high) {
			TypeName* A = new TypeName[size];
			for (TypeName index = 0; index < size; index++)
				A[index] = jel::random(low,high);
			return A;
		}
	} random_array;

	//---------------------------------------
	//temporary stuff w/o a home

	class tuple {
	public:
		long long* arg1;
		long long size;
		tuple() : arg1(nullptr), size(0) {}
		tuple(long long init_size) : arg1(nullptr), size(init_size) {
			arg1 = new long long[init_size];
		}
		tuple(const tuple& t) : arg1(t.arg1), size(t.size) {}
		~tuple() {
			if (arg1 != nullptr) {
				delete[] arg1;
			}
		}
		void print() {
			for (long long i = 0; i < size; i += 2) {
				std::cout << "(" << arg1[i] << ", " << arg1[i + 1] << ") ";
			}
		}
	};
	tuple* spliter(long long size, long long cores) {
		tuple* t = new tuple(cores * 2);
		long long sub_size = ceil((size - 1) / cores);
		long long i = 0;
		long long j = 0;
		for (i = 0; i < (cores - 1) * 2; i += 2) {
			t->arg1[i] = j;
			t->arg1[i + 1] = j + sub_size;
			j += sub_size + 1;
		}
		t->arg1[i] = j;
		(j < (size - 1)) ? t->arg1[i + 1] = j + ((size - 1) - j) : t->arg1[i + 1] = j;
		return t;
	}


	void array_print(int* A, int s, int e) {
		std::cout << "A [";
		for (int i = s; i < e - 1; i++)
			std::cout << A[i] << ", ";
		std::cout << A[e - 1] << "] \n";
	}



}

#endif