#include<iostream>
#if !defined(__DS_BINTREE_HEADER__)
#define __DS_BINTREE_HEADER__

namespace ds {
	namespace binary_tree {
		class leaf {
		public:
			int key;
			leaf* p;
			leaf* left;
			leaf* right;
			leaf(int);
			leaf();
		private:
			
			leaf(const leaf&) {}
			leaf(leaf&&) {}
		};
		class tree {
		public:
			leaf* root;
			tree();
		private:
			tree(const tree&) {}
			tree(leaf&&) {}
			
		};
	};
};

#endif
