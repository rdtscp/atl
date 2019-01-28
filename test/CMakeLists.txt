enable_testing()

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include")

add_executable(runHashUnitTests Test_Hash.cpp  main.cpp)
target_link_libraries(runHashUnitTests libgtest libgmock)
add_test(HashUnitTests runHashUnitTests)

add_executable(runStringUnitTests Test_String.cpp  main.cpp)
target_link_libraries(runStringUnitTests libgtest libgmock)
add_test(StringUnitTests runStringUnitTests)

add_executable(runVectorUnitTests Test_Vector.cpp  main.cpp)
target_link_libraries(runVectorUnitTests libgtest libgmock)
add_test(VectorUnitTests runVectorUnitTests)