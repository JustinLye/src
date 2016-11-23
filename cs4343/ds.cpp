#include<iostream>
#include<fstream>
#include<iomanip>
#include<vector>
#include"dsarray.h"
#include"dsbintree.h"
#include"dstree.h"
#include"dsrbtree.h"
using namespace ds;
ds::Array<int> keys = { 12,44,13,88,23,94,11,38,20,16,5,36,42,37,39}; 
ds::Array<int> dkeys = { 17,16,18,14,5,3,15,12,7,4 };




namespace ds {
	namespace binary_tree {
		void test();
	};
	namespace rb_tree {
		void test();
	};
};
int main(int argc, char* argv[]) {
	using namespace rb_tree;
	if (argc > 1) {
		std::ifstream infile;
		infile.open(argv[1]);
		std::vector<int> v;
		int x = 0;
		infile >> x;
		while (!infile.eof()) {
			v.push_back(x);
			infile >> x;
		}
		v.push_back(x);
		keys.resize(v.size());
		for (int i = 0; i < keys.length(); i++) {
			keys[i] = v[i];
		}
		test();
	} else {
		test();
	}
	return 0;
}

namespace ds {
	namespace binary_tree {
		void test() {
			std::cout << "Binary Tree Test" << std::endl << std::endl;
			leaf* leaves = new leaf[keys.length()];
			tree t;
			for (int i = 0; i < keys.length(); i++) {
				leaves[i].key = keys[i];
			}

			for (int i = 0; i < keys.length(); i++) {
				op::insert(t, &leaves[i]);
			}

			op::inorder_walk(std::cout, t.root);
			op::print_leaves(std::cout, t.root);
			delete[] leaves;
		}
	};
	namespace rb_tree {
		void test() {
			std::ofstream outfile;
			outfile.open("output.txt");
			outfile << "Red-Black Tree Test" << std::endl << std::endl;
			leaf* leaves = new leaf[keys.length()];
			leaf* dleaves = new leaf[dkeys.length()];
			tree t;
			for (int i = 0; i < keys.length(); i++) {
				leaves[i].key = keys[i];
			}
			for (int i = 0; i < dkeys.length(); i++) {
				dleaves[i].key = dkeys[i];
			}

			for (int i = 0; i < keys.length(); i++) {
				outfile << "inserting key " << leaves[i].key << " interation " << i << std::endl;
				op::insert(t, &leaves[i]);
				op::print_leaves(outfile, t.root);
				outfile << std::endl;
			}
			outfile << "before" << std::endl << std::endl;
			op::print_leaves(outfile, t.root);

			for (int i = 0; i < dkeys.length(); i++) {
				outfile << "deleting key " << dleaves[i].key << " iteration " << i << std::endl;
				op::remove(t, op::search(t.root, dleaves[i].key));
				op::print_leaves(outfile, t.root);
				outfile << std::endl;
			}
			
			outfile << std::endl << "after" << std::endl << std::endl;
			op::print_leaves(outfile, t.root);



			outfile.close();
			delete[] leaves;
		}
	};
};