#ifndef TESTFUNCTIONS_HPP
#define TESTFUNCTIONS_HPP

#define _USE_MATH_DEFINES

#include <functional>
#include <iostream>
#include <vector>
#include <cmath>

namespace TestFunctions {
	// Returns a function object that computes the sphere function
	// Global minimum at f(0,...,0) = 0
	std::function<double(std::vector<double>)> sphere();

	// Returns a function object that computes the rastrigin function
	// Global minimum at f(0,...,0) = 0
	std::function<double(std::vector<double>)> rastrigin();

	// Returns a function object that computes the ackley function
	// Global minimum at f(0,...,0) = 0
	std::function<double(std::vector<double>)> ackley();


	// Returns domain bounds for a given function
	std::pair<double, double> get_bounds(const std::string& function_name);
};

#endif
