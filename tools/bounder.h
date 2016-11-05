#if !defined(__JEL_BOUNDER_HEADER__)
#define __JEL_BOUNDER_HEADER__

namespace jel {
	template<typename IndexType>
	class bounds {
	public:
		//default constructor
		bounds() : _lower(0), _upper(0) {}
		//copy constructor
		bounds(const bounds& b) : _lower(b._lower), _upper(b._upper) {}
		//move constructor
		bounds(bounds&& b) : _lower(std::move(b._lower)), _upper(std::move(b._upper)) {}
		//upper bound constructor
		bounds(IndexType Upper) : _lower(0), _upper(Upper) {}
		//ranged constructor
		bounds(IndexType Lower, IndexType Upper) : _lower(Lower), _upper(Upper) {}

		inline IndexType lower() const { return _lower; }
		inline IndexType upper() const { return _upper; }
		inline void lower(IndexType val) { _lower = val; }
		inline void upper(IndexType val) { _upper = val; }
		inline friend std::ostream& operator<<(std::ostream& s, const bounds& b) {
			b.print(s);
			return s;
		}

	private:
		//members
		IndexType _lower;
		IndexType _upper;

		//methods
		inline void print(std::ostream& s) const {
			s << "(" << _lower << ", " << _upper << ")";
		}
	};

	template<typename IndexType>
	class bound_index {
	public:
		bound_index(IndexType Upper) : _idx(0), _lower(0), _upper(Upper) {}
		bound_index(IndexType Lower, IndexType Upper) : _idx(Lower), _lower(Lower), _upper(Upper) {}

		inline IndexType operator++() { (_idx != _upper) ? return _idx++ : return _idx; }
		inline IndexType operator()() { return _idx; }

		IndexType operator(int)() { return int(_idx); }
		
	private:
		bound_index() {}
		bound_index(const bound_index& b) {}
		bound_index(bound_index&& b) {}
		IndexType _idx;
		IndexType _lower;
		IndexType _upper;

		void print(std::ostream& s) const {
			s << _idx;
		}

	};

	template<typename IndexType>
	bounds<IndexType>* bounder(IndexType array_size, int splits);

	template<typename IndexType>
	bounds<IndexType>* bounder(IndexType lower, IndexType lpper, int splits);

#if !defined(__JEL_BOUNDER_CPP__)
#include "bounder.cpp"
#endif

}

#endif