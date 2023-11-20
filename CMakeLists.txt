cmake_minimum_required(VERSION 3.10...3.27 FATAL_ERROR)

# set C++ version requirements
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set variable for project name
set(PROJ_NAME
    PSO
)

# set libraries names
set(LIBRARIES
	#TODO: add libraries here
)

# set project name and version
project(
  ${PROJ_NAME}
  VERSION 1.0
  LANGUAGES CXX)

# set include directory
include_directories(/include)

# iterate over libraries and add them
foreach(LIBRARY ${LIBRARIES})
    add_library(${LIBRARY}
        include/${LIBRARY}.hpp
        src/${LIBRARY}.cpp
    )
endforeach(LIBRARY)

# create executable
add_executable(${PROJ_NAME}
    src/main.cpp
)

# link libraries to project
# target_link_libraries(${PROJ_NAME} ${LIBRARIES})