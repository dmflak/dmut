# CMakeList.txt : CMake project for dmut, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("dmut")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "")

SET(
    ROOT_SOURCES
    "dmut/src/dmut.cpp"
)

SET(
    ROOT_HEADERS
    "dmut/src/dmut.h"
)

list(APPEND ROOT_SOURCES ${ROOT_HEADERS})

SOURCE_GROUP(src FILES ${ROOT_SOURCES})
# Add source to this project's executable.
add_executable (dmut ${ROOT_SOURCES})

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")

message ("cxx Flags:" ${CMAKE_CXX_FLAGS})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET dmut PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
