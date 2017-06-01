
cmake_minimum_required (VERSION 3.7)
project (Search)
add_executable(search main.c)


include(CTest)

add_test(Runs search foo search-file.txt)

add_test(FindsFoo search foo search-file.txt)
set_tests_properties(FindsFoo PROPERTIES PASS_REGULAR_EXPRESSION "0")

add_test(FindsBar search bar search-file.txt)
set_tests_properties(FindsBar PROPERTIES PASS_REGULAR_EXPRESSION "3")

add_test(FindsBaz search baz search-file.txt)
set_tests_properties(FindsBaz PROPERTIES PASS_REGULAR_EXPRESSION "6")

add_test(FindsBa search ba search-file.txt)
set_tests_properties(FindsBa PROPERTIES PASS_REGULAR_EXPRESSION "3\n6")
