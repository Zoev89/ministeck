
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_library(libministeck
    inc/IMinisteck.h
    Ministeck.cpp Ministeck.h
    Colors.cpp Colors.h inc/IColors.h
    libMinisteckBuilder.cpp inc/libMinisteckBuilder.h
)

add_subdirectory(Test)

target_include_directories (libministeck PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
