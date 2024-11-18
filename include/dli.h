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

#define DLI_EMPTY_MSG "dli is empty"
#define DLI_ERR_MSG "dli is undefined"
#define DLI_OUT_OF_RANGE "index is out of range"
#define DLI_INIT_ERR_MSG "dli initialization failed. aborting"
#define DLI_MEM_ERR_MSG "memory re-/allocation for data failed"

typedef void (*dli_print_fn)(const void *);

typedef struct
{
  void **data;
  uint32_t size;
  uint32_t capacity;
  uint32_t elem_size;
  dli_print_fn print;
} dli;

void dli_print(dli *d);

void *dli_first(dli *d);

void *dli_last(dli *d);

void dli_pseudo_str_fill(dli *d);

void print_str(const void *data);

void print_int(const void *data);

void print_long(const void *data);

void print_char(const void *data);

void print_float(const void *data);

void *dli_at(dli *d, uint32_t idx);

void print_double(const void *data);

int dli_free(dli *d);

int dli_is_full(dli *d);

int dli_is_empty(dli *d);

int dli_pseudo_fill(dli *d);

int dli_push(dli *d, void *data);

int dli_init(dli *d, uint32_t elem_size, uint32_t capacity, dli_print_fn print);

/* int dli_resize(dli *d); --> STATIC */
/* int dli_reallocate(dli *d); --> STATIC */
/* int dli_safe_deallocate(dli *d); --> STATIC */
/* int dli_is_in_range(dli *d, uint32_t idx); --> STATIC */
/* int dli_is_valid_idx(dli *d, uint32_t idx); --> STATIC */
/* int dli_allocate(dli *d, uint8_t elem_size, uint32_t capacity, dli_print_fn print); --> STATIC */
