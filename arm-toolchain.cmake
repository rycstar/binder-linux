# this is required
SET(CMAKE_SYSTEM_NAME Linux)

# specify the cross compiler
SET(CMAKE_C_COMPILER   arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

find_program(toolchain_path arm-linux-gnueabihf-gcc PATH)

string(REGEX REPLACE "(.+)\\bin/arm-linux.*" "\\1" toolchain_root_dir ${toolchain_path})

set(CMAKE_CROSSCOMPILING TRUE)
# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH  ${toolchain_root_dir}/arm-linux-gnueabihf/)

# search for programs in the build host directories (not necessary)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

add_definitions(-D BINDER_IPC_32BIT)
