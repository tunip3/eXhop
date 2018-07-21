#include <switch.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>


void error(const char *error)
{
    printf("[eXhop:Error] %s", error);
    while(appletMainLoop())
    {
        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
    }
}

int main()
{
    gfxInitDefault();
    nsInitialize();
    fsInitialize();
    consoleInit(NULL);
    printf("\n");
    while(appletMainLoop())
    {
        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
        hidScanInput();
        int k = hidKeysDown(CONTROLLER_P1_AUTO);
        if(k & KEY_A)
        {
			CURL *curl;
			curl = curl_easy_init();
			if(curl) {
			  CURLcode res;
			  curl_easy_setopt(curl, CURLOPT_URL, "https://tunip3.github.io/eNXhop.txt");
			  curl_easy_perform(curl);
              res = curl_easy_perform(curl);
              if (res != CURLE_OK) {
              printf("! Failed to get latest app version: %s\n", curl_easy_strerror(res));
              }
			  curl_easy_cleanup(curl);
			}
        }
    }
    while(appletMainLoop())
    {
        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
    }
    nsExit();
    fsExit();
    gfxExit();
}