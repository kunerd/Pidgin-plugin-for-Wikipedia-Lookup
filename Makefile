 #
 #  Wikipedia Lookup - A third-party Pidgin plug-in which offers 
 #					  you the possibility to look up received and
 #					  typed words on Wikipedia.
 #
 #  Copyright (C) 2011 Hendrik Kunert kunerd@users.sourceforge.net
 #
 #  This file is part of wplookup.
 #
 #  wplookup is free software: you can redistribute it and/or modify
 #  it under the terms of the GNU General Public License as published by
 #  the Free Software Foundation, either version 2 of the License, or
 #  (at your option) any later version.
 #
 #  Foobar is distributed in the hope that it will be useful,
 #  but WITHOUT ANY WARRANTY; without even the implied warranty of
 #  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 #  GNU General Public License for more details.
 #
 #  You should have received a copy of the GNU General Public License
 #  along with wplookup.  If not, see <http://www.gnu.org/licenses/>.
 #

CC := gcc
LIBTOOL := libtool

ifeq ($(PREFIX),)
  PLUGIN_INSTALL_DIR = $(HOME)/.purple/plugins
else
  PLUGIN_INSTALL_DIR = $(PREFIX)/lib/pidgin
endif

PIDGIN_WPLOOKUP = wplookup

PIDGIN_CFLAGS  = $(shell pkg-config pidgin --cflags)
GTK_CFLAGS   = $(shell pkg-config gtk+-2.0 --cflags)
PIDGIN_LIBS    = $(shell pkg-config pidgin --libs)
GTK_LIBS     = $(shell pkg-config gtk+-2.0 --libs)
PIDGIN_LIBDIR  = $(shell pkg-config --variable=libdir pidgin)/pidgin

all: $(PIDGIN_WPLOOKUP).so

install: all
	mkdir -p $(PLUGIN_INSTALL_DIR)
	cp $(PIDGIN_WPLOOKUP).so $(PLUGIN_INSTALL_DIR)

$(PIDGIN_WPLOOKUP).so: $(PIDGIN_WPLOOKUP).o
	$(CC) $(LDFLAGS) -shared $(CFLAGS) $< -o $@ $(PIDGIN_LIBS) $(GTK_LIBS) -Wl,--export-dynamic -Wl,-soname

$(PIDGIN_WPLOOKUP).o:$(PIDGIN_WPLOOKUP).c $(PIDGIN_WPLOOKUP).h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@ $(PIDGIN_CFLAGS) $(GTK_CFLAGS) -DHAVE_CONFIG_H

clean:
	rm -rf *.o *.c~ *.h~ *.so *.la .libs
