#include<iostream>
#if !defined(__NN_TRAINING_POLICY_HEADER__)
#define __NN_TRAINING_POLICY_HEADER__

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

};

#endif