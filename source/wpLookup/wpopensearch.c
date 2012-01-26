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

#include "wpopensearch.h"

OpenSearchItem *OpenSearchItem_construct()
{
    OpenSearchItem *o;
    if(!(o=malloc(sizeof(OpenSearchItem))))
    {
        return NULL;
    }

    o->text = NULL;
    o->description = NULL;
    o->url = NULL;

    return o;
}

void OpenSearchItem_destruct(OpenSearchItem *o)
{
    if(o)
    {
        g_free(o->text);
        g_free(o->description);
        g_free(o->url);
        free(o);
    }
}

OpenSearch *OpenSearch_construct(WikipediaLookup *wpl)
{
    OpenSearch *o;
    if(!(o=malloc(sizeof(OpenSearch))))
    {
        return NULL;
    }

    o->list = NULL;
    o->wpl = wpl;

    return o;
}

void OpenSearch_destruct(OpenSearch *o)
{
    if(o)
    {
        g_list_free_full(o->list, (GDestroyNotify)OpenSearchItem_destruct);
        free(o);
    }
}

/** Lookup a word with OpenSearch engine on Wikipedia.
  *
  * @param o A OpenSearch structure to hold the data.
  * @param text The text to look up.
  *
  * @return The number of results.
  *
  */
int OpenSearch_search(OpenSearch *o, gchar *text)
{
    //TODO: remove local static text, refactor
    gchar *url;
    gchar *escaped_text;
    WikipediaXml *xml;
    gint index = 0;
    OpenSearchItem *item;
    xmlXPathObjectPtr result = NULL;
    xmlNodePtr cur;

    escaped_text = g_uri_escape_string(text, NULL, TRUE);

    url = g_strdup_printf ("%s/w/api.php?action=opensearch&search=%s&limit=%d&format=xml",
                                  o->wpl->url, escaped_text, o->wpl->opensearchLimit);

    xml = WikipediaXml_construct();
    WikipediaXml_loadUrl(xml, url);

    result = WikipediaXml_getNodeset(xml, "/os:SearchSuggestion/os:Section/os:Item");

    if (result ==NULL)
        return 0;

    for(index = 0; index < result->nodesetval->nodeNr; index++)
    {
        cur = result->nodesetval->nodeTab[index]->xmlChildrenNode;

        item = OpenSearchItem_construct();
        while(cur != NULL)
        {
            if (!strcmp(cur->name, "Text"))
            {
                item->text = xmlNodeListGetString(xml->doc, cur->xmlChildrenNode, 1);
            }
            if (!strcmp(cur->name, "Description"))
            {
                item->description = xmlNodeListGetString(xml->doc, cur->xmlChildrenNode, 1);
            }
            if (!strcmp(cur->name, "Url"))
            {
                item->url = xmlNodeListGetString(xml->doc, cur->xmlChildrenNode, 1);
            }
            cur = cur->next;
        }
        o->list = g_list_append(o->list, (gpointer) item);
    }
    xmlXPathFreeObject (result);
    WikipediaXml_destruct(xml);
    g_free(escaped_text);
    g_free(url);

    return g_list_length(o->list);

}
