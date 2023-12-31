#ifndef PARTICLESWARMOPTIMIZATION_HPP
#define PARTICLESWARMOPTIMIZATION_HPP

#include <iostream>
#include <vector>
#include <array>
#include "Particle.hpp"

/**
 * @brief Class that represents the Particle Swarm Optimization algorithm.
 *
 * @param fitness_function the fitness function to be optimized
 * @param n the number of particles in the swarm
 * @param max_iter the maximum number of iterations
 * @param lower_bound the lower bound of the search space
 * @param upper_bound the upper bound of the search space
 * @param tolerance the tolerance for the stopping criterion
 * @param inertia_weight the inertia weight
 * @param c1 the cognitive parameter
 * @param c2 the social parameter
 * @param swarm the vector of Particle<dim> objects, containing the swarm's particles
 * @param global_best_value the best value of the fitness function found by the swarm
 * @param global_best_position the best position of the fitness function found by the swarm
 *
 * @tparam dim the dimension of the space in which the function is defined
 */
template <std::size_t dim>
class ParticleSwarmOptimization
{
	typedef std::array<double, dim> Vector;

private:
	const std::function<double(std::array<double, dim>&)> fitness_function_;
	int n_;
	int max_iter_;
	double lower_bound_;
	double upper_bound_;
	double tolerance_;
	double inertia_weight_;
	double c1_, c2_;
	double global_best_value_;
	Vector global_best_position_;
	std::vector<Particle<dim>> swarm_;

public:
	ParticleSwarmOptimization(const std::function<double(std::array<double, dim>&)> &fitness_function, int n,
							  int max_iter, double lower_bound, double upper_bound, double tolerance_,
							  double _inertia_weight, double c1_, double c2_);
	~ParticleSwarmOptimization() = default;

	/**
	 * @brief Initialize the swarm's particles, and the PSO initial state in serial
	 *
	 * @return int The status code (0: success, -1: error)
	 */
	int initialize();

	/**
	 * @brief Initialize the swarm's particles, and the PSO initial state in parallel with OpenMP
	 *
	 * @return int The status code (0: success, -1: error)
	 */
	int initialize_parallel();

	int optimize();

	/**
	 * @brief As ParticleSwarmOptimization::optimize, but stores the history of the best value every interval iterations
	 *
	 * @param history The vector where the history will be stored
	 * @param interval The interval between each history value
	 * @return int The status code (0: success, -1: error)
	 */
	int optimize(std::vector<double> &history, const int interval = 50);

	int optimize_parallel();

	/**
	 * @brief As ParticleSwarmOptimization::optimize_parallel, but stores the history of the best value every interval iterations
	 *
	 * @param history The vector where the history will be stored
	 * @param interval The interval between each history value
	 * @return int The status code (0: success, -1: error)
	 */
	int optimize_parallel(std::vector<double> &history, const int interval = 50);

	// getters
	const Vector &get_global_best_position() const { return global_best_position_; }
	const double &get_global_best_value() const { return global_best_value_; }
	const int &get_iter() const { return max_iter_; }
	const double &get_tolerance() const { return tolerance_; }
	};

#include "ParticleSwarmOptimization.cpp"
#endif