#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buildgen.h"
#include "macros.h"
#include "stringarray.h"


/* Static functions */
BuildgenBuilder *builder_init() {
    BuildgenBuilder *self = malloc(sizeof(BuildgenBuilder));
    NULL_CHECK(self, "error allocating builder\n");

    self->files = stringarray_init();
    NULL_CHECK(self->files, "error allocating files array\n");

    self->include_paths = stringarray_init();
    NULL_CHECK(self->include_paths, "error allocating include paths array\n");

    self->link_paths = stringarray_init();
    NULL_CHECK(self->link_paths, "error allocating link paths array\n");

    self->link_stubs = stringarray_init();
    NULL_CHECK(self->link_stubs, "error allocating link stubs array\n");

    return self;
}

void builder_free(BuildgenBuilder *builder) {
    NULL_CHECK(builder, "cannot deallocate builder (passed a null pointer)\n");
    NULL_CHECK(builder->files, "cannot deallocate list of files (passed a null pointer)\n");
    NULL_CHECK(builder->include_paths, "cannot deallocate list of include paths (passed a null pointer)\n");
    NULL_CHECK(builder->link_paths, "cannot deallocate list of include paths (passed a null pointer)\n");
    NULL_CHECK(builder->link_stubs, "cannot deallocate list of include paths (passed a null pointer)\n");

    stringarray_free(builder->link_stubs);
    stringarray_free(builder->link_paths);
    stringarray_free(builder->include_paths);
    stringarray_free(builder->files);
    free(builder);
}


void builder_add_source(BuildgenBuilder *builder, char *filename) {
    NULL_CHECK(builder, "cannot add source, builder pointer is null\n");

    stringarray_append(builder->files, filename);
}

void builder_add_include_path(BuildgenBuilder *builder, char *path) {
    NULL_CHECK(builder, "cannot add include path, builder pointer is null\n");
    stringarray_append(builder->include_paths, path);
}

void builder_add_link_path(BuildgenBuilder *builder, char *path) {
    NULL_CHECK(builder, "cannot add link path, builder pointer is null\n");
    stringarray_append(builder->link_paths, path);
}

void builder_link_to(BuildgenBuilder *builder, char *stub) {
    NULL_CHECK(builder, "cannot add link library, builder pointer is null\n");
    stringarray_append(builder->link_stubs, stub);
}

static char *add_string(char *ptr, char *s) {
    uint32_t len = strlen(s);
    strncpy(ptr, s, len);
    return ptr + len;
}

void builder_compile_to(BuildgenBuilder *builder, char *output) {
    NULL_CHECK(builder, "cannot compile, builder pointer is null\n");
    NULL_CHECK(builder->files, "cannot compile, builder files list is null\n");

    char *builder_files_string = stringarray_concat(builder->files);
    NULL_CHECK(builder_files_string, "null builder files string\n");

    char cmd[65335];
    memset(cmd, 0, sizeof(cmd) / sizeof(char));
    char *ptr = cmd;

    ptr = add_string(ptr, "gcc ");
    for (int i=0; i<builder->include_paths->length; i++) {
        ptr = add_string(ptr, "-I");
        ptr = add_string(ptr, builder->include_paths->data[i]);
        ptr = add_string(ptr, " ");
    }

    for (int i=0; i<builder->link_paths->length; i++) {
        ptr = add_string(ptr, "-L");
        ptr = add_string(ptr, builder->link_paths->data[i]);
        ptr = add_string(ptr, " ");
    }

    for (int i=0; i<builder->files->length; i++) {
        ptr = add_string(ptr, builder->files->data[i]);
        ptr = add_string(ptr, " ");
    }

    for (int i=0; i<builder->link_stubs->length; i++) {
        ptr = add_string(ptr, "-l");
        ptr = add_string(ptr, builder->link_stubs->data[i]);
        ptr = add_string(ptr, " ");
    }

    ptr = add_string(ptr, "-o ");
    ptr = add_string(ptr, output);

    printf("%s\n", cmd);

    system(cmd);
}
