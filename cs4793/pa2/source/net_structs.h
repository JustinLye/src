//This header contains structures taken from class examples
//Modifications to the example structure are efforts to understand
//the examples better.

#include<Eigen/Core>
#include<vector>
#include<set>
#include<map>
#include"pa_util.h"

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
		
		mat_ptr network_value;
		
		friend std::ostream& operator<<(std::ostream& s, const Node_Layer& n);

	private:
		Node_Layer() {}
		Node_Layer(Node_Layer&& n) {}
	};
	
	class Output_Node_Layer : private Node_Layer {
	public:
		Output_Node_Layer(mat_ptr, mat_ptr, mat_ptr);
		Output_Node_Layer(const Output_Node_Layer&);
		
		mat_ptr network_activation;
		mat_ptr network_activation_prime;
		friend std::ostream& operator<<(std::ostream&, const Output_Node_Layer&);

	private:
		Output_Node_Layer() = delete;
		Output_Node_Layer(Output_Node_Layer&&) = delete;
	};


	class Node_Linkage_Delta : private Node_Linkage {
	public:
		Node_Linkage_Delta(mat_ptr, vec_ptr, mat_ptr, vec_ptr);
		Node_Linkage_Delta(const Node_Linkage&, mat_ptr, vec_ptr);
		Node_Linkage_Delta(const Node_Linkage_Delta&);
		ai::mat_ptr weights_delta;
		ai::vec_ptr bias_delta;
	private:
		Node_Linkage_Delta() = delete;
		Node_Linkage_Delta(Node_Linkage_Delta&&) = delete;
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

	struct Layer_Info {
		int input_rows;
		int input_dims;
		int output_dims;
		ai::mat weights;
		ai::vec bias;
		ai::mat input;
		ai::mat output;
		Layer_Info() {}
		Layer_Info(const Layer_Info&);
		Layer_Info(int, int, int, const ai::mat&, const ai::vec&, const ai::mat&, const ai::mat&);
	};

	struct Training_Info : Layer_Info {
		int target_dims;
		double in_target;
		double out_target;
		ai::mat targets;
		ai::mat errors;
		Training_Info() {}
		Training_Info(const Layer_Info&, int, double, double, const ai::mat&, const ai::mat&);
		Training_Info(int, int, int, const ai::mat&, const ai::vec&, const ai::mat&, const ai::mat&, int, double, double, const ai::mat&, const ai::mat&);

	};


}

#endif