cmake_minimum_required(VERSION 3.25.0)
project(MetasequoiaImeFloatingToolWindow VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_definitions(
    /D_UNICODE=1
    /DUNICODE=1
)
# fmt
find_package(fmt CONFIG REQUIRED)

set(MY_EXECUTABLE_NAME "MetasequoiaImeFloatingToolWindow")

include_directories("./src")
set(
  SOURCE_FILES
  "./src/d2d/render_d2d.cpp"
  "./src/d2d/render_d2d.h"
  "./src/tool_window/tool_window.cpp"
  "./src/tool_window/tool_window.h"
  "./src/utils/window_utils.cpp"
  "./src/utils/window_utils.h"
  "./src/main.cpp"
)

add_executable(${MY_EXECUTABLE_NAME} WIN32 ${SOURCE_FILES})

target_link_libraries(${MY_EXECUTABLE_NAME} PRIVATE fmt::fmt)