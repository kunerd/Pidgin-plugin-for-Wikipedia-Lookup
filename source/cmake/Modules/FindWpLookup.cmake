# - Try to find Wplookup
# Once done this will define
#  WPLOOKUP_FOUND - System has WpLookup
#  WPLOOKUP_INCLUDE_DIRS - The WpLookup include directories
#  WPLOOKUP_LIBRARIES - The libraries needed to use WpLookup
#  WPLOOKUP_DEFINITIONS - Compiler switches required for using WpLookup

FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES(PC_LIBXML wplookup QUIET)
SET(WPLOOKUP_DEFINITIONS ${PC_WPLOOKUP_CFLAGS_OTHER})

find_path(
        WPLOOKUP_INCLUDE_DIR wplookup.h
        HINTS ${CMAKE_FIND_ROOT_PATH}
                ${PC_WPLOOKUP_INCLUDEDIR}
                ${PC_WPLOOKUP_INCLUDE_DIRS}
        PATH_SUFFIXES wpLookup
)

find_library(
        WPLOOKUP_LIBRARY NAMES wplookup
        HINTS ${CMAKE_FIND_ROOT_PATH}
                ${PC_WPLOOKUP_LIBDIR}
                ${PC_WPLOOKUP_LIBRARY_DIRS}
)

set(WPLOOKUP_LIBRARIES ${WPLOOKUP_LIBRARY} )
set(WPLOOKUP_INCLUDE_DIRS ${WPLOOKUP_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set WPLOOKUP_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(WpLookup  DEFAULT_MSG
                                  WPLOOKUP_LIBRARY WPLOOKUP_INCLUDE_DIR)

mark_as_advanced(WPLOOKUP_INCLUDE_DIR WPLOOKUP_LIBRARY )
