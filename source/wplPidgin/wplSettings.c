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

#include "wplSettings.h"

gboolean
WplPidginSettings_selectionCallback (GtkTreeSelection *selection,
                               GtkTreeModel     *model,
                               GtkTreePath      *path,
                               gboolean          path_currently_selected,
                               WplPidginSettings *o)
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
                    g_free(o->wpl->language);
                    g_free(o->wpl->url);

                    o->wpl->language = language;
                    o->wpl->url = url;
                }
        }

        return TRUE; /* allow selection state to change */
}

/** Creates the language list and the model for it.
  */
GtkWidget *WplPidginSettings_createViewAndModel(WplPidginSettings *o)
{
        GtkCellRenderer *renderer = NULL;
        GtkTreeModel *model = NULL;
        GtkWidget *view = NULL;
        GtkTreeSelection *selection = NULL;
        GtkTreeIter sel_iter;
        GtkListStore *store = NULL;
        GtkTreeIter iter;
        GList *list, *iterator;
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

        list = WikipediaLookup_getLanguages();
        for(iterator = list; iterator != NULL; iterator = g_list_next(iterator))
        {
                wpl = (WikipediaLookup*) iterator->data;

                gtk_list_store_append (store, &iter);
                gtk_list_store_set (store, &iter,
                                    COL_NAME, wpl->language,
                                    COL_URL, wpl->url,
                                    -1);

                /* preselection */
                if(0 == g_strcmp0(wpl->language, o->wpl->language))
                {
                    sel_iter = iter;
                }

                WikipediaLookup_destruct(wpl);

                iterator = iterator->next;
        }
        g_list_free(list);

        model = GTK_TREE_MODEL (store);



        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));

        gtk_tree_selection_set_select_function(selection, (GtkTreeSelectionFunc)WplPidginSettings_selectionCallback, (gpointer) o, NULL);

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

WplPidginSettings *WplPidginSettings_construct()
{
    WplPidginSettings *o;
    if(!(o=malloc(sizeof(WplPidginSettings))))
    {
        return NULL;
    }

    o->wpl = WikipediaLookup_construct(NULL,NULL);

    return o;
}

void WplPidginSettings_destruct(WplPidginSettings *o)
{	
    if(o != NULL)
    {
        WikipediaLookup_destruct(o->wpl);
        free(o);
    }
}

/** Load all plugin settings to an xml file.
*/
void WplPidginSettings_loadFromFile(WplPidginSettings *o)
{
    gchar *filepath = NULL;
    gchar *temp = NULL;
    guint maxOpenSearchResults;
    WikipediaXml *xml = NULL;

    xml = WikipediaXml_construct();
    filepath = g_build_filename(purple_user_dir(),"wpl_settings.xml",NULL);
    WikipediaXml_loadFile(xml, filepath);
    g_free(filepath);

    o->wpl->url = WikipediaXml_getText(xml, "/settings/url");
    o->wpl->language = WikipediaXml_getAttribute(xml, "/settings/url", "language");

    temp = WikipediaXml_getText(xml, "/settings/limit");
    if(temp)
    {
        maxOpenSearchResults = g_ascii_strtoll(temp, NULL, 10);
        if(maxOpenSearchResults > 0)
        {
            o->wpl->opensearchLimit = maxOpenSearchResults;
        }
    }
    g_free(temp);

    /*free the document */
    WikipediaXml_destruct(xml);
    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();
}


/** Save all plugin settings to an xml file.
*/
void WplPidginSettings_saveToFile(WplPidginSettings *o)
{
    gchar *filename = NULL;
    gchar *temp = NULL;
    xmlDocPtr doc = NULL;       	/* document pointer */
    xmlNodePtr root_node = NULL;
    xmlNodePtr url_node = NULL;         /* node pointers */
    xmlNodePtr max_opensearch_result = NULL;

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
               BAD_CAST o->wpl->url);

   xmlNewProp(url_node, BAD_CAST "language", BAD_CAST o->wpl->language);

   temp = g_strdup_printf("%d", o->wpl->opensearchLimit);
   if(temp)
   {
        max_opensearch_result = xmlNewChild(root_node, NULL, BAD_CAST "limit",
                                               BAD_CAST temp);
        g_free(temp);
   }
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
