/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) Hendrik Kunert 2011 <hendrik@linux-vxjw.site>
	 * 
 * libcurl is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
	 * 
 * libcurl is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "wikiinfo.h"

static size_t
WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
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

static xmlXPathObjectPtr
getnodeset (xmlDocPtr doc, xmlChar *xpath){

	xmlXPathContextPtr context;
	xmlXPathObjectPtr result;

	context = xmlXPathNewContext(doc);
	if (context == NULL) {
		return NULL;
	}
	result = xmlXPathEvalExpression(xpath, context);
	xmlXPathFreeContext(context);
	if (result == NULL) {
		return NULL;
	}
	if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
		xmlXPathFreeObject(result);
		return NULL;
	}
	return result;
}

static GtkTreeModel * getWikipediaLanguages()
{
	char *marker;
	int i = 0;
	CURL *curl_handle=NULL;
	xmlDoc *doc = NULL;
	xmlDoc *subDoc = NULL;
	xmlNode *root_element = NULL;
	xmlXPathObjectPtr result = NULL;
	xmlXPathObjectPtr result2 = NULL;
	xmlChar *xpathName = (xmlChar*) "/api/sitematrix/language";
	xmlChar *xpathUrl = (xmlChar*) "/language/site/site[@code=\"wiki\"]/@url";
	xmlNodeSetPtr nodeset = NULL;
	xmlNodeSetPtr nodeset2= NULL;
	xmlChar *url = NULL;
	xmlChar *name = NULL;
	GtkListStore  *store;
	GtkTreeIter    iter;
	
	struct MemoryStruct chunk;

	chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */ 
	chunk.size = 0;    /* no data at this point */

	store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_STRING);

	curl_global_init(CURL_GLOBAL_NOTHING);

	/* init the curl session */ 
	curl_handle = curl_easy_init();

	/* specify URL to get */ 
	curl_easy_setopt(curl_handle, CURLOPT_URL, "http://de.wikipedia.org/w/api.php?action=sitematrix&format=xml");

	/* send all data to this function  */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

	/* we pass our 'chunk' struct to the callback function */ 
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

	/* some servers don't like requests that are made without a user-agent field, so we provide one */ 
	curl_easy_setopt (curl_handle, CURLOPT_USERAGENT, "Mozilla/4.0");

	/* get it! */ 
	curl_easy_perform(curl_handle);

	/* cleanup curl stuff */ 
	curl_easy_cleanup(curl_handle);

	/* we're done with libcurl, so clean it up */
	curl_global_cleanup();

	doc = xmlParseMemory(chunk.memory, chunk.size);
	if(doc == NULL){
		printf("no valid xml");
	}

	//print_element_names(root_element);
	result = getnodeset (doc, xpathName);
	                 
	if (result) {
		nodeset = result->nodesetval;

		for (i=0; i < nodeset->nodeNr; i++) {
			
			subDoc = xmlNewDoc("1.0");
			if(subDoc == NULL){
				printf("no valid xml");
			}
			
			root_element = nodeset->nodeTab[i];
			xmlDocSetRootElement(subDoc, root_element);
			result2 = getnodeset (subDoc, xpathUrl);
			if (result2) {
				nodeset2 = result2->nodesetval;
				if(nodeset2->nodeNr)
				{
					url = xmlNodeListGetString(subDoc, nodeset2->nodeTab[0]->xmlChildrenNode, 1);
					name = xmlGetProp(nodeset->nodeTab[i], (const xmlChar*)"name");
					
					  gtk_list_store_append (store, &iter);
					  gtk_list_store_set (store, &iter,
										  COL_NAME, name,
										  COL_URL, url,
										  -1);
					//printf("url: %s\n", keyword);
					//if(keyword)
					//	xmlFree(keyword);

					xmlFree(url);
					xmlFree(name);
				}
				/*keyword = xmlGetProp(nodeset->nodeTab[i], (const xmlChar*)"name");
				printf("language: %s\n", keyword);
				if(keyword)
					xmlFree(keyword);*/

				xmlXPathFreeObject (result2);
			}
			xmlUnlinkNode(root_element);
			xmlFreeNode(root_element);
			xmlFreeDoc(subDoc);
		}
		xmlXPathFreeObject (result);
	}
	/*free the document */
	xmlFreeDoc(doc);
	/*
	*Free the global variables that may
	*have been allocated by the parser.
	*/
	xmlCleanupParser();
	if(chunk.memory)
		xmlFree(chunk.memory);

	GTK_TREE_MODEL (store);
}

GtkWidget *
create_view_and_model ()
{
  GtkCellRenderer     *renderer;
  GtkTreeModel        *model;
  GtkWidget           *view;

  view = gtk_tree_view_new ();

  /* --- Column #1 --- */

  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                               -1,      
                                               "Sprache",  
                                               renderer,
                                               "text", COL_NAME,
                                               NULL);

  /* --- Column #2 --- */

  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                               -1,      
                                               "URL",  
                                               renderer,
                                               "text", COL_URL,
                                               NULL);

  model = getWikipediaLanguages();

  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

  /* The tree view has acquired its own reference to the
   *  model, so we can drop ours. That way the model will
   *  be freed automatically when the tree view is destroyed */

  g_object_unref (model);

  return view;
}
