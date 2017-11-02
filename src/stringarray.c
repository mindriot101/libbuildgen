#include "stringarray.h"
#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include <string.h>

StringArray *stringarray_init() {
    StringArray *self = malloc(sizeof(StringArray));
    NULL_CHECK(self, "error allocating string array\n");

    self->data = malloc(32 * sizeof(char**));
    self->length = 0;
    self->capacity = 32;

    return self;
}

void stringarray_free(StringArray *array) {
    NULL_CHECK(array, "cannot deallocate array (passed a null pointer)\n");
    NULL_CHECK(array->data, "cannot deallocate array (passed a null pointer)\n");

    for (uint32_t i=0; i<array->length; i++) {
        free(array->data[i]);
    }

    free(array->data);
    free(array);
}

void stringarray_append(StringArray *array, char *s) {
    NULL_CHECK(array, "cannot add source, array pointer is null\n");

    if (array->length >= array->capacity) {
        printf("Reallocating data array\n");
        uint32_t new_capacity = array->capacity * 2;
        array->data = realloc(array->data, new_capacity * sizeof(char**));
        array->capacity = new_capacity;
    }

    uint32_t s_length = strlen(s);
    array->data[array->length] = malloc((s_length + 1) * sizeof(char));
    strncpy(array->data[array->length], s, s_length + 1);
    array->length += 1;
}

char *stringarray_concat(StringArray *array) {
    NULL_CHECK(array, "cannot create array files string, array pointer is null\n");
    NULL_CHECK(array->data, "cannot create array files string, array files pointer is null\n");

    uint32_t total_length = 0;
    for (uint32_t i=0; i<array->length; i++) {
        total_length += (strlen(array->data[i]) + 1);
    }

    char *out_str = malloc(total_length * sizeof(char) + 1);
    char *ptr = out_str;
    for (uint32_t i=0; i<array->length; i++) {
        char *text = array->data[i];
        uint32_t text_len = strlen(text);
        strncpy(ptr, text, text_len);
        ptr += (text_len + 1);
    }

    out_str[total_length - 1] = '\0';
    return out_str;
}

char *stringarray_concat_with_flags(StringArray *array, char *flag) {
    NULL_CHECK(array, "cannot create array files string, array pointer is null\n");
    NULL_CHECK(array->data, "cannot create array files string, array files pointer is null\n");

    uint32_t flag_length = strlen(flag);
    uint32_t total_length = 0;
    for (uint32_t i=0; i<array->length; i++) {
        /* e.g. ' -I blah ' */
        total_length += (strlen(array->data[i]) + flag_length + 3);
    }
    char *out_str = malloc(total_length * sizeof(char) + 1);
    char *ptr = out_str;
    for (uint32_t i=0; i<array->length; i++) {
        /* write the flag */
        strncpy(ptr, flag, flag_length);
        ptr += flag_length;
        *ptr = ' ';
        ptr += 1;

        char *text = array->data[i];
        uint32_t text_len = strlen(text);
        strncpy(ptr, text, text_len);
        ptr += (text_len + 1);
    }


    out_str[total_length - 1] = '\0';
    return out_str;
}
