#include"dsbintree.h"

using namespace ds::binary_tree;

leaf::leaf() : key(0), p(nullptr), left(nullptr), right(nullptr) {}
leaf::leaf(int k) : key(k), p(nullptr), left(nullptr), right(nullptr) {}

tree::tree() : root(nullptr) {}