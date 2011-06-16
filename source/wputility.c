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

#include "wputility.h"

 /* Function : wputility_get_nodeset
 	-----------------------------------------------------------
    Input    : 	xmlDocPtr doc	-> pointer to xml document
    			xmlChar *xpath	-> xpath to find the nodeset
    			
    Output   : 	xmlXPathObjectPtr -> pointer to start node in the xml doc
	 
    Procedure: 	returns a pointer to an xml node found via xpath, if no such node
    			exists return value is NULL
 */
xmlXPathObjectPtr
wputility_get_nodeset (xmlDocPtr doc, xmlChar *xpath){

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

/* Function : wplanguage_write_memory_callback(void *ptr, size_t size, size_t nmemb, void *data)
 	-----------------------------------------------------------
    Input    : 	void *ptr, size_t size, size_t nmemb, void *data
 
    Output   : 	size_t
	 
    Procedure: 	callback for curl to allocate memory and save xml
 */
size_t
wplanguage_write_memory_callback(void *ptr, size_t size, size_t nmemb, void *data)
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

gchar * wputility_get_uri(gchar *path, gchar *filename)
{
	GFile *dir = NULL;
	GFile *file = NULL;
	gchar *uri = NULL;

	dir = g_file_new_for_path(path);
	file = g_file_get_child(dir, filename);
	uri = g_file_get_uri (file);

	if(file != NULL)
		g_object_unref(file);
	if(dir != NULL)
		g_object_unref(dir);

	return uri;
}
