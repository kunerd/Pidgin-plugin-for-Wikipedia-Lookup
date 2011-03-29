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
 *  the Free Software Foundation, either version 2 of the License, or
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

#ifndef WPLOOKUP_H
#define WPLOOKUP_H

#define WPLOOKUP_PLUGIN_ID "gtk-hendrik_kunert-wikipedia-lookup"

#define PURPLE_PLUGINS

#include <glib.h>
#include <glib/gprintf.h>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <libpurple/conversation.h>
#include <libpurple/debug.h>
#include <libpurple/plugin.h>
#include <libpurple/notify.h>
#include <libpurple/version.h>
#include <pidgin/gtkplugin.h>
#include <gtkprefs.h>
#include <gtkutils.h>
#include <gtkconvwin.h>
#include <gtk/gtk.h>

#ifdef _WIN32
#include <windows.h>
#endif

PurplePlugin *wplookup_plugin_handle = NULL;

guchar *wikipedia_search_url = NULL;

//static void GetActiveConversation(PidginConversation **conv);

/*static void show_wikipedia(guchar *search_text);

static void menu_popup(GtkTextView *text_view, GtkMenu *menu);

static void wplookup_attach_conv(PurpleConversation *conv);

static void wplookup_remove_from_conv(PidginConversation *gtkconv);*/

/*static gboolean
plugin_load(PurplePlugin *plugin);

static gboolean
plugin_unload(PurplePlugin *plugin);*/

#endif