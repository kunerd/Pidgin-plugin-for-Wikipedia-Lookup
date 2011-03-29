# - Try to find Pidgin Devel
# Once done this will define
#  PIDGIN_FOUND - System has LibXml2
#  PIDGIN_INCLUDE_DIRS - The LibXml2 include directories
#  PIDGIN_LIBRARIES - The libraries needed to use LibXml2
#  PIDGIN_DEFINITIONS - Compiler switches required for using LibXml2

find_package(PkgConfig)
pkg_check_modules(PC_PIDGIN QUIET pidgin/pidgin.h)
set(PC_PIDGIN_DEFINITIONS ${PC_PIDGIN_CFLAGS_OTHER})

find_path(PIDGIN_INCLUDE_DIR pidgin
          HINTS ${PC_PIDGIN_INCLUDEDIR} ${PC_PIDGIN_INCLUDE_DIRS}
          PATH_SUFFIXES pidgin )

#find_library(PIDGIN_LIBRARY NAMES pidgin
#             HINTS ${PC_PIDGIN_LIBDIR} ${PC_PIDGIN_LIBRARY_DIRS} )

#set(PIDGIN_LIBRARIES ${PIDGIN_LIBRARY} )
set(PIDGIN_INCLUDE_DIRS ${PIDGIN_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set PIDGIN_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(pidgin DEFAULT_MSG
                                   PIDGIN_INCLUDE_DIR)

mark_as_advanced(PIDGIN_INCLUDE_DIR PIDGIN_LIBRARY )
