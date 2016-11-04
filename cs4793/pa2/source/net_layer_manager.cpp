#include "net_layer_manager.h"


ai::Layer_Info::Layer_Info(int rows, int in_dims, int out_dims, const ai::mat& layer_weights, const ai::vec& layer_bias, const ai::mat& layer_input, const ai::mat& layer_output) :
	input_rows(rows),
	input_dims(in_dims),
	output_dims(out_dims),
	weights(layer_weights),
	bias(layer_bias),
	input(layer_input),
	output(layer_output) {}

ai::Layer_Manager::Layer_Manager(int input_rows, int input_dims, int output_dims) :
	layer(nullptr),
	_input_rows(input_rows),
	_input_dims(input_dims),
	_output_dims(output_dims),
	_weights(input_dims, output_dims),
	_bias(input_dims),
	_input(input_rows, input_dims),
	_output(input_rows, output_dims),
	_links(&_weights, &_bias),
	_input_layer(&_input),
	_output_layer(&_output) {
	layer = new ai::Network_Layer(&_links, &_input_layer, &_output_layer);
}

ai::Layer_Manager::Layer_Manager(std::istream& in, int output_dims, int start_col) :
	layer(nullptr),
	_input_rows(1),
	_input_dims(1),
	_output_dims(1),
	_weights(1, output_dims),
	_bias(1),
	_input(1, 1),
	_output(1, output_dims),
	_links(&_weights, &_bias),
	_input_layer(&_input),
	_output_layer(&_output) {
	if (!this->_set_input(in, start_col, output_dims, false)) {
		std::cerr << "fatal error occurred constructing Layer_Manager\n";
		throw std::runtime_error("fatal error occurred");
	} else {
		this->layer = new ai::Network_Layer(&_links, &_input_layer, &_output_layer);
	}

}
	

ai::Layer_Manager::~Layer_Manager() {
	delete layer;
}

void ai::Layer_Manager::set_input(std::istream& in, int start_col, int output_dims, bool save_info) {
	if(output_dims < 0)
		output_dims = this->_output_dims;
	if (!_set_input(in, start_col, output_dims, save_info)) {
		if (save_info) {
			std::cerr << "Failure to set input. Layer has not been modified.\n";
		} else {
			std::cerr << "Failure to set input. Warning!! Layer may have been modified.\n";
		}
	}

}

bool ai::Layer_Manager::_set_input(std::istream& in, int start_col, int output_dims, bool save_info) {
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
			this->_input.resize(this->_input_rows, this->_input_dims);
			this->_weights.resize(this->_input_dims, this->_output_dims);
			this->_bias.resize(this->_input_dims);
			this->_output.resize(this->_input_rows, this->_output_dims);

			for (int r = 0; r < this->_input_rows; ++r) {
				for (int c = 0; c < this->_input_dims; ++c) {
					this->_input(r, c) = data[r][c + start_col];
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
	info = ai::Layer_Info(_input_rows, _input_dims, _output_dims, _weights, _bias, _input, _output);
}

void ai::Layer_Manager::_restore_info(const ai::Layer_Info& info) {
	this->_input_rows = info.input_rows;
	this->_input_dims = info.input_dims;
	this->_output_dims = info.output_dims;
	this->_input.resize(this->_input_rows, this->_input_dims);
	this->_weights.resize(this->_input_dims, this->_output_dims);
	this->_bias.resize(this->_input_dims);
	this->_output.resize(this->_input_rows, this->_output_dims);
	this->_input = info.input;
	this->_weights = info.weights;
	this->_bias = info.bias;
	this->_output = info.output;
}