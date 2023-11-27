#include "../include/TestFunctions.hpp"

// get standard domain bounds for a given std::function object
const std::pair<double, double> TestFunctions::get_bounds(const std::string& function_name) {
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
	auto a = TestFunctions::sphere;
	std::cout << a({0, 0, 0}) << std::endl;
	auto b = TestFunctions::rastrigin;
	std::cout << b({0, 0, 0}) << std::endl;
	auto c = TestFunctions::ackley;
	std::cout << c({0, 0, 0}) << std::endl;

	// check get_bounds function
	auto bounds = TestFunctions::get_bounds("sphere");
	std::cout << bounds.first << " " << bounds.second << std::endl;
	bounds = TestFunctions::get_bounds("rastrigin");
	std::cout << bounds.first << " " << bounds.second << std::endl;
	bounds = TestFunctions::get_bounds("ackley");
	std::cout << bounds.first << " " << bounds.second << std::endl;

	return 0;
}