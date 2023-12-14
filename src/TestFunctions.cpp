#include "../include/TestFunctions.hpp"

// N-dimensional sphere function
// Global minimum at f(0,...,0) = 0
template <std::size_t dim>
double TestFunctions::sphere(std::array<double, dim> x)
{
	double sum = 0.0;
	for (auto &i : x)
	{
		sum += i * i;
	}
	return sum;
}

// N-dimensional rastrigin function
// Global minimum at f(0,...,0) = 0
template <std::size_t dim>
double TestFunctions::rastrigin(std::array<double, dim> x)
{
	double sum = 0.0;
	for (auto &i : x)
	{
		sum += (i * i - 10 * cos(2 * M_PI * i));
	}
	return 10 * x.size() + sum;
}

// N-dimensional ackley function
// Global minimum at f(0,...,0) = 0
template <std::size_t dim>
double TestFunctions::ackley(std::array<double, dim> x)
{
	double sum1 = 0.0;
	double sum2 = 0.0;
	for (auto &i : x)
	{
		sum1 += i * i;
		sum2 += cos(2 * M_PI * i);
	}
	return -20 * exp(-0.2 * sqrt(sum1 / x.size())) - exp(sum2 / x.size()) + 20 + M_E;
}

// get standard domain bounds for a given function
const std::pair<double, double> TestFunctions::get_bounds(const std::string &function_name)
{
	if (function_name == "sphere")
	{
		return std::make_pair(-100.0, 100.0);
	}
	else if (function_name == "rastrigin")
	{
		return std::make_pair(-5.12, 5.12);
	}
	else if (function_name == "ackley")
	{
		return std::make_pair(-32.768, 32.768);
	}
	else
	{
		std::cerr << "Error: function not found" << std::endl;
		return std::make_pair(0, 0);
	}
}

// get global minimum for a given function
template <std::size_t dim>
double TestFunctions::get_global_minimum(const std::string &function_name)
{
	std::array<double, dim> x;
	x.fill(0.0);

	if (function_name == "sphere")
	{
		return TestFunctions::sphere<dim>(x);
	}
	else if (function_name == "rastrigin")
	{
		return TestFunctions::rastrigin<dim>(x);
	}
	else if (function_name == "ackley")
	{
		return TestFunctions::ackley<dim>(x);
	}
	else
	{
		std::cerr << "Error: function not found" << std::endl;
		return -1;
	}
}

/*
int main()
{
	// check if the functions returns f(0,...,0) ~ 0

	std::cout << TestFunctions::sphere<3>({0, 0, 0}) << std::endl;

	std::cout << TestFunctions::rastrigin<3>({0, 0, 0}) << std::endl;

	std::cout << TestFunctions::ackley<3>({0, 0, 0}) << std::endl;

	// check get_bounds function
	auto bounds = TestFunctions::get_bounds("sphere");
	std::cout << bounds.first << " " << bounds.second << std::endl;
	bounds = TestFunctions::get_bounds("rastrigin");
	std::cout << bounds.first << " " << bounds.second << std::endl;
	bounds = TestFunctions::get_bounds("ackley");
	std::cout << bounds.first << " " << bounds.second << std::endl;

	return 0;
}*/