#include<vector>
#include<fstream>
#if !defined(__AI_NET_LAYER_MANAGER_HEADER__)
#define __AI_NET_LAYER_MANAGER_HEADER__
#include "pa_util.h"
#include "net_structs.h"

namespace ai {
	struct Layer_Info {
		int input_rows;
		int input_dims;
		int output_dims;
		ai::mat weights;
		ai::vec bias;
		ai::mat input;
		ai::mat output;
		Layer_Info() {}
		Layer_Info(int,int,int,const ai::mat&, const ai::vec&, const ai::mat&, const ai::mat&);
	};
	class Layer_Manager {
	public:
		Layer_Manager(int input_rows, int input_dims, int output_dims);
		Layer_Manager(std::istream&, int, int = 0);
		~Layer_Manager();

		ai::Network_Layer* layer;

		//reads data from file. Any information in current later is discarded.
		void set_input(std::istream&, int = 0, int = -1, bool = true);

	private:
		int _input_rows;
		int _input_dims;
		int _output_dims;
		ai::mat _weights;
		ai::vec _bias;
		ai::mat _input;
		ai::mat _output;
		ai::Node_Linkage _links;
		ai::Node_Layer _input_layer;
		ai::Node_Layer _output_layer;
		Layer_Manager() = delete;
		bool _set_input(std::istream&, int, int, bool);
		void _backup_info(ai::Layer_Info&);
		void _restore_info(const ai::Layer_Info&);

	};
}

#endif