cmake_minimum_required(VERSION 3.9.2 FATAL_ERROR)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Bluetooth REQUIRED)

setup_lib(bluetooth)

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Bluetooth)
