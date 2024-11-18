#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define ALLOC_ERR_MSG "memory allocation failed."
#define FATAL_ERR_MSG "[fatal error]\nterminated."

#define EXIT_ON_ERR(ptr, msg) do {  \
  if (!(ptr))                       \
  {                                 \
    fprintf(stderr, "%s\n", (msg)); \
    exit(EXIT_FAILURE);             \
  }                                 \
} while(0);

#define RET_ON_NULL(ptr, ret, msg, va) do {         \
  if (!(ptr))                                       \
  {                                                 \
    fprintf(stderr, "error: %s %s\n", (msg), (va)); \
    return (ret);                                   \
  }                                                 \
} while(0);

#define ZR_ON_NULL(ptr, msg) do {           \
  if (!(ptr))                               \
  {                                         \
    fprintf(stderr, "error: %s.\n", (msg)); \
    return 0;                               \
  }                                         \
} while(0);

#define RET_ON_TRUE(ptr, ret, msg, va) do {         \
  if ((ptr))                                        \
  {                                                 \
    fprintf(stderr, "error: %s %s\n", (msg), (va)); \
    return (ret);                                   \
  }                                                 \
} while(0);

#define ZR_ON_TRUE(ptr, msg) do {           \
  if ((ptr))                                \
  {                                         \
    fprintf(stderr, "error: %s.\n", (msg)); \
    return 0;                               \
  }                                         \
} while(0);
