cmake_minimum_required (VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=gnu++11 -fPIC -DPIC")
set(CMAKE_C_FLAGS "-fPIC -DPIC")

find_program(_AIDL_CPP aidl-cpp)
set(srv_header "${CMAKE_CURRENT_BINARY_DIR}/com/fv/IRgbLedsService.h")
set(bn_header "${CMAKE_CURRENT_BINARY_DIR}/com/fv/BnRgbLedsService.h")
set(bp_header "${CMAKE_CURRENT_BINARY_DIR}/com/fv/BpRgbLedsService.h")
set(srv_src "${CMAKE_CURRENT_BINARY_DIR}/IRgbLedsService.cpp")

get_filename_component(src_aidl "./com/fv/IRgbLedsService.aidl" ABSOLUTE)
get_filename_component(src_aidl_path "${src_aidl}" PATH)
add_custom_command(
        OUTPUT "${srv_header}" "${bn_header}" "${bp_header}" "${srv_src}"
	COMMAND ${_AIDL_CPP} 
        ARGS "${src_aidl}" "${CMAKE_CURRENT_BINARY_DIR}"
        "${CMAKE_CURRENT_BINARY_DIR}/IRgbLedsService.cpp"
        DEPENDS "${src_aidl}"
)

include_directories(../include ../android  ${CMAKE_CURRENT_BINARY_DIR})

set(SRCS
    IRgbLedsService.cpp
    RgbLedsService.cpp
)

set(CLIENT_SRCS
    IRgbLedsService.cpp
    RgbLedsClient.cpp
)
add_executable(fv_rgb_service ${SRCS})
target_link_libraries(fv_rgb_service binder)
add_executable(fv_rgb_client ${CLIENT_SRCS})
target_link_libraries(fv_rgb_client binder)
