
#include"nn_training_policy.h"

nn::training_policy_info::training_policy_info() {}
nn::training_policy_info::training_policy_info(const training_policy_info&) {}
nn::training_policy_info::training_policy_info(training_policy_info&&) {}

nn::base_training_policy::base_training_policy(bool = true) {}
nn::base_training_policy::base_training_policy(const base_training_policy&) {}
nn::base_training_policy::base_training_policy(base_training_policy&&) {}

void nn::base_training_policy::print() const {}