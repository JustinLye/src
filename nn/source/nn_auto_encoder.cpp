#include "nn_auto_encoder.h"

using namespace nn::encoder;
training_assistant::training_assistant() :
	encoder(nullptr),
	bpe(0),
	row_offset(0) {}
training_assistant::training_assistant(const training_assistant& copy_assistant) :
	encoder(copy_assistant.encoder),
	bpe(copy_assistant.bpe),
	row_offset(copy_assistant.row_offset),
	sample_indices(copy_assistant.sample_indices) {}

training_assistant::training_assistant(training_assistant&& move_assistant) :
	encoder(std::move(move_assistant.encoder)),
	bpe(std::move(move_assistant.bpe)),
	row_offset(std::move(move_assistant.row_offset)),
	sample_indices(std::move(move_assistant.sample_indices)) {}


void training_assistant::train() {
	//initialize training environment
	training_prep();
	//train up-to maximum epochs stating in hidden_layer's (network) training policy
	for (int i = 0; i < encoder->policy->max_epoch(); ++i) {
		epoch();
	}
}

void training_assistant::training_prep() {
	//calculate batches per epoch
	bpe = int(std::ceil(encoder->input_nodes->network_values.rows() / double(encoder->policy->batch_size())));
	//clear indices vector
	sample_indices.clear();
	//resize index vector to fit number of input values
	sample_indices.resize(encoder->input_nodes->network_values.rows());
	//copy indices into vector
	for (int i = 0; i < encoder->input_nodes->network_values.rows(); i++) {
		sample_indices[i] = i;
	}
	//initialize weights and bais of incoming and outgoing links (hidden_layer input and output links)
	encoder->randomize_weights();
}

void training_assistant::epoch_prep() {
	//shuffle input value indices
	std::random_shuffle(sample_indices.begin(), sample_indices.end());
	//copy training inputs and targets in random order
	for (int i = 0; i < encoder->noised_input.rows(); i++) {
		encoder->training_inputs.row(i) = encoder->noised_input.row(sample_indices[i]);
		encoder->training_targets.row(i) = encoder->targets.row(sample_indices[i]);
	}
}

void training_assistant::epoch() {
	//shuffle training inputs and targets
	epoch_prep();
	//train mini-batches up-to bpe
	train_batches();
	//todo: add early exit with validation testing
}

void training_assistant::train_batches() {
	for (int i = 0; i < bpe; ++i) {
		//resets delta accumulators
		encoder->clear_delta();
		//update row offset
		row_offset = i * encoder->policy->batch_size();
		//train mini-batch
		encoder->training_step(row_offset);
	}
}

auto_encoder::auto_encoder() {}
auto_encoder::auto_encoder(const char* filename) :
	_input(filename),
	_output(_input.network_values.rows(), _input.network_values.cols()),
	_hidden(nullptr),
	_policy(training_policy()),
	_trainer(training_assistant()) {}


//copies policy
void auto_encoder::set_policy(const training_policy& init_policy) {
	_policy = init_policy;
	_hidden = new encoding_layer(&_input, &_output, &_policy);
	_trainer.encoder = _hidden;

}
