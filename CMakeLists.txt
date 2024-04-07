cmake_minimum_required(VERSION 3.0)
project(TCP-UDP-NTP-Server-client)

# Set C standard to C99
set(CMAKE_C_STANDARD 99)

# Get all .c files in the current directory
file(GLOB SOURCES "*.c")

foreach(SOURCE ${SOURCES})
    # Extract the file name without the extension
    get_filename_component(EXECUTABLE_NAME ${SOURCE} NAME_WE)

    # Add executable target for each source file
    add_executable(${EXECUTABLE_NAME} ${SOURCE})
endforeach()
