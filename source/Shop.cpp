#include "Includes.h"


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
	printf("%s%s%s", CONSOLE_RED, "Please be aware by using this program you risk a ban", CONSOLE_RESET);
    printf("\n");
    printf("[eXhop:Info] Reading title file (sdmc:/switch/eXhop.txt)\n");
    printf("[eXhop:Info] Press A to download the title from exhop.txt to the SD.\n");
    printf("[eXhop:Info] Press B to download the title from exhop.txt to NAND.\n");
    while(appletMainLoop())
    {
        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
        hidScanInput();
        int k = hidKeysDown(CONTROLLER_P1_AUTO);
        if(k & KEY_A)
        {
			ifstream ifs("sdmc:/switch/eXhop.txt");
			if(ifs.good())
			{
				string buf;
				while(getline(ifs, buf))
				{
					buf.pop_back();
					u64 id = strtoull(buf.c_str(), NULL, 16);
					nsBeginInstallApplication(id, 0, FsStorageId_SdCard);
					printf("started downloading %s", id);
				}
			}
			ifs.close();
			printf("%s%s%s", CONSOLE_GREEN, "Complete, feel free to exit to the home menu.", CONSOLE_RESET);
        }
		if(k & KEY_B)
        {
			ifstream ifs("sdmc:/switch/eXhop.txt");
			if(ifs.good())
			{
				string buf;
				while(getline(ifs, buf))
				{
					buf.pop_back();
					u64 id = strtoull(buf.c_str(), NULL, 16);
					nsBeginInstallApplication(id, 0, FsStorageId_NandUser);
					printf("started downloading %s", id);
				}
			}
			ifs.close();
			printf("%s%s%s", CONSOLE_GREEN, "Complete, feel free to exit to the home menu.", CONSOLE_RESET);
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
