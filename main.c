
#include <stdio.h>

#define LOGGER_TYPES                                                           \
    _X(OUT_OF_MEMORY, "out of memory")                                         \
    _X(NULL_PTR_DEREF, "null deref")

#include "logger.h"

int main() {
    THROW_ERROR(OUT_OF_MEMORY);
    return 0;
}
