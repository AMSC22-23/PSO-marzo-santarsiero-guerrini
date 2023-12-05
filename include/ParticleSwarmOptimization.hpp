#ifndef PARTICLESWARMOPTIMIZATION_HPP
#define PARTICLESWARMOPTIMIZATION_HPP

#include <iostream>
#include <vector>
#include <array>
#include "Particle.hpp"

template <std::size_t dim>
class ParticleSwarmOptimization
{
	typedef std::array<double, dim> Vector;

private:
	const std::function<double(std::array<double, dim>)> _fitness_function;
	int _n;
	int _max_iter;
	double _lower_bound;
	double _upper_bound;
	double _tolerance;
	double _intertia_weight;
	double _c1, _c2;
	double _global_best_value;
	Vector _global_best_position;
	std::vector<Particle<dim>> _swarm;

public:
	ParticleSwarmOptimization(const std::function<double(std::array<double, dim>)> &fitness_function, int n,
							  int max_iter, double lower_bound, double upper_bound, double _tolerance,
							  double _inertia_weight, double _c1, double _c2);
	~ParticleSwarmOptimization() = default;

	/**
	 * @brief Initialize the swarm's particles, and the PSO initial state
	 *
	 * @return int The status code (0: success, -1: error)
	 */
	int initialize();
	int initialize_parallel();

	int optimize();
	int optimize_parallel();

	// getters
	const Vector &get_global_best_position() const { return _global_best_position; }
	const double &get_global_best_value() const { return _global_best_value; }
	const int &get_iter() const { return _max_iter; }
	const double &get_tolerance() const { return _tolerance; }
};

#include "../src/ParticleSwarmOptimization.cpp"
#endif