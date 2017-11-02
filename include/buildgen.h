#ifndef BUILDGEN_H_
#define BUILDGEN_H_

#include <stdint.h>
#include "stringarray.h"

typedef struct {
    StringArray *files;
} BuildgenBuilder;

/* Memory allocation */
BuildgenBuilder *builder_init();
void builder_free(BuildgenBuilder *);

/* Source file management */
void builder_add_source(BuildgenBuilder *builder, char *filename);

/* Compilation */
void builder_compile_to(BuildgenBuilder *builder, char *output);

#endif // BUILDGEN_H_
