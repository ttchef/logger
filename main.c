
#include <stdio.h>

#define LOGGER_LEVELS                                                          \
    _X(INFO, LOGGER_COLOR_BLUE)                                                \
    _X(WARN, LOGGER_COLOR_YELLOW)                                              \
    _X(ERROR, LOGGER_COLOR_RED)

#define LOGGER_TYPES                                                           \
    _X(ERROR, OUT_OF_MEMORY, "out of memory")                                  \
    _X(ERROR, NULL_PTR_DEREF, "null deref")                                    \
    _X(WARN, VALUE_NOT_SET, "value not set")                                   \
    _X(INFO, PRINTED, "printed smth")

#include "logger.h"

int main() {
    LOG(ERROR_OUT_OF_MEMORY);
    LOG(WARN_VALUE_NOT_SET);
    LOG(INFO_PRINTED);
    return 0;
}
