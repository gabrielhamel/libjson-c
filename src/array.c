#include <stdlib.h>
#include <string.h>

#include "internal.h"

JsonAny* json_array_create()
{
    JsonArray* object = malloc(sizeof(JsonArray));
    object->type = JsonTypeArray;
    LIST_INIT(&object->entries);
    return (JsonAny*)object;
}

char *json_array_serialize(const JsonArray* object)
{
    char* result = strdup("[");

    struct JsonArrayEntry* it;
    LIST_FOREACH(it, &object->entries, entries) {
        string_concat(&result, json_serialize(it->value));
        if (it->entries.le_next != NULL) {
            string_concat(&result, strdup(","));
        }
    }

    string_concat(&result, strdup("]"));
    return result;
}

void json_array_delete(JsonArray* object)
{
    struct JsonArrayEntry* it;
    struct JsonArrayEntry* it_tmp;
    LIST_FOREACH_SAFE(it, &object->entries, entries, it_tmp) {
        json_delete(it->value);
        free(it);
    }
}

void json_array_push(JsonArray* array, const JsonAny* object)
{
    struct JsonArrayEntry* entry = malloc(sizeof(struct JsonArrayEntry));

    entry->value = json_clone(object);
    entry->entries.le_prev = NULL;
    entry->entries.le_next = NULL;

    if (LIST_EMPTY(&array->entries)) {
        LIST_INSERT_HEAD(&array->entries, entry, entries);
    } else {
        struct JsonArrayEntry* it = array->entries.lh_first;
        for (; it->entries.le_next != NULL; it = it->entries.le_next);
        LIST_INSERT_AFTER(it, entry, entries);
    }
}

JsonAny* json_array_clone(const JsonArray* source)
{
    JsonArray* dest = &json_array_create()->array;

    struct JsonArrayEntry* it;
    LIST_FOREACH(it, &source->entries, entries) {
        json_array_push(dest, it->value);
    }

    return (JsonAny*)dest;
}