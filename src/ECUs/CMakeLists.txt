add_library(ECUs
    BMSECU.cpp
)

# Public include directory
target_include_directories(ECUs
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/ECUs
)

# Compiler warnings (professional touch)
target_compile_options(ECUs PRIVATE
    -Wall -Wextra -Wpedantic
)