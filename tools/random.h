#if !defined(__JEL_RANDOM_HEADER__)
#define __JEL_RANDOM_HEADER__
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


	void array_print(int* A, int s, int e) {
		std::cout << "A [";
		for (int i = s; i < e - 1; i++)
			std::cout << A[i] << ", ";
		std::cout << A[e - 1] << "] \n";
	}

};

#endif