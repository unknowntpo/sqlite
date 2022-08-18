file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.c")
list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/src/main.c")

file(GLOB tests "${PROJECT_SOURCE_DIR}/test/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/test/main.cpp")

# add_test(NAME integration_test
# COMMAND bundle exec rspec
# message(STATUS "Current dir : ${CMAKE_CURRENT_LIST_DIR}")

# # execute_process(
# # COMMAND bundle exec rspec ${CMAKE_BINARY_DIR}
# # )
# )
add_test(NAME integration_test
    COMMAND
    rspec ${PROJECT_BINARY_DIR}/spec/main_spec.rb
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})