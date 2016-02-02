#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>

#include "store_phych.h"

static size_t write_data (void *ptr, size_t size, size_t nmemb, void *stream) {

	size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
	return written;
}
 
int store_phych (void) {

	CURL *curl_handle;
	static const char *pagefilename = PHYCH_SHOT;
	FILE *pagefile;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL);

	/* init the curl session */ 
	curl_handle = curl_easy_init();

	/* specify special port */ 
	curl_easy_setopt(curl_handle, CURLOPT_PORT, PORT);

	/* set URL to get here */ 
	curl_easy_setopt(curl_handle, CURLOPT_URL, PHYCH_URL);

	/* Switch on full protocol/debug output while testing */ 
	//curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);

	/* disable progress meter, set to 0L to enable and disable debug output */ 
	curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

	/* send all data to this function  */ 
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

	/* open the file */ 
	pagefile = fopen(pagefilename, "wb");
	if (pagefile) {

		/* write the page body to this file handle */ 
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);

		/* specify basic authentificaiton 
		   (a creepy plain text fly through my wall) */
		curl_easy_setopt(curl_handle, CURLOPT_HTTPAUTH, (long)CURLAUTH_BASIC);

		/* set user name and password for the authentication */ 
		curl_easy_setopt(curl_handle, CURLOPT_USERPWD, USERPWD); 

		/* get it! */ 
		res = curl_easy_perform(curl_handle);

		/* Check for errors */ 
		if(res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
		      	  curl_easy_strerror(res));
			return 0;
		}

		/* close the header file */ 
		fclose(pagefile);
	}

	/* cleanup curl stuff */ 
	curl_easy_cleanup(curl_handle);

	return 1;
}
