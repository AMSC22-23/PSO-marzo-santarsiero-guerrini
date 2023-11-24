#include "../include/TestFunctions.hpp"


std::function<double(std::vector<double>)> TestFunctions::sphere() {
	return [](std::vector<double> x) {
		double sum = 0.0;
		for (auto &i : x) {
			sum += i * i;
		}
		return sum;
	};
}

// Returns a function object that computes the rastrigin function
// Global minimum at f(0,...,0) = 0
std::function<double(std::vector<double>)> TestFunctions::rastrigin() {
	return [](std::vector<double> x) {
		double sum = 0.0;
		for (auto &i : x) {
			sum += (i * i - 10 * cos(2 * M_PI * i));
		}
		return 10 * x.size() + sum;
	};
}

// Returns a function object that computes the ackley function
// Global minimum at f(0,...,0) = 0
std::function<double(std::vector<double>)> TestFunctions::ackley() {
	return [](std::vector<double> x) {
		double sum1 = 0.0;
		double sum2 = 0.0;
		for (auto &i : x) {
			sum1 += i * i;
			sum2 += cos(2 * M_PI * i);
		}
		return -20 * exp(-0.2 * sqrt(sum1 / x.size())) - exp(sum2 / x.size()) + 20 + M_E;
	};
}

// get standard domain bounds for a given std::function
std::pair<double, double> TestFunctions::get_bounds(const std::string& function_name) {
	if (function_name == "sphere") {
		return std::make_pair(-100.0, 100.0);
	}
	else if (function_name == "rastrigin") {
		return std::make_pair(-5.12, 5.12);
	}
	else if (function_name == "ackley") {
		return std::make_pair(-32.768, 32.768);
	}
	else {
		std::cerr << "Error: function not found" << std::endl;
		return std::make_pair(0, 0);
	}
}


int main_test()
{
	// check if the functions returns f(0,...,0) ~ 0
	auto a = TestFunctions::sphere();
	std::cout << a({0, 0, 0}) << std::endl;
	auto b = TestFunctions::rastrigin();
	std::cout << b({0, 0, 0}) << std::endl;
	auto c = TestFunctions::ackley();
	std::cout << c({0, 0, 0}) << std::endl;

	std::cout << std::endl;

	// check get_bounds function
	auto bounds = TestFunctions::get_bounds("sphere");
	std::cout << bounds.first << " " << bounds.second << std::endl;
	bounds = TestFunctions::get_bounds("rastrigin");
	std::cout << bounds.first << " " << bounds.second << std::endl;
	bounds = TestFunctions::get_bounds("ackley");
	std::cout << bounds.first << " " << bounds.second << std::endl;

	return 0;
}