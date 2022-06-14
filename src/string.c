#include <stdlib.h>
#include <string.h>

#include "internal.h"

JsonAny* json_string_create(const char* value)
{
    JsonString* object = malloc(sizeof(JsonString));
    object->type = JsonTypeString;
    object->value = strdup(value);
    return (JsonAny*)object;
}

void json_string_delete(JsonString* object)
{
    free(object->value);
    free(object);
}

char* json_string_serialize(const JsonString* object)
{
    char* escaped_string = string_escape(object->value);
    size_t len = strlen(escaped_string);

    char* result = malloc(sizeof(char) * (len + 2 + 1));
    memset(result, '\0', len + 2 + 1);

    result[0] = '"';

    strcat(result + 1, escaped_string);
    free(escaped_string);

    result[len + 1] = '"';
    result[len + 2] = '\0';

    return result;
}

JsonAny* json_string_clone(const JsonString* source)
{
    return json_string_create(source->value);
}