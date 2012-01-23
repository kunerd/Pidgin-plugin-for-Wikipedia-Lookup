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

/**
* @file wplPidgin.h
*
* @brief Pidgin plugin bindings
*
* Here are all Pidgin plugin bindings.
*/

#include "wplPidgin.h"
#include "wpconf.h"


WplPidginPlugin *wpl_plugin = NULL;

WplPidginPlugin *WplPidginPlugin_construct(void)
{
    WplPidginPlugin *o;
    if(!(o=malloc(sizeof(WplPidginPlugin))))
    {
        return NULL;
    }

    return o;
}

void WplPidginPlugin_destruct(WplPidginPlugin *o)
{
    if(o != NULL)
    {
        WplPidginSettings_destruct(o->settings);
        free(o);
    }
}

static void opensearchMenuCallback(GtkMenuItem *menuitem,
                                   gchar*     url)
{
    if(url != NULL)
    {
        purple_notify_uri(wpl_plugin->wplookup_plugin_handle, url);
        g_free(url);
    }
}

/**
  Hallo Doxygen
  */
static void wplookup_attach_conv(PurpleConversation *conv, WplPidginPlugin *o){

 PidginConversation *gtkconv;
  GtkTextView *view;

  gtkconv = PIDGIN_CONVERSATION(conv);
  
  view = GTK_TEXT_VIEW(gtkconv->imhtml);
  g_signal_connect(G_OBJECT(view), "populate-popup", G_CALLBACK(WikipediaLookup_rightClickPopup), (gpointer)o->settings->wpl);

  view = GTK_TEXT_VIEW(gtkconv->entry);
  g_signal_connect(G_OBJECT(view),"populate-popup", G_CALLBACK(WikipediaLookup_rightClickPopup), (gpointer)o->settings->wpl);

}

static void wplookup_remove_from_conv(PidginConversation *gtkconv){

  GtkTextView *view;

  view = GTK_TEXT_VIEW(gtkconv->imhtml);
  g_signal_handlers_disconnect_matched(G_OBJECT(view),G_SIGNAL_MATCH_FUNC, 0, 0, NULL, G_CALLBACK(WikipediaLookup_rightClickPopup), NULL);
  
  view = GTK_TEXT_VIEW(gtkconv->entry);
  g_signal_handlers_disconnect_matched(G_OBJECT(view),G_SIGNAL_MATCH_FUNC, 0, 0, NULL, G_CALLBACK(WikipediaLookup_rightClickPopup), NULL);

}

//Function is called on loading of the plugin
static gboolean
plugin_load(PurplePlugin *plugin) {
    void *conv_handle;
    GList *convs;
    WplPidginSettings *settings;

    wpl_plugin = WplPidginPlugin_construct();

    settings = WplPidginSettings_construct();
    WplPidginSettings_loadFromFile(settings);

    wpl_plugin->settings = settings;
    wpl_plugin->wplookup_plugin_handle = plugin;
    wpl_plugin->settings->wpl->opensearchCallback = G_CALLBACK(opensearchMenuCallback);

    conv_handle = purple_conversations_get_handle();

    /*Attach to existing conversations */
    for (convs = purple_get_conversations(); convs != NULL; convs = convs->next)
    {
        wplookup_attach_conv((PurpleConversation *)convs->data, (gpointer)wpl_plugin);
    }

    purple_signal_connect(conv_handle, "conversation-created",
                          plugin, PURPLE_CALLBACK(wplookup_attach_conv), (gpointer)wpl_plugin);

    return TRUE;
}

static gboolean
plugin_unload(PurplePlugin *plugin){
  void *conv_handle;
  GList *convs;

  conv_handle = purple_conversations_get_handle();

  /*save settings */
  WplPidginSettings_saveToFile(wpl_plugin->settings);

  for (convs = purple_get_conversations(); convs != NULL; convs = convs->next)
  {
    PurpleConversation *conv = (PurpleConversation *)convs->data;
    if(PIDGIN_IS_PIDGIN_CONVERSATION(conv)){
      wplookup_remove_from_conv(PIDGIN_CONVERSATION(conv));
    }
  }

  /* cleanup */
  WplPidginPlugin_destruct(wpl_plugin);

  return TRUE;
}

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

        language_list = WplPidginSettings_createViewAndModel(wpl_plugin->settings);
        gtk_container_add(GTK_CONTAINER(win), language_list);

        gtk_widget_show(language_list);

        gtk_widget_show_all(ret);
        return ret;
}

static PidginPluginUiInfo settings =
{
        WplPidginSettings_createWindows,
	0, /* page_num (Reserved) */

	/* padding */
        NULL,
	NULL,
	NULL,
	NULL
};

static PurplePluginInfo info = {
    PURPLE_PLUGIN_MAGIC,
    PURPLE_MAJOR_VERSION,
    PURPLE_MINOR_VERSION,
    PURPLE_PLUGIN_STANDARD,
    PIDGIN_PLUGIN_TYPE,
    0,
    NULL,
    PURPLE_PRIORITY_DEFAULT,
    WPL_PIDGIN_PLUGIN_ID,
    "Wikipedia Lookup",
    VERSION_NUMBER,
    "Wikipedia-Lookup Plugin",
    "Plugin that show you Wikipedia articles for recieved or typed words.",
    "Hendrik Kunert <kunerd@users.sourceforge.net>",
    "https://sourceforge.net/projects/pidginpluginfor/",
    plugin_load,  //on load
    plugin_unload,//on unload   gboolean plugin_unload(PurplePlugin *plugin)
    NULL,         //on destroy  void plugin_destroy(PurplePlugin *plugin)
    &settings,    //UI info struct pointer
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

PURPLE_INIT_PLUGIN(wplPidgin, init_plugin, info)
