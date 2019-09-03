#include <config.h>

configParams* getConfigVariables() {
    
    configParams* params = malloc(sizeof(configParams));
    params->port = malloc(256);
    params->dirColors = malloc(256);
    params->dirHisto = malloc(256);
    params->dirLog = malloc(256);

    FILE *file = fopen(CONFIG_FILE, "r");
    char line[256];
    char *initialPos, *finalPos; //to values substrings

    fgets(line, sizeof(line), file);

    initialPos = strchr(line, (int)':') + 2;
    finalPos = strchr(line, 0) - 1;
    strncpy(params->port, initialPos, finalPos - initialPos);
    
    fgets(line, sizeof(line), file);
    initialPos = strchr(line, (int)':') + 2;
    finalPos = strchr(line, 0) - 1;
    strncpy(params->dirColors, initialPos, finalPos - initialPos);

    fgets(line, sizeof(line), file);
    initialPos = strchr(line, (int)':') + 2;
    finalPos = strchr(line, 0) - 1;
    strncpy(params->dirHisto, initialPos, finalPos - initialPos);

    fgets(line, sizeof(line), file);
    initialPos = strchr(line, (int)':') + 2;
    finalPos = strchr(line, 0) - 1;
    strncpy(params->dirLog, initialPos, finalPos - initialPos);
       
    fclose(file);
    return params;
}