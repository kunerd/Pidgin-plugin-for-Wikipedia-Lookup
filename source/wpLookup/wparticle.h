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

#ifndef WPLOOKUP_WPARTICLE_H
#define WPLOOKUP_WPARTICLE_H

#include <gtk/gtk.h>
#include <stdlib.h>

#include "wplookup.h"

/** Struct that holds an Wikipedia aricle.
  */
typedef struct
{
    gchar *name; /** Name of the Wikipedia article. */
    gchar *content; /** Content of the Wikipedia article. */
    gchar *url; /** Url of the Wikipedia article. */
    WikipediaLookup *wpl; /** WikipediaLookup struct @see WikipediaLookup */
} WikipediaArticle;

WikipediaArticle *WikipediaArticle_construct(WikipediaLookup *wpl);

void WikipediaArticle_load(WikipediaArticle *o, gchar *search);

void WikipediaArticle_destruct(WikipediaArticle *o);

#endif
