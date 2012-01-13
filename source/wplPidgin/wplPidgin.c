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
//#include "wplPreview.h"
#include "wpconf.h"
//#include "wpsettings.h"
//#include "wplanguage.h"

//WplPidginPlugin *wpl_plugin = NULL;

/*WplPidginPlugin *PidginPlugin_construct(void)
{
    WplPidginPlugin *o;
    if(!(o=malloc(sizeof(WplPidginPlugin))))
    {
        return NULL;
    }

    return o;
}

void PidginPlugin_destruct(WplPidginPlugin *o)
{
    if(o != NULL)
    {
        free(o);
    }
}*/

/**
  Hallo Doxygen
  */
static void wplookup_attach_conv(PurpleConversation *conv){

 /*PidginConversation *gtkconv;
  GtkTextView *view;

  gtkconv = PIDGIN_CONVERSATION(conv);
  
  view = GTK_TEXT_VIEW(gtkconv->imhtml);
  g_signal_connect(G_OBJECT(view),"populate-popup", G_CALLBACK(wpview_right_click_popup), (gpointer)o);
  
  view = GTK_TEXT_VIEW(gtkconv->entry);
  g_signal_connect(G_OBJECT(view),"populate-popup", G_CALLBACK(wpview_right_click_popup), (gpointer)o);
*/
}

static void wplookup_remove_from_conv(PidginConversation *gtkconv){
/*
  GtkTextView *view;

  view = GTK_TEXT_VIEW(gtkconv->imhtml);
  g_signal_handlers_disconnect_matched(G_OBJECT(view),G_SIGNAL_MATCH_FUNC, 0, 0, NULL, G_CALLBACK(wpview_right_click_popup), NULL);
  
  view = GTK_TEXT_VIEW(gtkconv->entry);
  g_signal_handlers_disconnect_matched(G_OBJECT(view),G_SIGNAL_MATCH_FUNC, 0, 0, NULL, G_CALLBACK(wpview_right_click_popup), NULL);
*/
}

//Function is called on loading of the plugin
static gboolean
plugin_load(PurplePlugin *plugin) {
    void *conv_handle;
    GList *convs;
    //WikipediaLookup *wpl;

    //wpl_plugin = PidginPlugin_construct();

    /* TODO: load settings */
    //wpsettings_load_settings();
    //wpl = WikipediaLookup_construct("http://de.wikipedia.org", "Detusch");

    //conv_handle = purple_conversations_get_handle();

    /*Attach to existing conversations */
    /*for (convs = purple_get_conversations(); convs != NULL; convs = convs->next)
    {
        wplookup_attach_conv(wpl, (PurpleConversation *)convs->data);
    }

    purple_signal_connect(conv_handle, "conversation-created",
                          plugin, PURPLE_CALLBACK(wplookup_attach_conv), (gpointer) wpl);
*/
    //wpl_plugin->wplookup_plugin_handle = plugin;

    return TRUE;
}

static gboolean
plugin_unload(PurplePlugin *plugin){
  void *conv_handle;
  GList *convs;

  //PidginPlugin_destruct(wpl_plugin);
  //conv_handle = purple_conversations_get_handle();

  /*save settings */
  //wpsettings_save_settings();

	/* free language */
        /*if(wpl_settings.language != NULL)
                g_free(wpl_settings.language);*/

	/* free wikipedia_search_url */
        /*if(wpl_settings.wikipedia_search_url != NULL)
                g_free(wpl_settings.wikipedia_search_url);*

  /* Delete Labels */
  /*for (convs = purple_get_conversations(); convs != NULL; convs = convs->next)
  {
    PurpleConversation *conv = (PurpleConversation *)convs->data;
    if(PIDGIN_IS_PIDGIN_CONVERSATION(conv)){
      wplookup_remove_from_conv(PIDGIN_CONVERSATION(conv));
    }
  }
*/
  return TRUE;
}

/*static PidginPluginUiInfo settings =
{
        WplPidginSettings_createWindows,
	0, /* page_num (Reserved) */

	/* padding */
/*        NULL,
	NULL,
	NULL,
	NULL
};*/

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
    NULL,    //UI info struct pointer
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
