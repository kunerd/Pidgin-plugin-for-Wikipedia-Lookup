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

#include "wplPreview.h"

WplPidginPreview *WplPidginPreview_construct()
{
    WplPidginPreview *o;
    if(!(o=malloc(sizeof(WplPidginPreview))))
    {
        return NULL;
    }

    o->parent_window = NULL;
    o->article = NULL;

    return o;
}

void WplPidginPreview_destruct(WplPidginPreview *o)
{
    if(o != NULL)
    {
        WikipediaArticle_destruct(o->article);
        free(o);
    }
}

void WplPidginPreview_openWindow(WplPidginPreview *o)
{
    GtkWidget *win, *dialog, *content_area, *web_view;
    gchar *webpage = NULL;

    /* Create the widgets */
    dialog = gtk_dialog_new_with_buttons ("preview",
                                          GTK_WINDOW(o->parent_window),
                                          GTK_DIALOG_DESTROY_WITH_PARENT,
                                          "open in browser",
                                          GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OK,
                                          GTK_RESPONSE_NONE,
                                          NULL);

    gtk_window_set_default_size (GTK_WINDOW(dialog), 500, 250);

    content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

    win = gtk_scrolled_window_new(0, 0);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(win),
                                        GTK_SHADOW_IN);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(win),
                                   GTK_POLICY_NEVER,
                                   GTK_POLICY_ALWAYS);

    /* for GtkWebkit */
    web_view = webkit_web_view_new ();
    gtk_container_add (GTK_CONTAINER (win), web_view);
    g_signal_connect_swapped (dialog,
                              "response",
                              G_CALLBACK (gtk_widget_destroy),
                              dialog);

    gtk_container_add (GTK_CONTAINER (content_area), win);

    WikipediaArticle_load(o->article, o->search_text);

    gtk_widget_show_all (dialog);

    if(o->article->content != NULL)
    {
        webkit_web_view_load_string (WEBKIT_WEB_VIEW (web_view),
                                     o->article->content,
                                     "text/html",
                                     "UTF-8",
                                     o->article->url);
        g_free(webpage);
    }

    WplPidginPreview_destruct(o);
}

void WplPidginPreview_rightClickPopup(GtkTextView *text_view, GtkMenu *menu, WikipediaLookup *wpl)
{
    GtkTextBuffer *buffer = NULL;
    GtkWidget *menu_entry = NULL;
    gchar *search_text = NULL;
    GtkTextIter start_selection;
    GtkTextIter end_selection;
    GtkWidget *parent = NULL;
    WplPidginPreview *preview = NULL;

    buffer = gtk_text_view_get_buffer(text_view);

    /* somthing selected? */
    if(gtk_text_buffer_get_selection_bounds(buffer, &start_selection, &end_selection))
    {
        /* get selected text */
        search_text = (gchar*)gtk_text_buffer_get_text(buffer, &start_selection, &end_selection, FALSE);

        /* add menu entry to popup menuy */
        menu_entry = gtk_menu_item_new_with_label("Wikipedia");
        gtk_menu_append(GTK_MENU(menu),menu_entry);

        /* Attach the callback functions to the activate signal */
        //g_signal_connect_swapped( GTK_OBJECT(menu_entry), "activate", GTK_SIGNAL_FUNC(wpview_show_in_browser), (gpointer) search_text);

        preview = WplPidginPreview_construct();
        parent = gtk_widget_get_toplevel (GTK_WIDGET(text_view));
        preview->parent_window = parent;
        preview->search_text = search_text;
        preview->article = WikipediaArticle_construct(wpl);

        if (gtk_widget_is_toplevel (parent))
        {
            g_signal_connect_swapped( GTK_OBJECT(menu_entry), "activate", GTK_SIGNAL_FUNC(WplPidginPreview_openWindow), (gpointer) preview);
            gtk_widget_show(menu_entry);
        }
    }
}
