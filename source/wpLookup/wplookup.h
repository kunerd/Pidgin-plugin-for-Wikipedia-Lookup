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

#ifndef WPLOOKUP_H
#define WPLOOKUP_H

#include <gtk/gtk.h>
#include <stdlib.h>

#include "wparticle.h"
#include "wplinkedlist.h"

typedef struct
{
    gchar *url;
    gchar *language;
} WikipediaLookup;

WikipediaLookup *WikipediaLookup_construct(gchar *url, gchar *language);

void WikipediaLookup_destruct(WikipediaLookup *o);

WikipediaArticle *WikipediaLookup_loadArticle(WikipediaLookup *o, gchar *search);

int WikipediaLookup_getLanguages(LinkedList *resultList);

#endif