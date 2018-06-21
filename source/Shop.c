#include <switch.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

char* readfile(char *filename)
{
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");
   if (handler)
   {
       fseek(handler, 0, SEEK_END);
       string_size = ftell(handler);
       rewind(handler);
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );
       read_size = fread(buffer, sizeof(char), string_size, handler);
       buffer[string_size] = '\0';
       if (string_size != read_size)
       {
           free(buffer);
           buffer = NULL;
       }
       fclose(handler);
    }

    return buffer;
}

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
    printf("[eXhop:Info] Reading title file (sdmc:/switch/eXhop.txt)\n");
    char *strid = readfile("sdmc:/switch/eXhop.txt");
    u64 id = strtoull(strid, NULL, 16);
    printf("[eXhop:Info] Press A to download the title from this ID: %#" PRIx64 "\n", id);
    while(appletMainLoop())
    {
        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
        hidScanInput();
        int k = hidKeysDown(CONTROLLER_P1_AUTO);
        if(k & KEY_A)
        {
            Result res = nsBeginInstallApplication(id, 0, FsStorageId_SdCard);
            if(R_SUCCEEDED(res))
            {
                printf("[eXhop:Info] Title download started, check it in Home Menu!\n");
            }
            else error("Failure starting title download.");
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