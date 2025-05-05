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

//-------------------------- Block Management --------------------------------//

// Type for storing header/footer
typedef unsigned int word_t;

// Word and header/footer size (bytes)
#define WSIZE sizeof(word_t)
// Double word size (bytes)
#define DSIZE (WSIZE << 1)

// Pack size and allocated bit into a word
#define PACK(size, alloc) ((size) | (alloc))

// Read and write a word at address p
#define GET(p) (*(word_t *)(p))
#define PUT(p, val) (*(word_t *)(p) = (val))

// Read the size and allocated fields from address p
#define GET_SIZE(p) (GET(p) & ~0x7) // Excluding 3 lowest bits, always power of 8
#define GET_ALLOC(p) (GET(p) & 0x1) // Lowest bit

// Given block ptr bp, compute address of its header and footer
#define HDRP(bp) ((char *)(bp) - WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

// Given block ptr bp, compute address of next and previous blocks
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

static size_t align(size_t size) {
  return DSIZE * ((size + DSIZE + (DSIZE - 1)) / DSIZE);
}

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
  void *prev = PREV_BLKP(curr);
  void *next = NEXT_BLKP(curr);
  word_t prev_alloc = GET_ALLOC(FTRP(prev));
  word_t next_alloc = GET_ALLOC(HDRP(next));
  word_t size = GET_SIZE(HDRP(curr));
  if (prev_alloc && next_alloc) { // Case 1
    return curr;
  } else if (prev_alloc && !next_alloc) { // Case 2
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
  return NULL;
}

//---------------------------- Malloc Functions ------------------------------//

void __attribute__ ((constructor)) malloc_module_init(void) {
  trace("malloc module is initialized\n");
  m_start = request_chunk();
  m_curr = m_start;
  m_end = PTR_ADD(m_start, CHUNKSIZE);
  trace("start=%p\nend=  %p\n", m_start, m_end);
}

void *malloc(size_t size) {
  if (size == 0) {
    return NULL;
  }
  void *ptr = NULL;
  size_t asize = align(size);
  if ((ptr = find_fit(asize)) != NULL) {
    place(ptr, asize);
  }
  trace("malloc(%zu) = %p\n", size, ptr);
  return ptr;
}

void free(void *ptr) {
  trace("free(%p)\n", ptr);
  word_t size = GET_SIZE(HDRP(ptr)); // Reset alloc
  PUT(HDRP(ptr), size);
  PUT(FTRP(ptr), size);
  coalesce(ptr);
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
