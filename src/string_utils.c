#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void string_concat(char** dest, char* source)
{
    char* buffer = NULL;
    asprintf(&buffer, "%s%s", *dest, source);
    free(*dest);
    free(source);
    *dest = buffer;
}

char* string_escape(const char* s1)
{
    // TODO
    return strdup(s1);
}
