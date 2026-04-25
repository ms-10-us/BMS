find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

add_library(Simulation
    Simulation.cpp
)

target_include_directories(Simulation
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include/RunComputation
)

target_link_libraries(Simulation
    PRIVATE
    Qt6::Core 
    Qt6::Widgets
)

target_compile_options(Utilities PRIVATE
    -Wall -Wextra -Wpedantic
)