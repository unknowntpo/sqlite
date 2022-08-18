cmake_minimum_required(VERSION 3.1)

project(sqlite)

# #
# ## Test definitions ###
# #
configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

# Copy everything in spec to ${CMAKE_BINARY_DIR}
file(COPY ${PROJECT_SOURCE_DIR}/spec
        DESTINATION ${CMAKE_BINARY_DIR})

enable_testing()
add_subdirectory(test)
add_subdirectory(spec)

# #
# ## Source definitions ###
# #
include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        "${PROJECT_SOURCE_DIR}/spec/main_spec.rb"
)

# Does cmake know ./bin ?
add_executable(sqlite ${sources})