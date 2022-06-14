#include <stdlib.h>
#include <string.h>

#include "internal.h"

JsonAny* json_object_create()
{
    JsonObject* object = malloc(sizeof(JsonObject));
    object->type = JsonTypeObject;
    LIST_INIT(&object->entries);
    return (JsonAny*)object;
}

void json_object_push(JsonObject* object, const JsonString* key, const JsonAny* value)
{
    struct JsonObjectEntry* entry = malloc(sizeof(struct JsonObjectEntry));

    entry->key = &json_string_clone(key)->string;
    entry->value = json_clone(value);
    entry->entries.le_prev = NULL;
    entry->entries.le_next = NULL;

    if (LIST_EMPTY(&object->entries)) {
        LIST_INSERT_HEAD(&object->entries, entry, entries);
    } else {
        struct JsonObjectEntry* it = object->entries.lh_first;
        do {
            if (!strcmp(it->key->value, key->value)) {
                json_delete(it->value);
                json_string_delete(entry->key);
                it->value = entry->value;
                free(entry);
                return;
            }
            if (it->entries.le_next != NULL) {
                it = it->entries.le_next;
            }
        } while (it->entries.le_next != NULL);
        LIST_INSERT_AFTER(it, entry, entries);
    }
}

char *json_object_serialize(const JsonObject* object)
{
    char* result = strdup("{");

    struct JsonObjectEntry* it;
    LIST_FOREACH(it, &object->entries, entries) {
        string_concat(&result, json_string_serialize(it->key));
        string_concat(&result, strdup(":"));
        string_concat(&result, json_serialize(it->value));
        if (it->entries.le_next != NULL) {
            string_concat(&result, strdup(","));
        }
    }

    string_concat(&result, strdup("}"));
    return result;
}

void json_object_delete(JsonObject* object)
{
    struct JsonObjectEntry* it;
    struct JsonObjectEntry* it_tmp;
    LIST_FOREACH_SAFE(it, &object->entries, entries, it_tmp) {
        json_string_delete(it->key);
        json_delete(it->value);
        free(it);
    }
}

JsonAny* json_object_clone(const JsonObject* source)
{
    JsonObject* dest = &json_object_create()->object;

    struct JsonObjectEntry* it;
    LIST_FOREACH(it, &source->entries, entries) {
        json_object_push(dest, it->key, it->value);
    }

    return (JsonAny*)dest;
}