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
#include "wpopensearch.h"

WikipediaArticle *WikipediaArticle_construct(WikipediaLookup *wpl)
{
    WikipediaArticle *o;
    if(!(o=malloc(sizeof(WikipediaArticle))))
    {
        return NULL;
    }

    o->name = NULL;
    o->content = NULL;
    o->wpl = wpl;

    return o;
}

void WikipediaArticle_destruct(WikipediaArticle *o)
{
    if(o)
    {
        g_free(o->name);
        g_free(o->content);
        free(o);
    }
}

void WikipediaArticle_load(WikipediaArticle *o, gchar *search)
{
    OpensearchItem *os;
    WikipediaXml *xml = NULL;
    gchar *url;
    gchar *escaped_text;

    os = OpensearchItem_construct(o->wpl);
    OpensearchItem_search(os, search);

    xml = WikipediaXml_construct();

    escaped_text = g_uri_escape_string(os->text, NULL, TRUE);
    // TODO: remove static local url here
    url = g_strdup_printf ("%s/w/api.php?action=parse&page=%s&section=0&format=xml&redirects",
                                  o->wpl->url, escaped_text);

    WikipediaXml_loadUrl(xml, url);

    o->name = WikipediaXml_getAttribute(xml,"/api/parse", "displaytitle");
    o->content = WikipediaXml_getText(xml, "/api/parse/text");

    WikipediaXml_destruct(xml);
    OpensearchItem_destruct(os);
    g_free(escaped_text);
    g_free(url);
}
