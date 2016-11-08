
#if !defined(__NN_ENCODER_HIDDEN_LAYER_HEADER__)
#define __NN_ENCODER_HIDDEN_LAYER_HEADER__

#include "nn_structs.h"
#include "nn_training_policy.h"
#include "noise.h"

namespace nn {
	namespace encoder {
		class encoding_layer : public nn::base_hidden_layer {
		public:
			//constructors
			encoding_layer();
			encoding_layer(const encoding_layer&);
			encoding_layer(encoding_layer&&);
			encoding_layer(input_layer*, output_layer*, const training_policy*);

			mat training_inputs;
			mat training_targets;
			mat noised_input;
			mat targets;

			virtual void initialize();
			virtual void clear_delta();
			virtual void randomize_weights();

			virtual void training_step(int = 0);
			virtual void feed_forward(int = 0);
			virtual void set_errors(int = 0);
			virtual void back_propogate(int = 0);
			virtual inline void update_links() {
				incoming_links.update();
				outgoing_links.update();
			}


			inline bool is_complete() const { return (input_nodes != nullptr && output_nodes != nullptr && policy != nullptr); }
			inline bool can_train() const { return (is_complete() && all_flags_are_set()); }
			mat noised_input;
			const training_policy* policy;
		private:
			nn::noise _noise_gen;
			int sample_size;
			//will be used during training step functions if there is a size conflict between the data and the batch size
			inline void set_sample_size(int rows_offset) {
				assert(input_nodes->network_values.rows() >= rows_offset);
				sample_size = std::min(input_nodes->network_values.rows() - rows_offset, policy->batch_size());
			}

			inline bool all_flags_are_set() const {
				return (has_noise_flag && has_targets_flag && dim_links_flag);
			}

			//flags
			bool has_noise_flag;
			bool has_targets_flag;
			bool dim_links_flag;

			//initialization helper functions
			virtual void add_noise();
			virtual void set_target();
			virtual void dim_links();

			virtual void print_layer_status_warnings(const char* = nullptr) const;
			virtual void print_layer_status_errors(const char* = nullptr) const;

			//inaccessible members
			virtual void feed_forward() {}
			virtual void back_propogate() {}
			encoding_layer(mat&) = delete;
			encoding_layer(int, int) = delete;
			encoding_layer(input_layer*, output_layer*) = delete;

		};
	};
};

#endif