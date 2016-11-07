
#include<Eigen/Core>

#if !defined(__NN_AUTO_ENCODER_HEADER__)
#define __NN_AUTO_ENCODER_HEADER__

#include "fann_structs.h"
#include "noise.h"

namespace nn {
	namespace encoder {

		class training_policy : public nn::base_training_policy {
			//setters
			virtual int batch_size() const { return policy.batch_size; }
			virtual int max_epoch() const { return policy.max_epoch; }
			virtual double init_lrate() const { return policy.init_lrate; }
			virtual bool update_lrate() const { return policy.update_lrate; }
			virtual bool use_weight_reg() const { return policy.use_weight_reg; }
			virtual double weight_reg_scaling() const { return policy.weight_reg_scaling; }

			//getters
			virtual void batch_size(int val) { policy.batch_size = val; }
			virtual void max_epoch(int val) { policy.max_epoch = val; }
			virtual void init_lrate(double val) { policy.init_lrate = val; }
			virtual void update_lrate(bool val) { policy.update_lrate = val; }
			virtual void use_weight_reg(bool val) { policy.use_weight_reg = val; }
			virtual void weight_reg_scaling(double val) { policy.weight_reg_scaling = val; }

		protected:
			training_policy_info policy;
			virtual void print() const;
		private:
			base_training_policy() = delete;
		};

		class hidden_layer : public nn::base_hidden_layer {
		public:

			//will be original input layer network values
			mat target;

			virtual void initialize_layer();
			
			virtual void feed_forward(int);
			virtual void back_propogate(int);

		private:
			virtual void feed_forward() {}
			virtual void back_propogate() {}
		};

		//could have a class to do general training cleanup and initialization
		class training_assistant {
		public:
			base_training_policy* policy;
			hidden_layer* network;

			virtual void train();
			virtual void prep_for_training();
			virtual void prep_for_batch();
			virtual void training_step();
		protected:
			virtual void initialize_delta_accumulators();
			virtual void randomize_weights();
		};

		class auto_encoder {
		public:
			base_training_policy policy;
			input_layer input;
			output_layer output;
			hidden_layer hidden;
			training_assistant trainer;

			//uses default policy
			void initialize_environment();


		};
	};
};

#endif