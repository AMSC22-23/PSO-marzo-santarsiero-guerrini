#include "../include/ParticleSwarmOptimization.hpp"
#include "../include/TestFunctions.hpp"
#include <iostream>
#include <fstream>
#include <chrono>

#define dimension 2

// hello world main
/*
constexpr int particles = 63;
	constexpr double inertia = 0.6571;
	constexpr double max_iter = 1000;
	constexpr double c1 = 1.6319;
	constexpr double c2 = 0.6239;*/

int main(int /*argc*/, char** /*argv*/) {
	constexpr int particles = 63;
	constexpr int max_iter = 100000;

	// Ackley function optimization
	std::cout << "Ackley optimization:" << std::endl;
	std::pair<double, double> bounds = TestFunctions::get_bounds("ackley");
	ParticleSwarmOptimization<dimension> pso(TestFunctions::ackley<dimension>, particles, max_iter, bounds.first, bounds.second, 10e-6, 0.6571, 1.6319, 0.6239);
	pso.initialize();
	auto t1 = std::chrono::high_resolution_clock::now();
	int status = pso.optimize();
    auto t2 = std::chrono::high_resolution_clock::now();
	std::cout << "Status serial: " << status << std::endl;
	std::cout << "Iterations serial: " << pso.get_iter() << std::endl;
	std::cout << std::endl;
	ParticleSwarmOptimization<dimension> pso1(TestFunctions::sphere<dimension>, 50, 10000, bounds.first, bounds.second, 0, 0.7, 2.0, 0.8);
	pso1.initialize_parallel();
	auto t3 = std::chrono::high_resolution_clock::now();
	status = pso1.optimize_parallel();
    auto t4 = std::chrono::high_resolution_clock::now();
	std::cout << "Status parallel: " << status << std::endl;
	std::cout << "Iterations parallel: " << pso1.get_iter() << std::endl;
	std::cout << std::endl;
    std::cout << "Time taken serial: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
              << " milliseconds" << std::endl;
	 std::cout << "Time taken parallel: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t4-t3).count()
              << " milliseconds" << std::endl << std::endl;
	return 0;
}
