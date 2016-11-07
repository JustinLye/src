
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