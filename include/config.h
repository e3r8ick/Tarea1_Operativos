/****************************************
 * Get config variables from file.
 * **************************************/

#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*************************************
 * Config file path
 *************************************/
static const char CONFIG_FILE[] = "config/config.conf";

typedef struct {
    char* port;
    char* dirColors;
    char* dirHisto;
    char* dirLog;
} configParams;

char* substring(char*, int, int);

/************************************************
 * Get configurations variables from config file
 * return:
 *      configParams struct, with all varables
 *      read.
 ************************************************/
configParams* getConfigVariables();

#endif