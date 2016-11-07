
#include<Eigen/Core>
#include<iostream>
#include<stdexcept>
#if !defined(__NN_AUTO_ENCODER_HEADER__)
#define __NN_AUTO_ENCODER_HEADER__

#include "nn_training_policy.h"
#include "fann_structs.h"
#include "noise.h"

/*notes:
	code use a lot of error handling; however, this project is overdue. hopefully these class objects can be reused in semester project.
*/

namespace nn {


	namespace encoder {
		//To save a little time, I will only support one constructor of the hidden layer class.
		//http://stackoverflow.com/questions/24609872/delete-virtual-function-from-a-derived-class/24610165
		
		class enviro_status : public nn::env::base_enviro_status {
		public:
			enviro_status() : base_enviro_status() {}
			enviro_status(const enviro_status& copy_status) : base_enviro_status(copy_status) {}
			enviro_status(enviro_status&& move_status) : base_enviro_status(move_status) {}
			enviro_status(int val) : nn::env::base_enviro_status(val) {}
			inline int status() const { return _state; }
			inline void status(int val) { _state = nn::env::set_status(val); }
			inline bool ready_to_train() const { return _state == nn::env::ready; }
			inline bool need_to_initialize() const { return _state == nn::env::uninitialized; }
			inline bool in_error_state() const { return _state == nn::env::bad; }
			inline bool policy_not_set() const { return (_state == nn::env::need_policy); }
			//could add list of flags for potential errors (i.e. failed to load data from input stream)
		};

		class training_policy : public nn::base_training_policy {
		public:
			//constructors
			training_policy();
			training_policy(const training_policy&);
			training_policy(training_policy&&);
			training_policy(const nn::training_policy_info&);
			training_policy(const nn::training_policy_info&,int, int);

			//some default constants
			static const double default_zero_out_pct;
			static const double default_gauss_std_dev;

			//getters
			inline virtual int batch_size() const { return policy.batch_size; }
			inline virtual int max_epoch() const { return policy.max_epoch; }
			inline virtual double init_lrate() const { return policy.init_lrate; }
			inline virtual bool update_lrate() const { return policy.update_lrate; }
			inline virtual bool use_weight_reg() const { return policy.use_weight_reg; }
			inline virtual double weight_reg_scaling() const { return policy.weight_reg_scaling; }
			inline virtual int noising_method() const { return _noising_method; }
			inline virtual int hidden_layer_dims() const { return _hidden_layer_dims; }
			inline virtual double noise_sigma() const { return _noise_sigma; }
			//setters
			inline virtual void batch_size(int val) { policy.batch_size = val; }
			inline virtual void max_epoch(int val) { policy.max_epoch = val; }
			inline virtual void init_lrate(double val) { policy.init_lrate = val; }
			inline virtual void update_lrate(bool val) { policy.update_lrate = val; }
			inline virtual void use_weight_reg(bool val) { policy.use_weight_reg = val; }
			inline virtual void weight_reg_scaling(double val) { policy.weight_reg_scaling = val; }
			inline virtual void noising_method(int val) { _noising_method = val; }
			inline virtual void hidden_layer_dims(int val) { _hidden_layer_dims = val; }
			inline virtual void noise_sigma(double val) { _noise_sigma = val; }

			training_policy& operator=(const training_policy& copy_policy) {
				this->policy = copy_policy.policy;
				this->_noising_method = copy_policy._noising_method;
				this->_hidden_layer_dims = copy_policy._hidden_layer_dims;
				this->_noise_sigma = copy_policy._noise_sigma;
				return *this;
			}

		protected:
			//training_policy_info policy;
			int _noising_method;
			int _hidden_layer_dims;
			double _noise_sigma;
			virtual void print(std::ostream& s) const;
		};

		class hidden_layer : public nn::base_hidden_layer {
		public:
			//constructors
			hidden_layer();
			hidden_layer(const hidden_layer&);
			hidden_layer(hidden_layer&&);
			hidden_layer(input_layer*, output_layer*, const training_policy*);
			//override base class initalize method. will 
			//will noise the input here
			//set member variables, create links, etc.
			virtual void initialize();
			virtual void clear_delta();
			virtual void randomize_weights();
			//feed input layer through network. 
			virtual void feed_forward(int);
			//backpropagate network error. assumes feed_forward has been called and errors have been set
			virtual void back_propogate(int);

			inline virtual bool has_valid_policy() const { return (policy != nullptr); }
			inline virtual bool has_input_nodes() const { return (input_nodes != nullptr); }
			inline virtual bool has_output_nodes() const { return (output_nodes != nullptr); }
			inline virtual bool has_target() const { return targets_are_set; }
			inline virtual bool has_noisy_input() const { return input_has_noise; }
			inline virtual bool has_hidden_dims() const {
				if (policy != nullptr) {
					return (policy->hidden_layer_dims() > 0);
				} else {
					return false;
				}
			}

		private:
			//training policy. will get hidden dims and noising method specified in the policy
			const training_policy* policy;
			//will be original input
			//mat target;
			//storage for noised input
			mat noised_input;
			//helper function to add noist to the input
			virtual void add_noise();
			
			//flags to use during initialization
			bool targets_are_set;
			bool input_has_noise;
			bool is_complete;
			bool incoming_links_are_set;
			bool outgoing_links_are_set;
			bool hidden_dims_are_set;
			nn::noise _noise_gen;

			//sets the is_complete flag to false if any critical members are incomplete
			void self_diagnostic();

			//inaccessible members
			virtual void feed_forward() {}
			virtual void back_propogate() {}
			hidden_layer(mat&) = delete;
			hidden_layer(int, int) = delete;
			hidden_layer(input_layer*, output_layer*) = delete;

		};

		//could have a class to do general training cleanup and initialization
		class training_assistant {
		public:
			training_assistant();
			training_assistant(const training_assistant&);
			training_assistant(training_assistant&&);
			training_assistant(training_policy* init_policy, hidden_layer* init_network);

			training_policy* policy;
			//can probably get rid of network member since policy is equal to network.policy
			hidden_layer* network;

			virtual void train();
			virtual void prep_for_training();
			virtual void prep_for_batch();

			//will call hidden_layer feed_forward and back_propogate methods using policy batch size as argument
			virtual void training_step();
		protected:
			//helper function to reset minibatch deltas
			virtual void initialize_delta_accumulators();
			virtual void randomize_weights();
		};


		//TODO: will need to access weights and hidden layer values after training
		class auto_encoder {
		public:
			auto_encoder();
			auto_encoder(const auto_encoder&);
			auto_encoder(auto_encoder&&);
			auto_encoder(const char*);
			auto_encoder(std::istream&);
			auto_encoder(mat&, int = NN_PREPARED_INPUT_VALUES);

			~auto_encoder() {
				if (_hidden != nullptr) {
					delete _hidden;
				}
			}

			//may want to ability to construct with a training policy

			//Returns true if pointer to training_policy class member is not null.
			//This will only return true after calling the set policy method.
			bool policy_has_been_set() const { return (_policy_set_ind != nullptr); }

			//BEFORE any TRAINING can occur, set_policy MUST BE CALLED 
			//Sets the training policy to be used.
			//set_policy() will use the default training policy defined in nn_training_policy.h
			void set_policy(const training_policy&);
			void set_policy(int = -1, int = NN_GAUSSIAN_METHOD);
			void set_policy(const training_policy_info&, int = -1, int = NN_GAUSSIAN_METHOD);

			inline bool train() {
				if (_status.ready_to_train()) {
					_trainer.train();
					return true;
				} else if (_status.need_to_initialize()) {
					std::cerr << "error: auto_encoder cannot train before the training environment has been initialized\n";
					return false;
				} else if (_status.policy_not_set()) {
					std::cerr << "error: auto_encoder cannot train until parameters of the training are known. Use set_policy() method to communicate training parameters to the auto_encoder.\n";
					return false;
				} else if (_status.in_error_state()) {
					std::cerr << "error: current training environment stats is set to an error state. training can only be performed when the environment is in a ready state.\n";
					return false;
				} else {
					std::cerr << "error: training could not occur because to environment is in an unknown state. training can only be performed when the environment is in a ready state.\n";
					return false;
				}
			}
		private:
			input_layer _input;
			output_layer _output;
			hidden_layer* _hidden;
			//this is a pointer that is set to null on construction. training will not proceed until this points at policy obj, which should only occur within the set_policy method
			training_policy* _policy_set_ind; 
			training_policy _policy;
			training_assistant _trainer;

			//flag to indicate if the training environment is in a ready state (i.e. training can begin)
			enviro_status _status;

			//if true then will need to be loaded during environment initialization
			bool _need_to_load_data;
			//temporary variables that may or may not be used during construction/environment initialization
			int _input_type;
			std::istream* _input_stream;
			const char* _filename;
			mat_ptr _input_data;
			
			//Helper function to setup the training environment. Will be called from set_policy method. 
			void initialize_environment();



		};
	};
};

#endif