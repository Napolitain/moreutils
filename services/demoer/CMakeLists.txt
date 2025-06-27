message(STATUS "Building demoer")

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

add_executable(demoer src/main.cpp)
target_link_libraries(demoer PRIVATE libdemoer user32 gdi32)

# if windows set WinMain
if (WIN32)
    set_target_properties(demoer PROPERTIES
            LINK_FLAGS "/SUBSYSTEM:WINDOWS"
    )
endif ()
