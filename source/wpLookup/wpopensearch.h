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

#ifndef WPLOOKUP_WPOPENSEARCH_H
#define WPLOOKUP_WPOPENSEARCH_H

#include <gtk/gtk.h>
#include <stdlib.h>

#include "wpxml.h"
#include "wplookup.h"

/** Structure that holds one OpenSearch result. */
typedef struct
{
    gchar *text;    /** Name of OpenSearch result */
    gchar *description;     /** Short Description */
    gchar *url;     /** Wikipedia article URL */
} OpenSearchItem;

/** Structure that holds the OpenSearch result data for one request.
  */
typedef struct
{
    /** list of OpenSearchItems */
    GList *list;
    WikipediaLookup *wpl;
} OpenSearch;

OpenSearchItem *OpenSearchItem_construct();
void OpenSearchItem_destruct(OpenSearchItem *o);

OpenSearch *OpenSearch_construct(WikipediaLookup *wpl);
void OpenSearch_destruct(OpenSearch *o);

int OpenSearch_search(OpenSearch *o, gchar *text);

#endif
