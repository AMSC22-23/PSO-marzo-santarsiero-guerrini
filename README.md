# AMSC project: Particle Swarm Optimization (PSO)
## Description
This project aims to implement the PSO algorithm both in serial and in parallel, the latter exploiting the OpenMP API.
The fully informed version of the algorithm has been choosen for its balance between simplicity of implementation and effectiveness.

Three main classes have been developed:
- `Particle` represents a single particle of the swarm and manage its initialization and update at each iteration.
- `ParticleSwarmOptimization` wraps the swarm of particles and the iterative PSO algorithm besides with initialization and output methods. 
- `TestFunctions` contains some common benchmarking functions and some utilities needed for the tesing of the algorithm.

The `ParticleSwarmOptimization` class provides methods for the serial and the parallel implementation for both initialization and optimization.
The parallel implementation exploits multithreading in order to speedup the particles update at each iteration, assigning to each thread 
a subset of the swarm.

Since there is no dependence between particles update at the same iteration, synchronization is only needed at the end of each iteration.
While a critical section is necessary at each update of the shared global best value and position in order to preserve the consistency of these values.

## Requirements
- CMake
- C++17
- OpenMP 3.1
- Python3

## How to compile and run
1. Create the folders needed for building the project and saving the output `.csv` and `.png`
   ```
   mkdir build
   mkdir output
   ```
2. Move into the build folder
   ```
   cd ./build
   ```
3. Execute cmake
   ```
   cmake ..
   ```
4. Build the project
   ```
   cmake --build .
   ```
5. Launch the PSO executable with a suitable test (a complete list of the available test is shown if no parameter is passed)
   ```
   ./PSO [test_name]
   ```
   The execution of a test may produce an output file `test_name.csv` that can be found under the `output` folder.
6. Plot the results in a graphical way passing to the `plot_csv.py` script only the filename of the .csv file
   ```
   cd ..
   python scripts/plot_csv.py test_name.csv
   ```
## Available tests
- `error_iteration`: Optimizes all the test functions with the same parameters both in serial and in parallel. Logs the error in function of the iterations count on the same optimizaiton loop for each function. Stores in the `error_iteration.csv` file all the errors in function of the iteration.

  > **Expected result**: It should show that the error decreases as the iteration count increases. The descent rate is random and starvation may be expected.

- `time_numparticles`: Optimizes several time the same test function with same parameters varying only the number of particles. The optimization is done both in serial and in parallel and the time is taken to analyse the speedup. Stores in the `time_numparticles.csv` file all the execution times of the serial and parallel optimize function for each swarm size of particles.

  > **Expected result**: It should show that the excution time increases linearly in both serial and parallel case. In particular we expect that the parallel increase rate is less than the serial one. Teoretically the coefficient of the parallel case should be $\frac{1}{num\ threads}$ of the serial one. The speedup converges to the theoretical result as the number of particles increases. It never reach that result due to the thread handling overhead.

- `serial_parallel_opt`: Basic optimization of a given test function both in serial and in parallel. Prints in standard output the execution time and the achieved error. Does not saves any file.
  > **Expected result**: It should show that the parallel version is faster than the serial one of about a factor of $num\ threads$. The error should be of the same magnitude, but may vary due to the rendomness of the method.

## Documentation
The complete documentation of the public interface of our project can be consulted [here](https://amsc22-23.github.io/PSO-marzo-santarsiero-guerrini/).

## Group members
- Pierpaolo Marzo
- Domenico Santarsiero
- Alberto Guerrini
