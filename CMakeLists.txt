project(robot_demo)
cmake_minimum_required(VERSION 2.8)

set ( SOURCES
 mainwindow.cpp
 irobotcreate.cpp
 odometry.cpp
 DifferencialDrive.cpp
        positionRegulator2dCircular.cpp
        positionRegulator2dLinear.cpp
        LimitInterface.cpp
        LocalMap.cpp
        LocalPlanner.cpp
        rplidar.cpp)

set ( MY_HEADERS
 mainwindow.h
 irobotcreate.h
 odometry.h
 DifferencialDrive.h
 regulator.h
        positionRegulator2dCircular.h
        types.h
        positionRegulator2dLinear.h
        LimitInterface.h
        LocalMap.h
        LocalPlanner.h
        rplidar.h)

set ( UIS
 mainwindow.ui
)
#set(CMAKE_AUTOMOC ON)
#aux_source_directory(. SRC_LIST)

find_package( Qt4 REQUIRED )
find_package(Threads REQUIRED)

include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )
include_directories(    ${CMAKE_BINARY_DIR}
                        include)

#QT4_ADD_RESOURCES( RES_SOURCES ${RESOURCES} )
QT4_WRAP_UI( UI_HEADERS ${UIS} )
QT4_WRAP_CPP( MOC_SRCS ${MY_HEADERS} )

set (CMAKE_CXX_STANDARD 11)

include_directories(CMAKE_BINARY_DIR)

add_executable(odometry_test    odometry_test.cpp
                                odometry.cpp
        )

add_executable(${PROJECT_NAME}  main.cpp
                                ${SOURCES}
                                ${MY_HEADERS}
                                ${UI_HEADERS}
                                ${MOC_SRCS})



target_compile_definitions(${PROJECT_NAME} PRIVATE MAP)
target_compile_definitions(${PROJECT_NAME} PRIVATE REAL_ROBOT)


target_link_libraries(  ${PROJECT_NAME} ${QT_LIBRARIES}
                                        ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(  odometry_test ${QT_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT})
