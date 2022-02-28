set(test_sources arma_test.cpp)

add_executable(arma_test ${test_sources})
target_link_libraries(
    arma_test
    PRIVATE
        armadillo
        h5cpp
        hdf5::hdf5
)
catch_discover_tests(arma_test WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
