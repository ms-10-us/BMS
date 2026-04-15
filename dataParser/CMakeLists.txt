add_library(DataParser 
    DataParse.cpp
)

# Public include directory
target_include_directories(DataParser 
    PUBLIC
        ${PROJECT_SOURCE_DIR}/dataParser
)

# Compiler warnings (professional touch)
target_compile_options(DataParser  PRIVATE
    -Wall -Wextra -Wpedantic
)