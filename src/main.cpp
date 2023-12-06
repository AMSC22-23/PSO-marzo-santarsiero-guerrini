#include "../include/ParticleSwarmOptimization.hpp"
#include "../include/TestFunctions.hpp"
#include <iostream>
#include <fstream>
#include <chrono>

#define dimension 6


int main(int /*argc*/, char** /*argv*/) {
	constexpr int particles = 63;
	constexpr double inertia = 0.6571;
	constexpr double max_iter = 100;
	constexpr double c1 = 1.6319;
	constexpr double c2 = 0.6239;

	constexpr int log_interval = 1;
	// Collect data for error-iteration plot with different functions
	// Initialize the file
	std::ofstream file_out;
	file_out.open("./output/error_iterations.csv");
	if(!file_out) {
		std::cout << "Error opening file" << std::endl;
		return -1;
	}
	// Write comments and header
	file_out << "# Error as function of iteration number for Sphere, Ackley, and Rastrigin functions" << std::endl;
	file_out << "# Dimension: " << dimension << std::endl;
	file_out << "# Particles: " << particles << std::endl;
	file_out << "# Inertia: " << inertia << std::endl;
	file_out << "# C_1: " << c1 << std::endl;
	file_out << "# C_2: " << c2 << std::endl;
	file_out << "Iterations,Sphere_error,Rastrigin_error,Ackley_error" << std::endl;

	// Initialize history and log_interval
	std::vector<double> history_sphere;
	std::vector<double> history_rastrigin;
	std::vector<double> history_ackley;

	// Optimize the sphere function
	std::pair<double, double> bounds = TestFunctions::get_bounds("sphere");
	ParticleSwarmOptimization<dimension> pso(TestFunctions::sphere<dimension>, particles, max_iter, bounds.first, bounds.second, 0, inertia, c1, c2);
	pso.initialize();
	int status = pso.optimize(history_sphere, log_interval);
	if(status != 0) {
		std::cout << "Error in optimization" << std::endl;
		return -1;
	}

	// Optimize the rastrigin function
	bounds = TestFunctions::get_bounds("rastrigin");
	ParticleSwarmOptimization<dimension> pso1(TestFunctions::rastrigin<dimension>, particles, max_iter, bounds.first, bounds.second, 0, inertia, c1, c2);
	pso1.initialize();
	status = pso1.optimize(history_rastrigin, log_interval);
	if(status != 0) {
		std::cout << "Error in optimization" << std::endl;
		return -1;
	}

	// Optimize the ackley function
	bounds = TestFunctions::get_bounds("ackley");
	ParticleSwarmOptimization<dimension> pso2(TestFunctions::ackley<dimension>, particles, max_iter, bounds.first, bounds.second, 0, inertia, c1, c2);
	pso2.initialize();
	status = pso2.optimize(history_ackley, log_interval);
	if(status != 0) {
		std::cout << "Error in optimization" << std::endl;
		return -1;
	}

	// Print the history vectors size
	std::cout << "Sphere history size:\t" << history_sphere.size() << std::endl;
	std::cout << "Rastrigin history size:\t" << history_rastrigin.size() << std::endl;
	std::cout << "Ackley history size:\t" << history_ackley.size() << std::endl;

	// Get the exact global minimum
	double exact_spere = TestFunctions::get_global_minimum<dimension>("sphere");
	double exact_rastrigin = TestFunctions::get_global_minimum<dimension>("rastrigin");
	double exact_ackley = TestFunctions::get_global_minimum<dimension>("ackley");

	// Write to file the error values
	for(int i = 0; i < history_sphere.size(); i++) {
		double sphere_error = std::abs(history_sphere[i]-exact_spere);
		double rastrigin_error = std::abs(history_rastrigin[i]-exact_rastrigin);
		double ackley_error = std::abs(history_ackley[i]-exact_ackley);
		// Write data to file
		file_out << i*log_interval << "," << sphere_error << "," << rastrigin_error << "," << ackley_error << std::endl;
	}

	// Close the file
	file_out.close();

	return 0;
}