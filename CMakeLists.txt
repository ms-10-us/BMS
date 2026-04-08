# =============================================================================
# CMakeLists.txt - Beginner-Friendly Modern Template (C++17)
# Copy this file into EVERY project folder inside your ./projects/ directory
# Example: ./projects/my_calculator/CMakeLists.txt
# =============================================================================

# 1. Minimum CMake version (Ubuntu 22.04+ default is fine)
cmake_minimum_required(VERSION 3.14)

# 2. Project name (change this to match your folder name)
project(BMS)

 # 2.1 Add Matplotlib-cpp
include(FetchContent)

FetchContent_Declare(
    matplotlib_cpp
    GIT_REPOSITORY https://github.com/lava/matplotlib-cpp.git
    GIT_TAG        master
    GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(matplotlib_cpp)

set(MATPLOTLIBCPP_INCLUDE_DIR ${matplotlib_cpp_SOURCE_DIR})

execute_process(
    COMMAND python3 -c "import numpy; print(numpy.get_include())"
    OUTPUT_VARIABLE NUMPY_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

include_directories(${NUMPY_INCLUDE_DIR})

set(Python3_NumPy_INCLUDE_DIRS ${NUMPY_INCLUDE_DIR})

# 3. Modern C++ standard (change to 20 or 23 if you want)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(BMS_BUILD_APP "Build the main application" ON)

# Add subdirectories
add_subdirectory(src/BMS)
add_subdirectory(src/ECUs)
add_subdirectory(src/Utilities)
add_subdirectory(app)

# 4. Build type (Release = fast, Debug = with debugger symbols)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# 5. Nice compiler warnings (highly recommended for beginners)
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()



