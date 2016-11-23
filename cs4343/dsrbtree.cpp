//algorithms from CLRS ch.12 and 13
#include"dsrbtree.h"

using namespace ds::rb_tree;

Color::Color() : _color(RED) {}
Color::Color(int c) : _color(c) {
	if (_color != RED && _color != BLACK)
		throw std::runtime_error("color must be red or black");
}
int Color::color() const { return _color; }
void Color::color(int c) {
	if (c != RED && c != BLACK)
		throw std::runtime_error("color must be red or black");
	_color = c;
}

const char* Color::to_string() const {
	if(_color == RED)
		return "RED";
	else
		return "BLACK";
}

Color& ds::rb_tree::Color::operator=(int c) {
	try {
		this->color(c);
	} catch (...) {
		throw;
	}
	return *this;
}

bool ds::rb_tree::Color::operator==(int c) {
	return (this->_color == c);
}
bool ds::rb_tree::Color::operator!=(int c) {
	return (this->_color != c);
}

leaf::leaf() :
	key(0),
	p(ds::rb_tree::tree::nil),
	left(ds::rb_tree::tree::nil),
	right(ds::rb_tree::tree::nil),
	color(Color(RED)) {}

leaf::leaf(int k) :
	key(k),
	p(ds::rb_tree::tree::nil),
	left(ds::rb_tree::tree::nil),
	right(ds::rb_tree::tree::nil),
	color(Color(RED)) {}

leaf::leaf(int k, int c) :
	key(k),
	p(ds::rb_tree::tree::nil),
	left(ds::rb_tree::tree::nil),
	right(ds::rb_tree::tree::nil),
	color(Color(c)) {}

leaf* tree::nil = new leaf(0, BLACK);

tree::tree() : root(nullptr) {
	
	nil->left = nil;
	nil->right = nil;
	nil->p = nil;
	root = nil;
}