#ifndef STRINGARRAY_H_
#define STRINGARRAY_H_

#include <stdint.h>

typedef struct {
    char **data;
    uint32_t length;
    uint32_t capacity;
} StringArray;

/* Memory management */
StringArray *stringarray_init();
void stringarray_free(StringArray *array);

/* String management */
void stringarray_append(StringArray *array, char *s);
char *stringarray_concat(StringArray *array);
char *stringarray_concat_with_flags(StringArray *array, char *flag);

#endif //  STRINGARRAY_H_
