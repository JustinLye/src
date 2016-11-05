#if !defined(__JEL_BOUNDER_CPP__)
#define __JEL_BOUNDER_CPP__

#if !defined(__JEL_BOUNDER_HEADER__)
#include "bounder.h"
#endif

//Returns an array of bounds.
//Ex: bounder<int>(100,2) returns pointer to array { (0,49),(50,99) }
//WARINING: caller is responsible for release of memory allocated to returned pointer.
template<typename IndexType>
jel::bounds<IndexType>* jel::bounder<IndexType>(IndexType array_size, int splits) {
	jel::bounds<IndexType>* result = new jel::bounds<IndexType>[splits]; //allocate resources
	IndexType range_size = ceil((array_size - 1) / splits);
	long idx = 0; //index increment
	IndexType bnd = 0; //bound value
	for (idx = 0; idx < (splits - 1); idx++) {
		result[idx].lower(bnd);
		result[idx].upper(bnd+range_size);
		bnd += range_size+1;
	}
	result[idx].lower(bnd);
	(bnd < (array_size - 1)) ? result[idx].upper(bnd + ((array_size-1)-bnd)) : result[idx].upper(bnd);
	return result;
}

template<typename IndexType>
jel::bounds<IndexType>* jel::bounder<IndexType>(IndexType lower, IndexType upper, int splits) {
	jel::bounds<IndexType>* result = new jel::bounds<IndexType>[splits];
	IndexType range_size = ceil(((upper - lower)-1)/ splits);
	long idx = 0;
	IndexType bnd = lower;
	for (idx = 0; idx < (splits - 1); idx++) {
		result[idx].lower(bnd);
		result[idx].upper(bnd+range_size);
		bnd += range_size + 1;
	}
	result[idx].lower(bnd);
	(bnd < (upper - 1)) ? result[idx].upper(bnd + ((upper-1)-bnd)) : result[idx].upper(bnd);
	return result;
}

#endif