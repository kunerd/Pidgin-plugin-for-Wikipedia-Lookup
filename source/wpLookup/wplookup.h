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

#ifndef WPLOOKUP_H
#define WPLOOKUP_H

#include <gtk/gtk.h>
#include <stdlib.h>

/** Structure that holds Wikipedia API data.
  */
typedef struct
{
    /** Wikipedia API url. */
    gchar *url;
    /** Wikipedia API language */
    gchar *language;
    /** Opensearch result limit. */
    guint opensearchLimit;
    /** Pointer to function, that is called, if the user
      * clicks left on an Opensearch entry in the popup menu.
    */
    GCallback opensearchCallback;
} WikipediaLookup;

WikipediaLookup *WikipediaLookup_construct(gchar *url, gchar *language);

void WikipediaLookup_destruct(WikipediaLookup *o);

GList *WikipediaLookup_getLanguages(void);

void WikipediaLookup_rightClickPopup(GtkTextView *text_view, GtkMenu *menu, WikipediaLookup *o);

#endif
