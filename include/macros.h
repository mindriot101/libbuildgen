#ifndef MACROS_H_
#define MACROS_H_

#define NULL_CHECK(ptr, msg) \
    if (ptr == NULL) { \
        fprintf(stderr, msg); \
        exit(1); \
    }

#endif // MACROS_H_
