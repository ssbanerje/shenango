/*
 * thread.h - support for user-level threads
 */

#pragma once

#include <base/types.h>
#include <base/compiler.h>

struct thread;
typedef void (*thread_fn_t)(void *arg);
typedef struct thread thread_t;


/*
 * Low-level routines, these are helpful for bindings and synchronization
 * primitives.
 */

extern void thread_park_and_unlock(spinlock_t *lock);
extern void thread_ready(thread_t *thread);
extern thread_t *thread_create(thread_fn_t fn, void *arg);
extern thread_t *thread_create_with_buf(thread_fn_t fn, void **buf, size_t len);

extern __thread thread_t *__self;

/**
 * thread_self - gets the currently running thread
 */
static inline thread_t *thread_self(void)
{
	return __self;
}


/*
 * High-level routines, use this API most of the time.
 */

extern void thread_yield(void);
extern int thread_spawn(thread_fn_t fn, void *arg);
extern void thread_exit(void) __noreturn;

/* main initialization */
extern int runtime_init(const char *cfgpath, thread_fn_t main_fn, void *arg);
