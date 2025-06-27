message(STATUS "Building libdemoer")

find_package(capnproto CONFIG REQUIRED)
file(GLOB_RECURSE CAPNP_SOURCES proto/*.capnp)
capnp_generate_cpp(CAPNP_SRCS CAPNP_HDRS ${CAPNP_SOURCES})

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

add_library(libdemoer STATIC ${SOURCES} ${HEADERS} ${CAPNP_SRCS} ${CAPNP_HDRS})
target_link_libraries(libdemoer PRIVATE CapnProto::capnp CapnProto::kj)
target_include_directories(libdemoer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(libdemoer PROPERTIES OUTPUT_NAME demoer)
