project(ConsoleUI)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "../include/*.hpp" "*.hpp" "*.cpp")
add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "../include/ConsoleUI")

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
)
