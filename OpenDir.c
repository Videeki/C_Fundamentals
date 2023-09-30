#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#endif

int main (int argc, char *argv[]) {
    #ifdef _WIN32
        WIN32_FIND_DATA fdFile;
        HANDLE hFind = NULL;

        char sPath[2048];

        //Specify a file mask. *.* = We want everything!
        sprintf(sPath, "%s\\*%s", argv[1], argv[2]);

        if((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
        {
            printf("Path not found: [%s]\n", argv[1]);
            return -1;
        }

        do
        {
            //Find first file will always return "."
            //    and ".." as the first two directories.
            if(strcmp(fdFile.cFileName, ".") != 0 && strcmp(fdFile.cFileName, "..") != 0)
            {
                //Build up our file path using the passed in
                //  [sDir] and the file/foldername we just found:
                sprintf(sPath, "%s\\%s", argv[1], fdFile.cFileName);

                //Is the entity a File or Folder?
                if(fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
                {
                    printf("Directory: %s\n", sPath);
                    ListDirectoryContents(sPath); //Recursion, I love it!
                }
                else{
                    printf("File: %s\n", sPath);
                }
            }
        }
        while(FindNextFile(hFind, &fdFile)); //Find the next file.

        FindClose(hFind); //Always, Always, clean things up!

    #elif __linux__
        struct dirent *pDirent;
        DIR *pDir;

        // Ensure correct argument count.

        if (argc != 3) {
            printf ("Usage: testprog <dirname>\n");
            return 1;
        }

        // Ensure we can open directory.

        pDir = opendir (argv[1]);
        if (pDir == NULL) {
            printf ("Cannot open directory '%s'\n", argv[1]);
            return 1;
        }

        // Process each entry.
        while ((pDirent = readdir(pDir)) != NULL) {
            if(strstr(pDirent->d_name, argv[2]))
            {
                printf ("%s\n", pDirent->d_name);
            }
        }

        // Close directory and exit.
        closedir (pDir);

    #else
        printf("Sorry, the system are not implemented yet... :'(\n");

    #endif

    return 0;
}
