add_library(Utilities
    CANBus.cpp
    GlobalVariables.cpp
    PIDController.cpp
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