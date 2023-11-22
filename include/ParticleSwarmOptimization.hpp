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
	ParticleSwarmOptimization(int n, int lower_bound, int upper_bound, int max_iter);
	~ParticleSwarmOptimization();

	/* row 1 to 9 pseudocode */
	int initialize();
	/* row 10 to 21 */
	int optimize();

};

#endif