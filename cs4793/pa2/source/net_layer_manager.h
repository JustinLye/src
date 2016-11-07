#include<vector>
#include<fstream>
#if !defined(__AI_NET_LAYER_MANAGER_HEADER__)
#define __AI_NET_LAYER_MANAGER_HEADER__
#include "noise.h"
#include "net_structs.h"

namespace nn {
#define AI_GAUSSIAN_NOISE 0x0040
#define AI_ZERO_OUT_NOISE 0x0041

	class Layer_Manager {
	public:
		Layer_Manager(int input_rows, int input_dims, int output_dims);
		Layer_Manager(std::istream&, int, int = 0);
		~Layer_Manager();

		nn::Network_Layer* layer;

		//reads data from file. Any information in current data is discarded.
		virtual void get_data(std::istream&, int = 0, int = -1, bool = true);
		void initialize_links();
		void add_input_noise(int = AI_GAUSSIAN_NOISE, double = -1.0);
		virtual void feed_forward();
	protected:
		int _input_rows;
		int _input_dims;
		int _output_dims;
		nn::mat _weights;
		nn::vec _bias;
		nn::mat _input_values;
		nn::mat _output_values;
		nn::mat _activation_values;
		nn::mat _derivative_values;
		nn::Output_Node_Layer _output_node_layer;
		nn::Node_Linkage _links;
		nn::Node_Layer _input_layer;
		nn::Node_Layer _output_layer;
		nn::noise _noise;

		Layer_Manager(std::istream&, int, bool, int = 0); //constructor used by inherited class to skip reading the input file

		virtual bool _get_input(std::istream&, int, int, bool);
		void _backup_info(nn::Layer_Info&);
		void _restore_info(const nn::Layer_Info&);

	private:
		Layer_Manager() = delete;
		Layer_Manager(Layer_Manager&&) = delete;


	};
}

#endif