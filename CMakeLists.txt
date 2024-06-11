# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MyProject)

# Add subdirectories
add_subdirectory(src/module1)
add_subdirectory(src/module2)

# Add the executable
add_executable(MyProject src/main.cpp)

# Link modules to the main executable
target_link_libraries(MyProject PRIVATE module1 module2)

# Add include directories
target_include_directories(MyProject PRIVATE src/module1 src/module2)
