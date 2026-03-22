
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>

#ifndef LOGGER_TYPES
#error "Logger types not definined"
#endif

#ifndef LOGGER_LEVELS
#error "Logger levels not definied"
#endif

#define LOGGER_COLOR_RED "\x1b[31m"
#define LOGGER_COLOR_RESET "\x1b[0m"

/* generate enum */
#define _X(level, type, msg, ...) level##_##type,
enum { LOGGER_TYPES };
#undef _X

#define _X(level, type, msg, ...) +1
static const int LOGGER_ERRORS_LEN = 0 LOGGER_TYPES;
#undef _X

/* logger level enum */
#define _X(name) name,
enum { LOGGER_LEVELS };
#undef _X

/* logger level string */
#define _X(name) #name,
const char *LOGGER_LEVEL_NAMES[] = {LOGGER_LEVELS};
#undef _X

struct logger_entry {
    int level;
    const char *msg;
};

/* generate struct */
#define _X(level, type, msg, ...) {level, msg},
struct logger_entry LOGGER_TABLE[] = {LOGGER_TYPES};
#undef _X

static inline void logger_log(const char *file, const char *func, int line,
                              struct logger_entry *e) {
    const char *level = LOGGER_LEVEL_NAMES[e->level];
    fprintf(stderr,
            LOGGER_COLOR_RED "[%s] " LOGGER_COLOR_RESET "(%s:%d %s): %s\n",
            level, file, line, func, e->msg);
}

#define PRINT_ERROR(type)                                                      \
    logger_log(__FILE__, __func__, __LINE__, &LOGGER_TABLE[type])

#define THROW_ERROR(type)                                                      \
    PRINT_ERROR(type);                                                         \
    exit(EXIT_FAILURE)

#endif // LOGGER_H
