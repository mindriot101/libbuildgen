#include <stdio.h>
#include <buildgen.h>


int main(int argc, char *argv[]) {
    char *source_file = "../tests/build.c";
    char *output_binary = "./foo";

    BuildgenBuilder *builder = builder_init();
    if (builder == NULL) {
        return 1;
    }

    builder_add_source(builder, source_file);
    builder_compile_to(builder, output_binary);

    builder_free(builder);

    return 0;
}
