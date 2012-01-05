#ifndef WPLOOKUP_WPARTICLE_H
#define WPLOOKUP_WPARTICLE_H

#include <gtk/gtk.h>
#include <stdlib.h>

typedef struct
{
    gchar *name;
    gchar *content;
} WikipediaArticle;

WikipediaArticle *WikipediaArticle_construct(void);

void WikipediaArticle_destruct(WikipediaArticle *o);

#endif
