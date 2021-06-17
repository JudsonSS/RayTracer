# CMake
cmake_minimum_required(VERSION 3.0.0)
project(RayTracer)
 
# Configuração do C++
 set(CMAKE_BUILD_TYPE Debug)
 set(CMAKE_CXX_STANDARD 17)

 # Configuração do GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Executáveis e Ligações
add_executable(UnitTest UnitTests/Test1.cpp UnitTests/Test2.cpp RayTracer/Types.cpp)
target_link_libraries(UnitTest ${GTEST_LIBRARIES} pthread gtest_main)
add_executable(Projectile RayTracer/Projectile.cpp RayTracer/Types.cpp)
