project(robot_demo)
cmake_minimum_required(VERSION 2.8)

set ( SOURCES
 main.cpp
 mainwindow.cpp
 irobotcreate.cpp
 odometry.cpp
 DifferencialDrive.cpp
        positionRegulator2dCircular.cpp
        positionRegulator2dLinear.cpp)

set ( MY_HEADERS
 mainwindow.h
 irobotcreate.h
 odometry.h
 DifferencialDrive.h
 regulator.h
        positionRegulator2dCircular.h types.h positionRegulator2dLinear.h)

set ( UIS
 mainwindow.ui
)
set(CMAKE_AUTOMOC ON)
aux_source_directory(. SRC_LIST)

find_package( Qt4 REQUIRED )
find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )
include_directories(    ${CMAKE_BINARY_DIR}
                        include)

QT4_ADD_RESOURCES( RES_SOURCES ${RESOURCES} )
QT4_WRAP_UI( UI_HEADERS ${UIS} )
QT4_WRAP_CPP( MOC_SRCS ${MY_HEADERS} )

set (CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME}  ${SOURCES}
                                ${MY_HEADERS}
                                ${UI_HEADERS})

message(STATUS ${QT_LIBRARIES})
target_link_libraries( ${PROJECT_NAME} ${QT_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )
