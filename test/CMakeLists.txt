enable_testing()

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include")

add_executable(runHashUnitTests Test_Hash.cpp  main.cpp)
target_link_libraries(runHashUnitTests libgtest libgmock)
add_test(HashUnitTests runHashUnitTests)

add_executable(runIfStreamUnitTests Test_IfStream.cpp  main.cpp)
target_link_libraries(runIfStreamUnitTests libgtest libgmock)
add_test(IfStreamUnitTests runIfStreamUnitTests)

add_executable(runMapUnitTests Test_Map.cpp  main.cpp)
target_link_libraries(runMapUnitTests libgtest libgmock)
add_test(MapUnitTests runMapUnitTests)

add_executable(runOfStreamUnitTests Test_OfStream.cpp  main.cpp)
target_link_libraries(runOfStreamUnitTests libgtest libgmock)
add_test(OfStreamUnitTests runOfStreamUnitTests)

add_executable(runPairUnitTests Test_Pair.cpp  main.cpp)
target_link_libraries(runPairUnitTests libgtest libgmock)
add_test(PairUnitTests runPairUnitTests)

add_executable(runSetUnitTests Test_Set.cpp  main.cpp)
target_link_libraries(runSetUnitTests libgtest libgmock)
add_test(SetUnitTests runSetUnitTests)

add_executable(runSharedPtrUnitTests Test_SharedPtr.cpp  main.cpp)
target_link_libraries(runSharedPtrUnitTests libgtest libgmock)
add_test(SharedPtrUnitTests runSharedPtrUnitTests)

add_executable(runStackUnitTests Test_Stack.cpp  main.cpp)
target_link_libraries(runStackUnitTests libgtest libgmock)
add_test(StackUnitTests runStackUnitTests)

add_executable(runStringUnitTests Test_String.cpp  main.cpp)
target_link_libraries(runStringUnitTests libgtest libgmock)
add_test(StringUnitTests runStringUnitTests)

add_executable(runVectorUnitTests Test_Vector.cpp  main.cpp)
target_link_libraries(runVectorUnitTests libgtest libgmock)
add_test(VectorUnitTests runVectorUnitTests)