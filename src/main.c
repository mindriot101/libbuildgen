#include <stdio.h>
#include <stdlib.h>
#include <buildgen.h>
#include <string.h>

#define NULL_CHECK(ptr, msg) \
    if (ptr == NULL) { \
        fprintf(stderr, msg); \
        exit(1); \
    }

/* Static functions */
static char *_builder_files_string(BuildgenBuilder *builder) {
    NULL_CHECK(builder, "cannot create builder files string, builder pointer is null\n");
    NULL_CHECK(builder->files, "cannot create builder files string, builder files pointer is null\n");

    uint32_t total_files_length = 0;
    for (uint32_t i=0; i<builder->files_length; i++) {
        total_files_length += (strlen(builder->files[i]) + 1);
    }

    char *out_str = malloc(total_files_length * sizeof(char) + 1);
    char *ptr = out_str;
    for (uint32_t i=0; i<builder->files_length; i++) {
        char *text = builder->files[i];
        strncpy(ptr, text, strlen(text));
        ptr += 1;
    }

    out_str[total_files_length - 1] = '\0';
    return out_str;
}

BuildgenBuilder *builder_init() {
    BuildgenBuilder *self = malloc(sizeof(BuildgenBuilder));
    NULL_CHECK(self, "error allocating builder\n");

    self->files = malloc(32 * sizeof(char**));
    self->files_length = 0;
    self->files_capacity = 32;

    return self;
}

void builder_free(BuildgenBuilder *builder) {
    NULL_CHECK(builder, "cannot deallocate builder (passed a null pointer)\n");
    NULL_CHECK(builder->files, "cannot deallocate list of files (passed a null pointer)\n");

    for (uint32_t i=0; i<builder->files_length; i++) {
        free(builder->files[i]);
    }

    free(builder->files);
    free(builder);
}


void builder_add_source(BuildgenBuilder *builder, char *filename) {
    NULL_CHECK(builder, "cannot add source, builder pointer is null\n");

    if (builder->files_length >= builder->files_capacity) {
        printf("Reallocating files array\n");
        uint32_t new_capacity = builder->files_capacity * 2;
        builder->files = realloc(builder->files, new_capacity * sizeof(char**));
        builder->files_capacity = new_capacity;
    }

    uint32_t filename_length = strlen(filename);
    builder->files[builder->files_length] = malloc((filename_length + 1) * sizeof(char));
    strncpy(builder->files[builder->files_length], filename, filename_length + 1);
    builder->files_length += 1;
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
