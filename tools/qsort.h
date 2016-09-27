#if !defined(__JEL_QSORT_HEADER__)
#define __JEL_QSORT_HEADER__

#include<iostream>
#include<random>
#include<ctime>
namespace jel {
	//quicksort algorithm taken from Introduction to Algorithms 3rd Edition page 171 and 179.

	void random_init();
	void random_init() {
		std::srand(std::time(NULL));
	}
	template<typename T>
	void random_quicksort_imp(T* A, int p, int r);
	template<typename T>
	void random_quicksort(T* A, int p, int r);
	template<typename T>
	int random_partition(T* A, int p, int r);
	template<typename T>
	void quicksort(T* A, int p, int r);
	template<typename T>
	int partition(T* A, int p, int r);
	template<typename T>
	void swap(T* A, int l, int r);

	template<typename T>
	void random_quicksort(T* A, int p, int r) {
		random_init();
		random_quicksort_imp<T>(A,p,r);
	}
	
	template<typename T>
	void random_quicksort_imp(T* A, int p, int r) {
		if (p < r) {
			int q = random_partition<T>(A,p,r);
			random_quicksort_imp<T>(A,p,q-1);
			random_quicksort_imp<T>(A,q+1,r);
		}
	}
	template<typename T>
	int random_partition(T* A, int p, int r) {
		int i = std::rand() % r + p;
		swap<T>(A,i,r);
		return partition<T>(A,p,r);
	}
	

	template<typename T>
	void quicksort(T* A, int p, int r) {
		if (p < r) {
			int q = partition<T>(A,p,r);
			quicksort<T>(A,p,q-1);
			quicksort<T>(A,q+1,r);
		}
	}
	template<typename T>
	int partition(T* A, int p, int r) {
		T& x = A[r];
		int i = p - 1;
		for (int j = p; j < r; j++) {
			if (A[j] <= x) {
				i++;
				if(i!=j)
					swap<T>(A,i,j);
			}
		}
		i++;
		swap<T>(A,i,r);
		return i;
	}

	template<typename T>
	void swap(T* A, int l, int r) {
		T temp = A[l];
		A[l] = A[r];
		A[r] = temp;
	}

}

#endif
