cmake_minimum_required(VERSION 3.8)
project(wafl-tests)

add_executable(${PROJECT_NAME} tests.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /WX /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra -Wpedantic -pedantic-errors -Wconversion -Wsign-conversion)
endif()

set(WAFL_ENABLE_WARNINGS_AS_ERRORS ON)
add_subdirectory(.. ${CMAKE_CURRENT_SOURCE_DIR}/build/wafl)
target_link_libraries(${PROJECT_NAME} PRIVATE wafl::wafl)

add_subdirectory(doctest)
target_link_libraries(${PROJECT_NAME} PRIVATE doctest::doctest)