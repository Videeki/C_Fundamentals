#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// Checking for windows OS with
// _WIN32 macro
#ifdef _WIN32
    #include <windows.h>

// Checking for mac OS with
// __APPLE__ macro
#elif __APPLE__

// Checking for linux OS with
// __linux__ macro
#elif __linux__
	#include <fcntl.h>
    #include <termios.h>
    #include <dirent.h>

#else
    perror("Unsupported OS\n");

#endif

int main()
{
#ifdef _WIN32    
    HKEY hKey;
    char keyName[1024];
    DWORD keySize = sizeof(keyName);
    char keyValue[1024];
    DWORD valueSize = sizeof(keyValue);
    int i = 0;

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        while (RegEnumValue(hKey, i++, keyName, &keySize, NULL, NULL, (LPBYTE)keyValue, &valueSize) == ERROR_SUCCESS)
        {
            printf("%s\n", keyValue);
            keySize = sizeof(keyName);
            valueSize = sizeof(keyValue);
        }
        RegCloseKey(hKey);
    }
    return 0;
    
#elif __linux__
    DIR *dir;
    struct dirent *entry;
    char *dev_dir = "/dev";
    char *port_prefix = "ttyS";
    char portname[20];

    dir = opendir(dev_dir);
    if (dir == NULL)
    {
        printf("Error opening %s\n", dev_dir);
        return -1;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strstr(entry->d_name, port_prefix) != NULL)
        {
            sprintf(portname, "%s/%s", dev_dir, entry->d_name);
            printf("%s\n", portname);
        }
    }

    closedir(dir);
    
    //system("ls -l /sys/class/tty/*/device/driver | grep -v \"platform/drivers/serial8250\" | awk '{print $9}' | awk -F'/' '{print \"/dev/\" $5}'");
        
    return 0;

#else
    perror("Unsupported OS\n");
#endif

}