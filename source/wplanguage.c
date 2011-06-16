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

#include "wplanguage.h"

/* Function : GtkTreeModel *wplanguage_get_wikipedia_languages(GtkTreeIter *sel_iter)
 	-----------------------------------------------------------
    Input    : 	GtkTreeIter *sel_iter	-> pointer of type GtkTreeIter to hold 
											preselection
 
    Output   : 	GtkTreeModel
	 
    Procedure: 	get all possible languages from Wikipedia and save them in the tree model
 */
GtkTreeModel *wplanguage_get_wikipedia_languages(GtkTreeIter *sel_iter)
{
	int i = 0;
	xmlDoc *doc = NULL;
	xmlDoc *subDoc = NULL;
	xmlNode *root_element = NULL;
	xmlXPathObjectPtr resultName = NULL;
	xmlXPathObjectPtr resultUrl = NULL;
	xmlChar *xpathName = (xmlChar*) "/api/sitematrix/language";
	xmlChar *xpathUrl = (xmlChar*) "/language/site/site[@code=\"wiki\"]/@url";
	xmlNodeSetPtr nodesetName = NULL;
	xmlNodeSetPtr nodesetUrl= NULL;
	xmlChar *url = NULL;
	xmlChar *name = NULL;
	GtkListStore  *store = NULL;
	GtkTreeIter    iter;

	struct MemoryStruct chunk;

	chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */ 
	chunk.size = 0;    /* no data at this point */

	store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_STRING);

	wpweb_get_webpage(WPL_WIKIPEDIA_SITEMATRIX, (void *)&chunk);

	doc = xmlParseMemory(chunk.memory, chunk.size);
	if(doc == NULL){
		printf("no valid xml");
	}

	resultName = wputility_get_nodeset (doc, xpathName);

	if (resultName != NULL) {
		nodesetName = resultName->nodesetval;

		for (i=0; i < nodesetName->nodeNr; i++) {

			subDoc = xmlNewDoc(BAD_CAST "1.0");
			if(subDoc == NULL){
				printf("no valid xml");
			}

			root_element = nodesetName->nodeTab[i];
			xmlDocSetRootElement(subDoc, root_element);
			resultUrl = wputility_get_nodeset (subDoc, xpathUrl);
			if (resultUrl != NULL) {
				nodesetUrl = resultUrl->nodesetval;
				if(nodesetUrl->nodeNr)
				{
					url = xmlNodeListGetString(subDoc, nodesetUrl->nodeTab[0]->xmlChildrenNode, 1);
					name = xmlGetProp(nodesetName->nodeTab[i], (const xmlChar*)"name");

					gtk_list_store_append (store, &iter);
					gtk_list_store_set (store, &iter,
					                    COL_NAME, name,
					                    COL_URL, url,
					                    -1);

					if(strcmp((gchar*)name,(gchar*)wpl_settings.language) == 0)
					{
						/*preselection*/
						*sel_iter=iter;
					}

					xmlFree(url);
					xmlFree(name);
				}
				xmlXPathFreeObject (resultUrl);
			}
		}
		xmlXPathFreeObject (resultName);
	}

	/*free the document */
	xmlFreeDoc(doc);
	/*
	 *Free the global variables that may
	 *have been allocated by the parser.
	 */
	xmlCleanupParser();
	if(chunk.memory)
		free(chunk.memory);

	return GTK_TREE_MODEL (store);
}

/* TODO: description
 */
static gboolean
wplanguage_selection_callback (GtkTreeSelection *selection,
                               GtkTreeModel     *model,
                               GtkTreePath      *path,
                               gboolean          path_currently_selected,
                               gpointer          userdata)
{
	GtkTreeIter iter;

	if (gtk_tree_model_get_iter(model, &iter, path))
	{
		guchar *language;
		guchar *url;

		gtk_tree_model_get(model, &iter, COL_NAME, &language, -1);
		gtk_tree_model_get(model, &iter, COL_URL, &url, -1);

		if (!path_currently_selected)
		{
			// safe selection
			wpsettings_change_settings(language, url);

		}

		g_free(url);
	}

	return TRUE; /* allow selection state to change */
}


/* TODO: description */
GtkWidget *
wplanguage_create_view_and_model()
{
	GtkCellRenderer     *renderer = NULL;
	GtkTreeModel        *model = NULL;
	GtkWidget           *view = NULL;
	GtkTreeSelection    *selection = NULL;
	GtkTreeIter		  sel_iter;

	view = gtk_tree_view_new ();
	gtk_widget_set_size_request(view, -1, 200);

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

	model = wplanguage_get_wikipedia_languages(&sel_iter);

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
	gtk_tree_selection_set_select_function(selection, wplanguage_selection_callback, NULL, NULL);

	gtk_tree_selection_set_mode(selection,
	                            GTK_SELECTION_SINGLE);

	gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

	/* preselection */
	gtk_tree_selection_select_iter(gtk_tree_view_get_selection(GTK_TREE_VIEW(view)), &sel_iter);
	gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(view),
	                             gtk_tree_model_get_path(model, &sel_iter),
	                             NULL,
	                             TRUE,0.5,0);

	/* The tree view has acquired its own reference to the
	 *  model, so we can drop ours. That way the model will
	 *  be freed automatically when the tree view is destroyed */

	g_object_unref (model);

	return view;
}
