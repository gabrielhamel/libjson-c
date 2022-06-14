#ifndef JSON_LIBRARY_H
#define JSON_LIBRARY_H

#include <stdbool.h>

/**
 * All json type handled
 */
typedef enum {
    JsonTypeString,
    JsonTypeNumber,
    JsonTypeBoolean,
    JsonTypeNull,
    JsonTypeArray,
    JsonTypeObject
} JsonType;

#define JSON_OBJECT_HEADER JsonType type;

/**
 * Null object
 * Equivalent to "null"
 */
typedef struct {
} JsonNull;

/**
 * Json escaped string
 */
typedef struct {
} JsonString;

/**
 * Json number
 * Handled by a double
 */
typedef struct {
} JsonNumber;

/**
 * Boolean
 * true or false
 */
typedef struct {
} JsonBoolean;

/**
 * Array container
 */
typedef struct {
} JsonArray;

/**
 * Json object
 * Contains key / value pairs
 */
typedef struct {
} JsonObject;

/**
 * Generic type, can contains any json type
 */
typedef union {
    JsonString string;
    JsonNumber number;
    JsonBoolean boolean;
    JsonNull null;
    JsonArray array;
    JsonObject object;
} JsonAny;

/**
 * Construct string object
 * @param value text to store
 * @return Json object
 */
JsonAny* json_string_create(const char* value);

/**
 * Construct number object
 * @param value numeric value to store
 * @return Json object
 */
JsonAny* json_number_create(double value);

/**
 * Construct boolean object
 * @param value true or false value
 * @return Json object
 */
JsonAny* json_boolean_create(bool value);

/**
 * Construct null object
 * @return Json object
 */
JsonAny* json_null_create();

/**
 * Construct array container object
 * @return Json object
 */
JsonAny* json_array_create();

/**
 * Insert object into array
 * @param array Json array object to fill
 * @param object Object to insert
 */
void json_array_push(JsonArray* array, const JsonAny* object);

/**
 * Construct new object container
 * @return Json object
 */
JsonAny* json_object_create();

/**
 * Insert key/value pair into object
 * @param object Json object to fill
 * @param key Object key in string format
 * @param value Object to associate with key
 */
void json_object_push(JsonObject* object, const JsonString* key, const JsonAny* value);

/**
 * Delete any json object
 * @param any Any object prefixed by JsonXXX
 */
void json_delete(JsonAny* any);

/**
 * Serialize any json object
 * @param any Any object prefixed by JsonXXX
 * @return Serialized string data
 */
char* json_serialize(const JsonAny* any);

/**
 * Duplicate json object (don't create deep dependencies)
 * @param source Json object to copy
 * @return New object cloned
 */
JsonAny* json_clone(const JsonAny* source);

#endif // JSON_LIBRARY_H
