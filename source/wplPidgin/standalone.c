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

#include <gtk/gtk.h>

#include "wplSettings.h"

/* Another callback */
static void destroy( GtkWidget *widget,
                    gpointer   data )
{
    gtk_main_quit ();
}

static void opensearchMenuCallback(GtkMenuItem *menuitem,
                            gchar*     url)
{
    if(url)
    {
        g_print(" --- \nURL: %s\n ---", url);
        //g_print(_("Hello out there!"));
        g_free(url);
    }
}

int main( int   argc,
         char *argv[] )
{
    /* GtkWidget is the storage type for widgets */
    GtkWidget *window, *text_view, *vbox, *vbox1, vbox2, *show, *prefs, *win;
    GtkTextTag *tag;
    GtkTextBuffer *buffer;
    GtkTextIter start, end;

    WplPidginSettings *settings = NULL;

    settings = WplPidginSettings_construct();
    WplPidginSettings_loadFromFile(settings);
    settings->wpl->opensearchCallback = G_CALLBACK(opensearchMenuCallback);

    g_print("---\nsettings: %s, %s,\n---", settings->wpl->url, settings->wpl->language);
    //g_print(_("Here is a translation test."));
    /* This is called in all GTK applications. Arguments are parsed
     * from the command line and are returned to the application. */
    gtk_init (&argc, &argv);

    /* create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /* When the window is given the "delete-event" signal (this is given
     * by the window manager, usually by the "close" option, or on the
     * titlebar), we ask it to call the delete_event () function
     * as defined above. The data passed to the callback
     * function is NULL and is ignored in the callback function. */
    g_signal_connect (window, "delete-event",
		      G_CALLBACK (destroy), NULL);

    /* Here we connect the "destroy" event to a signal handler.
     * This event occurs when we call gtk_widget_destroy() on the window,
     * or if we return FALSE in the "delete-event" callback. */
    g_signal_connect (window, "destroy",
		      G_CALLBACK (destroy), NULL);

    /* Sets the border width of the window. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);


    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_container_set_border_width(GTK_CONTAINER(vbox), 4);
    gtk_widget_show(vbox);


    text_view = gtk_text_view_new();
    //win = gtk_scrolled_window_new(0, 0);
    gtk_box_pack_start(GTK_BOX(vbox), text_view, TRUE, TRUE, 0);
    /*gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(win), GTK_SHADOW_IN);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(win),
                    GTK_POLICY_NEVER,
                    GTK_POLICY_ALWAYS);

    gtk_widget_show(win);

    prefs = WplPidginSettings_createViewAndModel(settings);*/
    gtk_container_add(GTK_CONTAINER(window), text_view);
    //gtk_box_pack_start(GTK_BOX(vbox), text_view, TRUE, TRUE, 0);
    //gtk_widget_set_has_tooltip ( text_view , true ) ;

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    /*g_signal_connect( G_OBJECT (text_view) , "query-tooltip" ,
                     G_CALLBACK (querytooltipcb) , (gpointer)settings->wpl) ;*/


    gtk_text_buffer_set_text(buffer, "Hallo Tooltip! Rory Gallagher.", -1);


    //mark = gtk_text_buffer_create_mark(buffer,"tooltip",,TRUE);
    //gtk_widget_set_tooltip_text(GTK_WIDGET(tag), "Word Tooltip");

    gtk_text_view_set_editable (GTK_TEXT_VIEW(text_view), TRUE);

    //show = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //vbox1 = gtk_vbox_new(FALSE, 0);
    //gtk_container_add(GTK_CONTAINER(vbox), vbox1);
    //gtk_container_set_border_width(GTK_CONTAINER(vbox1), 4);
    //gtk_widget_show(vbox1);

    gtk_widget_show_all(window);

    //gtk_widget_show_all(show);

    g_signal_connect(G_OBJECT(text_view), "populate-popup", G_CALLBACK(WikipediaLookup_rightClickPopup), (gpointer)settings->wpl);

    /* All GTK applications must have a gtk_main(). Control ends here
     * and waits for an event to occur (like a key press or
     * mouse event). */
    gtk_main ();

    //g_signal_handlers_disconnect_matched(G_OBJECT(text_view),G_SIGNAL_MATCH_FUNC, 0, 0, NULL, G_CALLBACK(WikipediaLookup_rightClickPopup), NULL);
    WplPidginSettings_saveToFile(settings);
    WplPidginSettings_destruct(settings);

    return 0;
}
