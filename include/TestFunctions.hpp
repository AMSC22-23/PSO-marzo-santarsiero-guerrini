#ifndef TESTFUNCTIONS_HPP
#define TESTFUNCTIONS_HPP

#define _USE_MATH_DEFINES

#include <functional>
#include <iostream>
#include <array>
#include <math.h>
#include <cmath>

namespace TestFunctions
{
	// N-dimensional sphere function
	// Global minimum at f(0,...,0) = 0
	template <std::size_t dim>
	double sphere(std::array<double, dim> x);

	// N-dimensional rastrigin function
	// Global minimum at f(0,...,0) = 0
	template <std::size_t dim>
	double rastrigin(std::array<double, dim> x);

	// N-dimensional ackley function
	// Global minimum at f(0,...,0) = 0
	template <std::size_t dim>
	double ackley(std::array<double, dim> x);

	// Returns domain bounds for a given function
	const std::pair<double, double> get_bounds(const std::string &f);
};

#include "../src/TestFunctions.cpp"
#endif