#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

FILE* LOG_FILE = NULL; // Убираем инициализацию здесь

const char* EXTENSION = ".log";

void CloseLogFile()
{
    if (LOG_FILE != NULL) {
        fprintf(LOG_FILE, "ЗАКРЫТ ФАЙЛ\n");
        fprintf(LOG_FILE, "\\----------------------------------------------------\\\n");
        fclose(LOG_FILE);
    }
}

void OpenLogFile(const char* FILE_NAME)
{
    char* file_name = strdup(FILE_NAME);

    LOG_FILE = fopen(file_name, "w");

    if (LOG_FILE == NULL)
    {
        LOG_FILE = stderr;
    }

    if (LOG_FILE != NULL) {
        fprintf(LOG_FILE, "\\----------------------------------------------------\\\n");
        fprintf(LOG_FILE, "ОТКРЫТ ФАЙЛ\n");
        atexit(CloseLogFile);
    }
}
