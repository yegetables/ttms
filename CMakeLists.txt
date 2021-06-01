# CMake 最低版本号要求
cmake_minimum_required (VERSION  3.8 )

# 项目信息
project (ttms)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(${CMAKE_SOURCE_DIR})

#configure_file(${CMAKE_SOURCE_DIR}/rely/config.h.in ${CMAKE_SOURCE_DIR}/src/config.h )
#configure_file(${CMAKE_SOURCE_DIR}/rely/s.log.conf.in ${CMAKE_SOURCE_DIR}/log/s.log.conf )

# 添加链接库
# target_link_libraries(ttms.exe  zlog  )

# aux_source_directory(${CMAKE_SOURCE_DIR}/src RELY_FUNC_SRCS)
# aux_source_directory(${CMAKE_SOURCE_DIR}/server SERVER_SRCS)
# aux_source_directory(${CMAKE_SOURCE_DIR}/client CLIENT_SRCS)


include_directories(${CMAKE_SOURCE_DIR}/Common)
include_directories(${CMAKE_SOURCE_DIR}/Service)
include_directories(${CMAKE_SOURCE_DIR}/Persistence)
include_directories(${CMAKE_SOURCE_DIR}/View)


# link_directories(${CMAKE_SOURCE_DIR}/lib)
# link_directories(${CMAKE_SOURCE_DIR}/lib/cjson)
# link_directories(${CMAKE_SOURCE_DIR}/lib/zlog)


#set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR})
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


# 指定生成目标 
#add_executable(server.out ${SERVER_SRCS}  ${RELY_FUNC_SRCS} )
#add_executable(client.out ${CLIENT_SRCS}  ${RELY_FUNC_SRCS} )



aux_source_directory(${CMAKE_SOURCE_DIR}/src RELY_FUNC_SRCS)
aux_source_directory(${CMAKE_SOURCE_DIR}/server SERVER_SRCS)


include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/server)


link_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(${CMAKE_SOURCE_DIR}/lib/cjson)
link_directories(${CMAKE_SOURCE_DIR}/lib/zlog)


set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


#add_executable(server.out ${SERVER_SRCS}  ${RELY_FUNC_SRCS} )


#configure_file(${CMAKE_SOURCE_DIR}/rely/config.h.in ${CMAKE_SOURCE_DIR}/server/config.h )


#add_definitions(  -g -Wall -DDEBUG )
# -fsanitize=address -fno-omit-frame-pointer



target_link_libraries(server.out cjson pthread zlog  mysqlclient)