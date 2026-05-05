cmake_minimum_required(VERSION 3.5)
project(dimple_trade_jni)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(JNI REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${JNI_INCLUDE_DIRS})

if(UNIX)
    set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lib/linux-x64")
    include_directories(${LIB_DIR})
    link_directories(${LIB_DIR})
    set(VENDOR_LIB KSDTradeApi64)
else()
    get_filename_component(LIB_PATH_WIN "${CMAKE_CURRENT_SOURCE_DIR}/../lib/win-x64/KSDTradeApi.lib" ABSOLUTE)
    set(VENDOR_LIB "${LIB_PATH_WIN}")
endif()

add_library(dimple_trade_jni SHARED dimple_jni_trade.cpp dimple_jni_trade.h)

if(MSVC)
    target_compile_options(dimple_trade_jni PRIVATE /utf-8)
endif()

if(UNIX)
    set_target_properties(dimple_trade_jni PROPERTIES
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "$ORIGIN"
    )
endif()

target_link_libraries(dimple_trade_jni ${JNI_LIBRARIES} ${VENDOR_LIB})

if(UNIX)
    set(NATIVE_RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../resources/linux-x64")
else()
    set(NATIVE_RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../resources/win-x64")
endif()

add_custom_command(TARGET dimple_trade_jni POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${NATIVE_RESOURCE_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:dimple_trade_jni>" "${NATIVE_RESOURCE_DIR}/$<TARGET_FILE_NAME:dimple_trade_jni>"
    COMMENT "Copying dimple_trade_jni native library to resources"
)
