/*
 *  Wikipedia Lookup - A third-party Pidgin plug-in which offers
 *  you the possibility to look up received and typed words on Wikipedia.
 *
 *  Copyright (C) 2011, 2012 Hendrik Kunert kunerd@users.sourceforge.net
 *
 *  This file is part of Wikipedia Lookup.
 *
 *  Wikipedia Lookup is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Wikipedia Lookup is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Wikipedia Lookup.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef WPLOOKUP_WPXML_H
#define WPLOOKUP_WPXML_H

#define WPLOOKUP_WPXML_USER_AGENT "Mozilla/4.0"

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <libxml/xpath.h>

struct MemoryStruct{
        gchar *memory;
        size_t size;
};

typedef struct {
        xmlDoc *doc;
        struct MemoryStruct chunk;
} WikipediaXml;

WikipediaXml *WikipediaXml_construct(void);

void WikipediaXml_destruct(WikipediaXml *o);

void WikipediaXml_loadUrl(WikipediaXml *o, gchar *url);

void WikipediaXml_loadFile(WikipediaXml *o, gchar *filepath);

gchar *WikipediaXml_getText(WikipediaXml *o, gchar *xPath);

gchar *WikipediaXml_getAttribute(WikipediaXml *o, gchar *xPath, gchar *name);

xmlXPathObjectPtr WikipediaXml_getNodeset (WikipediaXml *o, xmlChar *xPath);

#endif
