#include <stdlib.h>
#include <string.h>

#include "internal.h"

JsonAny* json_boolean_create(bool value)
{
    JsonNumber* object = malloc(sizeof(JsonBoolean));
    object->type = JsonTypeBoolean;
    object->value = value;
    return (JsonAny*)object;
}

char *json_boolean_serialize(const JsonBoolean* object)
{
    return strdup(object->value ? "true" : "false");
}

void json_boolean_delete(JsonBoolean* object)
{
    free(object);
}

JsonAny* json_boolean_clone(const JsonBoolean* source)
{
    return json_boolean_create(source->value);
}