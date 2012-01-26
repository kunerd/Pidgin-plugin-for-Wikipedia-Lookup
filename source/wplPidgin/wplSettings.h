/*
 *  Wikipedia Lookup - A third-party Pidgin plug-in which offers
 *  you the possibility to look up received and typed words on Wikipedia.
 *
 *  Copyright (C) 2011, 2012 Hendrik Kunert kunerd@users.sourceforge.net
 *
 *  This file is part of Wikipedia Lookup.
 *
 *  Wikipedia Lookup is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Wikipedia Lookup is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Wikipedia Lookup.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef WPL_PIDGIN_SETTINGS_H
#define WPL_PIDGIN_SETTINGS_H

#include <gtk/gtk.h>
#include <gtkutils.h>

#include "wpxml.h"
#include "wplookup.h"

/** Struct for all plug-in settings.
  */
typedef struct
{
    WikipediaLookup *wpl;
}WplPidginSettings;

enum
{
        COL_NAME = 0,
        COL_URL,
        NUM_COLS
};

WplPidginSettings *WplPidginSettings_construct();
void WplPidginSettings_destruct(WplPidginSettings *o);

GtkWidget *WplPidginSettings_createViewAndModel(WplPidginSettings *o);

void WplPidginSettings_loadFromFile(WplPidginSettings *o);
void WplPidginSettings_saveToFile(WplPidginSettings *o);


#endif
