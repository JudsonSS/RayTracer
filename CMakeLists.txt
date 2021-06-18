# CMake
cmake_minimum_required(VERSION 3.0.0)
project(RayTracer)
 
# Configuração do C++
 set(CMAKE_BUILD_TYPE Debug)
 set(CMAKE_CXX_STANDARD 17)

# Aplicação de Exemplo
set (SOURCE_FILES "RayTracer/Types.cpp" "RayTracer/Canvas.cpp")
add_executable(Projectile RayTracer/Projectile.cpp ${SOURCE_FILES} )

 # Configuração do GoogleTest
 find_package(GTest REQUIRED)
 include_directories(${GTEST_INCLUDE_DIRS}) 

# Testes de Unidade
set (TEST_FILES "UnitTests/Test1.cpp" "UnitTests/Test2.cpp")
add_executable(UnitTests ${TEST_FILES} ${SOURCE_FILES})
target_link_libraries(UnitTests ${GTEST_LIBRARIES} pthread)

# Configura exibição de testes com ctest
enable_testing()
include(GoogleTest)
gtest_discover_tests(UnitTests)