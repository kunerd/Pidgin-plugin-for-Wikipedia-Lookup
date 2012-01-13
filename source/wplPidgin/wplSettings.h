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

#ifndef WPL_PIDGIN_SETTINGS_H
#define WPL_PIDGIN_SETTINGS_H

#include <gtk/gtk.h>
//#include <purple.h>
//#include <pidgin.h>
#include <gtkutils.h>

#include "wplinkedlist.h"
#include "wpxml.h"
#include "wplookup.h"

typedef struct
{
        guchar *language;
        guchar *url;
}WplPidginSettings;

enum
{
        COL_NAME = 0,
        COL_URL,
        NUM_COLS
};

WplPidginSettings *WplPidginSettings_construct();
void WplPidginSettings_destruct(WplPidginSettings *o);

GtkWidget *WplPidginSettings_createWindows(PurplePlugin *plugin);

#endif
