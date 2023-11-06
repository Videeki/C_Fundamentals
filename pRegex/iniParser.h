#ifndef INIPARSER_H
#define INIPARSER_H

#define INIPARSER_VERSION_MAJOR   0
#define INIPARSER_VERSION_MINOR   0
#define INIPARSER_VERSION_FIX     2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>


typedef struct _kvc
{
    char key[255];
    char value[255];
}kvc;

typedef struct _section
{
    char sectionName[255];
    kvc keyvalue[255];
}section;

typedef struct _config
{
    section sections[10];
}config;

int openConfig(char* iniPath, char* configStr);
int parseConfig(char* configStr, config* parsedConfig);
//int parseConfig(char* configStr, section* parsedConfig);
int closeConfig(char* configStr);

#endif /* INIPARSER_H */