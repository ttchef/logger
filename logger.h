
#ifndef LOGGER_H
#define LOGGER_H

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

enum {
    LOGGER_FLAG_THREAD_ID = (1 << 0),
    LOGGER_FLAG_TIME = (1 << 1),
};

static struct {
    FILE *fd;
    int flags;
} logger_state;

static inline void logger_log(FILE *fd, const char *file, const char *func,
                              int line, struct logger_entry *e) {
    const char *level = LOGGER_LEVEL_TABLE[e->level].name;
    if (fd == stderr) {
        fprintf(fd,
                LOGGER_COLOR_BOLD "%s[%s] " LOGGER_COLOR_RESET "(%s:%d %s) ",
                LOGGER_COLOR_STR[LOGGER_LEVEL_TABLE[e->level].color], level,
                file, line, func);
        if (logger_state.flags & LOGGER_FLAG_THREAD_ID) {
            fprintf(fd,
                    "[" LOGGER_COLOR_BOLD "%stid" LOGGER_COLOR_RESET " %lu] ",
                    LOGGER_COLOR_STR[LOGGER_COLOR_GREEN], pthread_self());
        }
        if (logger_state.flags & LOGGER_FLAG_TIME) {
            time_t now = time(NULL);
            struct tm *t = localtime(&now);
            fprintf(fd,
                    "[" LOGGER_COLOR_BOLD "%sTime:" LOGGER_COLOR_RESET
                    " %02d:%02d:%02d] ",
                    LOGGER_COLOR_STR[LOGGER_COLOR_GREEN], t->tm_hour, t->tm_min,
                    t->tm_sec);
        }
    } else {
        fprintf(fd, "[%s] (%s:%d %s) ", level, file, line, func);
        if (logger_state.flags & LOGGER_FLAG_THREAD_ID) {
            fprintf(fd, "[tid %lu] ", pthread_self());
        }
        if (logger_state.flags & LOGGER_FLAG_TIME) {
            time_t now = time(NULL);
            struct tm *t = localtime(&now);
            fprintf(fd, "[Time: %02d:%02d:%02d] ", t->tm_hour, t->tm_min,
                    t->tm_sec);
        }
    }

    fprintf(fd, "%s\n", e->msg);
}

static inline void logger_set_file(FILE *fd) { logger_state.fd = fd; }
static inline void logger_unset_file(FILE *fd) { logger_state.fd = NULL; }
static inline void logger_enable_flags(int flags) {
    logger_state.flags |= flags;
}
static inline void logger_clear_flags() { logger_state.flags = 0; }

#define LOG(type)                                                              \
    do {                                                                       \
        if (logger_state.fd) {                                                 \
            logger_log(logger_state.fd, __FILE__, __func__, __LINE__,          \
                       &LOGGER_TABLE[type]);                                   \
        }                                                                      \
        logger_log(stderr, __FILE__, __func__, __LINE__, &LOGGER_TABLE[type]); \
    } while (0)

#endif // LOGGER_H
