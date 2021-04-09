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


set(evtbus_srv_header "${CMAKE_CURRENT_BINARY_DIR}/com/fv/IEventBusInterface.h")
set(evtbus_bn_header "${CMAKE_CURRENT_BINARY_DIR}/com/fv/BnEventBusInterface.h")
set(evtbus_bp_header "${CMAKE_CURRENT_BINARY_DIR}/com/fv/BpEventBusInterface.h")
set(evtbus_srv_src "${CMAKE_CURRENT_BINARY_DIR}/IEventBusInterface.cpp")

get_filename_component(evtbus_src_aidl "./com/fv/IEventBusInterface.aidl" ABSOLUTE)

add_custom_command(
        OUTPUT "${evtbus_srv_header}" "${evtbus_bn_header}" "${evtbus_bp_header}" "${evtbus_srv_src}"
	COMMAND ${_AIDL_CPP} 
        ARGS "${evtbus_src_aidl}" "${CMAKE_CURRENT_BINARY_DIR}"
        "${evtbus_srv_src}"
        DEPENDS "${evtbus_src_aidl}"
)

set(evtlistener_srv_header "${CMAKE_CURRENT_BINARY_DIR}/com/fv/IEventListenerInterface.h")
set(evtlistener_bn_header "${CMAKE_CURRENT_BINARY_DIR}/com/fv/BnEventListenerInterface.h")
set(evtlistener_bp_header "${CMAKE_CURRENT_BINARY_DIR}/com/fv/BpEventListenerInterface.h")
set(evtlistener_srv_src "${CMAKE_CURRENT_BINARY_DIR}/IEventListenerInterface.cpp")

get_filename_component(evtlistener_src_aidl "./com/fv/IEventListenerInterface.aidl" ABSOLUTE)
add_custom_command(
        OUTPUT "${evtlistener_srv_header}" "${evtlistener_bn_header}" "${evtlistener_bp_header}" "${evtlistener_srv_src}"
	COMMAND ${_AIDL_CPP} 
        ARGS "${evtlistener_src_aidl}" "${CMAKE_CURRENT_BINARY_DIR}"
        "${evtlistener_srv_src}"
        DEPENDS "${evtlistener_src_aidl}"
)

include_directories(../include ../android ./  ${CMAKE_CURRENT_BINARY_DIR})

set(SRCS
    IRgbLedsService.cpp
    RgbLedsService.cpp
    c_config.c
)

set(CLIENT_SRCS
    IRgbLedsService.cpp
    RgbLedsClient.cpp
    main.c
)

set(EVENT_BUS_SRCS
    IEventBusInterface.cpp
    IEventListenerInterface.cpp
    EventBus.cpp
)

set(EVENT_POST_SRCS
    IEventBusInterface.cpp
    EventPost.cpp
)

set(EVENT_LISTENER_SRCS
    IEventListenerInterface.cpp
    IEventBusInterface.cpp
    EventListener.cpp
)

add_executable(fv_rgb_service ${SRCS})
target_link_libraries(fv_rgb_service binder)
add_executable(fv_rgb_client ${CLIENT_SRCS})
target_link_libraries(fv_rgb_client binder)
add_executable(event_bus ${EVENT_BUS_SRCS})
target_link_libraries(event_bus binder)

add_executable(event_post ${EVENT_POST_SRCS})
target_link_libraries(event_post binder)

add_executable(event_listener ${EVENT_LISTENER_SRCS})
target_link_libraries(event_listener binder)