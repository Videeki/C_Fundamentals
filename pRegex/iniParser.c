#include "iniParser.h"
#include "pRegex.h"

// A main function to test the above functions
int main(int argc, char* argv[])
{
  printf("Iniparser version %d.%d.%d\n", INIPARSER_VERSION_MAJOR, INIPARSER_VERSION_MINOR, INIPARSER_VERSION_FIX);
  // Check if there are enough arguments
  //if (argc < 4) {
  //  printf("Usage: %s filename key value\n", argv[0]);
  //  return -1;
  //}

  config PRI;
  //section PRI;
  //char* configStr = "[Default]\r\nFolder=C:\\Users\\Videeki\\Music\\Vegyes\r\nTheme=Fire.ui\r\nAddButton=23";
  // Get the filename, key and value from the arguments
  char *filename = argv[1];
  char *key = argv[2];
  char *value = argv[3];

  char* configStr = openConfig(filename);
  printf("Main: %s\n", configStr);
  parseConfig(configStr, &PRI);
  closeConfig(configStr);

  printf("Main Key: %s\n", PRI.sections[0].keyvalue[4].key);
  printf("Main Value: %s\n", PRI.sections[0].keyvalue[4].value);

  return 0;
}

char* openConfig(char* iniPath)
{
    puts("OpenConfig start...");
    FILE *fp;
    long size;

    fp = fopen(iniPath, "rb"); // read mode

    if (fp == NULL) {
        perror("Error while opening the file.\n");
        return -1;
    }

    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    char* configStr = calloc(size + 1, sizeof(char));

    if (configStr == NULL) {
        fclose(fp);
        perror("Memory allocation failed.\n");
        return -2;
    }

    fread(configStr, size, 1, fp);
    fclose(fp);
    puts(configStr);
    puts("OpenConfig end...");
    return configStr;
}

int parseConfig(char* configStr, config* parsedConfig)
{
  puts("Parse Config start...");
  int i = 0;
  int j = 0;
  int found = 0;
  char shiftRegister[strlen(configStr)];

  strcpy(shiftRegister, configStr);
  do
  {
    char before[255] = "";
    char match[255] = "";
    char after[255] = "";
    found = matchPattern(shiftRegister, "\r\n", before, match, after);
    
    char key[255] = "";
    char value[255] = "";
    
    if(before[0] == '[')
    {
      strcpy(parsedConfig->sections[0].sectionName, before);
      i++;
    }
    else
    {
      if(0 == matchPattern(before, "=", key, match, value))
      {
        strcpy(parsedConfig->sections[0].keyvalue[j].key, key);
        
        strcpy(parsedConfig->sections[0].keyvalue[j].value, value);
        j++;
      }
    }
    strcpy(shiftRegister, after);
    i++;
  
  }while(strlen(shiftRegister));

  puts("Parse Config end...");

  return 0;
}

int writeConfig(char* iniPath, config* parsedConfig)
{
  return 0;
}

int closeConfig(char* configStr)
{
  puts("Close Config start...");
  free(configStr);
  puts("Close Config end...");
  return 0;
}


char* readKey(config* parsedConfig, char* section, char* key)
{
  return "readKey is not implemented yet";
}

int writeKey(config* parsedConfig, char* section, char* key, char* value)
{
  return 0;
}

char** getSectionNames(config* parseConfig)
{
  char* sectionNames[1] = {"getSectionNames is not implemented yet"};
  return sectionNames;
}
char** getKeyNames(config* parseConfig, char* section)
{
  char* keyNames[1] = {"getKeyNames is not implemented yet"};
  return keyNames;
}