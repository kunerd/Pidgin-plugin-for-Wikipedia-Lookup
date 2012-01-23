#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "wplSettings.h"

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

void testLOADSETTINGS(void)
{
    WplPidginSettings *settings;

    settings = WplPidginSettings_construct();
    WplPidginSettings_loadFromFile(settings);

    CU_ASSERT(0 == g_strcmp0((gchar*)"Deutsch", settings->wpl->language));
    CU_ASSERT(0 == g_strcmp0((gchar*)"http://de.wikipedia.org", settings->wpl->url));  

    WplPidginSettings_destruct(settings);
}

void testSAVESETTINGS(void)
{
    WplPidginSettings *settings;

    settings = WplPidginSettings_construct();

    settings->wpl->language = g_strdup_printf("English");
    settings->wpl->url = g_strdup_printf("http://en.wikipedia.org");

    WplPidginSettings_saveToFile(settings);

    g_free(settings->wpl->language);
    g_free(settings->wpl->url);

    WplPidginSettings_loadFromFile(settings);

    CU_ASSERT(0 == g_strcmp0((gchar*)"English", settings->wpl->language));
    CU_ASSERT(0 == g_strcmp0((gchar*)"http://en.wikipedia.org", settings->wpl->url));

    g_free(settings->wpl->language);
    g_free(settings->wpl->url);

    settings->wpl->language = g_strdup_printf("Deutsch");
    settings->wpl->url = g_strdup_printf("http://de.wikipedia.org");

    WplPidginSettings_saveToFile(settings);

    WplPidginSettings_destruct(settings);
}

void testCreateViewAndModel()
{
    GtkWidget *viewAndModel = NULL;
    WplPidginSettings *settings = NULL;

    settings = WplPidginSettings_construct();
    WplPidginSettings_loadFromFile(settings);

    viewAndModel = WplPidginSettings_createViewAndModel(settings);

    CU_ASSERT(NULL != viewAndModel);

    WplPidginSettings_destruct(settings);
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main( int   argc,
         char *argv[] )
{
   gtk_init (&argc, &argv);

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
   if ((NULL == CU_add_test(pSuite, "test load settings", testLOADSETTINGS)) ||
      ((NULL == CU_add_test(pSuite, "test save settings", testSAVESETTINGS)) ||
      ((NULL == CU_add_test(pSuite, "test create view and model", testCreateViewAndModel)))))
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


