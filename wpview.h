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

#ifndef WP_VIEW_H
#define WP_VIEW_H

#define WPL_WIKIPEDIA_API_PATH		"%s/w/api.php?action=query&prop=revisions&titles=%s&rvprop=content&rvsection=0&rvparse&format=xml"
#define WPL_USER_AGENT				"Mozilla/4.0"

#include <string.h>
#include <gtk/gtk.h>
#include <pidgin.h>
#include <curl/curl.h>
#include <webkit/webkit.h>
#include <stdio.h>

#include "wpsettings.h"
#include "wputility.h"

extern struct settings wpl_settings;
extern PurplePlugin *wplookup_plugin_handle;

//void wpview_open_preview_window(GtkWidget *parent);
void wpview_right_click_popup(GtkTextView *text_view, GtkMenu *menu);

#endif