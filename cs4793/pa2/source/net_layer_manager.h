#include<vector>
#include<fstream>
#if !defined(__AI_NET_LAYER_MANAGER_HEADER__)
#define __AI_NET_LAYER_MANAGER_HEADER__
#include "noise.h"
#include "net_structs.h"

namespace ai {
#define AI_GAUSSIAN_NOISE 0x0040
#define AI_ZERO_OUT_NOISE 0x0041

	class Layer_Manager {
	public:
		Layer_Manager(int input_rows, int input_dims, int output_dims);
		Layer_Manager(std::istream&, int, int = 0);
		~Layer_Manager();

		ai::Network_Layer* layer;

		//reads data from file. Any information in current data is discarded.
		virtual void get_data(std::istream&, int = 0, int = -1, bool = true);
		void initialize_links();
		void add_input_noise(int = AI_GAUSSIAN_NOISE, double = -1.0);
		virtual void feed_forward();
	protected:
		int _input_rows;
		int _input_dims;
		int _output_dims;
		ai::mat _weights;
		ai::vec _bias;
		ai::mat _input_values;
		ai::mat _output_values;
		ai::mat _activation_values;
		ai::mat _derivative_values;
		ai::Output_Node_Layer _output_node_layer;
		ai::Node_Linkage _links;
		ai::Node_Layer _input_layer;
		ai::Node_Layer _output_layer;
		ai::noise _noise;

		Layer_Manager(std::istream&, int, bool, int = 0); //constructor used by inherited class to skip reading the input file

		virtual bool _get_input(std::istream&, int, int, bool);
		void _backup_info(ai::Layer_Info&);
		void _restore_info(const ai::Layer_Info&);

	private:
		Layer_Manager() = delete;
		Layer_Manager(Layer_Manager&&) = delete;


	};
}

#endif