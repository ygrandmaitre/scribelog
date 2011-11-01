macro(add_test NAME)
  add_executable(${NAME}-unit-test EXCLUDE_FROM_ALL ${ARGN})
  target_link_libraries(${NAME}-unit-test
                        boost_unit_test_framework
                        ${CACHE_LINK_LIBS})
  add_custom_target(${NAME}-test COMMAND ./${NAME}-unit-test --log_level=all
                                DEPENDS ${NAME}-unit-test)
  add_dependencies(test ${NAME}-test)
endmacro(add_test)

add_custom_target(test)

add_definitions(-DTEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
add_definitions(-DBOOST_TEST_DYN_LINK)
add_definitions(-DBOOST_TEST_MAIN)
add_test(config-parser configparsertest.cc ../src/configparser.cc)
