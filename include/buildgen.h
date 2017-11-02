#ifndef BUILDGEN_H_
#define BUILDGEN_H_

#include <stdint.h>
#include "stringarray.h"

typedef struct {
    StringArray *files;
    StringArray *include_paths;
} BuildgenBuilder;

/* Memory allocation */
BuildgenBuilder *builder_init();
void builder_free(BuildgenBuilder *);

/* Source file management */
void builder_add_source(BuildgenBuilder *builder, char *filename);

void builder_add_include_path(BuildgenBuilder *builder, char *path);

/* Compilation */
void builder_compile_to(BuildgenBuilder *builder, char *output);

#endif // BUILDGEN_H_
