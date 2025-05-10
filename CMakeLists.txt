cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(English_russian_dict)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -pedantic -Werror")

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()
include_directories(src test)

add_executable(run
	main.cpp
)
add_executable(test_exec
	test_main.cpp
	test/initial_test.cpp
)
target_include_directories(test_exec
	PRIVATE
	${gtest_SOURCE_DIR}/include
)
target_link_libraries(test_exec
	gtest
	gtest_main
)
include(GoogleTest)
gtest_discover_tests(test_exec)
