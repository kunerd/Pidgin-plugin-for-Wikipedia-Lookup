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

#include "wparticle.h"

WikipediaArticle *WikipediaArticle_construct(gchar *name, gchar *content)
{
    WikipediaArticle *o;
    if(!(o=malloc(sizeof(WikipediaArticle))))
    {
        return NULL;
    }
    o->name = name;
    o->content = content;

    return o;
}

void WikipediaArticle_destruct(WikipediaArticle *o)
{
    if(o)
    {
        free(o);
    }
}

gchar *WikipediaArticle_getName(WikipediaArticle *o)
{
    return o->name;
}

gchar *WikipediaArticle_getContent(WikipediaArticle *o)
{
    return o->content;
}

void WikipediaArticle_setName(WikipediaArticle *o, gchar *name)
{
    o->name = name;
}

void WikipediaArticle_setContent(WikipediaArticle *o, gchar *content)
{
    o->content = content;
}
