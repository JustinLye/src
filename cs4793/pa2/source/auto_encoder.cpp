#include "auto_encoder.h"

using namespace nn::encoder;

training_policy::training_policy() {}
training_policy::training_policy(const training_policy& copy_policy) {}
training_policy::training_policy(training_policy&& move_policy) {}
training_policy::training_policy(nn::training_policy_info& init_policy_info ) {}
training_policy::training_policy(nn::training_policy_info& intit_policy_info, int noise_method) {}
void training_policy::print() const {}

