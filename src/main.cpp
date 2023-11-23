#include "../include/ParticleSwarmOptimization.hpp"
// hello world main
int main(int argc, char** argv) {
	Particle(2, false, [](Vector v) { return v[0] * v[0] + v[1] * v[1]; });
	std::cout << "Hello World!" << std::endl;
	return 0;
}
