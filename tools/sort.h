#if !defined(__JEL_SORT_HEADER__)
#define __JEL_SORT_HEADER__
#include<ctime>
#include<random>
#include"random.h"

namespace jel {
	template<class ArrayType, typename IndexType = int>
	class sort {
	public:
		sort() : {
			jel::random_seed(time(NULL));
		}

		inline void sort_array(ArrayType* A, IndexType start_index, IndexType end_index) {
			_qsort(A, start_index, end_index);
		}
		void merge_array(ArrayType* A, IndexType Ls, IndexType Le, IndexType Rs, IndexType Re, IndexType JumpIndex -1);
	private:
		void _qsort(ArrayType* A, IndexType start_idx, IndexType end_idx);
		IndexType _partition(ArrayType* A, IndexType start_idx, IndexType end_idx);
		inline void _random_swap(ArrayType* A, IndexType start_idx, IndexType end_idx) {
			IndexType random_idx = jel::random(start_idx, end_idx);
			_swap(A, random_idx, end_idx);
		}
		inline void _swap(ArrayType* A, IndexType left_idx, IndexType right_idx) {
			ArrayType placeholder = std::move(A[left_idx]);
			A[left_idx] = std::move(A[right_idx]);
			A[right_idx] = std::move(placeholder);
		}
	};
#if !defined(__JEL_SORT_CPP__)
#include"sort.cpp"
#endif
}
#endif