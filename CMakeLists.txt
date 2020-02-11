CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

# set the project name and version
project(unittest VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


SET(PRO_3RDPARTY_PATH "${PROJECT_SOURCE_DIR}/3rdparty")
INCLUDE_DIRECTORIES(
    ${PRO_3RDPARTY_PATH}/gtest/include
)

LINK_DIRECTORIES(

    ${PRO_3RDPARTY_PATH}/gtest/lib    
)


FILE(GLOB SRC_LISTS 
    ${PROJECT_SOURCE_DIR}/[^.]*.cpp 
    ${PROJECT_SOURCE_DIR}/src/[^.]*.cpp
    ${PROJECT_SOURCE_DIR}/src/managercase/[^.]*.cpp
)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC_LISTS})


#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/testfile)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
    libgtest.a
    libgtest_main.a
)
TARGET_LINK_LIBRARIES(${PROJECT_NAME}
    libpthread.so
    )

