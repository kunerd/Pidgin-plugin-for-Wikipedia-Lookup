#ifndef WPLOOKUP_WPARTICLE_H
#define WPLOOKUP_WPARTICLE_H

#include <gtk/gtk.h>
#include <stdlib.h>

#include "wplookup.h"

typedef struct
{
    gchar *name;
    gchar *content;
    WikipediaLookup *wpl;
} WikipediaArticle;

WikipediaArticle *WikipediaArticle_construct(WikipediaLookup *wpl);

void WikipediaArticle_load(WikipediaArticle *o, gchar *search);

void WikipediaArticle_destruct(WikipediaArticle *o);

#endif
