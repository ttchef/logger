
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>

#ifndef LOGGER_TYPES
#error "Logger types not definined"
#endif

/* generate enum */
#define _X(type, msg, ...) type,
enum { LOGGER_TYPES };
#undef _X

/* generate text */
#define _X(type, msg, ...) msg,
const char *LOGGER_NAMES[] = {LOGGER_TYPES};
;
#undef _X

#define _X(type, msg, ...) +1
static const int LOGGER_ERRORS_LEN = 0 LOGGER_TYPES;
#undef _X

#define PRINT_ERROR(type) printf("[ERROR]: %s\n", LOGGER_NAMES[type])
#define THROW_ERROR(type)                                                      \
    PRINT_ERROR(type);                                                         \
    exit(EXIT_FAILURE)

#endif // LOGGER_H
