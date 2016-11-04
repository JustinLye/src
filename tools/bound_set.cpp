#if !defined(__JEL_BOUND_SET_CPP__)
#define __JEL_BOUND_SET_CPP__

#if !defined(__JEL_BOUND_SET_HEADER__)
#include "bound_set.h"
#endif

template<typename IndexType>
void jel::bound_set<IndexType>::rebound(IndexType ArraySize, int Splits) {
	if(_array_size == ArraySize && _splits == Splits)
		return;

	this->_array_size = ArraySize;
	this->_splits = Splits;
	this->_lower = 0;
	this->_upper = ArraySize;

	if(this->_set != nullptr)
		delete[] this->_set;

	_set = jel::bounder<IndexType>(ArraySize, Splits);
}

template<typename IndexType>
void jel::bound_set<IndexType>::rebound(IndexType Lower, IndexType Upper, int Splits) {
	if(this->_lower == Lower && this->_upper == Upper && this->_splits == Splits)
		return;

	this->_array_size = Upper - Lower;
	this->_splits = Splits;
	this->_lower = Lower;
	this->_upper = Upper;

	if(this->_set != nullptr)
		delete[] this->_set;
	_set = jel::bounder<IndexType>(Lower, Upper, Splits);
}

template<typename IndexType>
jel::bound_set<IndexType>& jel::bound_set<IndexType>::operator()(IndexType ArraySize, int Splits) {
	this->rebound(ArraySize, Splits);
	return *this;
}

template<typename IndexType>
jel::bound_set<IndexType>& jel::bound_set<IndexType>::operator()(IndexType Lower, IndexType Upper, int Splits) {
	this->rebound(Lower, Upper, Splits);
	return *this;
}

#endif