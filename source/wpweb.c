
#include "wpweb.h"

void wpweb_get_webpage(gchar *url, void *chunk)
{
	CURL *curl_handle=NULL;

	curl_global_init(CURL_GLOBAL_ALL);

	/* init the curl session */
	curl_handle = curl_easy_init();

	/* specify URL to get */
	curl_easy_setopt(curl_handle, CURLOPT_URL, url);

	/* send all data to this function  */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, wplanguage_write_memory_callback);

	/* we pass our 'chunk' struct to the callback function */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, chunk);

	/* some servers don't like requests that are made without a user-agent field, so we provide one */
	curl_easy_setopt (curl_handle, CURLOPT_USERAGENT, WPL_USER_AGENT);

	/* get it! */
	curl_easy_perform(curl_handle);

	/* cleanup curl stuff */
	curl_easy_cleanup(curl_handle);

	/* we're done with libcurl, so clean it up */
	curl_global_cleanup();
}
