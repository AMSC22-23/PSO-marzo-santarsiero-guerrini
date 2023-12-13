#include "../include/ParticleSwarmOptimization.hpp"
#include "../include/TestFunctions.hpp"
#include <iostream>
#include <fstream>
#include <chrono>

#define dimension 6

// test the error as function of the iteration number
int error_iterations_test()
{
	constexpr int particles = 62;
	constexpr double inertia = 0.6571;
	constexpr double max_iter = 1000;
	constexpr double c1 = 1.6319;
	constexpr double c2 = 0.6239;

	constexpr int log_interval = 1;
	// Collect data for error-iteration plot with different functions
	// Initialize the file
	std::ofstream file_out;
	file_out.open("../output/error_iterations.csv");
	if (!file_out)
	{
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
	file_out << "Iterations,Sphere_serial,Rastrigin_serial,Ackley_serial,Sphere_parallel,Rastrigin_parllel,Ackley_parallel" << std::endl;

	// Initialize history and log_interval
	std::vector<double> history_sphere;
	std::vector<double> history_rastrigin;
	std::vector<double> history_ackley;
	std::vector<double> history_sphere_p;
	std::vector<double> history_rastrigin_p;
	std::vector<double> history_ackley_p;

	// Optimize the sphere function
	std::pair<double, double> bounds = TestFunctions::get_bounds("sphere");
	ParticleSwarmOptimization<dimension> pso(TestFunctions::sphere<dimension>, particles, max_iter, bounds.first, bounds.second, 0, inertia, c1, c2);
	pso.initialize();
	int status = pso.optimize(history_sphere, log_interval);
	if (status != 0)
	{
		std::cout << "Error in optimization" << std::endl;
		return -1;
	}
	pso.initialize_parallel();
	status = pso.optimize_parallel(history_sphere_p, log_interval);

	// Optimize the rastrigin function
	bounds = TestFunctions::get_bounds("rastrigin");
	ParticleSwarmOptimization<dimension> pso1(TestFunctions::rastrigin<dimension>, particles, max_iter, bounds.first, bounds.second, 0, inertia, c1, c2);
	pso1.initialize();
	status = pso1.optimize(history_rastrigin, log_interval);
	if (status != 0)
	{
		std::cout << "Error in optimization" << std::endl;
		return -1;
	}
	pso1.initialize_parallel();
	status = pso1.optimize_parallel(history_rastrigin_p, log_interval);

	// Optimize the ackley function
	bounds = TestFunctions::get_bounds("ackley");
	ParticleSwarmOptimization<dimension> pso2(TestFunctions::ackley<dimension>, particles, max_iter, bounds.first, bounds.second, 0, inertia, c1, c2);
	pso2.initialize();
	status = pso2.optimize(history_ackley, log_interval);
	if (status != 0)
	{
		std::cout << "Error in optimization" << std::endl;
		return -1;
	}
	pso2.initialize_parallel();
	status = pso2.optimize_parallel(history_ackley_p, log_interval);

	// Print the history vectors size
	std::cout << "Sphere history size:\t" << history_sphere.size() << std::endl;
	std::cout << "Rastrigin history size:\t" << history_rastrigin.size() << std::endl;
	std::cout << "Ackley history size:\t" << history_ackley.size() << std::endl;

	// Get the exact global minimum
	double exact_spere = TestFunctions::get_global_minimum<dimension>("sphere");
	double exact_rastrigin = TestFunctions::get_global_minimum<dimension>("rastrigin");
	double exact_ackley = TestFunctions::get_global_minimum<dimension>("ackley");

	// Write to file the error values
	for (int i = 0; i < history_sphere.size(); i++)
	{
		double sphere_error = std::abs(history_sphere[i] - exact_spere);
		double rastrigin_error = std::abs(history_rastrigin[i] - exact_rastrigin);
		double ackley_error = std::abs(history_ackley[i] - exact_ackley);
		double sphere_error_p = std::abs(history_sphere_p[i] - exact_spere);
		double rastrigin_error_p = std::abs(history_rastrigin_p[i] - exact_rastrigin);
		double ackley_error_p = std::abs(history_ackley_p[i] - exact_ackley);
		// Write data to file
		file_out << i * log_interval << "," << sphere_error << "," << rastrigin_error << "," << ackley_error <<
			"," << sphere_error_p << "," << rastrigin_error_p << "," << ackley_error_p << std::endl;
	}

	// Close the file
	file_out.close();
	return 0;
}

// test the time as function of the number of particles
int time_numparticles_test()
{
	constexpr int max_particles = 600;
	constexpr double inertia = 0.6571;
	constexpr double max_iter = 2000;
	constexpr double c1 = 1.6319;
	constexpr double c2 = 0.6239;

	constexpr int log_interval = 5;
	// Collect data for error-iteration plot with different functions
	// Initialize the file
	std::ofstream file_out;
	file_out.open("../output/time_numparticles.csv");
	if (!file_out)
	{
		std::cout << "Error opening file" << std::endl;
		return -1;
	}
	// Write comments and header
	file_out << "# Execution time as function of the number of particles" << std::endl;
	file_out << "# Function: Ackley" << std::endl;
	file_out << "# Dimension: " << dimension << std::endl;
	file_out << "# Iterations: " << max_iter << std::endl;
	file_out << "# Inertia: " << inertia << std::endl;
	file_out << "# C_1: " << c1 << std::endl;
	file_out << "# C_2: " << c2 << std::endl;
	file_out << "Num_particles,Serial_time,Parallel_time,Speedup" << std::endl;

	std::pair<double, double> bounds = TestFunctions::get_bounds("ackley");

	for (int i = 1; i <= max_particles; i += log_interval)
	{
		if(i % (log_interval*10) == 0)
			std::cout << "Starting test with " << i << "particles" << std::endl;
		// Optimize the ackley function
		ParticleSwarmOptimization<dimension> pso(TestFunctions::ackley<dimension>, i, max_iter, bounds.first, bounds.second, 0, inertia, c1, c2);
		pso.initialize();
		auto t1 = std::chrono::high_resolution_clock::now();
		pso.optimize();
		auto t2 = std::chrono::high_resolution_clock::now();
		// Optimize the ackley function in parallel
		ParticleSwarmOptimization<dimension> pso1(TestFunctions::ackley<dimension>, i, max_iter, bounds.first, bounds.second, 0, inertia, c1, c2);
		pso1.initialize_parallel();
		auto t3 = std::chrono::high_resolution_clock::now();
		pso1.optimize_parallel();
		auto t4 = std::chrono::high_resolution_clock::now();
		// Write data to file
		file_out << i << "," <<
			std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "," <<
			std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count() << "," <<
			double(std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count())
			/ std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count() << std::endl;
	}
	file_out.close();
	return 0;
}

// take the time of the serial and parallel version of the algorithm
int serial_parallel_opt_test()
{
	constexpr int particles = 60;
	constexpr double inertia = 0.6571;
	constexpr double max_iter = 1000;
	constexpr double c1 = 1.6319;
	constexpr double c2 = 0.6239;
	// Print the parameters
	std::cout << "Function:.........Sphere" << std::endl;
	std::cout << "Space dimension:.." << dimension << std::endl;
	std::cout << "Particles:........" << particles << std::endl;
	std::cout << "Inertia:.........." << inertia << std::endl;
	std::cout << "Max iterations:..." << max_iter << std::endl;
	std::cout << "C_1:.............." << c1 << std::endl;
	std::cout << "C_2:.............." << c2 << std::endl;
	std::cout << std::endl;

	std::cout << "Serial optimization" << std::endl;
	std::pair<double, double> bounds = TestFunctions::get_bounds("sphere");
	ParticleSwarmOptimization<dimension> pso(TestFunctions::sphere<dimension>, particles, max_iter, bounds.first, bounds.second, 0, inertia, c1, c2);
	pso.initialize();
	auto t1 = std::chrono::high_resolution_clock::now();
	int status = pso.optimize();
	auto t2 = std::chrono::high_resolution_clock::now();
	std::cout << "\tStatus:..." << status << std::endl;
	std::cout << "\tError:...." << pso.get_global_best_value() - TestFunctions::get_global_minimum<dimension>("sphere") << std::endl;
	std::cout << "\tTime:....." << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
			  << " ms" << std::endl;
	std::cout << std::endl;
	std::cout << "Parallel optimization" << std::endl;
	ParticleSwarmOptimization<dimension> pso1(TestFunctions::sphere<dimension>, particles, max_iter, bounds.first, bounds.second, 0, inertia, c1, c2);
	pso1.initialize_parallel();
	auto t3 = std::chrono::high_resolution_clock::now();
	status = pso1.optimize_parallel();
	auto t4 = std::chrono::high_resolution_clock::now();
	std::cout << "\tStatus:..." << status << std::endl;
	std::cout << "\tError:...." << pso1.get_global_best_value() - TestFunctions::get_global_minimum<dimension>("sphere") << std::endl;
	std::cout << "\tTime:....." << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count()
			  << " ms" << std::endl;
	std::cout << std::endl;
	return 0;
}

int main(int argc, char ** argv)
{
	// Check the number of arguments
	if (argc != 2)
	{
		std::cout << "Usage: ./PSO test_name" << std::endl;
		std::cout << "Available tests: error_iterations, serial_parallel_opt, time_numparticles" << std::endl;
		return -1;
	}
	// Get from command line the required test
	std::string test = argv[1];
	if (test == "error_iterations")
		error_iterations_test();
	else if (test == "serial_parallel_opt")
		serial_parallel_opt_test();
	else if (test == "time_numparticles")
		time_numparticles_test();
	else
	{
		std::cout << "Usage: ./PSO test_name" << std::endl;
		std::cout << "Available tests: error_iterations, serial_parallel_opt, time_numparticles" << std::endl;
		return -1;
	}
	return 0;
}