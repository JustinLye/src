
#include"nn_training_policy.h"

nn::training_policy_info::training_policy_info() {}
nn::training_policy_info::training_policy_info(const training_policy_info& copy_info) {}
nn::training_policy_info::training_policy_info(training_policy_info&& move_info) {}

nn::base_training_policy::base_training_policy(bool use_default_policy) {}
nn::base_training_policy::base_training_policy(const base_training_policy& copy_policy) {}
nn::base_training_policy::base_training_policy(base_training_policy&& move_policy) {}

void nn::base_training_policy::print() const {}