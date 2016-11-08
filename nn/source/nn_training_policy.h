#include<iostream>
#if !defined(__NN_TRAINING_POLICY_HEADER__)
#define __NN_TRAINING_POLICY_HEADER__

#include "nn_util.h"

namespace nn {

	namespace default_training_policy {
		static const int batch_size = 120;
		const int max_epoch = 500;
		const double init_lrate = 10.0;
		const bool update_lrate = true;
		//set to false b/c I am uncertain how to weight_reg_scaling is used, thus I do not really know what a good default value would be
		const bool use_weight_reg = false;
		const double weight_reg_scaling = 1.0;

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
		training_policy_info& operator=(const training_policy_info& copy_policy) {
			this->batch_size = copy_policy.batch_size;
			this->max_epoch = copy_policy.max_epoch;
			this->init_lrate = copy_policy.init_lrate;
			this->update_lrate = copy_policy.update_lrate;
			this->use_weight_reg = copy_policy.use_weight_reg;
			this->weight_reg_scaling = copy_policy.weight_reg_scaling;
			return *this;
		}
	};

	class base_training_policy {
	public:
		base_training_policy(bool = true);
		base_training_policy(const base_training_policy&);
		base_training_policy(base_training_policy&&);
		base_training_policy(const training_policy_info&);

		//getters
		virtual int batch_size() const = 0;
		virtual int max_epoch() const = 0;
		virtual double init_lrate() const = 0;
		virtual bool update_lrate() const = 0;
		virtual bool use_weight_reg() const = 0;
		virtual double weight_reg_scaling() const = 0;

		//setters
		virtual void batch_size(int) = 0;
		virtual void max_epoch(int) = 0;
		virtual void init_lrate(double) = 0;
		virtual void update_lrate(bool) = 0;
		virtual void use_weight_reg(bool) = 0;
		virtual void weight_reg_scaling(double) = 0;
		inline friend std::ostream& operator<<(std::ostream& s, const base_training_policy& p) {
			p.print(s);
			return s;
		}

		base_training_policy& operator=(const base_training_policy& copy_policy) {
			this->policy = copy_policy.policy;
			return *this;
		}

	protected:
		training_policy_info policy;
		virtual void print(std::ostream&) const;
	private:
		//base_training_policy() = delete;
	};

	namespace encoder {
		class training_policy : public nn::base_training_policy {
		public:
			//constructors
			training_policy();
			training_policy(const training_policy&);
			training_policy(training_policy&&);
			training_policy(const nn::training_policy_info&);
			training_policy(const nn::training_policy_info&, int, int);

			//current learning rate
			double lrate;

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

			friend std::ostream& operator<<(std::ostream& s, const training_policy& p) {
				p.print(s);
				return s;
			}

		protected:
			//training_policy_info policy;
			int _noising_method;
			int _hidden_layer_dims;
			double _noise_sigma;
			virtual void print(std::ostream& s) const;
		};
	};


};

#endif