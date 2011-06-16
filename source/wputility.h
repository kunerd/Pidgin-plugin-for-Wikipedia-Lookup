/*
 *  Wikipedia Lookup - A third-party Pidgin plug-in which offers 
 *					  you the possibility to look up received and
 *					  typed words on Wikipedia.
 *
 *  Copyright (C) 2011 Hendrik Kunert kunerd@users.sourceforge.net
 *
 *  This file is part of wplookup.
 *
 *  wplookup is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Foobar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with wplookup.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef WP_UTILITY_H
#define WP_UTILITY_H

#include <string.h>
#include <gtk/gtk.h>
#include <libxml/xpath.h>

struct MemoryStruct {
	char *memory;
	size_t size;
};

struct PreviewData {
	GtkWidget *parent_window;
	gchar *search_text;
};

xmlXPathObjectPtr
wputility_get_nodeset (xmlDocPtr doc, xmlChar *xpath);

size_t
wplanguage_write_memory_callback(void *ptr, size_t size, size_t nmemb, void *data);

gchar * wputility_get_uri(gchar *path, gchar *filename);

#endif
