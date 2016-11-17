#include<iostream>
#include<fstream>

#include"dshash.h"
#include"dsarray.h"

//ds::Array<int> keys = { 15,21,35,4,10,25,17,82,56 };
ds::Array<int> keys = { 10, 22, 31, 4, 15, 28, 17, 88, 59 };
const char* q1_output = "CS4343 - HW6 - Q2.txt";

int h(int,int);

int main(int argc, char* argv[]) {
	ds::hash_table::chained l(7);
	std::cout << l << std::endl;
	for (int i = 0; i < keys.length(); i++) {
		l.hash_insert(keys[i]);
	}
	std::cout << l << std::endl;
	return 0;
}
int h(int k, int m) { return k % 7; }