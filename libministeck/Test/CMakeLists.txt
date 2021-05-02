#find_package (GMock)
find_package (GTest)

add_executable(libministecktest
  ColorsTest.cpp
  libministeckMain.cpp
  MinisteckTest.cpp
  )

include_directories( ${GTEST_INCLUDE_DIRS})
target_link_libraries(libministecktest libministeck ${GTEST_LIBRARIES} pthread)

