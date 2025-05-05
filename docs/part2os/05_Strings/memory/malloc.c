#include "malloc.h"

#include <assert.h>
#include <string.h>
#include <unistd.h>

#include "trace.h"

//------------------------ Heap Management Functions -------------------------//

// Size of chunk to be requested from OS. 4096 is memory page size.
#define CHUNKSIZE (1 << 12)

// Moves a pointer forward/backward by the specified number of bytes.
#define PTR_ADD(p, offset) (((char *) p) + offset)
#define PTR_SUB(p, offset) (((char *) p) - offset)

// Start of reserved memory region.
static void *heap_start;
// End of reserved memory region.
static void *heap_end;

static void *request_memory(size_t size) {
  void *start = sbrk(0);
  void *ptr = sbrk(size);
  assert(start == ptr);
  return ptr;
}

//-------------------------- Block Management --------------------------------//

// Type for storing header/footer
typedef unsigned int word_t;

// Word and header/footer size (bytes)
#define WSIZE sizeof(word_t)
// Double word size (bytes)
#define DSIZE (WSIZE << 1)

// Read and write a word at address p
#define GET(p) (*(word_t *)(p))
#define PUT(p, val) (*(word_t *)(p) = (val))

// Read the size and allocated fields from address p
#define GET_SIZE(p) (GET(p) & ~0x7) // Excluding 3 lowest bits, always power of 8
#define GET_ALLOC(p) (GET(p) & 0x1) // Lowest bit

// Given block ptr bp, compute address of its header and footer
#define HDRP(bp) ((char *)(bp) - WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

// Size aligned by the border of given units (e.g. 8-byte double words).
#define ALIGNED_SIZE(size, unit) (unit * ((size + (unit - 1)) / unit))

// Head of block list.
static void *list_head = NULL;

static void place(void *bp, size_t asize) {
  void *hdr = HDRP(bp);
  void *ftr = FTRP(bp);
  size_t bsize = GET_SIZE(hdr); // Block size.
  assert(asize <= bsize);
  size_t rsize = bsize - asize; // Remaining size.
  if (rsize >= DSIZE) { // Split the block.
    void *rhdr = PTR_ADD(hdr, asize);
    void *aftr = PTR_SUB(rhdr, WSIZE);
    PUT(hdr, asize | 1); // Allocated header.
    PUT(aftr, asize | 1); // Allocated footer.
    PUT(rhdr, rsize); // Remaining header.
    PUT(ftr, rsize); // Remaining footer.
  } else { // Do not change the block size.
    PUT(hdr, bsize | 1);
    PUT(ftr, bsize | 1);
  }
}

static void *coalesce(void *curr) {
  size_t size = GET_SIZE(HDRP(curr));
  word_t prev_alloc = GET_ALLOC(PTR_SUB(curr, DSIZE));
  word_t next_alloc = GET_ALLOC(PTR_ADD(curr, size - WSIZE));
  if (prev_alloc && next_alloc) { // Case 1
    return curr;
  }
  void *prev = PTR_SUB(curr, GET_SIZE(PTR_SUB(curr, DSIZE)));
  void *next = PTR_ADD(curr, size);
  if (prev_alloc && !next_alloc) { // Case 2
    size += GET_SIZE(HDRP(next));
    PUT(HDRP(curr), size);
    PUT(FTRP(curr), size);
  } else if (!prev_alloc && next_alloc) { // Case 3
    size += GET_SIZE(HDRP(prev));
    PUT(FTRP(curr), size);
    PUT(HDRP(prev), size);
    curr = prev;
  } else { // Case 4
    size += GET_SIZE(HDRP(prev)) + GET_SIZE(FTRP(next));
    PUT(HDRP(prev), size);
    PUT(FTRP(next), size);
    curr = prev;
  }
  return curr;
}

static void *find_fit(size_t size) {
  void *ptr = list_head;
  void *hdr = HDRP(ptr);
  size_t bsize;
  while ((bsize = GET_SIZE(hdr))) {
    if (!GET_ALLOC(hdr) && bsize >= size) {
      return ptr;
    }
    ptr = PTR_ADD(ptr, bsize);
    hdr = HDRP(ptr);
  }
  return NULL;
}

static void *extend_heap(size_t size) {
  size_t asize = ALIGNED_SIZE(size, CHUNKSIZE);
  void *ptr = request_memory(asize);
  PUT(PTR_SUB(ptr, WSIZE), asize - WSIZE); // Header
  PUT(PTR_ADD(ptr, asize - DSIZE), asize - WSIZE); // Footer
  PUT(PTR_ADD(ptr, asize - WSIZE), 1); // Epilogue header (0-size allocated block)
  return coalesce(ptr);
}

static void dump_blocks() {
  void *ptr = list_head;
  void *hdr = HDRP(ptr);
  size_t bsize;
  while ((bsize = GET_SIZE(hdr))) {
    trace("%p = %zu/%d\n", ptr, bsize, GET_ALLOC(hdr));
    ptr = PTR_ADD(ptr, bsize);
    hdr = HDRP(ptr);
  }
}

//---------------------------- Malloc Functions ------------------------------//

void __attribute__ ((constructor)) malloc_module_init(void) {
  trace("malloc module is initialized\n");
  void *ptr = request_memory(CHUNKSIZE);
  heap_start = ptr;
  heap_end = PTR_ADD(ptr, CHUNKSIZE);
  PUT(ptr, 1); // Prologue footer (0-size allocated block)
  PUT(PTR_ADD(ptr, WSIZE), CHUNKSIZE - DSIZE); // Header
  PUT(PTR_ADD(ptr, CHUNKSIZE - DSIZE), CHUNKSIZE - DSIZE); // Footer
  PUT(PTR_ADD(ptr, CHUNKSIZE - WSIZE), 1); // Epilogue header (0-size allocated block)
  list_head = PTR_ADD(ptr, DSIZE);
  trace("start=%p\nend=  %p\nhead= %p\n", heap_start, heap_end, list_head);
  dump_blocks();
}

void __attribute__ ((destructor)) malloc_module_clean(void) {
  // dump_blocks();
  trace("malloc module is finalized\n");
}

void *malloc(size_t size) {
  trace("malloc(%zu)\n", size);
  if (size == 0) {
    return NULL;
  }
  size_t asize = ALIGNED_SIZE(size, DSIZE) + DSIZE;
  void *ptr = find_fit(asize);
  if (!ptr) {
    ptr = extend_heap(asize);
  }
  place(ptr, asize);
  trace("malloc(%zu) = %p\n", size, ptr);
  // dump_blocks();
  return ptr;
}

void free(void *ptr) {
  trace("free(%p)\n", ptr);
  if (!ptr) {
    return;
  }
  word_t size = GET_SIZE(HDRP(ptr)); // Reset alloc
  PUT(HDRP(ptr), size);
  PUT(FTRP(ptr), size);
  coalesce(ptr);
  // dump_blocks();
}

void *calloc(size_t nmemb, size_t size) {
  size_t newsize = nmemb * size;
  if (newsize / size != nmemb) {
    return NULL; // Overflow!
  }
  void *ptr = malloc(newsize);
  if (ptr) {
    memset(ptr, 0, newsize);
  }
  trace("calloc(%zu, %zu) = %p\n", nmemb, size, ptr);
  return ptr;
}

void *realloc(void *ptr, size_t size) {
  if (!ptr) {
    return malloc(size);
  }
  void *newptr = ptr;
  size_t oldsize = GET_SIZE(HDRP(ptr)) - DSIZE;
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
