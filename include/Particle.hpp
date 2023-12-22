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
 * @paramposition_ the position of the particle in the search space
 * @param velocity_ the velocity of the particle in the search space
 * @param best_position_ the best position of all the particles in the search space
 * @param r1_ the first random vector used in the update
 * @param r2_ the second random vector used in the update
 * @param lower_bound_ the lower bound of the search space
 * @param upper_bound_ the upper bound of the search space
 * @param best_value_ the value of the fitness function in the global best position
 * @param random_generator_ the random number generator
 * @param fitness_function_ the fitness function to be optimized
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
	Vector position_;
	Vector velocity_;
	Vector best_position_;
	Vector r1_;
	Vector r2_;
	double lower_bound_;
	double upper_bound_;
	double best_value_;
	std::mt19937 random_generator_;
	std::function<double(std::array<double, dim>&)> fitness_function_;

public:
	/**
	 * @brief Construct a new Particle object
	 *
	 * @param fitness_function the fitness function to optimize
	 * @param lower_bound the lower bound of the search space, same for each dimension
	 * @param upper_bound the upper bound of the search space, same for each dimension
	 */
	Particle(const std::function<double(std::array<double, dim>&)> &fitness_function,
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
	const Vector &get_position() const { return position_; }
	const double &get_best_value() const { return best_value_; }
	const Vector &get_best_position() const { return best_position_; }

};

#include "Particle.cpp"
#endif