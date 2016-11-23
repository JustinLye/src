//algorithms from CLRS ch.12 and 13

#include"dstree.h"


void ds::binary_tree::op::insert(ds::binary_tree::tree& T, ds::binary_tree::leaf* z) {
	ds::binary_tree::leaf* y = nullptr;
	ds::binary_tree::leaf* x = T.root;
	while (x != nullptr) {
		y = x;
		if (z->key < x->key) {
			x = x->left;
		} else {
			x = x->right;
		}
	}
	z->p = y;
	if (y == nullptr) {
		T.root = z;
	} else if (z->key < y->key) {
		y->left = z;
	} else {
		y->right = z;
	}
}

void ds::binary_tree::op::inorder_walk(std::ostream& s, ds::binary_tree::leaf* z) {
	if (z != nullptr) {
		inorder_walk(s, z->left);
		s << z->key << std::endl;
		inorder_walk(s, z->right);
	}
}

void ds::binary_tree::op::print_leaves(std::ostream& s, ds::binary_tree::leaf* z) {
	if (z != nullptr) {
		print_leaf(s, z);
		print_leaves(s, z->left);
		print_leaves(s, z->right);
	}
}

ds::binary_tree::leaf* ds::binary_tree::op::search(ds::binary_tree::leaf* x, int k) {
	if (x == nullptr) {
		return x;
	} else {
		ds::binary_tree::leaf* t = x;
		while (t != nullptr) {
			if(t->key == k)
				return t;
			else if (k < t->key) {
				t = t->left;
			} else {
				t = t->right;
			}
		}
	}
}

ds::binary_tree::leaf* ds::binary_tree::op::min(ds::binary_tree::leaf* x) {
	if (x == nullptr)
		return x;

	ds::binary_tree::leaf* t = x;
	while (t->left != nullptr) {
		t = t->left;
	}
	return t;
}

ds::binary_tree::leaf* ds::binary_tree::op::max(ds::binary_tree::leaf* x) {
	if(x == nullptr)
		return x;

	ds::binary_tree::leaf* t = x;
	while (t->right != nullptr) {
		t = t->right;
	}
	return t;
}

ds::binary_tree::leaf* ds::binary_tree::op::successor(ds::binary_tree::leaf* x) {
	if(x == nullptr)
		return x;

	ds::binary_tree::leaf* t = x;
	if(t->right != nullptr)
		return min(t->right);
	ds::binary_tree::leaf* y = t->p;
	while (y != nullptr && t == y->right) {
		t = y;
		y = y->p;
	}
	return y;
}


ds::binary_tree::leaf* ds::binary_tree::op::predecessor(ds::binary_tree::leaf* x) {
	if(x == nullptr)
		return x;
	ds::binary_tree::leaf* t = x;
	if(t->left != nullptr)
		return max(t->left);
	ds::binary_tree::leaf* y = t->p;
	while (y != nullptr && t == y->left) {
		t = y;
		y = y->p;
	}
	return y;
}

void ds::binary_tree::op::transplant(ds::binary_tree::tree& T, ds::binary_tree::leaf* u, ds::binary_tree::leaf* v) {
	if (u->p == nullptr) {
		//u is the root
		T.root = v;
	} else if (u == u->p->left) {
		//u is the left child, replace the left child of u's parent with v
		u->p->left = v;
	} else {
		//u is the right child, replace the right child of u's parent with v
		u->p->right = v;
	}
	if (v != nullptr) {
		//we allow v to be NIL. Update v if it is non-nil
		v->p = u->p;
	}
}

void ds::binary_tree::op::remove(ds::binary_tree::tree& T, ds::binary_tree::leaf* z) {
	if(z == nullptr)
		return;
	if(z->left == nullptr)
		transplant(T,z,z->right);
	else if(z->right == nullptr)
		transplant(T, z, z->left);
	else {
		ds::binary_tree::leaf* y = min(z->right);
		if (y->p != z) {
			transplant(T, y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		transplant(T, z, y);
		y->left = z->left;
		y->left->p = y;
	}
}

void ds::binary_tree::op::left_rotate(ds::binary_tree::tree& T, ds::binary_tree::leaf* x) {
	if(x == nullptr || x->right == nullptr)
		return;
	leaf* y = x->right;
	x->right = y->left;
	if(y->left != nullptr)
		y->left->p = x;
	y->left = x;
	if (x == T.root) {
		T.root = y;
	} else if (x == x->p->left) {
		x->p->left = y;
	} else {
		x->p->right = y;
	}
	y->p = x->p;
	x->p = y;
}

void ds::binary_tree::op::right_rotate(ds::binary_tree::tree& T, ds::binary_tree::leaf* x) {
	if(x == nullptr || x->left == nullptr)
		return;
	leaf* y = x->left;
	x->left = y->right;
	y->right = x;
	if (x == T.root) {
		T.root = y;
	} else if (x == x->p->left) {
		x->p->left = y;
	} else {
		x->p->right = y;
	}
	y->p = x->p;
	x->p = y;
}

void ds::binary_tree::op::print_leaf(std::ostream& s, ds::binary_tree::leaf* z) {
	if (z != nullptr) {
		if(z->p == nullptr)
			s << "ROOT: " << z->key << std::endl << '\t';
		else
			s << "LEAF: " << z->key << std::endl << '\t';
		s << "LEFT: ";
		if(z->left == nullptr)
			s << "\\" << std::endl << '\t';
		else
			s << z->left->key << std::endl << '\t';
		s << "RIGHT: ";
		if(z->right == nullptr)
			s << "\\" << std::endl;
		else
			s << z->right->key << std::endl;
	}
}

/*------------------------------------------------------*/
//////////////////////////////////////////////////////////
//  Red-Black Binary Trees                              //
//////////////////////////////////////////////////////////
/*------------------------------------------------------*/

void ds::rb_tree::op::insert(tree& T, leaf* z) {
	leaf* y = tree::nil;
	leaf* x = T.root;
	while (x != tree::nil) {
		y = x;
		if (x->key < z->key)
			x = x->right;
		else
			x = x->left;
	}
	z->p = y;
	if (y == tree::nil) {
		T.root = z;
	} else if(z->key < y->key) {
		y->left = z;
	} else {
		y->right = z;
	}
	z->left = tree::nil;
	z->right = tree::nil;
	//ensure the color is red
	z->color = RED;
	fix_up(T, z);
}

void ds::rb_tree::op::inorder_walk(std::ostream& s, leaf* z) {
	if (z != tree::nil) {
		inorder_walk(s, z->left);
		s << z->key << std::endl;
		inorder_walk(s, z->right);
	}
}

ds::rb_tree::leaf* ds::rb_tree::op::search(leaf* x, int k) {
	if (x == tree::nil) {
		return x;
	}
	ds::rb_tree::leaf* result = tree::nil;
	ds::rb_tree::leaf* y = x;
	while (y != tree::nil) {
		if (y->key == k) {
			return y;
		} else {
			if (y->key < k) {
				y = y->right;
			} else {
				y = y->left;
			}
		}
	}
	return result;
}

ds::rb_tree::leaf* ds::rb_tree::op::min(leaf* x) {
	if(x == tree::nil)
		return x;
	leaf* y = x;
	while (y->left != tree::nil)
		y = y->left;
	return y;
}

ds::rb_tree::leaf* ds::rb_tree::op::max(leaf* x) {
	if( x == tree::nil)
		return x;
	leaf* y = x;
	while(y->right != tree::nil)
		y = y->right;
	return y;
}

ds::rb_tree::leaf* ds::rb_tree::op::successor(leaf* x) {
	if(x == tree::nil)
		return x;
	if (x->right != tree::nil) {
		return min(x->right);
	} else {
		leaf* y = x->p;
		leaf* t = x;
		while (y != tree::nil && t == y->right) {
			t = y;
			y = y->p;
		}
		return y;
	}
}

ds::rb_tree::leaf* ds::rb_tree::op::predecessor(leaf* x) {
	if(x == tree::nil)
		return x;
	if(x->left != tree::nil)
		return max(x->left);
	else {
		leaf* x_copy = x;
		leaf* x_ancestors = x->p;
		//the first ancestor that is not the left child will be the will be predecessor
		while (x_ancestors != tree::nil && x_copy == x_ancestors->left) {
			x_copy = x_ancestors;
			x_ancestors = x_ancestors->p;
		}
		return x_ancestors;
	}
}

void ds::rb_tree::op::transplant(tree& T, leaf* u, leaf* v) {
	if (u == T.root) {
		T.root = v;
	} else if (u == u->p->left) {
		u->p->left = v;
	} else {
		u->p->right = v;
	}
	 v->p = u->p;
}



void ds::rb_tree::op::left_rotate(tree& T, leaf* x) {
	leaf* y = x->right;
	x->right = y->left;
	y->left = x;
	if(x->right != tree::nil)
		x->right->p = x;
	if(x == T.root)
		T.root = y;
	else if(x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	y->p = x->p;
	x->p = y;
}

void ds::rb_tree::op::right_rotate(tree& T, leaf* x) {
	leaf* y = x->left;
	x->left = y->right;
	y->right = x;
	if(x->left != tree::nil)
		x->left->p = x;
	if(x == T.root)
		T.root = y;
	else if(x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	y->p = x->p;
	x->p = y;
}

void ds::rb_tree::op::print_leaf(std::ostream& s, ds::rb_tree::leaf* z) {
	if (z != tree::nil) {
		if (z->p == tree::nil)
			s << "ROOT: " << z->key << " COLOR: " << z->color << std::endl << '\t';
		else
			s << "LEAF: " << z->key << " COLOR: " << z->color << std::endl << '\t';
		s << "LEFT: ";
		if (z->left == tree::nil)
			s << "\\" << " COLOR: " << std::endl << '\t';
		else
			s << z->left->key << " COLOR: " << z->left->color << std::endl << '\t';
		s << "RIGHT: ";
		if (z->right == tree::nil)
			s << "\\" << " COLOR: " << std::endl;
		else
			s << z->right->key << " COLOR: " << z->right->color << std::endl;
	}
}

void ds::rb_tree::op::print_leaves(std::ostream& s, ds::rb_tree::leaf* z) {
	if (z != tree::nil) {
		print_leaf(s, z);
		print_leaves(s, z->left);
		print_leaves(s, z->right);
	}
}


/*
	Assumes T is a Red-Black tree w/o violations prior to the
	insertion if z.

	--> If property 2 is violated, then the red root must be the
	    newly added node z, which is the only internal node in 
		the tree.
	--> If property 4 is violated, then the violation only occurs
	    because z and z.p are red

	CASE 1: z's uncle y is red.
			We know z, z.p, and y are red and z.p.p is black.
			Property 4 can be maintained by coloring z.p and y black
			and coloring z.p.p red.
			Repeat the while loop where z = z.p.p
			In the next iteration z' = z.p.p.
			If z' is the root then z'.p is black.
			If z' is not the root and z'.p is black there is no further
			violations of property 4.
			If z'.p is red, then an violation of property 4 was introduced
			by case 1.
	CASE 2: z's uncle y is black and z is a right child
			If z is the right child of z.p then we left rotate z,
			which transforms the situation to case 3.
	CASE 3: z's uncle y is black and z is a left child
*/

void ds::rb_tree::op::fix_up(tree& T, leaf* z) {
	//variable to store uncle node
	leaf* y = tree::nil;
	//test if z's parent is red.
	while (z->p->color == RED) {
		//test for case that z's parent is the left child
		if (z->p == z->p->p->left) {
			//set the y equal to z's uncle
			y = z->p->p->right;
			//test if y is red
			if (y->color == RED) {
				//color z's uncle and parent black
				y->color = BLACK;
				z->p->color = BLACK;
				//color z's grandparent red
				z->p->p->color = RED;
				//point to z to its grandparent and repeat the loop
				z = z->p->p;
			} else {
				//if case 2, then transform to case 3
				if (z == z->p->right) {
					z = z->p;
					left_rotate(T, z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				right_rotate(T, z->p->p);
			}
		} else {
			y = z->p->p->left;
			if (y->color == RED) {
				y->color = BLACK;
				z->p->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			} else {
				if (z == z->p->left) {
					z = z->p;
					right_rotate(T, z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				left_rotate(T, z->p->p);
			}
		}
	}
	T.root->color = BLACK;
}

void ds::rb_tree::op::remove(tree& T, leaf* z) {
	Color original_color = z->color;
	leaf* y = z;
	leaf* x = T.nil;
	if (z->left == T.nil) {
		std::cout << "left is t.nil" << std::endl;
		x = z->right;
		op::transplant(T, z, z->right);
	} else if (z->right == T.nil) {
		x = z->left;
		op::transplant(T, z, z->left);
	} else {
		y = op::min(z->right);
		original_color = y->color;
		x = y->right;
		if (y->p == z) {
			x->p = y;
		} else {
			op::transplant(T, y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		op::transplant(T, z, y);
		y->left = z->left;
		y->left->p = y;
		y->color = z->color;
	}
	std::cout << "color: " << original_color << std::endl;
	if (original_color == BLACK) {
		delete_fix_up(T,x);
	}
	T.nil->p = T.nil;
	T.nil->left = T.nil;
	T.nil->right = T.nil;
	T.root->p = T.nil;
}

void ds::rb_tree::op::delete_fix_up(tree& T, leaf* x) {
	leaf* w = nullptr;
	while (x != T.root && x->color == BLACK) {
		if (x == x->p->left) {
			w = x->p->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				op::left_rotate(T, x->p);
				w = x->p->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->p;
			} else {
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					op::right_rotate(T, w);
					w = x->p->right;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				op::left_rotate(T, x->p);
				x = T.root;
			}
		} else {
			w = x->p->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				op::right_rotate(T, x->p);
				w = x->p->left;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->p;
			} else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					left_rotate(T,w);
					w = x->p->left;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				op::right_rotate(T, x->p);
				x = T.root;
			}
		}
	}
	x->color = BLACK;
}