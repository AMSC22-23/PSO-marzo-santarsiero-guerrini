#include "Particle.hpp"

template <std::size_t dim>
Particle<dim>::Particle(const std::function<double(std::array<double, dim>&)> &fitness_function,
                        const double &lower_bound, const double &upper_bound)
    : fitness_function_(fitness_function),
      lower_bound_(lower_bound),
      upper_bound_(upper_bound)
{
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    random_generator_ = generator;
}

template <std::size_t dim>
double Particle<dim>::initialize()
{
    // Create the uniform double generator in the range [lower_bound, upper_bound]
    std::uniform_real_distribution<double> distr(lower_bound_, upper_bound_);
    // Initialize the position and velocity vectors
    std::generate(position_.begin(), position_.end(), [&]()
                  { return distr(random_generator_); });
    std::generate(velocity_.begin(), velocity_.end(), [&]()
                  { return distr(random_generator_); });
    // Initialize the best position
    best_position_ = position_;
    // Initialize the best value
    best_value_ = fitness_function_(best_position_);
    return best_value_;
}

template <std::size_t dim>
double Particle<dim>::update(const Vector &global_best_position, const double &w, const double &c1, const double &c2)
{
    //  Create the uniform double generator in the range [lower_bound, upper_bound]
    std::uniform_real_distribution<double> distr(0, 1);
    // Initialize the position and velocity vectors
    std::generate(r1_.begin(), r1_.end(), [&]()
                  { return distr(random_generator_); });
    std::generate(r2_.begin(), r2_.end(), [&]()
                  { return distr(random_generator_); });

    // For each dimension
    for (std::size_t i = 0; i < velocity_.size(); ++i)
    {
        // Velocity update
        velocity_[i] = w * velocity_[i] + c1 * r1_[i] * (best_position_[i] - position_[i]) + c2 * r2_[i] * (global_best_position[i] - position_[i]);

        // Position update
        position_[i] += velocity_[i];
        // Check boundaries
        if (position_[i] < lower_bound_)
            position_[i] = lower_bound_;
        else if (position_[i] > upper_bound_)
            position_[i] = upper_bound_;
    }

    // Update best position if necessary
    double current_value = fitness_function_(position_);
    if (current_value < best_value_)
    {
        best_position_ = position_;
        best_value_ = current_value;
    }

    // Return the value of the fitness function in the best position
    return best_value_;
}

template <std::size_t dim>
void Particle<dim>::print() const
{
    std::cout << "Position:\t(";
    for (auto &i : position_)
    {
        std::cout << i << ", ";
    }
    std::cout << "\b\b)" << std::endl;

    std::cout << "Velocity:\t(";
    for (auto &i : velocity_)
    {
        std::cout << i << ", ";
    }
    std::cout << "\b\b)" << std::endl;

    std::cout << "Best position:\t(";
    for (auto &i : best_position_)
    {
        std::cout << i << ", ";
    }
    std::cout << "\b\b)" << std::endl;

    std::cout << "Best value:\t" << best_value_ << std::endl;
    std::cout << std::endl;
}

// particle class test
/*int main()
{
    std::cout << "Particle class test: start" << std::endl;
    std::cout << "-> Initialize particle" << std::endl;
    // create a particle
    Particle p(2, [](Vector v) { return v[0] * v[0] + v[1] * v[1]; }, -100, 100);
    // initialize the particle
    p.initialize();
    // print the particle
    p.print();
    // update the particle
    Vector r1 = {0.1, 0.2};
    Vector r2 = {0.3, 0.4};
    Vector global_best_position = {0.5, 0.6};
    std::cout << "-> Update particle" << std::endl;
    p.update(global_best_position, 0.1, 0.2, 0.3);
    // print the particle
    p.print();
    std::cout << "Particle class test: end" << std::endl;
    return 0;
}*/