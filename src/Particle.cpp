#include "../include/Particle.hpp"

Particle::Particle(const int dim, const bool inertia, const std::function<double(Vector)>& fitness_function)
    : _position(dim), _velocity(dim), _best_position(dim), _fitness_function(fitness_function)
{
    //TODO: handle inertia flag
}

int Particle::initialize(const double &lower_bound, const double &upper_bound)
{
    // create the uniform double generator in the range [lower_bound, upper_bound]
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<double> distr(lower_bound, upper_bound);
    // initialize the position and velocity vectors
    std::generate(_position.begin(), _position.end(), [&]() { return distr(generator); });
    std::generate(_velocity.begin(), _velocity.end(), [&]() { return distr(generator); });
    // initialize the best position
    _best_position = _position;
    // initialize the best value
    _best_value = _fitness_function(_best_position);
    return 0;
}

double Particle::update(const Vector &global_best_position, const float &w, const float &c1, const float &c2, const Vector &r1, const Vector &r2) {
    
    // Velocity update
    for (size_t i = 0; i < _velocity.size(); ++i) {
        _velocity[i] = w * _velocity[i] + c1 * r1[i] * (_best_position[i] - _position[i]) + c2 * r2[i] * (global_best_position[i] - _position[i]);
    }

    // Position update
    for (size_t i = 0; i < _position.size(); ++i) {
        _position[i] += _velocity[i];
    }

    // Update best position if necessary
    double current_value = _fitness_function(_position);
    if (current_value < _best_value) {
        _best_position = _position;
        _best_value = current_value;
    }

    return 0.0;
}

void Particle::print() const {
    std::cout << "Position:\t(";
    for (auto &i : _position) {
        std::cout << i << ", ";
    }
    std::cout << "\b\b)" << std::endl;

    std::cout << "Velocity:\t(";
    for (auto &i : _velocity) {
        std::cout << i << ", ";
    }
    std::cout << "\b\b)" << std::endl;

    std::cout << "Best position:\t(";
    for (auto &i : _best_position) {
        std::cout << i << ", ";
    }
    std::cout << "\b\b)" << std::endl;

    std::cout << "Best value:\t" << _best_value << std::endl;
    std::cout << std::endl;
}

const Vector& Particle::get_best_position() const {
    return _best_position;
}


// particle class test
int main_test()
{
    std::cout << "Particle class test: start" << std::endl;
    std::cout << "-> Initialize particle" << std::endl;
    // create a particle
    Particle p(2, false, [](Vector v) { return v[0] * v[0] + v[1] * v[1]; });
    // initialize the particle
    p.initialize(-10, 10);
    // print the particle
    p.print();
    // update the particle
    Vector r1 = {0.1, 0.2};
    Vector r2 = {0.3, 0.4};
    Vector global_best_position = {0.5, 0.6};
    std::cout << "-> Update particle" << std::endl;
    p.update(global_best_position, 0.1, 0.2, 0.3, r1, r2);
    // print the particle
    p.print();
    std::cout << "Particle class test: end" << std::endl;
    return 0;
}