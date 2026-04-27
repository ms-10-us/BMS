# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(CMAKE_AUTORCC ON)

add_executable(bms_app 
    main.cpp
    ../resources.qrc
    )

target_link_libraries(bms_app
    PRIVATE 
    BatteryModel
    ECUs
    Utilities
    ExtendedKalmanFilter
    GUI
    DataParser
    Qt6::Core 
    Qt6::Widgets
    ObjectModel
    Simulation
)
