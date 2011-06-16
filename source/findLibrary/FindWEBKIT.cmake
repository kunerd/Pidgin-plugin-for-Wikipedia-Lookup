# - Try to find Webkit
# Once done this will define
#  LIBXML2_FOUND - System has LibXml2
#  LIBXML2_INCLUDE_DIRS - The LibXml2 include directories
#  LIBXML2_LIBRARIES - The libraries needed to use LibXml2
#  LIBXML2_DEFINITIONS - Compiler switches required for using LibXml2

find_package(PkgConfig)
pkg_check_modules(PC_WEBKIT QUIET webkit-1.0)
set(WEBKIT_DEFINITIONS ${PC_WEBKIT_CFLAGS_OTHER})

find_path(WEBKIT_INCLUDE_DIR webkit/webkit.h
          HINTS ${PC_WEBKIT_INCLUDEDIR} ${PC_WEBKIT_INCLUDE_DIRS}
          PATH_SUFFIXES webkit-1.0)

find_library(WEBKIT_LIBRARY NAMES webkit-1.0
             HINTS ${PC_WEBKIT_LIBDIR} ${PC_WEBKIT_LIBRARY_DIRS} )

set(WEBKIT_LIBRARIES ${WEBKIT_LIBRARY} )
set(WEBKIT_INCLUDE_DIRS ${WEBKIT_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set WEBKIT_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(Webkit  DEFAULT_MSG
                                  WEBKIT_LIBRARIES WEBKIT_INCLUDE_DIR)

mark_as_advanced(WEBKIT_INCLUDE_DIR WEBKIT_LIBRARIES)
