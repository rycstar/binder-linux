# this is required
SET(CMAKE_SYSTEM_NAME Linux)

# specify the cross compiler
SET(CMAKE_C_COMPILER   /opt/gcc-arm-8.2-2018.08-x86_64-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER /opt/gcc-arm-8.2-2018.08-x86_64-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++)

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH  /opt/gcc-arm-8.2-2018.08-x86_64-arm-linux-gnueabihf/arm-linux-gnueabihf/)

# search for programs in the build host directories (not necessary)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

add_definitions(-D BINDER_IPC_32BIT)

# configure Boost and Qt
#SET(QT_QMAKE_EXECUTABLE /opt/qt-embedded/qmake)
#SET(BOOST_ROOT /opt/boost_arm)
