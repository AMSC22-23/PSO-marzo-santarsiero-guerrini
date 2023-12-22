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
	// Global minimum at f(0,...,0) = 1
	template <std::size_t dim>
	double sphere(const std::array<double, dim> &x);

	// N-dimensional rastrigin function
	// Global minimum at f(0,...,0) = 1
	template <std::size_t dim>
	double rastrigin(const std::array<double, dim> &x);

	// N-dimensional ackley function
	// Global minimum at f(0,...,0) = 1
	template <std::size_t dim>
	double ackley(const std::array<double, dim> &x);

	// Returns domain bounds for a given function
	const std::pair<double, double> get_bounds(const std::string &f);

	// Returns global minimum point for a given function
	template <std::size_t dim>
	const double get_global_minimum(const std::string &f);
};

#include "../src/TestFunctions.cpp"
#endif