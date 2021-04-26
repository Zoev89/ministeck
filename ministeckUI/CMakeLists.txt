
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_executable(ministeck
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )

target_link_libraries(ministeck PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
