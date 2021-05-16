#find_package (GMock)
#find_package (GTest)
find_package(OpenCV REQUIRED)
#find_package(CImg REQUIRED)

add_executable(libministecktest
    ColorConverterTest.cpp
    ColorsTest.cpp
    libministeckMain.cpp
    MinisteckTest.cpp
)

include_directories( ${GTEST_INCLUDE_DIRS})
target_link_libraries(libministecktest libministeck ${OpenCV_LIBS} ${GTEST_LIBRARIES} pthread gtest gmock X11)

