cmake_minimum_required(VERSION 3.5) 
 
# Set the project name 
project(ExpoFinder) 
 
# Specify C++ standard 
set(CMAKE_CXX_STANDARD 17) 
 
# Create the executable target first 
set(SOURCES 
 main.cpp 
 DataController.cpp 
) 
set(HEADERS DataController.h FrontendController.h) 
 
# Add the executable target 
add_executable(ExpoFinder ${SOURCES} ${HEADERS}) 
 
# Find the OpenMP package 
find_package(OpenMP REQUIRED) 
 
# Apply OpenMP settings if OpenMP is found 
if(OpenMP_CXX_FOUND) 
 target_compile_options(ExpoFinder PRIVATE ${OpenMP_CXX_FLAGS}) 
 target_link_libraries(ExpoFinder PRIVATE ${OpenMP_CXX_LIBRARIES}) 
 message(STATUS "Found OpenMP") 
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}") 
 add_definitions(-DOPENMP_SUPPORT) 
endif() 
 
# Find Drogon framework 
find_package(Drogon CONFIG REQUIRED) 
 
# Link Drogon library to the executable 
target_link_libraries(ExpoFinder PRIVATE Drogon::Drogon) 
 
# Enable testing 
enable_testing() 
 
# Add a test executable 
add_executable(ExpoFinderTests test.cpp DataController.cpp) 
 
# Link GTest, Drogon, and OpenMP libraries to the test executable 
target_link_libraries(ExpoFinderTests PRIVATE Drogon::Drogon OpenMP::OpenMP_CXX) 
 
# Define the test 
add_test(NAME ExpoFinderTests COMMAND ExpoFinderTests)