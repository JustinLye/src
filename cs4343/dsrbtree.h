//algorithms from CLRS ch.12 and 13
#include<iostream>
#include<stdexcept>

#if !defined(__DS_RB_TREE_HEADER__)
#define __DS_RB_TREE_HEADER__

namespace ds {
	namespace rb_tree {
		const int RED = 0;
		const int BLACK = 1;
		class Color {
		public:
			int color() const;
			void color(int c);
			const char* to_string() const;
			Color();
			Color(int);
			Color& operator=(int c);
			bool operator==(int c);
			bool operator!=(int c);
	
			friend std::ostream& operator<<(std::ostream& s, const Color& c) {
				c.print(s);
				return s;
			}
			friend std::ostream& operator<<(std::ostream& s, const Color* const c) {
				c->print(s);
				return s;
			}
		protected:
			int _color;
			void print(std::ostream& s) const {
				s << to_string();
			}
		};
		
		class leaf {
		public:
			int key;
			Color color;
			leaf* p;
			leaf* left;
			leaf* right;
			leaf();
			leaf(int);
			leaf(int, int);
		};
		
/*
Red-Black Properties:
1. Every node is either red or black
2. The root is black
3. Every leaf (NIL) is black
4. If a node is red, then both its childern are black
5. For each node, all simple paths from the node to
   descendant leaves contain the same number of
   black nodes
*/

		class tree {
		public:
			static leaf* nil;
			leaf* root;
			
			tree();
		};

	};
};


#endif
