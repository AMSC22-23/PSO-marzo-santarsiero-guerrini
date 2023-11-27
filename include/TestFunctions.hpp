#ifndef TESTFUNCTIONS_HPP
#define TESTFUNCTIONS_HPP

#define _USE_MATH_DEFINES

#include <functional>
#include <iostream>
#include <vector>
#include <cmath>

namespace TestFunctions {
	// N-dimensional sphere function
	// Global minimum at f(0,...,0) = 0
	const std::function<double(std::vector<double>)> sphere =
		[](std::vector<double> x) {
			double sum = 0.0;
			for (auto &i : x) {
				sum += i * i;
			}
			return sum;
		};

	// N-dimensional rastrigin function
	// Global minimum at f(0,...,0) = 0
	const std::function<double(std::vector<double>)> rastrigin =
		[](std::vector<double> x) {
		double sum = 0.0;
		for (auto &i : x) {
			sum += (i * i - 10 * cos(2 * M_PI * i));
		}
		return 10 * x.size() + sum;
		};

	// N-dimensional ackley function
	// Global minimum at f(0,...,0) = 0
	const std::function<double(std::vector<double>)> ackley =
		[](std::vector<double> x) {
		double sum1 = 0.0;
		double sum2 = 0.0;
		for (auto &i : x) {
			sum1 += i * i;
			sum2 += cos(2 * M_PI * i);
		}
		return -20 * exp(-0.2 * sqrt(sum1 / x.size())) - exp(sum2 / x.size()) + 20 + M_E;
		};


	// Returns domain bounds for a given function
	const std::pair<double, double> get_bounds(const std::string& f);
};

#endif