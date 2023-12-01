#include "../include/ParticleSwarmOptimization.hpp"
#include "../include/TestFunctions.hpp"
#include <iostream>
#include <chrono>

#define dimension 4

// hello world main
int main(int argc, char** argv) {

	// Sphere function optimization
	std::cout << "Sphere optimization:" << std::endl;
	std::pair<double, double> bounds = TestFunctions::get_bounds("sphere");
	ParticleSwarmOptimization<dimension> pso(TestFunctions::sphere<dimension>, 50, bounds.first, bounds.second, 100000, 10e-6, 0.4, 0.9, 2.0);
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
	ParticleSwarmOptimization<dimension> pso1(TestFunctions::sphere<dimension>, 50, bounds.first, bounds.second, 100000, 10e-6, 0.4, 0.9, 2.0);
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
	return 0;
}
