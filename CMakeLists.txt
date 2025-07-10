cmake_minimum_required(VERSION 3.25.0)
project(MetasequoiaImeFloatingToolWindow VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_definitions(
    /D_UNICODE=1
    /DUNICODE=1
)

set(MY_EXECUTABLE_NAME "MetasequoiaImeFloatingToolWindow")

include_directories("./src")
set(
  SOURCE_FILES
  "./src/tool_window/tool_window.cpp"
  "./src/tool_window/tool_window.h"
  "./src/main.cpp"
)

add_executable(${MY_EXECUTABLE_NAME} WIN32 ${SOURCE_FILES})
