#include"noise.h"

const double ai::noise_policy::MIN_SWAPS = 0.65;
const double ai::noise_policy::MAX_SWAPS = 0.95;
const int ai::noise_policy::MAX_REDRAWS = 3;

ai::noise::noise() {
	gen = std::mt19937(rd());
	gen.seed(std::time(NULL));
}

void ai::noise::RandomZeroOut(std::vector<std::vector<double>>& input, std::vector<std::vector<double>>& output, double zero_out_pct) {
	output.clear();
	int vec_count = input.size();
	for (int i = 0; i < vec_count; i++) {
		output.push_back(input[i]);
		ZeroOut(output[i], zero_out_pct);
	}
}

void ai::noise::RandomZeroOut(Eigen::MatrixXd& input, Eigen::Ref<Eigen::MatrixXd> output, double zero_out_pct) {
	output = input;
	for (int i = 0; i < output.cols(); i++) {
		ZeroOut(output, i, zero_out_pct);
	}

}

void ai::noise::RandomZeroOut(Eigen::Ref<Eigen::MatrixXd> input, double zero_out_pct) {
	for (int i = 0; i < input.cols(); i++) {
		ZeroOut(input, i, zero_out_pct);
	}
}

void ai::noise::AddGaussianNoise(std::vector<std::vector<double>>& input, std::vector<std::vector<double>>& output, double std_dev) {
	norm_dist = std::normal_distribution<double>(0.0,std_dev);
	output.clear();
	for (int i = 0; i < input.size(); i++) {
		output.push_back(input[i]);
		GaussianNoise(output[i]);
	}
}

void ai::noise::AddGaussianNoise(Eigen::MatrixXd& input, Eigen::Ref<Eigen::MatrixXd> output, double std_dev) {
	this->norm_dist = std::normal_distribution<double>(0.0,std_dev);
	output.resize(input.rows(), input.cols());
	output = input;
	for (int i = 0; i < output.cols(); i++) {
		GaussianNoise(output, i);
	}

}

void ai::noise::AddGaussianNoise(Eigen::Ref<Eigen::MatrixXd> input, double std_dev) {
	this->norm_dist = std::normal_distribution<double>(0.0, std_dev);
	for (int i = 0; i < input.cols(); i++) {
		GaussianNoise(input, i);
	}

}

void ai::noise::ZeroOut(std::vector<double>& output_vec, double zero_out_pct) {
	int vec_size = output_vec.size();
	int zero_count = static_cast<int>(floor((vec_size-1) * zero_out_pct));
	std::vector<int> indices;
	for (int i = 0; i < vec_size; i++) {
		indices.push_back(i);
	}
	std::shuffle(indices.begin(), indices.end(), this->gen);
	for (int i = 0; i < zero_count; i++) {
		output_vec[indices[i]] = 0.0;
	}
}

void ai::noise::ZeroOut(Eigen::Ref<Eigen::MatrixXd> output, int col, double zero_out_pct) {
	int row_count = output.rows();
	int zero_count = static_cast<int>(floor((row_count-1) * zero_out_pct));
	std::vector<int> indices;
	for (int i = 0; i < row_count; i++) {
		indices.push_back(i);
	}
	std::shuffle(indices.begin(), indices.end(), this->gen);
	for (int i = 0; i < zero_count; i++) {
		output(indices[i],col) = 0.0;
	}
}

void ai::noise::GaussianNoise(std::vector<double>& output) {
	for (int i = 0; i < output.size(); i++) {
		output[i] += this->norm_dist(this->gen);
	}
}

void ai::noise::GaussianNoise(Eigen::Ref<Eigen::MatrixXd> output, int col) {
	for (int i = 0; i < output.rows(); i++) {
		output(i,col) = output(i,col) + this->norm_dist(this->gen);
	}
}