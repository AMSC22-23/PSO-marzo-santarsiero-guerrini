#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <iostream>
#include <array>
#include <random>
#include <functional>
#include <memory>

/**
 * @brief Class that represents a single particle in the swarm
 * 
 * @param _position the position of the particle in the search space
 * @param _velocity the velocity of the particle in the search space
 * @param _best_position the best position of all the particles in the search space
 * @param _r1 the first random vector used in the update
 * @param _r2 the second random vector used in the update
 * @param _lower_bound the lower bound of the search space
 * @param _upper_bound the upper bound of the search space
 * @param _best_value the value of the fitness function in the global best position
 * @param _random_generator the random number generator
 * @param _fitness_function the fitness function to be optimized
 * 
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
	Vector _position;
	Vector _velocity;
	Vector _best_position;
	Vector _r1;
	Vector _r2;
	double _lower_bound;
	double _upper_bound;
	double _best_value;
	std::mt19937 _random_generator;
	std::function<double(std::array<double, dim>)> _fitness_function;

public:

	Particle(const std::function<double(std::array<double, dim>)> &fitness_function,
			 const double &lower_bound, const double &upper_bound);
	Particle() = default;
	~Particle() = default;

	/**
	 * @brief Initialize the particle velocity and position according to uniform distribution
	 * 
	 * @return double representing the value of the fitness function in the initial position of the particle
	 */
	double initialize();

	/**
	 * @brief Update velocity and position of the particle
	 * 
	 * @param global_best_position the best position of the swarm
	 * @param w the inertia weight
	 * @param c1 the cognitive parameter
	 * @param c2 the social parameter
	 * @return double representing the value of the fitness function in the best global position,
	 * eventually updated if the current position is the best one
	 */
	double update(const Vector &global_best_position, const double &w, const double &c1, const double &c2);

	void print() const;

	// getters
	const Vector &get_position() const { return _position; }
	const double &get_best_value() const { return _best_value; }
	const Vector &get_best_position() const { return _best_position; }
};

#include "../src/Particle.cpp"
#endif