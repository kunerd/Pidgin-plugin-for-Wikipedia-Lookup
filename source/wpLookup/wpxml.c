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

#include "wpxml.h"

size_t WikipediaXml_writeMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data);

WikipediaXml *WikipediaXml_construct(void)
{
    WikipediaXml *o;
    if(!(o=malloc(sizeof(WikipediaXml))))
    {
        return NULL;
    }

    if(!(o->chunk.memory = malloc(1)))
    {
        WikipediaXml_destruct(o);
        return NULL;
    }

    o->chunk.size = 0;

    return o;
}

void WikipediaXml_destruct(WikipediaXml *o)
{
    if(o)
    {
        xmlFreeDoc(o->doc);
        g_free(o->chunk.memory);
        free(o);
    }
}

void WikipediaXml_load(WikipediaXml *o, gchar *url)
{
        CURL *curl_handle=NULL;

        curl_global_init(CURL_GLOBAL_ALL);
        curl_handle = curl_easy_init();

        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WikipediaXml_writeMemoryCallback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&(o->chunk));
        curl_easy_setopt (curl_handle, CURLOPT_USERAGENT, WPLOOKUP_WPXML_USER_AGENT);

        curl_easy_perform(curl_handle);
        curl_easy_cleanup(curl_handle);

        curl_global_cleanup();

        o->doc = xmlParseMemory(o->chunk.memory, o->chunk.size);
        if(o->doc == NULL){
            //TODO: real error logging
            printf("no valid xml");
        }
        xmlCleanupParser();
}

gchar *WikipediaXml_getText(WikipediaXml *o, gchar *xPath)
{
    gchar *content = NULL;
    xmlXPathObjectPtr result = NULL;

    result = WikipediaXml_getNodeset(o, (xmlChar*)xPath);
    if(result == NULL)
    {
        return NULL;
    }

    content = (gchar*) xmlNodeListGetString(o->doc, result->nodesetval->nodeTab[0]->xmlChildrenNode, 1);

    xmlXPathFreeObject(result);

    return content;
}

gchar *WikipediaXml_getAttribute(WikipediaXml *o, gchar *xPath, gchar *name)
{
    gchar *content= NULL;
    xmlXPathObjectPtr result = NULL;

    result = WikipediaXml_getNodeset(o, (xmlChar*)xPath);
    if(result == NULL)
    {
        return NULL;
    }
    content = (gchar*)xmlGetProp(result->nodesetval->nodeTab[0], (xmlChar*)name);

    xmlXPathFreeObject(result);

    return content;
}

/* Function : wputility_get_nodeset
       -----------------------------------------------------------
   Input    : 	xmlDocPtr doc	-> pointer to xml document
                       xmlChar *xpath	-> xpath to find the nodeset

   Output   : 	xmlXPathObjectPtr -> pointer to start node in the xml doc

   Procedure: 	returns a pointer to an xml node found via xpath, if no such node
                       exists return value is NULL
*/
xmlXPathObjectPtr WikipediaXml_getNodeset (WikipediaXml *o, xmlChar *xPath){

       xmlXPathContextPtr context = NULL;
       xmlXPathObjectPtr result = NULL;
       xmlNodeSetPtr nodeset = NULL;

       if(o->doc == NULL)
       {
           return NULL;
       }

       context = xmlXPathNewContext(o->doc);
       if (context == NULL) {
               return NULL;
       }

       // TODO: remove local static text
       xmlXPathRegisterNs(context,  BAD_CAST "os", BAD_CAST "http://opensearch.org/searchsuggest2");

       result = xmlXPathEvalExpression(xPath, context);
       if (result == NULL) {
           xmlXPathFreeContext(context);
           return NULL;
       }

       nodeset = result->nodesetval;
       if(xmlXPathNodeSetIsEmpty(nodeset)){
           xmlXPathFreeContext(context);
           xmlXPathFreeObject(result);
           return NULL;
       }
       xmlXPathFreeContext(context);

       return result;
  }

/* Function : wplanguage_write_memory_callback(void *ptr, size_t size, size_t nmemb, void *data)
        -----------------------------------------------------------
    Input    : 	void *ptr, size_t size, size_t nmemb, void *data

    Output   : 	size_t

    Procedure: 	callback for curl to allocate memory and save xml
 */
size_t WikipediaXml_writeMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
        size_t realsize = size * nmemb;
        struct MemoryStruct *mem = (struct MemoryStruct *)data;

        mem->memory = realloc(mem->memory, mem->size + realsize + 1);
        if (mem->memory == NULL) {
                /* out of memory! */
                printf("not enough memory (realloc returned NULL)\n");
                exit(EXIT_FAILURE);
        }

        memcpy(&(mem->memory[mem->size]), ptr, realsize);
        mem->size += realsize;
        mem->memory[mem->size] = 0;

        return realsize;
}
