#
# Try to find AntTweakBar library and include path.
# Once done this will define
#
# ANTTWEAKBAR_FOUND
# ANTTWEAKBAR_INCLUDE_DIR
# ANTTWEAKBAR_LIBRARY
#

IF (WIN32)
    IF( CMAKE_SIZEOF_VOID_P EQUAL 8 )
        SET( BITS "64" )
    ELSE()
        SET( BITS "" )
    ENDIF()

    FIND_PATH( ANTTWEAKBAR_INCLUDE_DIR AntTweakBar.h PATHS
        ${CMAKE_CURRENT_LIST_DIR}/../external/AntTweakBar/include
        $ENV{ANTTWEAKBAR_ROOT}/include
        DOC "The directory where AntTweakBar.h resides")

    FIND_LIBRARY( ANTTWEAKBAR_LIBRARY AntTweakBar${BITS} PATHS
	    IF( CMAKE_SIZEOF_VOID_P EQUAL 8 )
                ${CMAKE_CURRENT_LIST_DIR}/../external/AntTweakBar/lib/x64
		ELSE()
                ${CMAKE_CURRENT_LIST_DIR}/../external/AntTweakBar/lib/win32
		ENDIF()
       # ${CMAKE_CURRENT_LIST_DIR}/../external/AntTweakBar/lib/x64
        $ENV{ANTTWEAKBAR_ROOT}/lib
        DOC "The AntTweakBar library")
else()
    FIND_PATH(ANTTWEAKBAR_INCLUDE_DIR AntTweakBar.h PATHS
        ${CMAKE_CURRENT_LIST_DIR}/../external/AntTweakBar/include/
        /usr/local/include
        /usr/X11/include
        /usr/include
        NO_DEFAULT_PATH)

    FIND_LIBRARY( ANTTWEAKBAR_LIBRARY AntTweakBar PATHS
        /usr/local/lib
        /usr/X11
        /usr
		${CMAKE_CURRENT_LIST_DIR}/../external/AntTweakBar/lib/x11
        PATH_SUFFIXES a lib64 lib dylib NO_DEFAULT_PATH)
endif()

if(ANTTWEAKBAR_INCLUDE_DIR AND ANTTWEAKBAR_LIBRARY)
    message(STATUS "Found ANTTWEAKBAR: ${ANTTWEAKBAR_LIBRARY}")
    set(ANTTWEAKBAR_FOUND TRUE)
endif()

#message(STATUS "ANTTWEAKBAR_INCLUDE_DIR: ${ANTTWEAKBAR_INCLUDE_DIR}")
#message(STATUS "ANTTWEAKBAR_LIBRARY: ${ANTTWEAKBAR_LIBRARY}")
