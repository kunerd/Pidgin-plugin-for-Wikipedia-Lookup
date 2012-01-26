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

#include <stdio.h>
#include <string.h>

#include "CUnit/Basic.h"
#include "wplookup.h"
#include "wpopensearch.h"
#include "wpxml.h"
#include "wparticle.h"

/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void)
{
   if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
      return -1;
   }
   else {
      return 0;
   }
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
   if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
   }
}

/* Simple test of fprintf().
 * Writes test data to the temporary file and checks
 * whether the expected number of bytes were written.
 */
void testFPRINTF(void)
{
   int i1 = 10;

   if (NULL != temp_file) {
      CU_ASSERT(0 == fprintf(temp_file, ""));
      CU_ASSERT(2 == fprintf(temp_file, "Q\n"));
      CU_ASSERT(7 == fprintf(temp_file, "i1 = %d", i1));
   }
}

/* Simple test of fread().
 * Reads the data previously written by testFPRINTF()
 * and checks whether the expected characters are present.
 * Must be run after testFPRINTF().
 */
void testFREAD(void)
{
   unsigned char buffer[20];

   if (NULL != temp_file) {
      rewind(temp_file);
      CU_ASSERT(9 == fread(buffer, sizeof(unsigned char), 20, temp_file));
      CU_ASSERT(0 == strncmp(buffer, "Q\ni1 = 10", 9));
   }
}

void testWPLOOKUP(void)
{
    WikipediaLookup *wpl;
    int i;

    GList *list, *iterator;
    list = WikipediaLookup_getLanguages();
    printf("  --> wiki-count: %d --> ", g_list_length(list));

    for(iterator = list; iterator != NULL; iterator = g_list_next(iterator))
    {
        wpl = (WikipediaLookup*)(iterator->data);
        //printf("Wiki: %s, URL: %s\n", wpl->language, wpl->url);
        WikipediaLookup_destruct(wpl);
        iterator = iterator->next;
    }
    g_list_free(list);
}

void testWPARTICLE(void)
{
    /*WikipediaLookup *wpl;
    WikipediaArticle *wpa;
    gchar* url = "http://de.wikipedia.org";
    gchar* language = "Deutsch";

    wpl = WikipediaLookup_construct(url, language);
    wpa = WikipediaArticle_construct(wpl);

    WikipediaArticle_load(wpa, "Rory Gallagher");

    CU_ASSERT(NULL != wpa->content);

    WikipediaArticle_destruct(wpa);
    //WikipediaLookup_destruct(wpl);*/
}

void testWPXML(void)
{
    WikipediaXml *xml;
    gchar *text;
    gchar *url;

    xml = WikipediaXml_construct();
    url = g_strdup_printf ("http://de.wikipedia.org/w/api.php?action=opensearch&search=%s&format=xml",
                                     "Rory%20Gallagher");

    WikipediaXml_loadUrl(xml, url);
    text = WikipediaXml_getText(xml, "/os:SearchSuggestion/os:Section/os:Item/os:Text");
    CU_ASSERT(0 == g_strcmp0((gchar*)"Rory Gallagher", text));
    g_free(text);

    text = WikipediaXml_getAttribute(xml, "/os:SearchSuggestion", "version");
    CU_ASSERT(0 == g_strcmp0((gchar*)"2.0", text));
    g_free(text);

    WikipediaXml_destruct(xml);
    g_free(url);
}

void testOPENSEARCH(void)
{
    OpenSearch *os;
    WikipediaLookup *wpl;
    gint length = 0;
    GList *iterator;
    OpenSearchItem *item;
    gchar *url;
    gchar *name;

    url = g_strdup("http://de.wikipedia.org");
    name = g_strdup("Deutsch");

    wpl = WikipediaLookup_construct(url, name);

    os = OpenSearch_construct(wpl);

    length = OpenSearch_search(os, "Rory Gallagher");

    printf("length: %d -> ", length);

    /*for(iterator = os->list; iterator != NULL; iterator = g_list_next(iterator))
    {
        item = (OpenSearchItem *)iterator->data;
        printf("\nName: %s\nDesciption: %s\nUrl %s\n", item->text, item->description, item->url);
    }*/

    CU_ASSERT(2 == length);

    OpenSearch_destruct(os);
    WikipediaLookup_destruct(wpl);
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if ((NULL == CU_add_test(pSuite, "test of fprintf()", testFPRINTF)) ||
       (NULL == CU_add_test(pSuite, "test of fread()", testFREAD)) ||
       (NULL == CU_add_test(pSuite, "test of WikipediaLookup", testWPLOOKUP)) ||
       (NULL == CU_add_test(pSuite, "test WikipediaArticle", testWPARTICLE)) ||
       (NULL == CU_add_test(pSuite, "get text from xml file", testWPXML)) ||
       (NULL == CU_add_test(pSuite, "test Opensearch", testOPENSEARCH)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}


