#include <iostream>
#include <random>
#include <vector>
#include <random>
#include <functional>

int main(int argc, char** argv) {
	std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<double> distr(1,1);
    // initialize the position and velocity vectors
	std::vector<double> _r1(20);
	std::vector<double> _r2(20);
    std::generate(_r1.begin(), _r1.end(), [&]() { return distr(generator); });
    std::generate(_r2.begin(), _r2.end(), [&]() { return distr(generator); });

	// print vector
	std::cout << "r1: ";
	for (auto &i : _r1) {
		std::cout << i << ", ";
	}
	return 0;
}