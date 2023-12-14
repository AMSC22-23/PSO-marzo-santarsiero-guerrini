#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <iostream>
#include <array>
#include <random>
#include <functional>
#include <memory>

/**
 * @brief Class that represents a single particle in the swarm
 * The particle is characterized by its position, velocity, and best position dim-dimensional vectors.
 * It also has the fitness function that needs to be optimized and the bounds of the search space.
 * @tparam dim the dimension of the space in which the function is defined
 */
template <std::size_t dim>
class Particle
{
	/**
	 * @brief Type trait to represent a vector in a dim-dimensional space
	 * This is just dim-dimensional array of doubles
	 */
	typedef std::array<double, dim> Vector;
private:
	std::function<double(std::array<double, dim>)> _fitness_function;
	Vector _position;
	Vector _velocity;
	Vector _best_position;
	Vector _r1;
	Vector _r2;
	double _lower_bound;
	double _upper_bound;
	double _best_value;
	std::shared_ptr<std::mt19937> _random_generator;

public:

	Particle(const std::function<double(std::array<double, dim>)> &fitness_function,
			 const double &lower_bound,
			 const double &upper_bound,
			 std::shared_ptr<std::mt19937> random_generator);

	Particle() = default;
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