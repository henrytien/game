cmake_minimum_required(VERSION 2.6)
set(CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE  true )
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}")

#SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_INSTALL_PREFIX}/../ )
set(CMAKE_USE_RELATIVE_PATHS  true )
set(SRC_PATH ${CMAKE_SOURCE_DIR}/src/)
find_package(glib REQUIRED)
find_package(tmbase REQUIRED)
find_package(tcmalloc REQUIRED)

set (SRC_LIST 
${SRC_PATH}main.cc
${SRC_PATH}read.cc
${SRC_PATH}read.h
${SRC_PATH}hiredis.cc
${SRC_PATH}hiredis.h
${SRC_PATH}net.cc
${SRC_PATH}net.h
${SRC_PATH}sds.cc
${SRC_PATH}sds.h
)

add_definitions("-Wall -MMD -g -std=c++11 -DDEBUG -D_GNU_SOURCE -DUSE_TLOG -O2 -funroll-loops -D__USE_STRING_INLINES  -D_REENTRANT  -z defs")
INCLUDE_DIRECTORIES(${SRC_PATH} ${GLIB_INCLUDE_DIR} ${TAOMEE_INCLUDE_DIR} 	)
set (EXTRA_LIBS ${EXTRA_LIBS} ${GLIB_LIBRARY} ${TAOMEE_LIBRARY} dl pthread crypto ssl m )
set (LAST_LIBS ${TCMALLOC_LIBRARY})
add_executable(myhi_redis ${SRC_LIST} ${LAST_LIBS} )
target_link_libraries (myhi_redis ${EXTRA_LIBS} ${LAST_LIBS})
INSTALL (TARGETS myhi_redis DESTINATION ./)