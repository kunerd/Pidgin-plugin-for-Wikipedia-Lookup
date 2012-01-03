#ifndef WPLOOKUP_WPARTICLE_H
#define WPLOOKUP_WPARTICLE_H

#include <gtk/gtk.h>
#include <stdlib.h>

typedef struct
{
    gchar *name;
    gchar *content;
} WikipediaArticle;

WikipediaArticle *WikipediaArticle_construct(gchar *name, gchar *content);

void WikipediaArticle_destruct(WikipediaArticle *o);

gchar *WikipediaArticle_getUrl(WikipediaArticle *o);

gchar *WikipediaArticle_getLanguage(WikipediaArticle *o);

void WikipediaArticle_setName(WikipediaArticle *o, gchar *name);

void WikipediaArticle_setContent(WikipediaArticle *o, gchar *content);

#endif
