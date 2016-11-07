#if !defined(__AI_NET_LAYER_TRAINER_HEADER__)
#define __AI_NET_LAYER_TRAINER_HEADER__

#include "net_layer_manager.h"

namespace nn {
	class Layer_Trainer : public Layer_Manager {
	public:

		Layer_Trainer(int , int , int , int = 0, double = 0.9, double = 0.1);
		Layer_Trainer(std::istream&, int, int = 0, int = 0, double = 0.9, double = 0.1);
		Layer_Trainer(const Layer_Trainer&);

		//uses CS4793 loadData() method
		virtual bool get_data(std::istream&);


	protected:
		int _target_dims;
		double _in_target;
		double _out_target;
		nn::mat _targets;
		nn::mat _error_values;


	private:
		Layer_Trainer() = delete;
		Layer_Trainer(Layer_Trainer&&) = delete;		
	};
}

#endif