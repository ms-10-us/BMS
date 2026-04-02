add_library(BatteryModel
    BatteryCell.cpp
    BatteryCellThermalModel.cpp
    BatteryCellElectricalModel.cpp
    BatteryPack.cpp
    BatteryStateMachine.cpp
    DTCManager.cpp
)

# Public include directory
target_include_directories(BatteryModel
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/BMS
)

# Compiler warnings (professional touch)
target_compile_options(BatteryModel PRIVATE
    -Wall -Wextra -Wpedantic
)