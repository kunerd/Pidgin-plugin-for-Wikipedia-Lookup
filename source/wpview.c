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

#include "wpview.h"

 /* Function : void wpview_show_in_browser(guchar *search_text)
 	-----------------------------------------------------------
    Input    : guchar *search -> search string (Wikipedia article name)
    Output   : void
    Procedure: open Wikipedia article in standard browser
 */
/*static void wpview_show_in_browser(guchar *search_text)
{
	guchar *search_url = NULL;
	int size = 0;

	size = strlen((gchar*)wpl_settings.wikipedia_search_url)+strlen((gchar*)WPL_WIKIPEDIA_PATH)+strlen((gchar*)search_text)+1;
	
	search_url = (guchar *) malloc(size*sizeof(guchar));
	if(search_url != NULL)
	{
		g_sprintf((gchar*)search_url,"%s%s", (gchar*)wpl_settings.wikipedia_search_url, search_text);
		purple_notify_uri(wplookup_plugin_handle, (gchar*)search_url);
	}
	if(search_text != NULL)
		g_free(search_text);
	if(search_url != NULL)
		g_free(search_url);
}*/

static gchar* get_wikipedia_article(gchar *search_url, gchar **name)
{
	xmlDoc *doc = NULL;
	xmlXPathObjectPtr result = NULL;
	xmlChar *xpathContent = (xmlChar*) "/api/parse/text";
	xmlChar *xpathName = (xmlChar*) "/api/parse";
	xmlChar *content = NULL;
	xmlNodeSetPtr nodeset = NULL;
	struct MemoryStruct chunk;

	chunk.memory = malloc(1);
	chunk.size = 0;

	wpweb_get_webpage(search_url, (void *)&chunk);

	doc = xmlParseMemory(chunk.memory, chunk.size);
	if(doc == NULL){
		printf("no valid xml");
	}

	result = wputility_get_nodeset (doc, xpathContent);

	if(result != NULL)
	{
		nodeset = result->nodesetval;
		content = xmlNodeListGetString(doc, nodeset->nodeTab[0]->xmlChildrenNode, 1);

		xmlXPathFreeObject (result);
	}

	result = wputility_get_nodeset (doc, xpathName);

	if(result != NULL)
	{
		nodeset = result->nodesetval;
		*name = (gchar*)xmlGetProp(nodeset->nodeTab[0], (const xmlChar*)"displaytitle");

		xmlXPathFreeObject (result);
	}

	xmlFreeDoc(doc);
	
	if(chunk.memory)
		free(chunk.memory);
	
	return (gchar*)content;

}

static gchar* wpview_create_webpage(gchar *head, gchar *content) {
	gchar *webpage = NULL;
	int size;

	size = strlen((gchar*)content)+strlen((gchar*)head)+strlen(WPL_PAGE_TEMPLATE)+1;
	webpage = (gchar *) malloc(size*sizeof(gchar));
	if(webpage != NULL)
	{
		g_sprintf((gchar*)webpage, WPL_PAGE_TEMPLATE, head, content);
	}

	return webpage;
}

void wpview_open_preview_window(void *preview_data)
{
	GtkWidget *win, *dialog, *content_area, *web_view;
	gchar *search_url = NULL;
	gchar *article_content = NULL;
	gchar *article_name	= NULL;
	gchar *webpage = NULL;
	int size = 0;
	struct PreviewData *data = (struct PreviewData *)preview_data;
	gchar *uri = NULL;
	gchar *user_dir;
	
	/* create search path */
	size = strlen((gchar*)wpl_settings.wikipedia_search_url)+strlen((gchar*)WPL_WIKIPEDIA_API_PATH)+strlen(data->search_text)+1;
	
	search_url = (gchar *) malloc(size*sizeof(gchar));
	if(search_url != NULL)
	{
		g_sprintf((gchar*)search_url, WPL_WIKIPEDIA_API_PATH, wpl_settings.wikipedia_search_url, data->search_text);
	}	
	
	/* Create the widgets */
	dialog = gtk_dialog_new_with_buttons ("preview",
                                         GTK_WINDOW(data->parent_window),
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_STOCK_OK,
                                         GTK_RESPONSE_NONE,
                                         NULL);
	gtk_window_set_default_size (GTK_WINDOW(dialog), 600, 400);

	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

	win = gtk_scrolled_window_new(0, 0);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(win),
										GTK_SHADOW_IN);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(win),
			GTK_POLICY_NEVER,
			GTK_POLICY_ALWAYS);

	/* for GtkWebkit */
	web_view = webkit_web_view_new ();
    gtk_container_add (GTK_CONTAINER (win), web_view);
	g_signal_connect_swapped (dialog,
                             "response",
                             G_CALLBACK (gtk_widget_destroy),
                             dialog);

	gtk_container_add (GTK_CONTAINER (content_area), win);

	article_content = get_wikipedia_article(search_url, &article_name);

	user_dir = g_build_path("/",(gchar*)purple_user_dir(),"wplookup","resources", NULL);
	g_printf("%s", user_dir);
	uri = wputility_get_uri(user_dir, "main-ltr.css");
	g_object_set (webkit_web_view_get_settings (WEBKIT_WEB_VIEW (web_view)),
	              "user-stylesheet-uri", uri, NULL);

	g_free(uri);
	g_free(user_dir);

	gtk_widget_show_all (dialog);

	if(article_content!=NULL)
	{
		webpage = wpview_create_webpage(article_name, article_content);
		if(webpage != NULL)
		{
			webkit_web_view_load_string (WEBKIT_WEB_VIEW (web_view),
										 webpage,
										 "text/html",
										 "UTF-8",
										 "file://");
			g_free(webpage);
		}
		g_free(article_name);
		g_free(article_content);
	}
	else {
		webpage = wpview_create_webpage("Error", "<p>Couldn't find an article</p>");
	}

	if(search_url != NULL)
		g_free(search_url);

	if(data != NULL)
		free(data);

}

/* Function : wpview_right_click_popup(GtkTextView *text_view, GtkMenu *menu)
 	-----------------------------------------------------------
    Input    : 	GtkTextView *text_view 	-> gtk text view that is right clicked
				GtkMenu *menu 			-> displayed menu for appending own menu entry
	 
    Output   : 	void
	 
    Procedure: 	callback for gtk textfields, called whenever a right click in the
	 			text view occured
 */
void wpview_right_click_popup(GtkTextView *text_view, GtkMenu *menu)
{
	GtkTextBuffer *buffer = NULL;
	GtkWidget *menu_entry = NULL;
	gchar *search_text = NULL;
	GtkTextIter start_selection;
	GtkTextIter end_selection;
	GtkWidget *parent = NULL;
    
  	buffer = gtk_text_view_get_buffer(text_view);

	struct PreviewData *preview_data;
  	
  	/* somthing selected? */
  	if(gtk_text_buffer_get_selection_bounds(buffer, &start_selection, &end_selection))
  	{
		preview_data = malloc(sizeof(struct PreviewData));
		  
		/* get selected text */
		search_text = (gchar*)gtk_text_buffer_get_text(buffer, &start_selection, &end_selection, FALSE);
		  
		/* add menu entry to popup menuy */
		menu_entry = gtk_menu_item_new_with_label("Wikipedia");
		gtk_menu_append(GTK_MENU(menu),menu_entry);
		  
		/* Attach the callback functions to the activate signal */
		//g_signal_connect_swapped( GTK_OBJECT(menu_entry), "activate", GTK_SIGNAL_FUNC(wpview_show_in_browser), (gpointer) search_text);

		parent = gtk_widget_get_toplevel (GTK_WIDGET(text_view));

		preview_data->search_text = g_uri_escape_string(search_text, NULL, TRUE);
		preview_data->parent_window = parent;
		
		if (gtk_widget_is_toplevel (parent))
		{
			g_signal_connect_swapped( GTK_OBJECT(menu_entry), "activate", GTK_SIGNAL_FUNC(wpview_open_preview_window), (gpointer) preview_data);
		  	gtk_widget_show(menu_entry);
		}
	}
}
