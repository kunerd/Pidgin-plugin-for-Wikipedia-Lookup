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

#define WPL_WIKIPEDIA_API_PATH		"%s/w/api.php?action=parse&page=%s&section=0&format=xml&redirects"
#define WPL_WIKIPEDIA_PATH 			"/wiki/"
#define WPL_USER_AGENT				"Mozilla/4.0"
#define WPL_PAGE_TEMPLATE "<html><head><title>preview</title></head><body class=\"mediawiki ltr capitalize-all-nouns ns-0 ns-subject page-Test skin-vector\"><div id=\"content\"><h1 id=\"firstHeading\" class=\"firstHeading\">%s</h1><div id=\"bodyContent\">%s<div style=\"clear:both\"></div></div></div></body></html>"

#include <string.h>
#include <gtk/gtk.h>
#include <pidgin.h>
#include <purple.h>
#include <curl/curl.h>
#include <webkit/webkit.h>
#include <stdio.h>

#include "wpsettings.h"
#include "wputility.h"

extern struct settings wpl_settings;
//extern PurplePlugin *wplookup_plugin_handle;

void wpview_right_click_popup(GtkTextView *text_view, GtkMenu *menu);

#endif
