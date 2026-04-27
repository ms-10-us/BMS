# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

# Add source files
add_library(GUI
    mainwindow.cpp
    LoadCycleWindow.cpp
    IconCreator.cpp
    )

# Include directories
target_include_directories(GUI 
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/gui
)

# Link Qt libraries
target_link_libraries(GUI 
    PRIVATE 
    Qt6::Core 
    Qt6::Widgets
    Utilities
    ObjectModel
    Simulation
    )