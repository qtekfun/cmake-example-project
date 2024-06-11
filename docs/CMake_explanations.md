The `target_include_directories` command in CMake is used to specify the directories that should be added to the include path for a given target. This allows the compiler to find the header files when compiling source files that include those headers.

### Explanation of `target_include_directories`

The syntax for `target_include_directories` is:
```cmake
target_include_directories(<target> <INTERFACE|PUBLIC|PRIVATE> [items1...])
```
- `<target>`: The name of the target (e.g., an executable or a library).
- `<INTERFACE|PUBLIC|PRIVATE>`: Specifies the scope of the include directories.
  - `INTERFACE`: The include directories are used by targets that link to this target, but not for the target itself.
  - `PUBLIC`: The include directories are used both by the target and by other targets that link to this target.
  - `PRIVATE`: The include directories are used only by the target itself, not by targets that link to it.
- `[items1...]`: The include directories to be added to the include path.

### Detailed Example

Let's break down the usage of `target_include_directories` with an example from the `module1` CMake file:

#### `src/module1/CMakeLists.txt`
```cmake
add_library(module1 module1.cpp)

# Specify include directories for this module
target_include_directories(module1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link module2 to module1
target_link_libraries(module1 PRIVATE module2)
```

1. **`add_library(module1 module1.cpp)`**:
   - This command creates a library target named `module1` with the source file `module1.cpp`.

2. **`target_include_directories(module1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})`**:
   - This command specifies the include directories for the `module1` target.
   - `${CMAKE_CURRENT_SOURCE_DIR}` is a CMake variable that holds the path to the directory containing the current CMake file (`CMakeLists.txt`). In this case, it refers to `src/module1`.
   - `PUBLIC` means that the include directory `src/module1` will be added to the include path for both the `module1` target and any other target that links against `module1`.

3. **`target_link_libraries(module1 PRIVATE module2)`**:
   - This command specifies that `module1` depends on `module2`, meaning `module1` uses functions or variables defined in `module2`.
   - `PRIVATE` means that this linkage is only for the `module1` target and not for other targets that link against `module1`.

### How It Works

With this setup:
- When `module1.cpp` is compiled, the compiler knows to look in `src/module1` for header files. This means you can use `#include "module2.h"` in `module1.cpp` without specifying the relative path to `module2`.
- Since `module1` includes `module2.h`, `module2` needs to be in the include path when `module1` is compiled. By setting `PUBLIC` for the include directory of `module2`, any target that links against `module2` (like `module1`) will have access to its headers.
- The `main.cpp` file in the top-level `MyProject` target can include headers from both `module1` and `module2` without specifying relative paths, because both `src/module1` and `src/module2` are added to the include path.

#### Applying the Same Logic to `module2`

Similarly, you add `src/module2` to the include path for `module2`:

#### `src/module2/CMakeLists.txt`
```cmake
add_library(module2 module2.cpp)

# Specify include directories for this module
target_include_directories(module2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

### Putting It All Together

Here’s the complete structure and CMake configuration for your project:

#### Project Structure
```
MyProject/
├── src/
│   ├── module1/
│   │   ├── module1.cpp
│   │   ├── module1.h
│   │   └── CMakeLists.txt
│   ├── module2/
│   │   ├── module2.cpp
│   │   ├── module2.h
│   │   └── CMakeLists.txt
│   └── main.cpp
├── include/
├── build/
├── CMakeLists.txt
└── CMakePresets.json
```

#### Top-level `CMakeLists.txt`
```cmake
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
```

### Build the Project

#### On Linux:
```sh
cmake --preset linux-ninja
cmake --build --preset linux-ninja
./build/linux-ninja/MyProject
```

#### On Windows:
Open a terminal (like PowerShell or Command Prompt) and run:
```sh
cmake --preset windows-ninja
cmake --build --preset windows-ninja
./build/windows-ninja/MyProject.exe
```

This setup ensures that the header files are correctly located by the compiler without needing relative paths, making the project more modular and easier to maintain.