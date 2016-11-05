

#if !defined(__JEL_SORT_CPP__)
#define __JEL_SORT_CPP__

#if !defined(__JEL_SORT_HEADER__)
#include "sort.h"
#endif

template<class ArrayType, typename IndexType>
void jel::sort<ArrayType, IndexType>::sort_array(ArrayType* A, IndexType start_index, IndexType end_index) {
	std::cout << "i'm sorta busy right now..\n";
	_qsort(A, start_index, end_index);
}

template<class ArrayType, typename IndexType>
void jel::sort<ArrayType, IndexType>::_qsort(ArrayType* A, IndexType start_idx, IndexType end_idx) {
	if (start_idx < end_idx) {
		IndexType p = _partition(A, start_idx, end_idx);
		_qsort(A,start_idx, p-1);
		_qsort(A,p+1,end_idx);
	}
}
template<class ArrayType, typename IndexType>
IndexType jel::sort<ArrayType, IndexType>::_partition(ArrayType* A, IndexType start_idx, IndexType end_idx) {
	_random_swap(A, start_idx, end_idx);
	IndexType wall = start_idx - 1;
	ArrayType key = A[end_idx];
	for (IndexType curr = start_idx; curr < end_idx; curr++) {
		if (A[curr] <= key) {
			wall++;
			if(wall != curr)
				_swap(A,wall,curr);
		}
	}
	wall++;
	if(wall != end_idx)
		_swap(A,wall,end_idx);
	return wall;
}


#endif
