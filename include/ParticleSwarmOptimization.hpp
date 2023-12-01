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
	int _n;
	double _lower_bound;
	double _upper_bound;
	int _max_iter;
	double _tolerance;
	double _intertia_weight;
	double _c1, _c2;
	Vector _global_best_position;
	double _global_best_value;
	std::vector<Particle<dim>> _swarm;
	const std::function<double(std::array<double, dim>)> &_fitness_function;

public:
	ParticleSwarmOptimization(const std::function<double(std::array<double, dim>)> &fitness_function, int n, double lower_bound, double upper_bound, int max_iter, double _tolerance, double _inertia_weight, double _c1, double _c2);
	~ParticleSwarmOptimization() = default;

	/* row 1 to 9 pseudocode */
	int initialize();
	/* row 10 to 21 */
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