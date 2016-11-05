#include<iostream>
#include<fstream>
#include "pa_util.h"

#if !defined(__NN_FANN_STRUCTS_HEADER__)
#define __NN_FANN_STRUCTS_HEADER__

namespace nn {
	typedef Eigen::MatrixXd mat;
	typedef Eigen::RowVectorXd vec;
	typedef Eigen::MatrixXd* mat_ptr;
	typedef Eigen::RowVectorXd* vec_ptr;

	//class to store input stream data.
	class data {
	protected:
		//Column offset where data begins
		//Default is 1 (i.e. target data is in column 0 and input data beings @ column 1)
		//Thus, target data column is assumed to be _column_offset - 1.
		//Currently any columns < _column_offset - 1 are ignored
		int column_offset;
		double true_class_target;
		double wrong_class_target;
		mat network_input;
		mat network_target;
		data() : column_offset(1), true_class_target(0.9), wrong_class_target(0.1) {}
	};

	//Manages input data stream.
	//Can load input from std::istream and provide read-only information on that data.
	//Also, can provide copies of input data and target data matrices.
	class input_stream : protected data {
	public:
		
		input_stream() : data() {}
		
		//Return number of rows in the input stream
		inline int input_rows() const { return network_input.rows(); }
		//Return number of dimensions of input data in stream
		inline int input_cols() const { return network_input.cols(); }
		//Returns a copy of input data matrix
		inline mat copy_input_data() const { return network_input; }
		//Returns a copy of target data matrix
		inline mat copy_target_data() const { return network_target; }
		
		//Returns current true class target value
		inline double true_target() const { return true_class_target; }
		//Sets current true class target value
		inline void true_target(double target) { true_class_target = target; } //todo: handle update if true target is not equal to current true target and data has already been loaded
		//Returns current wrong class target value
		inline double wrong_target() const { return wrong_class_target; }
		//Sets current wrong class target value
		inline void wrong_target(double target) { wrong_class_target = target; } //todo: handle update if wrong target is not equal to current wrong target and data has alread been loaded
	protected:
		//Loads input and target data matrices from given input stream.
		//Usage: load_data(standard input stream, column offset, true class target, wrong class target)
		//Returns true if data was successfully load, false otherwise
		virtual bool load_data(std::istream&, int = -1, double = -1, double = -1);
	};


	//same as CS4793::Links
	class Net_Link {
	public:
		int input_dims;
		int output_dims;
		mat weights;
		vec bias;
		mat weights_delta;
		vec bias_delta;

		Net_Link();
		Net_Link(int,int);
	protected:
		//returns false if current net link dims are different than the argument dimensions
		inline bool same_dimensions(int input_dimensions, int output_dimensions = -1) {
			if (input_dimensions == input_dims && ((output_dimensions >= 0 && output_dimensions == output_dims) || (output_dimensions < 0 && (output_dims == input_dims))))
				return true;
			else
				return false;
		}
			
		virtual void redimensionalize(int, int = -1);
		
	};

	class Base_Layer_Data : protected input_stream, protected Net_Link {

	};

	//same as CS4793::Links
	class Layer_Data : protected input_stream, protected Net_Link {
	public:
		mat network_output;
		mat network_activation;
		mat activation_derivative;
		mat network_error;
		Layer_Data();
		Layer_Data(const char*);
		Layer_Data(std::istream&);

		inline friend std::ostream& operator<<(std::ostream& s, const nn::Layer_Data& l) {
			l.print(s);
			return s;
		}

	protected:
		virtual void redimensionalize(int, int = -1);
	private:
		virtual void print(std::ostream&) const;
		
	};
};

#endif