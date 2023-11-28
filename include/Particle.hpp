#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <iostream>
#include <vector>
#include <random>
#include <functional>

typedef std::vector<double> Vector;

class Particle
{

private:
	Vector _position;
	Vector _velocity;
	Vector _best_position;
	double _best_value;
	Vector _r1;
	Vector _r2;
	double _lower_bound;
	double _upper_bound;
	std::function<double(Vector)> _fitness_function;
public:
	Particle(const int dim, const std::function<double(Vector)>& fitness_function, const double &lower_bound, const double &upper_bound);
	~Particle() = default;

	//Initialize the particle velocity and position accorting to uniform distribution
	double initialize();

	// Update velocity and position of the particle
	double update(const Vector &global_best_position, const double &w, const double &c1, const double &c2);
	void print() const;


	// getters
	const Vector& get_position() const { return _position; }
	const double& get_best_value() const { return _best_value; }
	const Vector& get_best_position() const { return _best_position; }
};

#endif