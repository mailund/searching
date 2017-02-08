cmake_minimum_required(VERSION 3.6)

project (Searching)
add_executable(search search.c)

enable_testing()
add_test(NAME search-test WORKING_DIRECTORY . COMMAND test.sh)