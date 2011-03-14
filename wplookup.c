/*
 * Wikipedia Lookup - Description.
 * Copyright (C) 2011 Hendrik Kunert kunerd@users.sourceforge.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1301, USA.
 */

#define WPLOOKUP_PLUGIN_ID "gtk-hendrik_kunert-wikipedia-lookup"

#include <glib.h>
#include <stdio.h>

#include "internal.h"
#include "conversation.h"
#include "debug.h"
#include "plugin.h"
#include <notify.h>
#include "version.h"
#include "gtkplugin.h"
#include "gtkprefs.h"
#include "gtkutils.h"
#include "gtkconvwin.h"

PurplePlugin *wplookup_plugin_handle = NULL;

static void GetActiveConversation(PidginConversation **conv){
  GList *windows;

  /* Attach to existing conversations */
  for (windows = pidgin_conv_windows_get_list(); windows != NULL; windows = windows->next)
  {
    PidginWindow *CurrentWindow = (PidginWindow*)windows->data;
    if(pidgin_conv_window_has_focus(CurrentWindow)){
      *conv = pidgin_conv_window_get_active_gtkconv(CurrentWindow);
      return;
    }
  }
  *conv = NULL;
}

static void show_wikipedia(gchar *search_text)
{
	const gchar *wikipedia = "http://de.wikipedia.org/wiki/";
	gchar *search_url = NULL;
	search_url = malloc(strlen(wikipedia)+1+strlen(search_text)+1);
	if(search_url != NULL)
	{
		g_sprintf(search_url,"%s%s", wikipedia, search_text);
		purple_notify_uri(wplookup_plugin_handle, search_url);
	}
	if(search_text != NULL)
		g_free(search_text);
	if(search_url != NULL)
		g_free(search_url);
}

static void menu_popup(GtkTextView *text_view, GtkMenu *menu)
{
    PidginConversation *GtkConv = NULL;
	GtkTextBuffer *buffer;
	GtkWidget *menu_entry = NULL;
	gchar *search_text = NULL;
	GtkTextIter start_selection;
	GtkTextIter end_selection;

    GetActiveConversation(&GtkConv);
    if(GtkConv == NULL){
      purple_debug_error("wplookup","No active Conversation found\n");
      return;
    }
    
  	buffer = gtk_text_view_get_buffer(text_view);
  	
  	// somthing selected?
  	if(gtk_text_buffer_get_selection_bounds(buffer, &start_selection, &end_selection))
  	{
		  /* get selected text */
		  search_text = gtk_text_buffer_get_text(buffer, &start_selection, &end_selection, FALSE);
		  
		  /* add menu entry to popup menuy */
		  menu_entry = gtk_menu_item_new_with_label("Wikipedia");
		  gtk_menu_append(GTK_MENU(menu),menu_entry);
		  
		  /* Attach the callback functions to the activate signal */
		  g_signal_connect( GTK_OBJECT(menu_entry), "activate", GTK_SIGNAL_FUNC(show_wikipedia), (gpointer) search_text);

		  gtk_widget_show(menu_entry);
	}
}

static void wplookup_attach_conv(PurpleConversation *conv){
  PidginConversation *gtkconv;
  GtkTextView *view;

  gtkconv = PIDGIN_CONVERSATION(conv);
  view = GTK_TEXT_VIEW(gtkconv->entry);

  g_signal_connect(G_OBJECT(view),"populate-popup", G_CALLBACK(menu_popup), NULL);
}

static void wplookup_remove_from_conv(PidginConversation *gtkconv){
  GtkTextView *view;
  view = GTK_TEXT_VIEW(gtkconv->entry);
  
  //TODO: disconnect menu-entry callback
  g_signal_handlers_disconnect_matched(G_OBJECT(view),G_SIGNAL_MATCH_FUNC, 0, 0, NULL, G_CALLBACK(menu_popup), NULL);
}

//Function is called on loading of the plugin
static gboolean
plugin_load(PurplePlugin *plugin) {
    void *conv_handle;
    GList *convs;

    conv_handle = purple_conversations_get_handle();

    /* Attach to existing conversations */
    for (convs = purple_get_conversations(); convs != NULL; convs = convs->next)
	{
		wplookup_attach_conv((PurpleConversation *)convs->data);
	}

	purple_signal_connect(conv_handle, "conversation-created",
			    plugin, PURPLE_CALLBACK(wplookup_attach_conv), NULL);

    wplookup_plugin_handle = plugin;

    return TRUE;
}

static gboolean
plugin_unload(PurplePlugin *plugin){
  void *conv_handle;
  GList *convs;

  conv_handle = purple_conversations_get_handle();

  /* Delete Labels */
  for (convs = purple_get_conversations(); convs != NULL; convs = convs->next)
  {
    PurpleConversation *conv = (PurpleConversation *)convs->data;
    if(PIDGIN_IS_PIDGIN_CONVERSATION(conv)){
      wplookup_remove_from_conv(PIDGIN_CONVERSATION(conv));
    }
  }

  return TRUE;
}

static PurplePluginInfo info = {
    PURPLE_PLUGIN_MAGIC,
    PURPLE_MAJOR_VERSION,
    PURPLE_MINOR_VERSION,
    PURPLE_PLUGIN_STANDARD,
    PIDGIN_PLUGIN_TYPE,
    0,
    NULL,
    PURPLE_PRIORITY_DEFAULT,
    WPLOOKUP_PLUGIN_ID,
    "Wikipedia Lookup",
    "0.1",
    N_("Wikipedia-Lookup Plugin"),
    N_("Plugin that show you Wikipedia articles for recieved or typed words."),
    N_("Hendrik Kunert kunerd@users.sourceforge.net"),
    N_("https://sourceforge.net/projects/pidginpluginfor/"),
    plugin_load,  //on load
    plugin_unload,//on unload   gboolean plugin_unload(PurplePlugin *plugin)
    NULL,         //on destroy  void plugin_destroy(PurplePlugin *plugin)
    NULL,         //UI info struct pointer
    NULL,         //unknown
    NULL,         //Configuration Frame
    NULL,         //UI functions
    NULL,         //placeholder
    NULL,         //placeholder
    NULL,         //placeholder
    NULL          //placeholder
};

static void
init_plugin(PurplePlugin *plugin)
{
}

PURPLE_INIT_PLUGIN(wplookup, init_plugin, info)
