#if !defined(__NN_FANN_STRUCTS_HEADER__)
#define __NN_FANN_STRUCTS_HEADER__

#include"fann_util.h"

namespace nn {
#define PREPARED_INPUT_VALUES 0x0050
#define RAW_INPUT_VALUES 0x0051

	static const struct default_training_policy {
		int batch_size = 120;
		int max_epoch = 500;
		double init_lrate = 10.0;
		bool update_lrate = true;
		//set to false b/c I am uncertain how to weight_reg_scaling is used, thus I do not really know what a good default value would be
		bool use_weight_reg = false;
		double weight_reg_scaling = 1.0;
	};

	struct training_policy_info {
		int batch_size;
		int max_epoch;
		double init_lrate;
		bool update_lrate;
		bool use_weight_reg;
		double weight_reg_scaling;
		training_policy_info();
		training_policy_info(const training_policy_info&);
		training_policy_info(training_policy_info&&);
	};

	class base_training_policy {
	public:
		base_training_policy(bool = true);
		base_training_policy(const base_training_policy&);
		base_training_policy(base_training_policy&&);

		//setters
		virtual int batch_size() const = 0;
		virtual int max_epoch() const = 0;
		virtual double init_lrate() const = 0;
		virtual bool update_lrate() const = 0;
		virtual bool use_weight_reg() const = 0;
		virtual double weight_reg_scaling() const = 0;

		//getters
		virtual void batch_size(int) = 0;
		virtual void max_epoch(int) = 0;
		virtual void init_lrate(double) = 0;
		virtual void update_lrate(bool) = 0;
		virtual void use_weight_reg(bool) = 0;
		virtual void weight_reg_scaling(double) = 0;

	protected:
		training_policy_info policy;
		virtual void print() const;
	private:
		base_training_policy() = delete;
	};

	class input_layer {
	public:
		input_layer();
		input_layer(const char*);
		input_layer(std::istream&);
		input_layer(mat&, int = PREPARED_INPUT_VALUES);
		mat network_values;
	};

	class output_layer {
	public:
		output_layer();
		output_layer(mat&);
		output_layer(int, int);

		mat network_values;
		mat network_activation;
		mat network_error;
		mat network_activation_prime;
		mat network_sensitivity;
		mat network_targets;
	};

	class layer_link {
	public:
		layer_link();
		layer_link(int);
		layer_link(int, int);
		layer_link(mat&);
		layer_link(mat&, vec&);

		int incoming_dims;
		int outgoing_dims;

		mat weights;
		vec bias;
		mat weights_delta;
		vec bias_delta;		

		virtual void initialize();
	};

	//pure virtual class. 
	class base_hidden_layer : public output_layer {
	public:
		base_hidden_layer();
		base_hidden_layer(input_layer*, output_layer*);

		input_layer* input_nodes;
		output_layer* output_nodes;
		layer_link incoming_links;
		layer_link outgoing_links;

		virtual void initialize_layer() = 0;
		virtual void feed_forward() = 0;
		virtual void back_propogate() =0;
	};



};

#endif