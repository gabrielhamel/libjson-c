#include "internal.h"

static const json_type_action_t actions[] = {
    { .clone = (void *)json_string_clone, .delete = (void *)json_string_delete, .serialize = (void *)json_string_serialize},
    { .clone = (void *)json_number_clone, .delete = (void *)json_number_delete, .serialize = (void *)json_number_serialize},
    { .clone = (void *)json_boolean_clone, .delete = (void *)json_boolean_delete, .serialize = (void *)json_boolean_serialize},
    { .clone = (void *)json_null_clone, .delete = (void *)json_null_delete, .serialize = (void *)json_null_serialize},
    { .clone = (void *)json_array_clone, .delete = (void *)json_array_delete, .serialize = (void *)json_array_serialize},
    { .clone = (void *)json_object_clone, .delete = (void *)json_object_delete, .serialize = (void *)json_object_serialize},
};

char* json_serialize(const JsonAny* any)
{
    return actions[any->type].serialize(any);
}

void json_delete(JsonAny* any)
{
    actions[any->type].delete(any);
}

JsonAny* json_clone(const JsonAny* source) {
    return actions[source->type].clone(source);
}