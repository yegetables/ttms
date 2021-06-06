# CMake 最低版本号要求
cmake_minimum_required (VERSION  3.8 )

# 项目信息
project (ttms)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


aux_source_directory(${CMAKE_SOURCE_DIR} MAIN_FUNC_SRCS)
aux_source_directory(${CMAKE_SOURCE_DIR}/Common COMMON_FUNC_SRCS)
aux_source_directory(${CMAKE_SOURCE_DIR}/Service SERVICE_FUNC_SRCS)
aux_source_directory(${CMAKE_SOURCE_DIR}/Persistence PERSISTENCE_FUNC_SRCS)
aux_source_directory(${CMAKE_SOURCE_DIR}/View VIEW_FUNC_SRCS)


include_directories(${CMAKE_SOURCE_DIR}/Common)
include_directories(${CMAKE_SOURCE_DIR}/Service)
include_directories(${CMAKE_SOURCE_DIR}/Persistence)
include_directories(${CMAKE_SOURCE_DIR}/View)

set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_SOURCE_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_definitions(  -g -Wall -DDEBUG )

# 指定生成目标 
add_executable( ttms  ${MAIN_FUNC_SRCS}  ${VIEW_FUNC_SRCS}   ${PERSISTENCE_FUNC_SRCS}  
 ${COMMON_FUNC_SRCS}  ${SERVICE_FUNC_SRCS})

# -fsanitize=address -fno-omit-frame-pointer