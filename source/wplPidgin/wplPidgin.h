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

#ifndef WPL_PIDGIN_H
#define WPL_PIDGIN_H

#define WPL_PIDGIN_PLUGIN_ID "gtk-hendrik_kunert-wikipedia-lookup"
#define PURPLE_PLUGINS

#include <pidgin.h>
#include <libpurple/version.h>
#include <pidgin/gtkplugin.h>

//#include "wplPreview.h"
#include "wplSettings.h"

typedef struct {
    WplPidginSettings *settings;
    PurplePlugin *wplookup_plugin_handle;
} WplPidginPlugin;

WplPidginPlugin *WplPidginPlugin_construct(void);
void WplPidginPlugin_destruct(WplPidginPlugin *o);

#endif
