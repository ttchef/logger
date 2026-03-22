
#ifndef LOGGER_H
#define LOGGER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef LOGGER_TYPES
#error "Logger types not definined"
#endif

#ifndef LOGGER_LEVELS
#error "Logger levels not definied"
#endif

#define LOGGER_COLORS                                                          \
    _Y(LOGGER_COLOR_BLUE, "\x1b[34m")                                          \
    _Y(LOGGER_COLOR_YELLOW, "\x1b[33m")                                        \
    _Y(LOGGER_COLOR_RED, "\x1b[31m")                                           \
    _Y(LOGGER_COLOR_GREEN, "\x1b[32m")

#define LOGGER_COLOR_BOLD "\x1b[1m"
#define LOGGER_COLOR_RESET "\x1b[0m"

/* generate color enum */
#define _Y(type, str) type,
enum { LOGGER_COLORS };
#undef _Y

/* generate color str array */
#define _Y(type, str) str,
static const char *LOGGER_COLOR_STR[] = {LOGGER_COLORS};
#undef _Y

/* generate enum */
#define _X(level, type, msg, ...) level##_##type,
enum { LOGGER_TYPES };
#undef _X

#define _X(level, type, msg, ...) +1
static const int LOGGER_ERRORS_LEN = 0 LOGGER_TYPES;
#undef _X

/* logger level enum */
#define _X(name, color) name,
enum { LOGGER_LEVELS };
#undef _X

struct logger_level {
    int color;
    const char *name;
};

#define _X(name, color) {color, #name},
const struct logger_level LOGGER_LEVEL_TABLE[] = {LOGGER_LEVELS};
#undef _X

struct logger_entry {
    int level;
    const char *msg;
};

/* generate struct */
#define _X(level, type, msg, ...) {level, msg},
struct logger_entry LOGGER_TABLE[] = {LOGGER_TYPES};
#undef _X

static inline void logger_log(FILE *fd, const char *file, const char *func,
                              int line, struct logger_entry *e, bool to_file) {
    const char *level = LOGGER_LEVEL_TABLE[e->level].name;
    if (!to_file) {
        fprintf(fd,
                LOGGER_COLOR_BOLD "%s[%s] " LOGGER_COLOR_RESET
                                  "(%s:%d %s): %s\n",
                LOGGER_COLOR_STR[LOGGER_LEVEL_TABLE[e->level].color], level,
                file, line, func, e->msg);
    } else {
        fprintf(fd, "[%s] (%s:%d %s): %s\n", level, file, line, func, e->msg);
    }
}

static FILE *LOGGER_FILE = NULL;

static inline void logger_set_file(FILE *fd) { LOGGER_FILE = fd; }

#define LOG(type)                                                              \
    do {                                                                       \
        if (LOGGER_FILE) {                                                     \
            logger_log(LOGGER_FILE, __FILE__, __func__, __LINE__,              \
                       &LOGGER_TABLE[type], true);                             \
        }                                                                      \
        logger_log(stderr, __FILE__, __func__, __LINE__, &LOGGER_TABLE[type],  \
                   false);                                                     \
    } while (0)

#endif // LOGGER_H
