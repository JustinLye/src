
#include<Eigen/Core>

#if !defined(__NN_AUTO_ENCODER_HEADER__)
#define __NN_AUTO_ENCODER_HEADER__

#include "nn_training_policy.h"
#include "fann_structs.h"
#include "noise.h"

/*notes:
	code use a lot of error handling; however, this project is overdue. hopefully these class objects can be reused in semester project.
*/

namespace nn {
#define NN_ZERO_OUT_METHOD 0x0010
#define NN_GAUSSIAN_METHOD 0x0011
	namespace encoder {

		class training_policy : public nn::base_training_policy {
		public:
			training_policy();
			training_policy(const training_policy&);
			training_policy(training_policy&&);
			training_policy(nn::training_policy_info&);
			training_policy(nn::training_policy_info&, int);
			//getters
			virtual int batch_size() const { return policy.batch_size; }
			virtual int max_epoch() const { return policy.max_epoch; }
			virtual double init_lrate() const { return policy.init_lrate; }
			virtual bool update_lrate() const { return policy.update_lrate; }
			virtual bool use_weight_reg() const { return policy.use_weight_reg; }
			virtual double weight_reg_scaling() const { return policy.weight_reg_scaling; }
			virtual int noising_method() const { return _noising_method; }

			//setters
			virtual void batch_size(int val) { policy.batch_size = val; }
			virtual void max_epoch(int val) { policy.max_epoch = val; }
			virtual void init_lrate(double val) { policy.init_lrate = val; }
			virtual void update_lrate(bool val) { policy.update_lrate = val; }
			virtual void use_weight_reg(bool val) { policy.use_weight_reg = val; }
			virtual void weight_reg_scaling(double val) { policy.weight_reg_scaling = val; }
			virtual void noising_method(int val) { _noising_method = val; }
			virtual bool

		protected:
			training_policy_info policy;
			int _noising_method;

			virtual void print() const;
		private:
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
			training_policy* policy;
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
			
			input_layer input;
			output_layer output;
			hidden_layer hidden;
			training_assistant trainer;

			void set_policy(const training_policy&, int = NN_GAUSSIAN_METHOD)
			void initialize_environment();

		private:
			//this is a pointer that is set to null on construction. training will not proceed until this points at policy obj, which should only occur within the set_policy method
			training_policy* _policy_set_ind; 
			training_policy _policy;



		};
	};
};

#endif