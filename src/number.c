#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "internal.h"

JsonAny* json_number_create(double value)
{
    JsonNumber* object = malloc(sizeof(JsonNumber));
    object->type = JsonTypeNumber;
    object->value = value;
    return (JsonAny*)object;
}

char *json_number_serialize(const JsonNumber* object)
{
    char *buffer = NULL;

    asprintf(&buffer, "%f", object->value);

    // Replace trailing zero
    for (size_t idx = strlen(buffer) - 1; idx > 0; idx--) {
        if (buffer[idx] == '0' || buffer[idx] == '.') {
            buffer[idx] = '\0';
        } else {
            break;
        }
    }

    return buffer;
}

void json_number_delete(JsonNumber* object)
{
    free(object);
}

JsonAny* json_number_clone(const JsonNumber* source)
{
    return json_number_create(source->value);
}