#include "malloc.h"

#include <assert.h>
#include <string.h>
#include <unistd.h>

#include "trace.h"

//------------------------ Heap Management Functions -------------------------//

// Size of chunk to be requested from OS. 4096 is memory page size.
#define CHUNKSIZE (1 << 12)

// Moves a pointer forward by the specified number of bytes.
#define PTR_ADD(p, offset) (((char *) p) + offset)

// Start of reserved memory region.
static void *m_start;
// End of reserved memory region.
static void *m_end;
// Current position (between area used for blocks and unused memory).
static void *m_curr;

// Requests a chunk of memory for the heap from the OS.
static void *request_chunk() {
   void *start = sbrk(0);
   void *ptr = sbrk(CHUNKSIZE);
   assert(start == ptr);
   return ptr;
}

// Requests a block of the specified size. Extends the heap if needed.
static void *request_block(size_t size) {
  while (m_curr + size > m_end) {
    void *ptr = request_chunk();
    assert(m_end == ptr);
    m_end = PTR_ADD(m_end, CHUNKSIZE);
  }
  void *bp = m_curr;
  m_curr = PTR_ADD(m_curr, size);
  return bp;
}

//----------------------------------------------------------------------------//

void __attribute__ ((constructor)) malloc_module_init(void) {
  trace("malloc module is initialized\n");
  m_start = request_chunk();
  m_curr = m_start;
  m_end = PTR_ADD(m_start, CHUNKSIZE);
  trace("start=%p\nend=  %p\n", m_start, m_end);
}

static void *find_fit(size_t size);
static void place(void *bp, size_t size);
static void *coalesce(void *bp);

//---------------------------- Malloc Functions ------------------------------//

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
