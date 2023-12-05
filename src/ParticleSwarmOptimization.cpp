// #include "../include/ParticleSwarmOptimization.hpp"

template <std::size_t dim>
ParticleSwarmOptimization<dim>::ParticleSwarmOptimization(
    const std::function<double(std::array<double, dim>)> &fitness_function, int n,
    int max_iter, double lower_bound, double upper_bound,
    double tolerance, double inertia_weight, double c1, double c2)
    : _fitness_function(fitness_function),
      _n(n),
      _max_iter(max_iter),
      _lower_bound(lower_bound),
      _upper_bound(upper_bound),
      _tolerance(tolerance),
      _intertia_weight(inertia_weight),
      _c1(c1),
      _c2(c2)
{
}

template <std::size_t dim>
int ParticleSwarmOptimization<dim>::initialize()
{
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    for (int i = 0; i < _n; i++)
    {
        _swarm.emplace_back(_fitness_function, _lower_bound, _upper_bound, generator);
        double current_fitness = _swarm[i].initialize();
        if (i == 0)
        {
            _global_best_value = current_fitness;
            _global_best_position = _swarm[i].get_best_position();
        }
        else if (current_fitness < _global_best_value)
        {
            _global_best_position = _swarm[i].get_best_position();
            _global_best_value = current_fitness;
        }
    }
    return 0;
}

template <std::size_t dim>
int ParticleSwarmOptimization<dim>::initialize_parallel()
{
    _swarm.resize(_n);
#pragma omp parallel
    {
        std::random_device rand_dev;
        std::mt19937 generator(rand_dev());
#pragma omp for schedule(static)
        for (int i = 0; i < _n; i++)
        {
            _swarm[i] = Particle<dim>(_fitness_function, _lower_bound, _upper_bound, generator);
            double current_fitness = _swarm[i].initialize();
            if (i == 0)
            {
                _global_best_value = current_fitness;
                _global_best_position = _swarm[i].get_best_position();
            }
            else if (current_fitness < _global_best_value)
            {
                _global_best_position = _swarm[i].get_best_position();
                _global_best_value = current_fitness;
            }
        }
    }
    return 0;
}

template <std::size_t dim>
int ParticleSwarmOptimization<dim>::optimize()
{
    int current_iter = 0;
    double temp_value = 0.0;
    while (current_iter < _max_iter)
    {
        for (auto &particle : _swarm)
        {
            // update particle position
            temp_value =
                particle.update(_global_best_position, _intertia_weight, _c1, _c2);
            // update global best position
            if (temp_value < _global_best_value)
            {
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
    // store in _max_iter the number of iterations
    _max_iter = current_iter;
    return 0;
}

template <std::size_t dim>
int ParticleSwarmOptimization<dim>::optimize_parallel()
{
    int current_iter = 0;
    double temp_value = 0.0;
    while (current_iter < _max_iter)
    {
#pragma omp parallel for schedule(static) reduction(min : _global_best_value) shared(_global_best_position)
        for (auto &particle : _swarm)
        {
            // update particle position
            temp_value =
                particle.update(_global_best_position, _intertia_weight, _c1, _c2);
            // update global best position
            if (temp_value < _global_best_value)
            {
                _global_best_value = temp_value;
#pragma omp critical
                {
                    _global_best_position = particle.get_best_position();
                }
            }
        }
        current_iter++;
    }
    // store in _max_iter the number of iterations
    _max_iter = current_iter;
    return 0;
}
