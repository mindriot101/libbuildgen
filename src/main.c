#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buildgen.h"
#include "macros.h"
#include "stringarray.h"


/* Static functions */
static char *_builder_files_string(BuildgenBuilder *builder) {
    NULL_CHECK(builder, "cannot create builder files string, builder pointer is null\n");
    NULL_CHECK(builder->files, "cannot create builder files string, builder files pointer is null\n");

    return stringarray_concat(builder->files);
}

BuildgenBuilder *builder_init() {
    BuildgenBuilder *self = malloc(sizeof(BuildgenBuilder));
    NULL_CHECK(self, "error allocating builder\n");

    self->files = stringarray_init();

    return self;
}

void builder_free(BuildgenBuilder *builder) {
    NULL_CHECK(builder, "cannot deallocate builder (passed a null pointer)\n");
    NULL_CHECK(builder->files, "cannot deallocate list of files (passed a null pointer)\n");

    stringarray_free(builder->files);
    free(builder);
}


void builder_add_source(BuildgenBuilder *builder, char *filename) {
    NULL_CHECK(builder, "cannot add source, builder pointer is null\n");

    stringarray_append(builder->files, filename);
}

void builder_compile_to(BuildgenBuilder *builder, char *output) {
    NULL_CHECK(builder, "cannot compile, builder pointer is null\n");

    char *builder_files_string = _builder_files_string(builder);
    NULL_CHECK(builder_files_string, "null builder files string\n");

    char cmd[1024];
    snprintf(cmd, 1024, "gcc %s -o %s", builder_files_string, output);
    free(builder_files_string);

    system(cmd);
}
