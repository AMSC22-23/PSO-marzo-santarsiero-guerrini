#ifndef PARTICLESWARMOPTIMIZATION_HPP
#define PARTICLESWARMOPTIMIZATION_HPP

#include <iostream>
#include <vector>
#include "Particle.hpp"

class ParticleSwarmOptimization
{
private:
	int _n;
	int _lower_bound;
	int _upper_bound;
	int _max_iter;
	double _tolerance;
	float _intertia_weight;
	float _c1, _c2;
	Vector _global_best_postion;
	std::vector<Particle> _swarm;
public:
	ParticleSwarmOptimization(std::function<double(std::vector<double>)> fitness_function, int lower_bound, int upper_bound, int dim, int n, int max_iter);
	~ParticleSwarmOptimization();

	// row 1 to 9 pseudocode
	int initialize();
	// row 10 to 21
	int optimize();

	// getters for results
	double get_global_best_value() const;
	const Vector& get_global_best_position() const;
	int get_iter() const;
	double get_tolerance() const;

	void print() const;

};

#endif