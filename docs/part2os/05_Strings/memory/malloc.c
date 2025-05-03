#include "malloc.h"

#include <assert.h>
#include <string.h>
#include <unistd.h>

#include "trace.h"

#define CHUNKSIZE (1 << 12) // 4096

static void *heap_start;
static void *heap_end;

static void heap_extend(size_t size);
static void *find_fit(size_t size);
static void place(void *bp, size_t size);
static void *coalesce(void *bp);

void __attribute__ ((constructor)) malloc_init(void) {
  trace("malloc is initialized\n");
  heap_start = sbrk(0);
  void *ptr = sbrk(4096);
  heap_end = ((char *) start) + 4096;
  assert(start == ptr);
  trace("start=%p\nend=  %p\n", heap_start, heap_end);
}

//---------------------------- Public Functions ------------------------------//

void *malloc(size_t size) {
  if (size == 0) {
    return NULL;
  }
  void *ptr = NULL;
  trace("malloc(%zu) = %p\n", size, ptr);
  return ptr;
}

void free(void *ptr) {
  trace("free(%p)\n", ptr);
  // TODO
}

void *calloc(size_t nmemb, size_t size) {
  void *ptr = malloc(size);
  if (ptr) {
    memset(ptr, 0, size);
  }
  trace("calloc(%zu) = %p\n", size, ptr);
  return ptr;
}

void *realloc(void *ptr, size_t size) {
  if (!ptr) {
    return malloc(size);
  }
  void *newptr = ptr;
  size_t oldsize = GET_SIZE(ptr);
  if (oldsize < size) {
    newptr = malloc(size);
    if (newptr) {
      memcpy(newptr, ptr, oldsize);
      free(ptr);
    }
  }
  trace("realloc(%p, %zu) = %p\n", ptr, size, newptr);
  return newptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size) {
  size_t newsize = nmemb * size;
  if (newsize / size != nmemb) {
    return NULL; // Overflow!
  }
  return realloc(ptr, size);
}
