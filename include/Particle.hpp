#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <iostream>
#include <vector>

class Particle {
	public:
		Particle(int n, int lower_bound, int upper_bound);
		~Particle();

		/* Initialize the particle velocity and position accorting to uniform distribution
		*/
		int initialize(double lower_bound, double upper_bound);
		int update_velocity(std::vector<double> global_best_position, double w, double c1, double c2);
		int update_position();
		int evaluate();
		int print();

		std::vector<double> get_position();
		std::vector<double> get_velocity();
		std::vector<double> get_best_position();
		double get_best_value();

	private:
		std::vector<double> position;
		std::vector<double> velocity;
		std::vector<double> best_position;
		double best_value;
};

#endif