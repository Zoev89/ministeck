
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(ministeckUI
    main.cpp
    mainwindow.cpp
    mainwindow.h
    ImageLabel.h
    mainwindow.ui
    baseplate.cpp baseplate.h basePlate.ui
  )

target_link_libraries(ministeckUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets libministeck ${OpenCV_LIBS})
