
#include <stdio.h>

#define LOGGER_LEVELS                                                          \
    _X(INFO)                                                                   \
    _X(WARN)                                                                   \
    _X(ERROR)

#define LOGGER_TYPES                                                           \
    _X(ERROR, OUT_OF_MEMORY, "out of memory")                                  \
    _X(ERROR, NULL_PTR_DEREF, "null deref")                                    \
    _X(WARN, VALUE_NOT_SET, "value not set")

#include "logger.h"

int main() {
    LOG(ERROR_OUT_OF_MEMORY);
    LOG(WARN_VALUE_NOT_SET);
    return 0;
}
