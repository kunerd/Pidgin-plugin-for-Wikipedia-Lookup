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

#include "wpsettings.h"

 /* Function : wpsettings_save_settings()
 	-----------------------------------------------------------
    Input    : 	void
    Output   : 	void
	 
    Procedure: 	save all plugin settings to an xml file
 */
void wpsettings_save_settings()
{
	gchar *filename = NULL;
	xmlDocPtr doc = NULL;       	/* document pointer */
    xmlNodePtr root_node = NULL, 
				url_node = NULL;	/* node pointers */
	
    /* 
     * Creates a new document, a node and set it as a root node
     */
    doc = xmlNewDoc(BAD_CAST "1.0");
    root_node = xmlNewNode(NULL, BAD_CAST "settings");
    xmlDocSetRootElement(doc, root_node);

    /* 
     * xmlNewChild() creates a new node, which is "attached" as child node
     * of root_node node. 
     */
    url_node = xmlNewChild(root_node, NULL, BAD_CAST "url",
                BAD_CAST wpl_settings.wikipedia_search_url);
	
    xmlNewProp(url_node, BAD_CAST "language", BAD_CAST wpl_settings.language);

    /* 
     * Dumping document to stdio or file
     */
	filename = g_build_filename(purple_user_dir(),"wpl_settings.xml",NULL);
    xmlSaveFormatFileEnc(filename, doc, "UTF-8", 1);

	g_free(filename);

    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();
}


/* Function : wpsettings_load_settings()
 	-----------------------------------------------------------
    Input    : 	void
    Output   : 	void
	 
    Procedure: 	loads all plugin settings from an xml file
 */
void wpsettings_load_settings()
{	
	gchar *filename = NULL;
	xmlDocPtr doc = NULL;
	xmlChar *xpathUrl = (xmlChar*) "/settings/url";
	xmlXPathObjectPtr result = NULL;

	filename = g_build_filename(purple_user_dir(),"wpl_settings.xml",NULL);
	doc = xmlReadFile(filename, NULL, 0);
	g_free(filename);
	
    if (doc == NULL) {
    	// set default, if no settings exist
    	wpsettings_change_settings((guchar*)"English", (guchar*)"http://en.wikipedia.org");
		return;
	}

	result = wputility_get_nodeset(doc, xpathUrl);
	if(result)
	{
		wpl_settings.language = xmlGetProp(result->nodesetval->nodeTab[0], (const xmlChar*)"language");
		wpl_settings.wikipedia_search_url = xmlNodeListGetString(doc, result->nodesetval->nodeTab[0]->xmlChildrenNode, 1);
		xmlXPathFreeObject (result);
	}

    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();
}

/* Function : wpsettings_change_settings
 	-----------------------------------------------------------
    Input    : 	guchar *name	-> language name
 				guchar *url		-> Wikipedia url for language
 
    Output   : 	void
	 
    Procedure: 	allocate the memory for the settings and store them in settings
 				struct
 */
void wpsettings_change_settings(guchar *name, guchar *url)
{
	int size = 0;

	/*name */
	/* add 1 for \0 */
	size = strlen((gchar*)name)+1;

	if(wpl_settings.language != NULL)
		g_free(wpl_settings.language);

	wpl_settings.language = (guchar *) malloc(size*sizeof(guchar));
	
	if(wpl_settings.language != NULL)
	{
		g_sprintf((gchar*)wpl_settings.language,"%s", (gchar*)name);
	}

	/* url */
	size = strlen((gchar*)url)+1;
	if(wpl_settings.wikipedia_search_url != NULL)
		g_free(wpl_settings.wikipedia_search_url);

	wpl_settings.wikipedia_search_url = (guchar *) malloc(size*sizeof(guchar));
	
	if(wpl_settings.wikipedia_search_url != NULL)
	{
		g_sprintf((gchar*)wpl_settings.wikipedia_search_url,"%s", (gchar*)url);
	}
}
