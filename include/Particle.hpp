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
	std::function<double(Vector)> _fitness_function;
	// TODO chiedere fitness function da utilizzare e come passarla;
public:
	Particle(const int dim, const bool inertia, const std::function<double(Vector)> fitness_function) : _position(dim), _velocity(dim), _best_position(dim), _fitness_function(fitness_function){};
	~Particle();

	/* Initialize the particle velocity and position accorting to uniform distribution
	 */
	int initialize(const double &lower_bound, const double &upper_bound);
	// Funzione che aggiorna la velocità e la posizione della particella
	double update(const Vector &global_best_position, const float &w, const float &c1, const float &c2, const Vector &r1, const Vector &r2);
	void print();

	Vector get_best_position();
};

#endif