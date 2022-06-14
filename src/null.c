#include <stdlib.h>
#include <string.h>

#include "internal.h"

JsonAny* json_null_create()
{
    JsonNull* object = malloc(sizeof(JsonNull));
    object->type = JsonTypeNull;
    return (JsonAny*)object;
}

char *json_null_serialize(const JsonNull* object)
{
    return strdup("null");
}

void json_null_delete(JsonNull* object)
{
    free(object);
}

JsonAny* json_null_clone(const JsonNull* source)
{
    (void)source;
    return json_null_create();
}