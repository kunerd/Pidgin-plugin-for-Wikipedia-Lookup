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

#include <libxml/xpath.h>
#include "wplookup.h"
#include "wpxml.h"

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
        g_free(o->language);
        g_free(o->url);
        free(o);
    }
}

WikipediaArticle *WikipediaLookup_loadArticle(WikipediaLookup *o, gchar *search)
{
    WikipediaArticle *article;

    article = WikipediaArticle_construct();

    return article;
}

int WikipediaLookup_getLanguages(LinkedList *resultList)
{
    // TODO: refactor
    WikipediaXml *xml = NULL;
    WikipediaXml *subXml = NULL;
    xmlXPathObjectPtr result = NULL;
    int count = 0;
    int index;
    gchar *name;
    gchar *url;

    xmlNode *root_element = NULL;
    xmlXPathObjectPtr resultUrl = NULL;
    xmlDoc *subDoc = NULL;
    xmlNodeSetPtr nodesetUrl= NULL;

    WikipediaLookup *wpl;

    xml = WikipediaXml_construct();
    // TODO: remove static local url here
    WikipediaXml_load(xml, "http://de.wikipedia.org/w/api.php?action=sitematrix&format=xml");

    result = WikipediaXml_getNodeset(xml, "/api/sitematrix/language");

    for(index = 0; index < result->nodesetval->nodeNr; index++)
    {
        subDoc = xmlNewDoc(BAD_CAST "1.0");
        if(subDoc == NULL){
            printf("no valid xml");
        }
        root_element = result->nodesetval->nodeTab[index];
        xmlDocSetRootElement(subDoc, root_element);
        subXml = WikipediaXml_construct();
        subXml->doc = subDoc;
        resultUrl = WikipediaXml_getNodeset (subXml, "/language/site/site[@code=\"wiki\"]/@url");
        if (resultUrl != NULL) {
            nodesetUrl = resultUrl->nodesetval;
            if(nodesetUrl->nodeNr)
            {
                url = (gchar*)xmlNodeListGetString(subDoc, nodesetUrl->nodeTab[0]->xmlChildrenNode, 1);
                name = (gchar*)xmlGetProp(result->nodesetval->nodeTab[index], (const xmlChar*)"name");

                wpl = WikipediaLookup_construct(url,name);

                LinkedList_addElement(resultList, wpl);
                count++;
            }
            xmlXPathFreeObject (resultUrl);
        }
        WikipediaXml_destruct(subXml);
        xmlCleanupParser();
    }
    xmlXPathFreeObject (result);
    WikipediaXml_destruct(xml);
    return count;
}

