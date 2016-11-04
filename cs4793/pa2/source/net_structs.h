//This header contains structures taken from class examples
//Modifications to the example structure are efforts to understand
//the examples better.

#include<Eigen/Core>

#if !defined(__AI_NET_STRUCTS_HEADER__)
#define __AI_NET_STRUCTS_HEADER__

namespace ai {
	
	typedef Eigen::MatrixXd mat;
	typedef Eigen::RowVectorXd vec;
	typedef Eigen::Ref<Eigen::MatrixXd> rmat;
	typedef Eigen::Ref<Eigen::RowVectorXd> rvec;
	typedef Eigen::MatrixXd* mat_ptr;
	typedef Eigen::RowVectorXd* vec_ptr;

	//Node_Linkage is a simplified version of Links, meant to be inherited
	class Node_Linkage {
	public:
		Node_Linkage(mat_ptr, vec_ptr);
		Node_Linkage(const Node_Linkage&);

		mat_ptr weights;
		vec_ptr bias;

		friend std::ostream& operator<<(std::ostream& s, const Node_Linkage& n);

	private:
		Node_Linkage() {}
		Node_Linkage(Node_Linkage&& n) {}
	};

	//Node_Layer is a simplified version of Nodes, meant to be inherited
	class Node_Layer {
	public:
		Node_Layer(mat_ptr);
		Node_Layer(const Node_Layer&);
		
		mat_ptr node_values;

		friend std::ostream& operator<<(std::ostream& s, const Node_Layer& n);

	private:
		Node_Layer() {}
		Node_Layer(Node_Layer&& n) {}
	};
	
	class Network_Layer {
	public:
		Network_Layer(Node_Linkage* node_linkage, Node_Layer* input_layer_ptr, Node_Layer* output_layer_ptr);
		Network_Layer(const Network_Layer&);
		Node_Linkage* layer_links;
		Node_Layer* input_layer;
		Node_Layer* output_layer;

		friend std::ostream& operator<<(std::ostream& s, const Network_Layer& n);

	private:
		Network_Layer() {}
		Network_Layer(Network_Layer&& n) {}
	};

}

#endif