#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <iostream>
#include <array>
#include <random>
#include <functional>

// define a template for dim
template <std::size_t dim>

class Particle
{
	typedef std::array<double, dim> Vector;

private:
	Vector _position;
	Vector _velocity;
	Vector _best_position;
	double _best_value;
	Vector _r1;
	Vector _r2;
	double _lower_bound;
	double _upper_bound;
	const std::function<double(Vector)> &_fitness_function;
	std::mt19937 &_random_generator;

public:
	Particle(const std::function<double(std::array<double, dim>)> &fitness_function,
			 const double &lower_bound, const double &upper_bound, std::mt19937 &random_generator);
	~Particle() = default;

	// Initialize the particle velocity and position accorting to uniform distribution
	double initialize();

	// Update velocity and position of the particle
	double update(const Vector &global_best_position, const double &w, const double &c1, const double &c2);
	void print() const;

	// getters
	const Vector &get_position() const { return _position; }
	const double &get_best_value() const { return _best_value; }
	const Vector &get_best_position() const { return _best_position; }
};

#include "../src/Particle.cpp"
#endif