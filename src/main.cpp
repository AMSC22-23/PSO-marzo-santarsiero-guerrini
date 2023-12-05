#include "../include/ParticleSwarmOptimization.hpp"
#include "../include/TestFunctions.hpp"
#include <iostream>
#include <fstream>
#include <chrono>

#define dimension 4

// hello world main
int main(int /*argc*/, char** /*argv*/) {
	constexpr int particles = 50;
	constexpr double inertia = 0.4;
	constexpr double c1 = 0.9;
	constexpr double c2 = 2.0;
	// Collect data for error-iteration plot with different functions
	// Initialize the file
	std::ofstream file_out;
	file_out.open("error_iterations.csv");
	if(!file_out) {
		std::cout << "Error opening file" << std::endl;
		return -1;
	}
	// Write comments and header
	file_out << "# Error as function of iteration number for Sphere, Ackley, and Rastrigin functions" << std::endl;
	file_out << "# Dimension:\t" << dimension << std::endl;
	file_out << "# Particles:\t" << particles << std::endl;
	file_out << "# Inertia:\t" << inertia << std::endl;
	file_out << "# C_1:\t" << c1 << std::endl;
	file_out << "# C_2:\t" << c2 << std::endl;
	file_out << "Iterations,Sphere_error,Rastrigin_error,Ackley_error," << std::endl;

	// Iterate over different number of iterations
	for(int i = 100; i <= 100000; i *= 2) {
		// Sphere function optimization
		std::pair<double, double> bounds = TestFunctions::get_bounds("sphere");
		ParticleSwarmOptimization<dimension> pso(TestFunctions::sphere<dimension>, particles, i, bounds.first, bounds.second, 0, inertia, c1, c2);
		pso.initialize_parallel();
		int status = pso.optimize_parallel();
		if(status != 0) {
			std::cout << "Error in optimization" << std::endl;
			return -1;
		}
		double sphere_error = std::abs(pso.get_global_best_value());
		// Rastrigin function optimization
		bounds = TestFunctions::get_bounds("rastrigin");
		ParticleSwarmOptimization<dimension> pso1(TestFunctions::rastrigin<dimension>, particles, i, bounds.first, bounds.second, 0, inertia, c1, c2);
		pso1.initialize_parallel();
		status = pso1.optimize_parallel();
		if(status != 0) {
			std::cout << "Error in optimization" << std::endl;
			return -1;
		}
		double rastrigin_error = std::abs(pso1.get_global_best_value());
		// Ackley function optimization
		bounds = TestFunctions::get_bounds("ackley");
		ParticleSwarmOptimization<dimension> pso2(TestFunctions::ackley<dimension>, particles, i, bounds.first, bounds.second, 0, inertia, c1, c2);
		pso2.initialize_parallel();
		status = pso2.optimize_parallel();
		if(status != 0) {
			std::cout << "Error in optimization" << std::endl;
			return -1;
		}
		double ackley_error = std::abs(pso2.get_global_best_value());
		// Write data to file
		file_out << i << "," << sphere_error << "," << rastrigin_error << "," << ackley_error << "," << std::endl;
	}



/*
	// Sphere function optimization
	std::cout << "Sphere optimization:" << std::endl;
	std::pair<double, double> bounds = TestFunctions::get_bounds("sphere");
	ParticleSwarmOptimization<dimension> pso(TestFunctions::sphere<dimension>, particles, 100000, bounds.first, bounds.second, 10e-6, 0.4, 0.9, 2.0);
	pso.initialize();
	auto t1 = std::chrono::high_resolution_clock::now();
	int status = pso.optimize();
    auto t2 = std::chrono::high_resolution_clock::now();
	std::cout << "Status: " << status << std::endl;
	std::cout << "Global best value: " << pso.get_global_best_value() << std::endl;
	std::cout << "Global best position: (" << pso.get_global_best_position()[0] << ", " << pso.get_global_best_position()[1] << ")" << std::endl;
	std::cout << "Iterations: " << pso.get_iter() << std::endl;
	std::cout << "Tolerance: " << pso.get_tolerance() << std::endl;
	std::cout << std::endl;

	ParticleSwarmOptimization<dimension> pso1(TestFunctions::sphere<dimension>, particles, 100000, bounds.first, bounds.second, 10e-6, 0.4, 0.9, 2.0);
	pso1.initialize();
	auto t3 = std::chrono::high_resolution_clock::now();
	status = pso1.optimize_parallel();
    auto t4 = std::chrono::high_resolution_clock::now();
	std::cout << "Status: " << status << std::endl;
	std::cout << "Global best value: " << pso1.get_global_best_value() << std::endl;
	std::cout << "Global best position: (" << pso1.get_global_best_position()[0] << ", " << pso1.get_global_best_position()[1] << ")" << std::endl;
	std::cout << "Iterations: " << pso1.get_iter() << std::endl;
	std::cout << "Tolerance: " << pso1.get_tolerance() << std::endl;
	std::cout << std::endl;
    std::cout << "Time taken: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
              << " milliseconds\n";
	 std::cout << "Time taken parallel: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t4-t3).count()
              << " milliseconds\n";
*/
	return 0;
}