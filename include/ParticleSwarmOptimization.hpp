#ifndef PARTICLESWARMOPTIMIZATION_HPP
#define PARTICLESWARMOPTIMIZATION_HPP

#include <iostream>
#include <vector>
#include "Particle.hpp"

class ParticleSwarmOptimization
{
private:
	int _n;
	int _dim;
	double _lower_bound;
	double _upper_bound;
	int _max_iter;
	double _tolerance;
	double _intertia_weight;
	double _c1, _c2;
	Vector _global_best_position;
	double _global_best_value;
	std::vector<Particle> _swarm;
	std::function<double(std::vector<double>)> _fitness_function;
public:
	ParticleSwarmOptimization(const std::function<double(std::vector<double>)>& fitness_function, int n, int dim, double lower_bound, double upper_bound, int max_iter, double _tolerance, double _inertia_weight, double _c1, double _c2);
	~ParticleSwarmOptimization() = default;

	/* row 1 to 9 pseudocode */
	int initialize();
	/* row 10 to 21 */
	int optimize();

	// getters
	const Vector& get_global_best_position() const { return _global_best_position; }
	const double& get_global_best_value() const { return _global_best_value; }
	const int& get_iter() const { return _max_iter; }
	const double& get_tolerance() const { return _tolerance; }

};

#endif