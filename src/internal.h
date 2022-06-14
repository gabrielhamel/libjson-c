#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include <sys/queue.h>
#include <stdbool.h>

#define JSON_OBJECT_HEADER JsonType type;

typedef enum {
    JsonTypeString,
    JsonTypeNumber,
    JsonTypeBoolean,
    JsonTypeNull,
    JsonTypeArray,
    JsonTypeObject
} JsonType;

typedef struct {
    JSON_OBJECT_HEADER
    char* value;
} JsonString;

typedef struct {
    JSON_OBJECT_HEADER
    double value;
} JsonNumber;

typedef struct {
    JSON_OBJECT_HEADER
    bool value;
} JsonBoolean;

typedef struct {
    JSON_OBJECT_HEADER
} JsonNull;

typedef struct {
    JSON_OBJECT_HEADER
    LIST_HEAD(, JsonArrayEntry) entries;
} JsonArray;

typedef struct {
    JSON_OBJECT_HEADER
    LIST_HEAD(, JsonObjectEntry) entries;
} JsonObject;

typedef union {
    JSON_OBJECT_HEADER
    JsonString string;
    JsonNumber number;
    JsonBoolean boolean;
    JsonNull null;
    JsonArray array;
    JsonObject object;
} JsonAny;

struct JsonArrayEntry {
    JsonAny* value;
    LIST_ENTRY(JsonArrayEntry) entries;
};

struct JsonObjectEntry {
    JsonString* key;
    JsonAny* value;
    LIST_ENTRY(JsonObjectEntry) entries;
};

char* json_string_serialize(const JsonString* object);
void json_string_delete(JsonString* object);
JsonAny* json_string_clone(const JsonString* source);

char* json_number_serialize(const JsonNumber* object);
void json_number_delete(JsonNumber* object);
JsonAny* json_number_clone(const JsonNumber* source);

char *json_boolean_serialize(const JsonBoolean* object);
void json_boolean_delete(JsonBoolean* object);
JsonAny* json_boolean_clone(const JsonBoolean* source);

char *json_null_serialize(const JsonNull* object);
void json_null_delete(JsonNull* object);
JsonAny* json_null_clone(const JsonNull* source);

char *json_array_serialize(const JsonArray* object);
void json_array_delete(JsonArray* object);
JsonAny* json_array_clone(const JsonArray* source);

JsonAny* json_object_create();
char* json_object_serialize(const JsonObject* object);
void json_object_delete(JsonObject* object);
JsonAny* json_object_clone(const JsonObject* source);

void string_concat(char** dest, char* source);
char* string_escape(const char* s1);

char* json_serialize(const JsonAny* any);
void json_delete(JsonAny* any);
JsonAny* json_clone(const JsonAny* source);

typedef struct {
    char* (*serialize)(const JsonAny*);
    void (*delete)(JsonAny*);
    JsonAny* (*clone)(const JsonAny*);
} json_type_action_t;

#endif // JSON_SERIALIZER_H
