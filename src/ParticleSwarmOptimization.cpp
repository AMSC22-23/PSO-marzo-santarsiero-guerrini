#include "../include/ParticleSwarmOptimization.hpp"

ParticleSwarmOptimization::ParticleSwarmOptimization(
    const std::function<double(std::vector<double>)> &fitness_function, int n,
    int dim, double lower_bound, double upper_bound, int max_iter,
    double tolerance, double inertia_weight, double c1, double c2)
    : _fitness_function(fitness_function),
      _n(n),
      _dim(dim),
      _lower_bound(lower_bound),
      _upper_bound(upper_bound),
      _max_iter(max_iter),
      _tolerance(tolerance),
      _intertia_weight(inertia_weight),
      _c1(c1),
      _c2(c2) {}

int ParticleSwarmOptimization::initialize() {
  for (int i = 0; i < _n; i++) {
    _swarm.emplace_back(_dim, _fitness_function, _lower_bound, _upper_bound);
    double current_fitness = _swarm.back().initialize();
    if (i == 0) {
      _global_best_value = current_fitness;
      _global_best_position = _swarm.back().get_best_position();
    } else if (current_fitness < _global_best_value) {
      _global_best_position = _swarm.back().get_best_position();
      _global_best_value = current_fitness;
    }
  }
  return 0;
}

int ParticleSwarmOptimization::optimize() {
  int current_iter = 0;
  double temp_value = 0.0;
  while (current_iter < _max_iter) {
    for (auto &particle : _swarm) {
      // update particle position
      temp_value =
          particle.update(_global_best_position, _intertia_weight, _c1, _c2);
      // update global best position
      if (temp_value < _global_best_value) {
        _global_best_value = temp_value;
        _global_best_position = particle.get_best_position();
      }
    }
    current_iter++;

    /*// log
    std::cout << "Best value: " << _global_best_value;
    std::cout << "\tBest position:\t(";
    for (auto &i : _global_best_position) {
      std::cout << i << ", ";
    }
    std::cout << "\b\b)" << std::endl;
    // end log*/
  }
  return 0;
}

int ParticleSwarmOptimization::optimize_parallel() {
  int current_iter = 0;
  double temp_value = 0.0;
  while (current_iter < _max_iter) {
    #pragma omp parallel for reduction(min: _global_best_value) shared(_global_best_position)
    for (auto &particle : _swarm) {
      // update particle position
      temp_value =
          particle.update(_global_best_position, _intertia_weight, _c1, _c2);
      // update global best position
      if (temp_value < _global_best_value) {
        _global_best_value = temp_value;
        #pragma omp atomic
        _global_best_position = particle.get_best_position();
      }
    }
    current_iter++;
  }
  return 0;
}
