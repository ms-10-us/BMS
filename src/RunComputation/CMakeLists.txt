find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

add_library(Simulation
    Simulation.cpp
    ${PROJECT_SOURCE_DIR}/include/RunComputation/Simulation.h
)

set_target_properties(Simulation PROPERTIES
    AUTOMOC ON
)

target_include_directories(Simulation
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include/RunComputation
)

target_link_libraries(Simulation
    PRIVATE
    Qt6::Core 
    Qt6::Widgets
    Utilities
    DataParser
    BatteryModel
    ExtendedKalmanFilter
    ECUs
)

target_compile_options(Utilities PRIVATE
    -Wall -Wextra -Wpedantic
)