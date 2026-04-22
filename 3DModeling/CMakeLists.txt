# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

add_library(ObjectModel
    CADWidget.cpp
    CADWidget.h
)

target_include_directories(ObjectModel PUBLIC
    /usr/include/opencascade
)

find_package(X11 REQUIRED)


# OCCT libraries
target_link_libraries(ObjectModel PRIVATE
    TKernel
    TKMath
    TKG2d
    TKService
    TKV3d
    TKOpenGl
    TKGeomBase
    TKGeomAlgo
    TKTopAlgo
    TKPrim
    TKBO
    TKBool
    TKOffset
    TKSTEP
    TKSTEPBase
    TKSTEPAttr
    TKIGES
    TKXSBase
    TKBRep
    TKShHealing
    Qt6::Core 
    Qt6::Widgets
    X11
)