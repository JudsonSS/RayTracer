# CMake
cmake_minimum_required(VERSION 3.0.0)
project(RayTracer)
 
# Configuração do C++
 set(CMAKE_BUILD_TYPE Debug)
 set(CMAKE_CXX_STANDARD 17)
 set(CMAKE_EXPORT_COMPILE_COMMANDS ON )

 # Configuração do GoogleTest
 find_package(GTest REQUIRED)
 include_directories(${GTEST_INCLUDE_DIRS}) 

# Projectile
set (PROJECTILE_FILES 
    "RayTracer/Types.cpp"
    "RayTracer/Tuple.cpp"
    "RayTracer/Point.cpp"
    "RayTracer/Vector.cpp"
    "RayTracer/Color.cpp" 
    "RayTracer/Canvas.cpp")

# Clock
set (CLOCK_FILES 
    "RayTracer/Types.cpp"
    "RayTracer/Tuple.cpp"
    "RayTracer/Point.cpp"
    "RayTracer/Color.cpp" 
    "RayTracer/Canvas.cpp" 
    "RayTracer/Matrix.cpp")

# RayTracer
set (RAYTRACER_FILES 
    "RayTracer/Types.cpp"
    "RayTracer/Tuple.cpp"
    "RayTracer/Point.cpp"
    "RayTracer/Vector.cpp"
    "RayTracer/Color.cpp" 
    "RayTracer/Canvas.cpp" 
    "RayTracer/Matrix.cpp"
    "RayTracer/Ray.cpp"
    "RayTracer/Object.cpp"
    "RayTracer/World.cpp")

# Testes de Unidade
set (TEST_FILES 
    "UnitTests/Chapter1.cpp" 
    "UnitTests/Chapter2.cpp" 
    "UnitTests/Chapter3.cpp" 
    "UnitTests/Chapter4.cpp"
    "UnitTests/Chapter5.cpp"
    "UnitTests/Chapter6.cpp"
    "UnitTests/Chapter7.cpp"
    "UnitTests/Chapter8.cpp"
    "UnitTests/Chapter9.cpp"
    "UnitTests/Chapter10.cpp")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/RayTracer")
add_executable(Projectile "Projects/Projectile.cpp" ${PROJECTILE_FILES})
add_executable(Clock "Projects/Clock.cpp" ${CLOCK_FILES})
add_executable(Sphere "Projects/Sphere.cpp" ${RAYTRACER_FILES})
add_executable(Scene "Projects/Scene.cpp" ${RAYTRACER_FILES})
add_executable(Plane "Projects/Plane.cpp" ${RAYTRACER_FILES})
add_executable(UnitTests ${TEST_FILES} ${RAYTRACER_FILES})
target_link_libraries(UnitTests ${GTEST_LIBRARIES} pthread)
