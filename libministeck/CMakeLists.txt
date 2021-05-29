
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)

add_library(libministeck
    inc/IBaseplateType.h
    inc/IMinisteck.h
    Ministeck.cpp Ministeck.h
    inc/IColorTypes.h
    Colors.cpp Colors.h inc/IColors.h inc/test/IColorsMock.h
    ColorConverter.cpp ColorConverter.h inc/IColorConverter.h inc/test/IColorConverterMock.h
    libMinisteckBuilder.cpp inc/libMinisteckBuilder.h
    Quantize.cpp Quantize.h inc/IQuantize.h inc/test/IQuantizeMock.h
    ScaledOutputImage.cpp ScaledOutputImage.h inc/IScaledOutputImage.h inc/test/IScaledOutputImageMock.h
    RandVorm.cpp RandVorm.h inc/IRandVorm.h inc/test/IRandVormMock.h
    inc/IMinisteckVormen.h
    )

add_subdirectory(Test)

include_directories( ${OpenCV_INCLUDE_DIRS} )

target_include_directories (libministeck PUBLIC ${OpenCV_LIBS} ${CMAKE_CURRENT_SOURCE_DIR}/inc)
