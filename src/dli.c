#include "dli.h"

/*functions:
  pop item
*/

static int dli_safe_deallocate(dli *d)
{
  for (int i = 0; i < d->size; ++i)
  {
    explicit_bzero(d->data[i], d->elem_size);
    free(d->data[i]);
    d->data[i] = NULL;
  }

  explicit_bzero(d->data, sizeof(void *));
  
  free(d->data);
  d->data = NULL;

  d->size = 0;
  d->capacity = 0;
  d->elem_size = 0;
  
  return 1;
}

static int dli_is_in_range(dli *d, uint32_t idx)
{
  return idx < d->size && idx >= 0;
}

static int dli_reallocate(dli *d)
{
  uint32_t new_cap = d->capacity * 2;
  uint32_t new_size = new_cap * d->elem_size;
  void **tmp = realloc(d->data, new_size);
  ZR_ON_NULL(tmp, DLI_MEM_ERR_MSG);
  d->data = tmp;
  d->capacity = new_cap;
  return 1;
}

static int dli_resize(dli *d)
{
  ZR_ON_NULL(d, DLI_ERR_MSG);
  ZR_ON_NULL(dli_reallocate(d), DLI_MEM_ERR_MSG);
  return 1;
}

static int dli_is_valid_idx(dli *d, uint32_t idx)
{
  ZR_ON_NULL(d, DLI_ERR_MSG);
  ZR_ON_TRUE(dli_is_empty(d), DLI_EMPTY_MSG);
  ZR_ON_NULL(dli_is_in_range(d, idx), DLI_OUT_OF_RANGE);
  return 1;
}

static int dli_allocate(dli *d, uint32_t elem_size, uint32_t capacity, dli_print_fn print)
{
  ZR_ON_NULL(d, DLI_ERR_MSG);
  ZR_ON_NULL(capacity, "invalid capacity");
  ZR_ON_NULL(elem_size, "invalid element size");
  
  d->size = 0;
  d->print = print;
  d->capacity = capacity;
  d->elem_size = elem_size;

  d->data = calloc(sizeof(void *) * capacity, 1);
  ZR_ON_NULL(d->data, DLI_MEM_ERR_MSG);
  return 1;
}

int dli_init(dli *d, uint32_t elem_size, uint32_t capacity, dli_print_fn print)
{
  ZR_ON_NULL(dli_allocate(d, elem_size, capacity, print), DLI_INIT_ERR_MSG);
  return 1;
}

int dli_free(dli *d)
{
  ZR_ON_NULL(d, DLI_ERR_MSG);
  ZR_ON_NULL(d->size, DLI_EMPTY_MSG);
  ZR_ON_NULL(dli_safe_deallocate(d), DLI_EMPTY_MSG);
  return 1;
}

void *dli_last(dli *d)
{
  RET_ON_NULL(d, NULL, DLI_ERR_MSG, "");
  RET_ON_TRUE(dli_is_empty(d), NULL, DLI_EMPTY_MSG, "");
  return d->data[d->size - 1];
}

void *dli_first(dli *d)
{
  RET_ON_NULL(d, NULL, DLI_ERR_MSG, "");
  RET_ON_TRUE(dli_is_empty(d), NULL, DLI_EMPTY_MSG, "");
  return d->data[0];
}

void *dli_at(dli *d, uint32_t idx)
{
  EXIT_ON_ERR(dli_is_valid_idx(d, idx), FATAL_ERR_MSG);
  return d->data[idx];
}

int dli_is_empty(dli *d)
{
  return (d->size - 1) < 0;
}

int dli_is_full(dli *d)
{
  return d->size == d->capacity;
}

int dli_pseudo_fill(dli *d)
{
  for (int i = 0; i < d->capacity; ++i)
    dli_push(d, &i);
  return 1;
}

void dli_pseudo_str_fill(dli *d)
{
  for (int i = 0; i < d->capacity; ++i)
  {
    char x[50];
    snprintf(x, sizeof(x), "Lorem ipsum - %d", i);
    dli_push(d, x);
  }
}

int dli_push(dli *d, void *data)
{
  if (dli_is_full(d))
    ZR_ON_NULL(dli_resize(d), DLI_MEM_ERR_MSG);

  void **pdata = d->data;
  uint32_t size = d->size;

  pdata[size] = malloc(d->elem_size);
  ZR_ON_NULL(pdata[size], DLI_MEM_ERR_MSG);
  
  memcpy(pdata[size], data, d->elem_size);

  d->size++;
  return 1;
}

void dli_print(dli *d)
{
  for (int i = 0; i < d->size; ++i)
    d->print(d->data[i]);
}

void print_int(const void *data)
{
  printf("%d\n", *(int *)data);
}

void print_str(const void *data)
{
  printf("%s\n", (char *)data);
}

// test fns below:

void print_float(const void *data)
{
  printf("%f\n", *(float *)data);
}

void print_double(const void *data)
{
  printf("%lf\n", *(double *)data);
}

void print_long(const void *data)
{
  printf("%ld\n", *(long *)data);
}

void print_char(const void *data)
{
  printf("%c\n", *(char *)data);
}
