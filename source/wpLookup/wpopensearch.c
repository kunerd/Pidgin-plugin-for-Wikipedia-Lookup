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
 *  Wikipedia Lookup is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with wplookup.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "wpopensearch.h"

OpensearchItem *OpensearchItem_construct(WikipediaLookup *wpl)
{
    OpensearchItem *o;
    if(!(o=malloc(sizeof(OpensearchItem))))
    {
        return NULL;
    }

    o->text = NULL;
    o->description = NULL;
    o->url = NULL;
    o->wpl = wpl;

    return o;
}

void OpensearchItem_destruct(OpensearchItem *o)
{
    if(o)
    {
        g_free(o->text);
        g_free(o->description);
        g_free(o->url);
        free(o);
    }
}

int OpensearchItem_search(OpensearchItem *o, gchar *text)
{
    //TODO: remove local static text
    gchar *url;
    WikipediaXml *xml;

    url = g_strdup_printf ("%s/w/api.php?action=opensearch&search=%s&format=xml",
                                  o->wpl->url, text);

    xml = WikipediaXml_construct();
    WikipediaXml_loadUrl(xml, url);

    o->text = WikipediaXml_getText(xml, "/os:SearchSuggestion/os:Section/os:Item/os:Text");
    o->description = WikipediaXml_getText(xml, "/os:SearchSuggestion/os:Section/os:Item/os:Description");
    o->url = WikipediaXml_getText(xml, "/os:SearchSuggestion/os:Section/os:Item/os:Url");

    g_free(url);
    WikipediaXml_destruct(xml);
}
