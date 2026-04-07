add_executable(bms_app main.cpp)

find_package(Python3 COMPONENTS Development NumPy REQUIRED)

target_include_directories(bms_app PRIVATE
    ${MATPLOTLIBCPP_INCLUDE_DIR}
    ${Python3_INCLUDE_DIRS}
    ${Python3_NumPy_INCLUDE_DIRS}
)

target_link_libraries(bms_app PRIVATE
    Python3::Python
    Python3::NumPy
)

target_link_libraries(bms_app
    PRIVATE 
    BatteryModel
    ECUs
    Utilities
)