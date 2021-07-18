cmake_minimum_required(VERSION 3.0.2)
project(mnist_from_scratch)
add_compile_options(-std=c++17)

find_package(Eigen3 REQUIRED)
find_package(Threads REQUIRED)

include_directories(
    include
    ${EIGEN_INCLUDE_DIRS}
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(train
    src/train.cpp
    src/utils.cpp
)

# add_executable(test
   #src/test.cpp
#)

target_link_libraries(train
    Eigen3::Eigen
)
