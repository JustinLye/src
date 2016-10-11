#if !defined(__JEL_RANDOM_HEADER__)
#include"random.h"
#endif		
#if !defined(__JEL_SORT_HEADER__)
#define __JEL_SORT_HEADER__
#if defined(JEL_BUILD_DLL)
	#define CLASS_SORT __declspec(dllexport)
#else
	#define CLASS_SORT __declspec(dllimport)
#endif	
#include<ctime>
#include<random>

namespace jel {
	template<class ArrayType, typename IndexType = unsigned int>
	class CLASS_SORT sort {
	public:
		sort() {
			jel::random_seed(time(NULL));
		}
		void sort_array(ArrayType* A, IndexType start_index, IndexType end_index);
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
//#define __JEL_RANDOM_HEADER__
#include"sort.cpp"
#endif
}
#endif