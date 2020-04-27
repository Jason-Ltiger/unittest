CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

# set the project name and version
project(unittest VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

SET(PRO_3RDPARTY_PATH "${PROJECT_SOURCE_DIR}/3rdparty")
INCLUDE_DIRECTORIES(
    ${PRO_3RDPARTY_PATH}/gtest/include

    ${PRO_3RDPARTY_PATH}/pthread/include
    ${PROJECT_SOURCE_DIR}/src
    ${PRO_3RDPARTY_PATH}/boost/include
    ${PRO_3RDPARTY_PATH}/evpp/include
    ${PRO_3RDPARTY_PATH}/glog/include
    ${PRO_3RDPARTY_PATH}/event/include
    ${PRO_3RDPARTY_PATH}/jsoncpp/include
)

LINK_DIRECTORIES(
    
    ${PRO_3RDPARTY_PATH}/gtest/lib    
    ${PRO_3RDPARTY_PATH}/pthread/lib 
    ${PRO_3RDPARTY_PATH}/boost/lib
    ${PRO_3RDPARTY_PATH}/evpp/lib
    ${PRO_3RDPARTY_PATH}/glog/lib
    ${PRO_3RDPARTY_PATH}/event/lib
    ${PRO_3RDPARTY_PATH}/jsoncpp/lib
)


FILE(GLOB SRC_LISTS 
    ${PROJECT_SOURCE_DIR}/[^.]*.cpp 
    ${PROJECT_SOURCE_DIR}/src/[^.]*.cpp
    ${PROJECT_SOURCE_DIR}/src/managercase/[^.]*.cpp
)

ADD_EXECUTABLE(unittest ${SRC_LISTS})

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/testfile)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
    libgtest.a
    libgtest_main.a
    libboost_filesystem.a
    libboost_iostreams.a
    libboost_regex.a
    libboost_system.a
    libboost_thread.a
    libboost_wave.a
    libZipper-static.a
    libevpp_static.a
    libevent.a
    libglog.a
    libcryptopp.a
    libjsoncpp.a
)
TARGET_LINK_LIBRARIES(${PROJECT_NAME}
    libpthread.so
    )
