cmake_minimum_required(VERSION 3.5)

project(BigIntCalculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt")


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)


add_executable(BigIntCalculator
    main.cpp
    mainwindow.cpp
    mainwindow.h
    BigInt.cpp
    BigInt.h
)


target_link_libraries(BigIntCalculator Qt${QT_VERSION_MAJOR}::Widgets)