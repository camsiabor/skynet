cmake_minimum_required(VERSION 3.14)

project(skynet)

set(CMAKE_C_STANDARD  99)

include_directories("3rd/lua")
include_directories("3rd/lpeg")
include_directories("3rd/jemalloc/include/jemalloc")

include_directories("skynet-src")

#-----------------------------------------------------------------------

add_library(gate SHARED service-src/service_gate.c)
add_library(harbor SHARED service-src/service_harbor.c)
add_library(logger SHARED service-src/service_logger.c)
add_library(snlua SHARED service-src/service_snlua.c)
set_target_properties(gate harbor logger snlua
        PROPERTIES
        PREFIX ""
        COMPILE_FLAGS ""
        LINK_FLAGS "-shared -rdynamic"
        LIBRARY_OUTPUT_DIRECTORY cservice)

#-----------------------------------------------------------------------



file(GLOB SKYNET_SRC "skynet-src/*.h" "skynet-src/*.c")
file(GLOB UTIL "util/*.h" "util/*.c")

link_directories(3rd/lua)
link_directories(3rd/jemalloc/lib)

add_executable(skynet ${SKYNET_SRC} ${UTIL})
target_link_libraries(skynet m dl pthread)
target_link_libraries(skynet lua)
target_link_libraries(skynet jemalloc)
set_target_properties(skynet
        PROPERTIES
        COMPILE_FLAGS ""
        LINK_FLAGS "-Wl,--export-dynamic"
        RUNTIME_OUTPUT_DIRECTORY ".")

