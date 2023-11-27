#include "../include/ParticleSwarmOptimization.hpp"
// hello world main
int main(int argc, char** argv) {
	ParticleSwarmOptimization pso(50,2,0,10,50,1e-6,0.6,2,2);
	pso.initialize();
	pso.optimize();
	//Particle(2, false, [](Vector v) { return v[0] * v[0] + v[1] * v[1]; });
	std::cout << "Hello World!" << std::endl;
	return 0;
}
