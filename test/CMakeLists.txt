enable_testing()

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include")

add_executable(runVectorUnitTests Test_Vector.cpp  main.cpp)
target_link_libraries(runVectorUnitTests libgtest libgmock)
add_test(VectorUnitTests runVectorUnitTests)