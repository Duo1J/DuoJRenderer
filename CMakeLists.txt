cmake_minimum_required(VERSION 3.8...3.28 FATAL_ERROR)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("DuoJRenderer")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/Bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/Lib")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Bin/Debug")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Bin/Release")

set(TARGET "DuoJRenderer")

add_subdirectory("Source")
add_subdirectory("ThirdParty")
