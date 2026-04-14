add_library(ExtendedKalmanFilter
    MatrixTranspose.cpp
    MatrixMultiplication.cpp
    ExtendedKalmanFilter.cpp
    MatrixAddition.cpp
    MatrixVectorMultiplication.cpp
    GainMultiplication.cpp
    MatrixPieceWiseMultiplication.cpp
)

target_include_directories(ExtendedKalmanFilter
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/ExtendedKalmanFilter
)

target_compile_options(ExtendedKalmanFilter PRIVATE
    -Wall -Wextra -Wpedantic
)