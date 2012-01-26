#
#  Wikipedia Lookup - A third-party Pidgin plug-in which offers
#  you the possibility to look up received and typed words on Wikipedia.
#
#  Copyright (C) 2011, 2012 Hendrik Kunert kunerd@users.sourceforge.net
#
#  This file is part of Wikipedia Lookup.
#
#  Wikipedia Lookup is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  Wikipedia Lookup is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with Wikipedia Lookup.  If not, see <http://www.gnu.org/licenses/>.
#

add_executable(wplookup_tests test.c)
set_target_properties(wplookup_tests PROPERTIES LINK_FLAGS -Wl,-lcunit)
target_link_libraries(
    wplookup_tests
    wplookup
)

add_test(wplookup_tests ${EXECUTABLE_OUTPUT_PATH}/wplookup_tests)

set(MEMORYCHECK_COMMAND:FILEPATH=/bin/usr/valgrind)
