#include "../include/ParticleSwarmOptimization.hpp"


ParticleSwarmOptimization::ParticleSwarmOptimization(int n, int dim, int lower_bound, int upper_bound, int max_iter, double tolerance,
    float inertia_weight, float c1, float c2): _n(n), _dim(dim), _lower_bound(lower_bound), _upper_bound(upper_bound),
    _max_iter(max_iter), _tolerance(tolerance), _intertia_weight(inertia_weight), _c1(c1), _c2(c2) {}

int ParticleSwarmOptimization::initialize()
{
    for (int i = 0; i < _n; i++)
    {
        _swarm.emplace_back(_dim, false, [](Vector v){ return v[0] * v[0] + v[1] * v[1]; });
        double current_fitness = _swarm.back().initialize(_lower_bound,_upper_bound);
        if(current_fitness < _global_best_value){
            _global_best_position = _swarm.back().get_best_position();
        }
    }
    //TODO: update _global_best_position. It could be done also direcly inside the particle's update method? comparing _global_best_value
    // and in case assigning vector _position to vector _global_best_position?

}


int ParticleSwarmOptimization::optimize()
{
    int current_iter;
    while(current_iter < _max_iter){
        for(auto &particle : _swarm){
            if(particle.update(_global_best_position,_intertia_weight,_c1,_c2) < _global_best_value){
                _global_best_position = particle.get_best_position();
            }
        }
        std::cout<<"Best value: "<<_global_best_value; 
        std::cout << "Best position:\t(";
        for (auto &i : _global_best_position) {
        std::cout << i << ", ";
    }
    std::cout << "\b\b)" << std::endl;

    }
}