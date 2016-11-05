#if !defined(__AI_NET_LAYER_TRAINER_HEADER__)
#define __AI_NET_LAYER_TRAINER_HEADER__

#include "net_layer_manager.h"

namespace ai {
	class Layer_Trainer : public Layer_Manager {
	public:

	protected:
		ai::mat _targets;
		double _in_target;
		double _out_target;
		std::vector<int> _tags;
		std::set<int> _unique_tags;
		std::map<int, int> _tags_map_to_nodes;
		ai::mat _error_values;
	};
}

#endif