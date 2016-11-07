#if !defined(__NN_TRAINING_POLICY_HEADER__)
#define __NN_TRAINING_POLICY_HEADER__

namespace nn {

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

	protected:
		training_policy_info policy;
		virtual void print() const;
	private:
		//base_training_policy() = delete;
	};

};

#endif