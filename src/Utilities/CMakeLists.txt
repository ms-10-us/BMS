add_library(Utilities
    CANBus.cpp
    GlobalVariables.cpp
    PIDController.cpp
    PlottingTool.cpp
)

find_package(Python3 REQUIRED COMPONENTS Development)

target_include_directories(Utilities PRIVATE
    ${MATPLOTLIBCPP_INCLUDE_DIR}
    ${Python3_INCLUDE_DIRS}
    ${Python3_NumPy_INCLUDE_DIRS}
)

target_link_libraries(Utilities PRIVATE
    Python3::Python
)

# Public include directory
target_include_directories(Utilities
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/Utilities
)

# Compiler warnings (professional touch)
target_compile_options(Utilities PRIVATE
    -Wall -Wextra -Wpedantic
)