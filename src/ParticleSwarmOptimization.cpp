// #include "ParticleSwarmOptimization.hpp"

template <std::size_t dim>
ParticleSwarmOptimization<dim>::ParticleSwarmOptimization(
    const std::function<double(std::array<double, dim>&)> &fitness_function, int n,
    int max_iter, double lower_bound, double upper_bound,
    double tolerance, double inertia_weight, double c1, double c2)
    : fitness_function_(fitness_function),
      n_(n),
      max_iter_(max_iter),
      lower_bound_(lower_bound),
      upper_bound_(upper_bound),
      tolerance_(tolerance),
      inertia_weight_(inertia_weight),
      c1_(c1),
      c2_(c2)
{
}

template <std::size_t dim>
int ParticleSwarmOptimization<dim>::initialize()
{
    // Initialize the swarm, creating n particles
    for (int i = 0; i < n_; i++)
    {
        swarm_.emplace_back(fitness_function_, lower_bound_, upper_bound_);
        double current_fitness = swarm_[i].initialize();
        // if the current particle is the first one, initialize the global best value and position
        if (i == 0)
        {
            global_best_value_ = current_fitness;
            global_best_position_ = swarm_[i].get_best_position();
        }
        // otherwise, update the global best value and position if necessary
        else if (current_fitness < global_best_value_)
        {
            global_best_position_ = swarm_[i].get_best_position();
            global_best_value_ = current_fitness;
        }
    }
    return 0;
}

template <std::size_t dim>
int ParticleSwarmOptimization<dim>::initialize_parallel()
{
    swarm_.resize(n_);
    // Initialize the swarm, creating n particles in parallel
#pragma omp parallel for schedule(static)
        for (int i = 0; i < n_; i++)
        {
            swarm_[i] = Particle<dim>(fitness_function_, lower_bound_, upper_bound_);
            double current_fitness = swarm_[i].initialize();
            // if the current particle is the first one, initialize the global best value and position
            if (i == 0)
            {
                global_best_value_ = current_fitness;
                global_best_position_ = swarm_[i].get_best_position();
            }
            // otherwise, update the global best value and position if necessary
            else if (current_fitness < global_best_value_)
            {
                global_best_position_ = swarm_[i].get_best_position();
                global_best_value_ = current_fitness;
            }
        }
    return 0;
}

template <std::size_t dim>
int ParticleSwarmOptimization<dim>::optimize()
{
    int current_iter = 0;
    double temp_value = 0.0;
    while (current_iter < max_iter_)
    {
        for (auto &particle : swarm_)
        {
            // update particle position
            temp_value =
                particle.update(global_best_position_, inertia_weight_, c1_, c2_);
            // update global best position
            if (temp_value < global_best_value_)
            {
                global_best_value_ = temp_value;
                global_best_position_ = particle.get_best_position();
            }
        }
        current_iter++;

    }
    // store in max_iter_ the number of iterations
    max_iter_ = current_iter;
    return 0;
}

template <std::size_t dim>
int ParticleSwarmOptimization<dim>::optimize(std::vector<double> &history, const int interval)
{
    int current_iter = 0;
    double temp_value = 0.0;
    // update all the particles, until the maximum number of iterations is reached
    while (current_iter < max_iter_)
    {
        for (auto &particle : swarm_)
        {
            // update particle position
            temp_value =
                particle.update(global_best_position_, inertia_weight_, c1_, c2_);
            // update global best position
            if (temp_value < global_best_value_)
            {
                global_best_value_ = temp_value;
                global_best_position_ = particle.get_best_position();
            }
        }
        // store current global best value in history
        if(current_iter % interval == 0)
        history.push_back(global_best_value_);

        current_iter++;
    }
    // store in max_iter_ the number of iterations
    max_iter_ = current_iter;
    return 0;
}

template <std::size_t dim>
int ParticleSwarmOptimization<dim>::optimize_parallel()
{
    int current_iter = 0;
    double temp_value = 0.0;
    while (current_iter < max_iter_)
    {
#pragma omp parallel for reduction(min : global_best_value_) shared(global_best_position_)
        for (auto &particle : swarm_)
        {
            // update particle position
            temp_value =
                particle.update(global_best_position_, inertia_weight_, c1_, c2_);
            // update global best position
            if (temp_value < global_best_value_)
            {
                global_best_value_ = temp_value;
#pragma omp critical
                {
                    global_best_position_ = particle.get_best_position();
                }
            }
        }
        current_iter++;
    }
    // store in max_iter_ the number of iterations
    max_iter_ = current_iter;
    return 0;
}

template <std::size_t dim>
int ParticleSwarmOptimization<dim>::optimize_parallel(std::vector<double> &history, const int interval)
{
    int current_iter = 0;
    double temp_value = 0.0;
    // update all the particles in parallel, until the maximum number of iterations is reached
    while (current_iter < max_iter_)
    {
#pragma omp parallel for reduction(min : global_best_value_) shared(global_best_position_)
        for (auto &particle : swarm_)
        {
            // update particle position
            temp_value =
                particle.update(global_best_position_, inertia_weight_, c1_, c2_);
            // update global best position
            if (temp_value < global_best_value_)
            {
                global_best_value_ = temp_value;
#pragma omp critical
                {
                    global_best_position_ = particle.get_best_position();
                }
            }
        }
        // store current global best value in history
        if(current_iter % interval == 0)
        history.push_back(global_best_value_);
        current_iter++;
    }
    // store in max_iter_ the number of iterations
    max_iter_ = current_iter;
    return 0;
}
