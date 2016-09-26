#if !defined(__JEL_QSORT_HEADER__)
#define __JEL_QSORT_HEADER__

#include<iostream>

namespace jel {
	//quicksort algorithm taken from Introduction to Algorithms 3rd Edition page 171.
	template<typename T>
	void quicksort(T* A, long p, long r) {
		if (p < r) {
			long q = parition<T>(A,p,r);
			quicksort<T>(A,p,q-1);
			quicksort<T>(A,q+1,r);
		}
	}
	template<typename T>
	long parition(T* A, long p, long r) {
		T& x = A[r];
		long i = p - 1;
		for (long j = p; j < r; j++) {
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
	void swap(T* A, long l, long r) {
		T temp = A[l];
		A[l] = A[r];
		A[r] = temp;
	}

}

#endif
