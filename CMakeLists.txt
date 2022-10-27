cmake_minimum_required(VERSION 3.0.0)

project(convertpsf CXX)

include(FetchContent)
enable_testing()

set(WITH_PYTHON OFF)
FetchContent_Declare(libpsf 
    GIT_REPOSITORY https://github.com/julidau/libpsf.git
)
FetchContent_Declare(highfive 
    GIT_REPOSITORY https://github.com/BlueBrain/HighFive
)

FetchContent_MakeAvailable(libpsf)
FetchContent_MakeAvailable(highfive)

add_executable(convertpsf main.cpp)
target_link_libraries(convertpsf HighFive psf)

add_test(NAME test_psf COMMAND convertpsf ${CMAKE_CURRENT_SOURCE_DIR}/test/results/1/psf/psf/tran.tran out.hdf5)