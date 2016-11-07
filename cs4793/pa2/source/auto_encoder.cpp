#include "auto_encoder.h"

using namespace nn::encoder;

training_policy::training_policy() {}
training_policy::training_policy(const training_policy& copy_policy) {}
training_policy::training_policy(training_policy&& move_policy) {}
training_policy::training_policy(nn::training_policy_info& init_policy_info ) {}
training_policy::training_policy(nn::training_policy_info& intit_policy_info, int noise_method) {}
void training_policy::print() const {}


hidden_layer::hidden_layer() {}
hidden_layer::hidden_layer(const hidden_layer& copy_layer) {}
hidden_layer::hidden_layer(hidden_layer&& move_layer) {}

hidden_layer::hidden_layer(nn::input_layer* init_input_layer , nn::output_layer* init_output_layer, const training_policy*) {}
void hidden_layer::initialize() {}
void hidden_layer::clear_delta() {}
void hidden_layer::randomize_weights() {}
void hidden_layer::feed_forward(int sample_size) {}
void hidden_layer::back_propogate(int sample_size) {}
void hidden_layer::add_noise() {}


training_assistant::training_assistant() {}
training_assistant::training_assistant(const training_assistant& copy_assistant) {}
training_assistant::training_assistant(training_assistant&& move_assistant) {}
training_assistant::training_assistant::training_assistant(training_policy* init_policy, hidden_layer* init_network) {}
void training_assistant::train() {}
void training_assistant::prep_for_training() {}
void training_assistant::prep_for_batch() {}
void training_assistant::training_step() {}
void training_assistant::initialize_delta_accumulators() {}
void training_assistant::randomize_weights() {}


auto_encoder::auto_encoder() {}
auto_encoder::auto_encoder(const auto_encoder& copy_encoder) {}
auto_encoder::auto_encoder(auto_encoder&& move_encoder) {}
auto_encoder::auto_encoder(const char* filename) {}
auto_encoder::auto_encoder(std::istream& data_input_stream) {}
auto_encoder::auto_encoder(mat& data_input, int input_type) {}


//copies policy
void auto_encoder::set_policy(const training_policy& init_policy) {}
//will use default policy.
//if hidden dims <=0 will set hidden dims = to incoming dims
void auto_encoder::set_policy(int init_hidden_dims, int init_noise_method) {}
//construct using policy info. if hidden dims <= 0 will set hidden dims = to incoming dims
void auto_encoder::set_policy(const training_policy_info&, int init_hidden_dims, int init_noise_method) {}

void auto_encoder::initialize_environment() {}
