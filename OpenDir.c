#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main (int argc, char *argv[]) {
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
    return 0;
}