FIND_PATH( GLIB_INCLUDE_DIR glib.h
	HINTS
	/usr/include/glib-2.0/
	DOC "The directory where glib.h resides")
MESSAGE(STATUS "Looking for glib - found:${GLIB_INCLUDE_PATH}")

FIND_PATH( GLIB_CONFIG_INCLUDE_PATH glibconfig.h
	HINTS
	/usr/lib64/glib-2.0/include/
	DOC "The directory where glib.h resides")
MESSAGE(STATUS "Looking for glib - found:${GLIB_CONFIG_INCLUDE_PATH}")

set (GLIB_INCLUDE_DIR ${GLIB_INCLUDE_DIR} ${GLIB_CONFIG_INCLUDE_PATH}	)

FIND_LIBRARY( GLIB_LIBRARY
	NAMES glib-2.0 
	PATHS
	/usr/lib64
	DOC "The GLIB library")

IF (GLIB_INCLUDE_DIR )
	SET( GLIB_FOUND 1 CACHE STRING "Set to 1 if Foo is found, 0 otherwise")
ELSE (GLIB_INCLUDE_DIR )
	SET( GLIB_FOUND 0 CACHE STRING "Set to 1 if Foo is found, 0 otherwise")
ENDIF (GLIB_INCLUDE_DIR )

MARK_AS_ADVANCED( GLIB_FOUND )

IF(GLIB_FOUND)
	MESSAGE(STATUS "find glib libaray")
ELSE(GLIB_FOUND)
	MESSAGE(FATAL_ERROR "cann't glib libaray, please install : sudo apt-get install  libglib2.0-dev")
ENDIF(GLIB_FOUND)

