#include "net_layer_manager.h"




ai::Layer_Manager::Layer_Manager(int input_rows, int input_dims, int output_dims) :
	layer(nullptr),
	_input_rows(input_rows),
	_input_dims(input_dims),
	_output_dims(output_dims),
	_weights(input_dims, output_dims),
	_bias(output_dims),
	_input_values(input_rows, input_dims),
	_output_values(input_rows, output_dims),
	_activation_values(input_rows, output_dims),
	_derivative_values(input_rows, output_dims),
	_output_node_layer(&_output_values, &_activation_values, &_derivative_values),
	_links(&_weights, &_bias),
	_input_layer(&_input_values),
	_output_layer(&_output_values) {
	layer = new ai::Network_Layer(&_links, &_input_layer, &_output_layer);
}

ai::Layer_Manager::Layer_Manager(std::istream& in, int output_dims, int start_col) :
	layer(nullptr),
	_input_rows(1),
	_input_dims(1),
	_output_dims(1),
	_weights(1, output_dims),
	_bias(output_dims),
	_input_values(1, 1),
	_output_values(1, output_dims),
	_activation_values(1, output_dims),
	_output_node_layer(&_output_values, &_activation_values, &_derivative_values),
	_links(&_weights, &_bias),
	_input_layer(&_input_values),
	_output_layer(&_output_values) {
	if (!this->_get_input(in, start_col, output_dims, false)) {
		std::cerr << "fatal error occurred constructing Layer_Manager\n";
		throw std::runtime_error("fatal error occurred");
	} else {
		this->layer = new ai::Network_Layer(&_links, &_input_layer, &_output_layer);
	}

}

ai::Layer_Manager::Layer_Manager(std::istream& in, int output_dims, bool skip_set_input, int start_col) :
	layer(nullptr),
	_input_rows(1),
	_input_dims(1),
	_output_dims(1),
	_weights(1, output_dims),
	_bias(output_dims),
	_input_values(1, 1),
	_output_values(1, output_dims),
	_activation_values(1, output_dims),
	_output_node_layer(&_output_values, &_activation_values, &_derivative_values),
	_links(&_weights, &_bias),
	_input_layer(&_input_values),
	_output_layer(&_output_values) {
	if (!skip_set_input) {
		if (!this->_get_input(in, start_col, output_dims, false)) {
			std::cerr << "fatal error occurred constructing Layer_Manager\n";
			throw std::runtime_error("fatal error occurred");
		} else {
			this->layer = new ai::Network_Layer(&_links, &_input_layer, &_output_layer);
		}
	} else {
		this->layer = new ai::Network_Layer(&_links, &_input_layer, &_output_layer);
	}

}

ai::Layer_Manager::~Layer_Manager() {
	delete layer;
}

void ai::Layer_Manager::get_data(std::istream& in, int start_col, int output_dims, bool save_info) {
	if(output_dims < 0)
		output_dims = this->_output_dims;
	if (!_get_input(in, start_col, output_dims, save_info)) {
		if (save_info) {
			std::cerr << "Failure to set input. Layer has not been modified.\n";
		} else {
			std::cerr << "Failure to set input. Warning!! Layer may have been modified.\n";
		}
	}

}

void ai::Layer_Manager::initialize_links() {
	this->_weights.setRandom() *= (1.0/(1.0 + sqrt(this->_output_dims)));
	this->_bias.setRandom() *= (1.0/(1.0 + sqrt(this->_output_dims)));
}

void ai::Layer_Manager::add_input_noise(int method, double sigma) {
	switch (method) {
	case AI_ZERO_OUT_NOISE:
		if (sigma <= 0) {
			this->_noise.RandomZeroOut(this->_input_values);
		} else {
			this->_noise.RandomZeroOut(this->_input_values, sigma);
		}
		break;
	default:
		if (sigma <= 0) {
			this->_noise.AddGaussianNoise(this->_input_values);
		} else {
			this->_noise.AddGaussianNoise(this->_input_values, sigma);
		}
		break;
	}
}

void ai::Layer_Manager::feed_forward() {
	this->_output_values = (this->_input_values * this->_weights).rowwise() + this->_bias;
	this->_activation_values = 1.0/(Eigen::exp(this->_output_values.array()*-1.0) + 1.0);
	this->_derivative_values = this->_activation_values.array() * (1.0 - this->_activation_values.array());
}

bool ai::Layer_Manager::_get_input(std::istream& in, int start_col, int output_dims, bool save_info) {
	bool flag = false;
	std::vector<std::vector<double>> data;
	ai::Layer_Info backup;
	if (!CS4793::readDataAsVecOfVecs(in, data)) {
		return flag;
	} else {
		if(save_info)
			this->_backup_info(backup);
		try {
			this->_input_rows = int(data.size());
			this->_input_dims = int(data[0].size() - start_col);
			this->_output_dims = output_dims;
			this->_input_values.resize(this->_input_rows, this->_input_dims);
			this->_weights.resize(this->_input_dims, this->_output_dims);
			this->_bias.resize(this->_output_dims);
			this->_output_values.resize(this->_input_rows, this->_output_dims);

			for (int r = 0; r < this->_input_rows; ++r) {
				for (int c = 0; c < this->_input_dims; ++c) {
					this->_input_values(r, c) = data[r][c + start_col];
				}
			}
		} catch (std::exception& e) {
			if(save_info)
				this->_restore_info(backup);
			std::cerr << e.what() << '\n';
			return flag;
		}
		flag = true;
	}
	return flag;

	
}

void ai::Layer_Manager::_backup_info(ai::Layer_Info& info) {
	info = ai::Layer_Info(_input_rows, _input_dims, _output_dims, _weights, _bias, _input_values, _output_values);
}

void ai::Layer_Manager::_restore_info(const ai::Layer_Info& info) {
	this->_input_rows = info.input_rows;
	this->_input_dims = info.input_dims;
	this->_output_dims = info.output_dims;
	this->_input_values.resize(this->_input_rows, this->_input_dims);
	this->_weights.resize(this->_input_dims, this->_output_dims);
	this->_bias.resize(this->_output_dims);
	this->_output_values.resize(this->_input_rows, this->_output_dims);
	this->_input_values = info.input;
	this->_weights = info.weights;
	this->_bias = info.bias;
	this->_output_values = info.output;
}
