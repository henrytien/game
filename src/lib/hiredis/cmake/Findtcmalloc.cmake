FIND_PATH( TCMALLOC_INCLUDE_DIR  gperftools/tcmalloc.h
	HINTS
	/usr/local/include/
	DOC "The directory where tcmalloc.h resides"  )
 
FIND_LIBRARY( TCMALLOC_LIBRARY
	NAMES tcmalloc
	HINTS
	PATHS /usr/local/lib/
	DOC "The TAOMEE library")

IF (TCMALLOC_INCLUDE_DIR )
	SET( TAOMEE_FOUND 1 CACHE STRING "Set to 1 if taomee is found, 0 otherwise")
ELSE (TCMALLOC_INCLUDE_DIR)
	SET( TAOMEE_FOUND 0 CACHE STRING "Set to 1 if taomee is found, 0 otherwise")
ENDIF (TCMALLOC_INCLUDE_DIR)

MARK_AS_ADVANCED( TAOMEE_FOUND )

IF(TAOMEE_FOUND)
	MESSAGE(STATUS "find tcmalloc library")
ELSE(TAOMEE_FOUND)
	MESSAGE(FATAL_ERROR "Looking for tcmalloc - not found :gperftools/tcmalloc.h  ")
ENDIF(TAOMEE_FOUND)
