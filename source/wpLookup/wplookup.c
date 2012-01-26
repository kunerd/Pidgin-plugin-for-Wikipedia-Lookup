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

#include <libxml/xpath.h>

#include "wplookup.h"
#include "wpopensearch.h"
#include "wpxml.h"

WikipediaLookup *WikipediaLookup_construct(gchar *url, gchar *language)
{
    WikipediaLookup *o;
    if(!(o=malloc(sizeof(WikipediaLookup))))
    {
        return NULL;
    }
    o->url = url;
    o->language = language;
    o->opensearchLimit = 10;
    o->opensearchCallback = NULL;

    return o;
}

void WikipediaLookup_destruct(WikipediaLookup *o)
{
    if(o != NULL)
    {
        g_free(o->language);
        g_free(o->url);
        free(o);
    }
}

/** Get's all Wikipedia URLs, for all existing Wikipedias.
  *
  * @return GList with WikipediaLookup structures of all Wikipedias out there.
  * @see WikipediaLookup
  */
GList *WikipediaLookup_getLanguages(void)
{
    GList *languageList = NULL;
    WikipediaXml *xml = NULL;
    xmlXPathObjectPtr result = NULL;
    int index;
    gchar *name;
    gchar *url;

    WikipediaLookup *wpl;

    xml = WikipediaXml_construct();
    // TODO: remove static local url here
    WikipediaXml_loadUrl(xml, "http://de.wikipedia.org/w/api.php?action=sitematrix&format=xml");

    result = WikipediaXml_getNodeset(xml, "/api/sitematrix/language | /api/sitematrix/language/site/site[@code=\"wiki\"]/@url");

    for(index = 0; index < result->nodesetval->nodeNr-1; index++)
    {
        name = (gchar*)xmlGetProp(result->nodesetval->nodeTab[index], (const xmlChar*)"name");
        if(name != NULL)
        {
            url = (gchar*)xmlNodeListGetString(xml->doc, result->nodesetval->nodeTab[index+1]->xmlChildrenNode, 1);
            if(url != NULL)
            {
                wpl = WikipediaLookup_construct(url,name);
                languageList = g_list_append(languageList, (gpointer) wpl);
            }
            else{
                g_free(name);
            }
        }
    }
    xmlXPathFreeObject (result);
    WikipediaXml_destruct(xml);
    return languageList;
}

static gchar *WikipediaLookup_getClickedWord(GtkTextView *text_view)
{
    int x = 0;
    int y = 0;
    int x1 ;
    int y1 ;
    GtkTextIter iter ;
    GtkTextIter startiter;
    GtkTextIter enditer;
    GtkTextBuffer *textBuffer = NULL;

    if(text_view == NULL)
    {
        return NULL;
    }
    gtk_widget_get_pointer(GTK_WIDGET(text_view), &x, &y);

    gtk_text_view_window_to_buffer_coords(GTK_TEXT_VIEW(text_view), GTK_TEXT_WINDOW_WIDGET,
                                          x , y , &x1 , &y1 );

    gtk_text_view_get_iter_at_location (GTK_TEXT_VIEW(text_view), &iter , x1 , y1 ) ;

    startiter = iter;
    enditer = iter;

    if ( gtk_text_iter_starts_word ( &iter ) )
    {
        gtk_text_iter_forward_word_end ( &enditer ) ;
    }
    else if ( gtk_text_iter_inside_word ( &iter ) )
    {
        gtk_text_iter_forward_word_end ( &enditer ) ;
        gtk_text_iter_backward_word_start ( &startiter ) ;
    }
    else if ( gtk_text_iter_ends_word ( &iter ) )
    {
        gtk_text_iter_backward_word_start ( &startiter ) ;
    }
    else
    {
        return NULL;
    }

    textBuffer = gtk_text_view_get_buffer(text_view);
    if(textBuffer == NULL)
    {
        return NULL;
    }

    return gtk_text_buffer_get_text ( textBuffer , &startiter , &enditer, FALSE);
}

void WikipediaLookup_rightClickPopup(GtkTextView *text_view, GtkMenu *menu, WikipediaLookup *o)
{
    gchar * word;
    OpenSearch *os;
    GList *iterator;
    OpenSearchItem *item;
    GtkWidget *menu_entry = NULL;
    GtkWidget *parent = NULL;

    if(o->opensearchCallback == NULL)
    {
        return;
    }

    word = WikipediaLookup_getClickedWord(text_view);

    if(word == NULL)
    {
        return;
    }

    os = OpenSearch_construct(o);
    OpenSearch_search(os, word);

    for(iterator = os->list; iterator != NULL; iterator = g_list_next(iterator))
    {
        item = (OpenSearchItem *)iterator->data;
        menu_entry = gtk_menu_item_new_with_label(item->text);
        gtk_widget_set_tooltip_text(menu_entry, item->description);

        gtk_menu_append(GTK_MENU(menu),menu_entry);

        parent = gtk_widget_get_toplevel (GTK_WIDGET(text_view));

        g_signal_connect(G_OBJECT(menu_entry), "activate", G_CALLBACK(o->opensearchCallback), (gpointer) g_strdup(item->url));
        gtk_widget_show(menu_entry);
    }

    g_free(word);
    OpenSearch_destruct(os);
}

