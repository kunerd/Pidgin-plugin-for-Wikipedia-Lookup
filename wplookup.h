/*
 * Wikipedia Lookup - A third-party Pidgin plug-in which offers 
 *					  you the possibility to look up received and
 *					  typed words on Wikipedia.
 *
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
 
#ifndef _PIDGIN_LATEX_H_
#define _PIDGIN_LATEX_H_
#ifndef G_GNUC_NULL_TERMINATED
#  if __GNUC__ >= 4
#    define G_GNUC_NULL_TERMINATED __attribute__((__sentinel__))
#  else
#    define G_GNUC_NULL_TERMINATED
#  endif /* __GNUC__ >= 4 */
#endif /* G_GNUC_NULL_TERMINATED */

#define PURPLE_PLUGINS

#include <string.h>
#include <libpurple/conversation.h>
#include <libpurple/debug.h>
#include <libpurple/plugin.h>
#include <libpurple/notify.h>
#include <libpurple/version.h>
#include <pidgin/gtkplugin.h>
#include <gtkprefs.h>
#include <gtkutils.h>
#include <gtkconvwin.h>

#ifdef _WIN32
#include <windows.h>
#endif

static void GetActiveConversation(PidginConversation **conv);

static void show_wikipedia(gchar *search_text);

static void menu_popup(GtkTextView *text_view, GtkMenu *menu);

static void wplookup_attach_conv(PurpleConversation *conv);

static void wplookup_remove_from_conv(PidginConversation *gtkconv);

static gboolean
plugin_load(PurplePlugin *plugin);

static gboolean
plugin_unload(PurplePlugin *plugin);

#endif
