#include "../include/ParticleSwarmOptimization.hpp"
#include "../include/TestFunctions.hpp"
#include <iostream>

// hello world main
int main(int argc, char** argv) {
	// Sphere function optimization
	std::cout << "Sphere optimization:" << std::endl;
	std::pair<double, double> bounds = TestFunctions::get_bounds("sphere");
	ParticleSwarmOptimization pso(TestFunctions::sphere, 50, 2, bounds.first, bounds.second, 1000, 10e-6, 0.4, 0.9, 2.0);
	pso.initialize();
	int status = pso.optimize();
	std::cout << "Status: " << status << std::endl;
	std::cout << "Global best value: " << pso.get_global_best_value() << std::endl;
	std::cout << "Global best position: (" << pso.get_global_best_position()[0] << ", " << pso.get_global_best_position()[1] << ")" << std::endl;
	std::cout << "Iterations: " << pso.get_iter() << std::endl;
	std::cout << "Tolerance: " << pso.get_tolerance() << std::endl;
	std::cout << std::endl;
	return 0;
}
