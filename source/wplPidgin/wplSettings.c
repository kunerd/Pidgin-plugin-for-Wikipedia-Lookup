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

#include "wplSettings.h"

GtkWidget *WpPidginSettings_createViewAndModel();

GtkWidget *WplPidginSettings_createWindows(PurplePlugin *plugin)
{
        GtkWidget *ret, *vbox, *win, *language_list;

        ret = gtk_vbox_new(FALSE, PIDGIN_HIG_CAT_SPACE);
        gtk_container_set_border_width (GTK_CONTAINER(ret), PIDGIN_HIG_BORDER);

        vbox = pidgin_make_frame(ret, "Settings");
        gtk_container_set_border_width(GTK_CONTAINER(vbox), 4);
        gtk_widget_show(vbox);

        win = gtk_scrolled_window_new(0, 0);
        gtk_box_pack_start(GTK_BOX(vbox), win, TRUE, TRUE, 0);
        gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(win), GTK_SHADOW_IN);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(win),
                        GTK_POLICY_NEVER,
                        GTK_POLICY_ALWAYS);

        gtk_widget_show(win);

        language_list = WpPidginSettings_createViewAndModel();
        gtk_container_add(GTK_CONTAINER(win), language_list);

        gtk_widget_show(language_list);

        gtk_widget_show_all(ret);
        return ret;
}

GtkWidget *WpPidginSettings_createViewAndModel()
{
        GtkCellRenderer *renderer = NULL;
        GtkTreeModel *model = NULL;
        GtkWidget *view = NULL;
        GtkTreeSelection *selection = NULL;
        GtkTreeIter sel_iter;
        GtkListStore *store = NULL;
        GtkTreeIter iter;
        LinkedList *list, *iterator;
        WikipediaLookup *wpl;

        view = gtk_tree_view_new ();
        gtk_widget_set_size_request(view, -1, 200);

        store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_STRING);

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

        list = LinkedList_construct(NULL);
        if(WikipediaLookup_getLanguages(list))
        {
            iterator = list;
            while(iterator != NULL)
            {
                wpl = (WikipediaLookup*)(iterator->data);

                gtk_list_store_append (store, &iter);
                gtk_list_store_set (store, &iter,
                                    COL_NAME, wpl->language,
                                    COL_URL, wpl->url,
                                    -1);
                printf("%s, %s\n", wpl->language, wpl->url);
                WikipediaLookup_destruct(wpl);

                iterator = iterator->next;
            }
            LinkedList_destruct(list);
        }

        model = GTK_TREE_MODEL (store);



        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
        //gtk_tree_selection_set_select_function(selection, wplanguage_selection_callback, NULL, NULL);

        gtk_tree_selection_set_mode(selection,
                                    GTK_SELECTION_SINGLE);

        gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

        /* preselection */
        /*gtk_tree_selection_select_iter(gtk_tree_view_get_selection(GTK_TREE_VIEW(view)), &sel_iter);
        gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(view),
                                     gtk_tree_model_get_path(model, &sel_iter),
                                     NULL,
                                     TRUE,0.5,0);
*/
        /* The tree view has acquired its own reference to the
         *  model, so we can drop ours. That way the model will
         *  be freed automatically when the tree view is destroyed */

        g_object_unref (model);

        return view;
}

 /* Function : wpsettings_save_settings()
 	-----------------------------------------------------------
    Input    : 	void
    Output   : 	void
	 
    Procedure: 	save all plugin settings to an xml file
 */
WplPidginSettings *WplPidginSettings_construct()
{
    WplPidginSettings *o;
    if(!(o=malloc(sizeof(WplPidginSettings))))
    {
        return NULL;
    }

    return o;
}


/* Function : wpsettings_load_settings()
 	-----------------------------------------------------------
    Input    : 	void
    Output   : 	void
	 
    Procedure: 	loads all plugin settings from an xml file
 */
void WplPidginSettings_destruct(WplPidginSettings *o)
{	
    if(o)
    {
        g_free(o->language);
        g_free(o->url);
        free(o);
    }
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
        //size = strlen((gchar*)name)+1;

        /*if(wpl_settings.language != NULL)
                g_free(wpl_settings.language);*/

        //wpl_settings.language = (guchar *) malloc(size*sizeof(guchar));
	
        /*if(wpl_settings.language != NULL)
	{
		g_sprintf((gchar*)wpl_settings.language,"%s", (gchar*)name);
        }*/

	/* url */
        //size = strlen((gchar*)url)+1;
        /*if(wpl_settings.wikipedia_search_url != NULL)
                g_free(wpl_settings.wikipedia_search_url);*/

        //wpl_settings.wikipedia_search_url = (guchar *) malloc(size*sizeof(guchar));
	
        /*if(wpl_settings.wikipedia_search_url != NULL)
	{
		g_sprintf((gchar*)wpl_settings.wikipedia_search_url,"%s", (gchar*)url);
        }*/
}

void WplPidginSettings_loadFromFile(WplPidginSettings *o)
{
    gchar *filepath = NULL;
    WikipediaXml *xml = NULL;

    xml = WikipediaXml_construct();
    filepath = g_build_filename(purple_user_dir(),"wpl_settings.xml",NULL);
    WikipediaXml_loadFile(xml, filepath);
    g_free(filepath);

    o->url = WikipediaXml_getText(xml, "/settings/url");
    o->language = WikipediaXml_getAttribute(xml, "/settings/url", "language");

    /*free the document */
    WikipediaXml_destruct(xml);
    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();
}

// TODO: refactor, like load from file
void WplPidginSettings_saveToFile(WplPidginSettings *o)
{
    gchar *filename = NULL;
    xmlDocPtr doc = NULL;       	/* document pointer */
    xmlNodePtr root_node = NULL,
    url_node = NULL;                    /* node pointers */

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
               BAD_CAST o->url);

   xmlNewProp(url_node, BAD_CAST "language", BAD_CAST o->language);

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
