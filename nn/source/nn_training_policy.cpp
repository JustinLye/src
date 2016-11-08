
#include"nn_training_policy.h"


nn::training_policy_info::training_policy_info() :
	batch_size(nn::default_training_policy::batch_size),
	max_epoch(nn::default_training_policy::max_epoch),
	init_lrate(nn::default_training_policy::init_lrate),
	update_lrate(nn::default_training_policy::update_lrate),
	use_weight_reg(nn::default_training_policy::use_weight_reg),
	weight_reg_scaling(nn::default_training_policy::weight_reg_scaling) {}

nn::training_policy_info::training_policy_info(const training_policy_info& copy_info) :
	batch_size(copy_info.batch_size),
	max_epoch(copy_info.max_epoch),
	init_lrate(copy_info.init_lrate),
	update_lrate(copy_info.update_lrate),
	use_weight_reg(copy_info.use_weight_reg),
	weight_reg_scaling(copy_info.weight_reg_scaling) {}

nn::training_policy_info::training_policy_info(training_policy_info&& move_info) :
	batch_size(std::move(move_info.batch_size)),
	max_epoch(std::move(move_info.max_epoch)),
	init_lrate(std::move(move_info.init_lrate)),
	update_lrate(std::move(move_info.update_lrate)),
	use_weight_reg(std::move(move_info.use_weight_reg)),
	weight_reg_scaling(std::move(move_info.weight_reg_scaling)) {}

nn::base_training_policy::base_training_policy(bool use_default_policy) :
	policy(nn::training_policy_info()) {
	if (!use_default_policy) {
		policy.batch_size = 0;
		policy.max_epoch = 0;
		policy.init_lrate = 0.0;
		policy.update_lrate = false;
		policy.use_weight_reg = false;
		policy.weight_reg_scaling = 0.0;
	}
}

nn::base_training_policy::base_training_policy(const base_training_policy& copy_policy) :
	policy(copy_policy.policy) {}

nn::base_training_policy::base_training_policy(base_training_policy&& move_policy) :
	policy(std::move(move_policy.policy)) {}

nn::base_training_policy::base_training_policy(const training_policy_info& init_policy) :
	policy(init_policy) {}

void nn::base_training_policy::print(std::ostream& s) const {
	s << "Training Policy:\n" << std::endl;
	s << "\tBatch Size:\t" << policy.batch_size << std::endl;
	s << "\tMax Epoch:\t" << policy.max_epoch << std::endl;
	s << "\tInit. LR:\t" << policy.init_lrate << std::endl;
	s << "\tUpdate LR:\t";
	(policy.update_lrate) ? s << "TRUE" : s << "FALSE";
	s << std::endl;
	s << "\tUse Reg:\t";
	(policy.use_weight_reg) ? s << "TRUE" : s << "FALSE";
	s << std::endl;
	s << "\tReg Scale:\t" << policy.weight_reg_scaling << std::endl;
}

using namespace nn::encoder;

const double training_policy::default_zero_out_pct = 0.40;
const double training_policy::default_gauss_std_dev = 0.001;

training_policy::training_policy() :
	base_training_policy(),
	_hidden_layer_dims(-1),
	_noising_method(NN_GAUSSIAN_METHOD),
	_noise_sigma(-1) {}

training_policy::training_policy(const training_policy& copy_policy) :
	base_training_policy(copy_policy),
	_hidden_layer_dims(copy_policy._hidden_layer_dims),
	_noising_method(copy_policy._noising_method),
	_noise_sigma(copy_policy._noise_sigma) {}

training_policy::training_policy(training_policy&& move_policy) :
	base_training_policy(move_policy),
	_hidden_layer_dims(std::move(move_policy._hidden_layer_dims)),
	_noising_method(std::move(move_policy._noising_method)),
	_noise_sigma(std::move(move_policy._noise_sigma)) {}

training_policy::training_policy(const nn::training_policy_info& init_policy_info) :
	base_training_policy(init_policy_info),
	_hidden_layer_dims(-1),
	_noising_method(NN_GAUSSIAN_METHOD),
	_noise_sigma(-1) {}

training_policy::training_policy(const nn::training_policy_info& init_policy_info, int init_hidden_dims, int noise_method) :
	base_training_policy(init_policy_info),
	_hidden_layer_dims(init_hidden_dims),
	_noising_method(NN_GAUSSIAN_METHOD) {}

void training_policy::print(std::ostream& s) const {
	base_training_policy::print(s);
	s << "\tHidden Dims:\t" << _hidden_layer_dims << std::endl;
	s << "\tNoise Method:\t";
	if (_noising_method == NN_GAUSSIAN_METHOD) {
		s << "GAUSSIAN";
	} else if (_noising_method == NN_ZERO_OUT_METHOD) {
		s << "ZERO OUT";
	} else {
		s << "NOT RECOGNIZED";
	}
	s << std::endl;
	s << "\tNoise Sigma:\t" << _noise_sigma << std::endl;
}
