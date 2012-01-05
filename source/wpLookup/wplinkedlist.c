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
 *  Wikipedia Lookup is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with wplookup.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "wplinkedlist.h"

LinkedList *LinkedList_insertAfter(LinkedList *node, void *data);

LinkedList *LinkedList_construct(void *data)
{
        LinkedList *node;
        if(!(node=malloc(sizeof(LinkedList))))
        {
            return NULL;
        }

        node->data=data;
        node->next=NULL;

        return node;
}

void LinkedList_destruct(LinkedList *o)
{
    LinkedList *current;
    LinkedList *next;
    current = o;

    while(current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

LinkedList *LinkedList_addElement(LinkedList *o, void *data)
{
    LinkedList *last = o;
    while(last->next != NULL)
    {
        last = last->next;
    }
    return LinkedList_insertAfter(last, data);
}

LinkedList *LinkedList_insertAfter(LinkedList *o, void *data)
{
    if(o->data == NULL)
    {
        o->data = data;
        return o;
    }

    LinkedList *newnode;
    newnode=LinkedList_construct(data);
    //newnode->next = o->next;
    o->next = newnode;

    return newnode;
}
