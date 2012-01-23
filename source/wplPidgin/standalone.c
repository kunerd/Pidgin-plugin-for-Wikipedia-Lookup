/*
 * main-window.c
 *
 *  Created on: 31.05.2011
 *      Author: hendrik
 */

#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include "wplookup.h"
#include "wplSettings.h"

/* Another callback */
static void destroy( GtkWidget *widget,
                    gpointer   data )
{
    gtk_main_quit ();
}

void enter_button(GtkWidget *widget, gpointer data)
{
  GdkColor color;
  color.red = 27000;
  color.green = 30325;
  color.blue = 34181;
  gtk_widget_modify_bg(widget, GTK_STATE_PRELIGHT, &color);
}

void opensearchMenuCallback(GtkMenuItem *menuitem,
                            gchar*     url)
{
    g_print(" --- \nURL: %s\n ---", url);
    g_free(url);
}

int main( int   argc,
         char *argv[] )
{
    /* GtkWidget is the storage type for widgets */
    GtkWidget *window, *text_view, *vbox, *show;
    GtkTextTag *tag;
    GtkTextBuffer *buffer;
    GtkTextIter start, end;

    WplPidginSettings *settings = NULL;

    settings = WplPidginSettings_construct();
    WplPidginSettings_loadFromFile(settings);
    settings->wpl->opensearchCallback = G_CALLBACK(opensearchMenuCallback);

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
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 200);


    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_container_set_border_width(GTK_CONTAINER(vbox), 4);
    gtk_widget_show(vbox);


    text_view = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(vbox), text_view, TRUE, TRUE, 0);
    gtk_widget_set_has_tooltip ( text_view , true ) ;

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    /*g_signal_connect( G_OBJECT (text_view) , "query-tooltip" ,
                     G_CALLBACK (querytooltipcb) , (gpointer)settings->wpl) ;*/

    g_signal_connect(G_OBJECT(text_view), "enter",
          G_CALLBACK(enter_button), NULL);


    gtk_text_buffer_set_text(buffer, "Hallo Tooltip! Rory Gallagher.", -1);

    tag = gtk_text_buffer_create_tag (buffer, "blue_foreground",
                                      "foreground", "blue", NULL);

    gtk_text_buffer_get_iter_at_offset (buffer, &start, 7);
    gtk_text_buffer_get_iter_at_offset (buffer, &end, 13);

    //mark = gtk_text_buffer_create_mark(buffer,"tooltip",,TRUE);
    gtk_text_buffer_apply_tag (buffer, tag, &start, &end);
    //gtk_widget_set_tooltip_text(GTK_WIDGET(tag), "Word Tooltip");

    gtk_text_view_set_editable (GTK_TEXT_VIEW(text_view), TRUE);


    show = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(show), FALSE);
    gtk_widget_show_all(show);

    g_signal_connect(G_OBJECT(text_view), "populate-popup", G_CALLBACK(WikipediaLookup_rightClickPopup), (gpointer)settings->wpl);

    gtk_widget_show_all(window);
    /* All GTK applications must have a gtk_main(). Control ends here
     * and waits for an event to occur (like a key press or
     * mouse event). */
    gtk_main ();

    WplPidginSettings_saveToFile(settings);
    WplPidginSettings_destruct(settings);

    return 0;
}
