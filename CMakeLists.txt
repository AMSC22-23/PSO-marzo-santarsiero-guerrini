cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

# set C++ version requirements
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set variable for project name
set(PROJ_NAME
    PSO
)

# set libraries names (no libraries without templates)
set(LIBRARIES
)

# set project name and version
project(
  ${PROJ_NAME}
  VERSION 1.0
  LANGUAGES CXX)

# set include directory
include_directories(/include)

#iterate over libraries and add them (not needed)
foreach(LIBRARY ${LIBRARIES})
    add_library(${LIBRARY}
        include/${LIBRARY}.hpp
        src/${LIBRARY}.cpp
    )
endforeach(LIBRARY)

# set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# create executable
add_executable(${PROJ_NAME}
    src/main.cpp
)

find_package(OpenMP)
# link libraries to project
if(OpenMP_CXX_FOUND)
    target_link_libraries(${PROJ_NAME} PUBLIC  ${LIBRARIES} OpenMP::OpenMP_CXX)
else()
    target_link_libraries(${PROJ_NAME} ${LIBRARIES})
endif()