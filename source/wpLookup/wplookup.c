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

#include "wplookup.h"

WikipediaLookup *WikipediaLookup_construct(gchar *url, gchar *language)
{
    WikipediaLookup *o;
    if(!(o=malloc(sizeof(WikipediaLookup))))
    {
        return NULL;
    }
    o->url = url;
    o->language = language;

    return o;
}

void WikipediaLookup_destruct(WikipediaLookup *o)
{
    if(o)
    {
        free(o);
    }
}

gchar *WikipediaLookup_getUrl(WikipediaLookup *o)
{
    return o->url;
}

gchar *WikipediaLookup_getLanguage(WikipediaLookup *o)
{
    return o->language;
}

void WikipediaLookup_setUrl(WikipediaLookup *o, gchar *url)
{
    o->url = url;
}

void WikipediaLookup_setLanguage(WikipediaLookup *o, gchar *language)
{
    o->language = language;
}

WikipediaArticle *WikipediaLookup_loadArticle(WikipediaLookup *o, gchar *search)
{
    WikipediaArticle *article;
    if(!(article=malloc(sizeof(WikipediaLookup))))
    {
        return NULL;
    }

    /* TODO: load article */

    return article;
}
