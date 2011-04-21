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
static void wpview_show_in_browser(guchar *search_text)
{
	guchar *search_url = NULL;
	int size = 0;

	size = strlen((gchar*)wpl_settings.wikipedia_search_url)+strlen((gchar*)search_text)+1;
	
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
}

 /* Function : void wpview_open_preview_window()
 	-----------------------------------------------------------
    Input    : void
    Output   : void
    Procedure: open Wikipedia article in preview window
 */
static void wpview_open_preview_window(guchar *search_text)
{
	
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
	guchar *search_text = NULL;
	GtkTextIter start_selection;
	GtkTextIter end_selection;
    
  	buffer = gtk_text_view_get_buffer(text_view);
  	
  	/* somthing selected? */
  	if(gtk_text_buffer_get_selection_bounds(buffer, &start_selection, &end_selection))
  	{
		  /* get selected text */
		  search_text = (guchar*)gtk_text_buffer_get_text(buffer, &start_selection, &end_selection, FALSE);
		  
		  /* add menu entry to popup menuy */
		  menu_entry = gtk_menu_item_new_with_label("Wikipedia");
		  gtk_menu_append(GTK_MENU(menu),menu_entry);
		  
		  /* Attach the callback functions to the activate signal */
		  g_signal_connect_swapped( GTK_OBJECT(menu_entry), "activate", GTK_SIGNAL_FUNC(wpview_show_in_browser), (gpointer) search_text);

		  gtk_widget_show(menu_entry);
	}
}
