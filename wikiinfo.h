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
 *  the Free Software Foundation, either version 2 of the License, or
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

#ifndef WIKIINFO_H
#define WIKIINFO_H

#include <gtk/gtk.h>
#include <curl/curl.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <gtkprefs.h>
#include <gtkutils.h>
#include <gtkconvwin.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define WPL_WIKIPEDIA_SITEMATRIX 	"http://de.wikipedia.org/w/api.php?action=sitematrix&format=xml"
#define WPL_USER_AGENT				"Mozilla/4.0"

struct MemoryStruct {
	char *memory;
	size_t size;
};

enum
{
  COL_NAME = 0,
  COL_URL,
  NUM_COLS
} ;

static size_t
WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data);

xmlXPathObjectPtr
getnodeset (xmlDocPtr doc, xmlChar *xpath);

GtkWidget * create_view_and_model ();

static GtkTreeModel * getWikipediaLanguages();

#endif