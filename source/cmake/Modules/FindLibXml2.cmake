# - Try to find LibXml2
# Once done this will define
#  LIBXML2_FOUND - System has LibXml2
#  LIBXML2_INCLUDE_DIRS - The LibXml2 include directories
#  LIBXML2_LIBRARIES - The libraries needed to use LibXml2
#  LIBXML2_DEFINITIONS - Compiler switches required for using LibXml2

FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES(PC_LIBXML libxml-2.0 QUIET)
SET(LIBXML2_DEFINITIONS ${PC_LIBXML2_CFLAGS_OTHER})

find_path(
	LIBXML2_INCLUDE_DIR libxml/xpath.h
	HINTS ${CMAKE_FIND_ROOT_PATH}
		${PC_LIBXML2_INCLUDEDIR}
   		${PC_LIBXML2_INCLUDE_DIRS}
	PATH_SUFFIXES libxml2
)

find_library(
	LIBXML2_LIBRARY NAMES xml2 libxml2
	HINTS ${CMAKE_FIND_ROOT_PATH}
		${PC_LIBXML2_LIBDIR}
		${PC_LIBXML2_LIBRARY_DIRS}
)

set(LIBXML2_LIBRARIES ${LIBXML2_LIBRARY} )
set(LIBXML2_INCLUDE_DIRS ${LIBXML2_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBXML2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(LibXml2  DEFAULT_MSG
                                  LIBXML2_LIBRARY LIBXML2_INCLUDE_DIR)

mark_as_advanced(LIBXML2_INCLUDE_DIR LIBXML2_LIBRARY )
