#if !defined(__JEL_BOUND_SET_HEADER__)
#define __JEL_BOUND_SET_HEADER__
#include"bounder.h"

namespace jel {
	template<class IndexType>
	class bound_set {
	public:
		bound_set() : _set(nullptr), _lower(0), _upper(0) {}
		bound_set(const bound_set& b) :
			_set(jel::bounder<IndexType>(b._lower, b._upper, b._splits)),
			_lower(b._lower),
			_upper(b._upper),
			_array_size(b._array_size),
			_splits(b._splits) {}
		bound_set(bound_set&& b) :
			_set(std::move(b._set)),
			_lower(std::move(b._lower)),
			_upper(std::move(b._upper)),
			_array_size(std::move(b._array_size)),
			_splits(std::move(b._splits)) {}
		bound_set(IndexType ArraySize, int Splits) :
			_set(jel::bounder<IndexType>(ArraySize, Splits)),
			_lower(0),
			_upper(ArraySize),
			_array_size(ArraySize),
			_splits(Splits) {}
		bound_set(IndexType Lower, IndexType Upper, int Splits) :
			_set(jel::bounder<IndexType>(Lower, Upper, Splits)),
			_lower(Lower),
			_upper(Upper),
			_array_size(Upper - Lower),
			_splits(Splits) {}

		~bound_set() {
			if(this->_set != nullptr)
				delete[] this->_set;
		}

		inline IndexType lower() const { return _lower; }
		inline IndexType upper() const { return _upper; }
		inline IndexType array_size() const { return _array_size; }
		inline int splits() const { return _splits; }
		void rebound(IndexType ArraySize, int Splits);
		void rebound(IndexType Lower, IndexType Upper, int Splits);

		inline bounds<IndexType>& operator[](IndexType loc) { return _set[loc]; }
		bound_set<IndexType>& operator()(IndexType ArraySize, int Splits);
		bound_set<IndexType>& operator()(IndexType Lower, IndexType Upper, int Splits);
		inline friend std::ostream& operator<<(std::ostream& s, const bound_set<IndexType>& b) {
			b.print(s);
			return s;
		}

	private:
		bounds<IndexType>* _set;
		IndexType _lower;
		IndexType _upper;
		IndexType _array_size;
		int _splits;
		inline void print(std::ostream& s) const {
			for(IndexType i = 0; i < _splits; i++)
				s << _set[i] << ' ';
		}
		//inline void print(std::ostream& s) {
		//	for (IndexType i = 0; i < _splits; i++)
		//		s << _set[i] << ' ';
		//}
	};
}

#if !defined(__JEL_BOUND_SET_CPP__)
#include"bound_set.cpp"
#endif

#endif