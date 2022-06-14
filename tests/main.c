#include <json/json.h>
#include <stdio.h>

int main(int ac, const char** av)
{
    JsonAny* greet = json_string_create("Hello world");
    JsonAny* number = json_number_create(0);
    JsonAny* boolean = json_boolean_create(false);
    JsonAny* null = json_null_create();

    JsonAny* array = json_array_create();
    json_array_push(&array->array, greet);
    json_array_push(&array->array, number);
    json_array_push(&array->array, boolean);
    json_array_push(&array->array, null);


    char* msg5 = json_serialize(array);
    printf("%s\n", msg5);

    JsonAny* array2 = json_clone(array);

    json_delete(array);

    char* msg6 = json_serialize(array2);
    printf("%s\n", msg6);

    JsonAny* object = json_object_create();
    JsonString* key = &json_string_create("key2")->string;

    json_object_push(&object->object, &greet->string, array2);
    json_object_push(&object->object, key, null);

    json_object_push(&object->object, &greet->string, boolean);


    char* msg7 = json_serialize(object);
    printf("%s\n", msg7);

    json_delete(greet);
    json_delete(number);
    json_delete(boolean);
    json_delete(null);

    json_delete(object);

    return 0;
}