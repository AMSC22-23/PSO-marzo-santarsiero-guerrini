#ifndef TESTFUNCTIONS_HPP
#define TESTFUNCTIONS_HPP

#define _USE_MATH_DEFINES

#include <functional>
#include <iostream>
#include <array>
#include <math.h>
#include <cmath>

/**
 * @brief Namespace to contain the optimization test functions and the related utilities
 *
 */
namespace TestFunctions
{
	/**
	 * @brief N-dimensional sphere function with global minimum f(0,...,0) = 1
	 *
	 * @tparam dim the dimension of the space in which the function is defined
	 * @param x the point in which the function is evaluated
	 * @return double the value f(x)
	 */
	template <std::size_t dim>
	double sphere(const std::array<double, dim> &x);

	/**
	 * @brief N-dimensional rastrigin function with global minimum f(0,...,0) = 1
	 *
	 * @tparam dim the dimension of the space in which the function is defined
	 * @param x the point in which the function is evaluated
	 * @return double the value f(x)
	 */
	template <std::size_t dim>
	double rastrigin(const std::array<double, dim> &x);

	/**
	 * @brief N-dimensional ackley function with global minimum f(0,...,0) = 1
	 *
	 * @tparam dim the dimension of the space in which the function is defined
	 * @param x the point in which the function is evaluated
	 * @return double the value f(x)
	 */
	template <std::size_t dim>
	double ackley(const std::array<double, dim> &x);

	/**
	 * @brief Get the bounds (same for each dimension) of the search space for a given function
	 *
	 * @param f the name of the function
	 * @return const std::pair<double, double> the bounds of the search space
	 */
	const std::pair<double, double> get_bounds(const std::string &f);

	// Returns global minimum point for a given function
	template <std::size_t dim>
	const double get_global_minimum(const std::string &f);
};

#include "TestFunctions.cpp"
#endif