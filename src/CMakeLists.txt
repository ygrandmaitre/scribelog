add_definitions(-D_GLIBCXX_USE_NANOSLEEP)
add_executable(scribelog
  main.cc
  log.cc
  configparser.cc
)

target_link_libraries(scribelog
  z ${CMAKE_THREAD_LIBS_INIT})
