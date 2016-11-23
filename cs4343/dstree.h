//algorithms from CLRS ch.12 and 13
#if !defined(__DS_TREE_HEADER__)
#define __DS_TREE_HEADER__
#include"dsbintree.h"
#include"dsrbtree.h"
namespace ds {
	namespace binary_tree {
		class op {
		public:
			static void insert(tree& T, leaf* z);
			static void inorder_walk(std::ostream& s, leaf* z);
			static leaf* search(leaf* x, int k);
			static leaf* min(leaf* x);
			static leaf* max(leaf* x);
			static leaf* successor(leaf* x);
			static leaf* predecessor(leaf* x);
			static void transplant(tree& T, leaf* u, leaf* v);
			static void remove(tree& T, leaf* z);
			static void print_leaf(std::ostream& s, leaf* z);
			static void print_leaves(std::ostream& s, leaf* z);
			static void left_rotate(tree& T, leaf* x);
			static void right_rotate(tree& T, leaf* x);
		private:
			op() {}
			op(const op&) {}
			op(op&&) {}
		};
	};
	namespace rb_tree {
		class op {
		public:
			static void insert(tree& T, leaf* z);
			static void inorder_walk(std::ostream& s, leaf* z);
			static leaf* search(leaf* x, int k);
			static leaf* min(leaf* x);
			static leaf* max(leaf* x);
			static leaf* successor(leaf* x);
			static leaf* predecessor(leaf* x);
			static void transplant(tree& T, leaf* u, leaf* v);
			static void remove(tree& T, leaf* z);
			static void print_leaf(std::ostream& s, leaf* z);
			static void print_leaves(std::ostream& s, leaf* z);
			static void left_rotate(tree& T, leaf* x);
			static void right_rotate(tree& T, leaf* x);
			static void fix_up(tree& T, leaf* z);
			static void delete_fix_up(tree& T, leaf* z);
		private:
			op() {}
			op(const op&) {}
			op(op&&) {}
		};
	};
};

#endif
