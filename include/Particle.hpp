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
	std::function<double(Vector)> _fitness_function;
	// TODO chiedere fitness function da utilizzare e come passarla;
public:
	Particle(const int dim, const bool inertia, const std::function<double(Vector)>& fitness_function);
	~Particle() = default;

	//Initialize the particle velocity and position accorting to uniform distribution
	double initialize(const double &lower_bound, const double &upper_bound);
	
	// Update velocity and position of the particle
	double update(const Vector &global_best_position, const float &w, const float &c1, const float &c2);
	void print() const;

	const Vector& get_best_position() const;
};

#endif