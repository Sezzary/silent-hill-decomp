#ifndef _COMMON_H
#define _COMMON_H

// Standard
#include <ctype.h>
#include <limits.h>
#include <memory.h>

// PsyQ
#include <psyq/inline_c.h>
#include <psyq/libapi.h>
#include <psyq/strings.h>

// Resources
#include "inline_no_dmpsx.h"
#include "include_asm.h"
#include "types.h"

#define PSX_SCRATCH ((void*)0x1F800000)

#define PSX_SCRATCH_ADDR(offset) ((void*)(((u8*)PSX_SCRATCH) + (offset)))

/** @brief Computes the size of an array.
 *
 * @param arr Array.
 * @return Element count.
 */
#define ARRAY_SIZE(arr) \
    (s32)(sizeof(arr) / sizeof((arr)[0]))

#define ALIGN(x, a) \
    (((u32)(x) + ((a) - 1)) & ~((a) - 1))

#define SECTION(x) \
    __attribute__((section(x)))

#define STATIC_ASSERT(cond, msg) \
    typedef char static_assertion_##msg[(cond) ? 1 : -1]

#define STATIC_ASSERT_SIZEOF(type, size) \
    typedef char static_assertion_sizeof_##type[(sizeof(type) == (size)) ? 1 : -1]

#endif
