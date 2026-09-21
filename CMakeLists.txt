cmake_minimum_required(VERSION 3.16)
project(ventana_qt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Multimedia Widgets)

add_executable(
    ventana_qt
    WIN32
    main.cpp
    Ventana.h
    Ventana.cpp
    Serpiente.h
    Serpiente.cpp
)

target_include_directories(ventana_qt PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ventana_qt PRIVATE Qt5::Multimedia Qt5::Widgets)

install(TARGETS ventana_qt RUNTIME DESTINATION .)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/audio DESTINATION .)

add_custom_command(TARGET ventana_qt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/audio
            $<TARGET_FILE_DIR:ventana_qt>/audio
)
