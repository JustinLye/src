#include"net_layer_trainer.h"

ai::Layer_Trainer::Layer_Trainer(int input_rows, int input_dims, int output_dims, int target_dims, double in_target, double out_target) :
	Layer_Manager(input_rows, input_dims, output_dims),
	_target_dims(output_dims),
	_in_target(in_target),
	_out_target(out_target),
	_targets(input_rows, output_dims),
	_error_values(input_rows, output_dims) {
	if (target_dims > 0) {
		_target_dims = target_dims;
		_targets.resize(input_rows, target_dims);
		_error_values.resize(input_rows, target_dims);
	}
	
}

ai::Layer_Trainer::Layer_Trainer(std::istream& in, int output_dims, int start_col, int target_dims, double in_target, double out_target) :
	Layer_Manager(in, output_dims, true, start_col),
	_target_dims(output_dims),
	_in_target(in_target),
	_out_target(out_target),
	_targets(1, output_dims),
	_error_values(1, output_dims) {
	if (target_dims > 0) {
		_target_dims = target_dims;
		_targets.resize(1, target_dims);
		_error_values.resize(1, target_dims);
	}

}


bool ai::Layer_Trainer::get_data(std::istream& in) {
	bool flag = CS4793::loadDataFile(in, this->_input_values, this->_targets, 1, this->_in_target, this->_out_target);
	if (flag) {
		this->_input_rows = this->_input_values.rows();
		this->_input_dims = this->_input_values.cols();
		this->_weights.resize(this->_input_dims, this->_output_dims);
		this->_bias.resize(this->_output_dims);
		this->_output_values(this->_input_rows, this->_output_dims);

	}
}