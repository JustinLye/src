
#include<Eigen/Core>
#include<iostream>
#include<stdexcept>
#if !defined(__NN_AUTO_ENCODER_HEADER__)
#define __NN_AUTO_ENCODER_HEADER__

#include "nn_hidden_layer.h"


/*notes:
	code use a lot of error handling; however, this project is overdue. hopefully these class objects can be reused in semester project.
*/

namespace nn {
	namespace encoder {
		//could have a class to do general training cleanup and initialization
		class training_assistant {
		public:
			training_assistant();
			training_assistant(const training_assistant&);
			training_assistant(training_assistant&&);

			encoding_layer* encoder;

			//driver function for training operations
			virtual void train();
			//this will calculate bpe. it will generate sample indices array, and randomize hidden_layer links
			//called once per training episode.
			virtual void training_prep();
			//this will shuffle the indice array and load the training_inputs and training_targets
			//called before each epoch up-to max epoches
			virtual void epoch_prep();
			//calls epoch prep and train_batches
			virtual void epoch();
			//this will call mini_batch_prep(), updates row_offset then calls hidden_layer.train(rows_offset) --> hidden_layer.train is effectively a mini-batch.
			//this is called bpe times per epoch
			virtual void train_batches();
		private:
			int bpe;
			int row_offset;
			std::vector<int> sample_indices;
		};
		class auto_encoder {
		public:
			auto_encoder();
			auto_encoder(const char*);
			~auto_encoder() {
				if (_hidden != nullptr) {
					delete _hidden;
				}
			}

			virtual void set_policy(const training_policy&);

			inline bool train() {
			}
		public:
			input_layer _input;
			output_layer _output;
			encoding_layer* _hidden;
			training_policy _policy;
			training_assistant _trainer;
		};
	};
};

#endif