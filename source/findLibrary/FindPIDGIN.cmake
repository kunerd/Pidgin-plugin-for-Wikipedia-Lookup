# - Try to find Pidgin Devel
# Once done this will define
#  PIDGIN_FOUND - System has LibXml2
#  PIDGIN_INCLUDE_DIRS - The LibXml2 include directories
#  PIDGIN_LIBRARIES - The libraries needed to use LibXml2
#  PIDGIN_DEFINITIONS - Compiler switches required for using LibXml2

find_path(PIDGIN_INCLUDE_DIR pidgin.h
          HINTS ${CMAKE_FIND_ROOT_PATH}
          PATH_SUFFIXES pidgin)

find_library(PIDGIN_LIBRARY NAMES pidgin
             HINTS ${CMAKE_FIND_ROOT_PATH}
          	PATH_SUFFIXES pidgin)

set(PIDGIN_LIBRARIES ${PIDGIN_LIBRARY} )

find_path(PIDGIN_WIN32_INCLUDE_DIR gtkwin32dep.h
          HINTS ${CMAKE_FIND_ROOT_PATH}
          PATH_SUFFIXES pidgin/win32)


set(PIDGIN_INCLUDE_DIRS ${PIDGIN_INCLUDE_DIR} ${PIDGIN_WIN32_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set PIDGIN_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(pidgin DEFAULT_MSG
                                   PIDGIN_LIBRARY PIDGIN_INCLUDE_DIR PIDGIN_WIN32_INCLUDE_DIR)

#mark_as_advanced(PIDGIN_INCLUDE_DIR)
