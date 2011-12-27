# - Try to find Webkit
# Once done this will define
#  LIBXML2_FOUND - System has LibXml2
#  LIBXML2_INCLUDE_DIRS - The LibXml2 include directories
#  LIBXML2_LIBRARIES - The libraries needed to use LibXml2
#  LIBXML2_DEFINITIONS - Compiler switches required for using LibXml2

#find_package(PkgConfig)
#pkg_check_modules(PC_GIO2 webkit-1.0 webkit)
set(GIO2_DEFINITIONS ${PC_GIO2_CFLAGS_OTHER})

find_path(GIO2_INCLUDE_DIR gio/gio.h
          HINTS ${PC_GIO2_INCLUDEDIR} ${PC_GIO2_INCLUDE_DIRS} ${CMAKE_FIND_ROOT_PATH}
          PATH_SUFFIXES glib-2.0)

find_library(GIO2_LIBRARY NAMES gio-2.0
             HINTS ${PC_GIO2_LIBDIR} ${PC_GIO2_LIBRARY_DIRS} ${CMAKE_FIND_ROOT_PATH})

set(GIO2_LIBRARIES ${GIO2_LIBRARY} )
set(GIO2_INCLUDE_DIRS ${GIO2_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set GIO2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(GIO2  DEFAULT_MSG
                                  GIO2_LIBRARY GIO2_INCLUDE_DIR)

mark_as_advanced(GIO2_INCLUDE_DIR GIO2_LIBRARY)
