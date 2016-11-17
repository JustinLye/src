#include<iostream>
#include<fstream>

#include"dshash.h"
#include"dsarray.h"

//ds::Array<int> keys = { 15,21,35,4,10,25,17,82,56 };
ds::Array<int> keys = { 10, 22, 31, 4, 15, 28, 17, 88, 59 };
const char* q1_output = "CS4343 - HW6 - Q1.txt";
int main(int argc, char* argv[]) {
	
	ds::hash::open_addressing::linear_probe T(11, ds::hash::open_addressing::default_nil());
	ds::hash::open_addressing::quadratic_probe Q(11, ds::hash::open_addressing::default_nil(), 1, 3);
	ds::hash::open_addressing::double_hash D(11, ds::hash::open_addressing::default_nil(), 10);
	std::ofstream outfile;
	outfile.open(q1_output);
	outfile << "CS4343 - HW6 - Q1 - Justin Lye" << std::endl << std::endl << "Linear Probing:" << std::endl;
	for (int i = 0; i < keys.length(); i++) {
		T.hash_insert(keys[i], &outfile);
	}
	outfile << std::endl << "Hash Table after inserting with Linear Probing hash function: " << std::endl << T;
	outfile << std::endl << std::endl << "Quadradic Probing:" << std::endl;
	for (int i = 0; i < keys.length(); i++) {
		Q.hash_insert(keys[i], &outfile);
	}
	outfile << std::endl << "Hash Table after inserting with Quadratic Probing hash function: " << std::endl << Q;
	outfile << std::endl << std::endl << "Double Hashing: " << std::endl;
	for (int i = 0; i < keys.length(); i++) {
		D.hash_insert(keys[i], &outfile);
	}
	outfile << std::endl << "Hash Table after inserting with Double hash function: " << std::endl << D;
	outfile.close();
	return 0;
}
