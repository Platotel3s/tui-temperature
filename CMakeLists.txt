cmake_minimum_required(VERSION 3.16)

project(SuhuConverterQtQuick LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_add_executable(appSuhu
    main.cpp
    Converter.cpp
    Converter.h
)

qt_add_qml_module(appSuhu
    URI SuhuApp
    VERSION 1.0
    QML_FILES qml/Main.qml
)

target_link_libraries(appSuhu PRIVATE Qt6::Quick)
