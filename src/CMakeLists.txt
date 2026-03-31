add_library(bms
    BatteryCell.cpp
    BatteryCellThermalModel.cpp
    BatteryCellElectricalModel.cpp
    DTCManager.cpp
    CANBus.cpp
    BatteryStateMachine.cpp
    BatteryPack.cpp
    GlobalVariables.cpp
)

# Public include directory
target_include_directories(bms
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# Compiler warnings (professional touch)
target_compile_options(bms PRIVATE
    -Wall -Wextra -Wpedantic
)