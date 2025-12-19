/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)


#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))
/* Basic constants and macros from CSAPP */
#define WSIZE 4 /* Word and header/footer size (bytes) */
#define DSIZE 8 /* Double word size (bytes) */
#define CHUNKSIZE (1<<12) /* Extend heap by this amount (bytes) */

#define MAX(x, y) ((x) > (y)? (x) : (y))

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc) ((size) | (alloc))

/* Read and write a word at address p */
#define GET(p) (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (val))

/* Read the size and allocated fields from address p */
#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp) ((char *)(bp) - WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)
#define NXTP(bp) ((char *)(bp)) // for explicit free list
#define PRVP(bp) ((char *)(bp) + WSIZE)

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))
#define GET_NEXT(bp) (*(char **)(NXTP(bp))) // for explicit free list
#define GET_PREV(bp) (*(char **)(PRVP(bp)))
#define PUT_PTR(p, ptr) (*(char **)(p) = (ptr))
#define GET_SEG_PTR(index) (char **)(seg_free_list + (index * WSIZE))
#define GET_INDEX(size)  ((size) <= 32 ? 0 : \
                          (size) <= 64 ? 1 : \
                          (size) <= 128 ? 2 : \
                          (size) <= 256 ? 3 : \
                          (size) <= 512 ? 4 : \
                          (size) <= 1024 ? 5 : \
                          (size) <= 2048 ? 6 : \
                          (size) <= 4096 ? 7 : \
                          (size) <= 8192 ? 8 : \
                          (size) <= 16384 ? 9 : \
                          (size) <= 32768 ? 10 : 11)

/* Global variables */
static char *heap_listp;  /* Pointer to first block */
static char *seg_free_list; /* Pointer to the start of seg free block */

/* Function prototypes for internal helper routines */
static void *extend_heap(size_t words);
static void *coalesce(void *bp);
static void *find_fit(size_t asize);
static void place(void *bp, size_t asize);
static void delete_block(void *bp);
static void insert_block(void *bp);

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    if ((heap_listp = mem_sbrk(4 * WSIZE + 12 * WSIZE)) == (void *) -1) { // add 12 free list pointer size more
        return -1;
    }
    seg_free_list = heap_listp; // seg_free_list goes first than Prologue Header and Footer
    for (int i = 0; i < 12; i++) {
        *(char **)GET_SEG_PTR(i) = NULL;
    }
    heap_listp += 12 * WSIZE;
    PUT(heap_listp, 0); /* Alignment padding */
    PUT(heap_listp + (1*WSIZE), PACK(DSIZE, 1)); /* Prologue header */
    PUT(heap_listp + (2*WSIZE), PACK(DSIZE, 1)); /* Prologue footer */
    PUT(heap_listp + (3*WSIZE), PACK(0, 1)); /* Epilogue header */
    heap_listp += (2*WSIZE);
    
    /* Extend the empty heap with a free block of CHUNKSIZE bytes */
    if (extend_heap(CHUNKSIZE/WSIZE) == NULL)
        return -1;
    return 0;
}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    size_t asize;      /* Adjusted block size */
    size_t extendsize; /* Amount to extend heap if no fit */
    char *bp;

    if (size == 0)
        return NULL;

    /* Adjust block size to include overhead and alignment reqs. */
    if (size <= 2 * DSIZE)
        asize = 3 * DSIZE;
    else
        asize = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);

    /* Search the free list for a fit */
    if ((bp = find_fit(asize)) != NULL) {
        place(bp, asize);
        return bp;
    }

    /* No fit found. Get more memory and place the block */
    extendsize = MAX(asize, CHUNKSIZE);
    if ((bp = extend_heap(extendsize/WSIZE)) == NULL)
        return NULL;

    place(bp, asize);
    return bp;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
    size_t size = GET_SIZE(HDRP(ptr));

    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    coalesce(ptr);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;
    size_t asize;
    copySize = GET_SIZE(HDRP(oldptr)) - DSIZE;
    
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(oldptr)));
    size_t old_size = GET_SIZE(HDRP(oldptr));
    size_t next_size = GET_SIZE(HDRP(NEXT_BLKP(oldptr)));
    
    /* Adjust block size to include overhead and alignment reqs. */
    if (size <= 2 * DSIZE)
        asize = 3 * DSIZE;
    else
        asize = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);

    // if size is decreased, return the same pointer
    if (asize <= old_size) {
        /*if (old_size - asize >= (2 * DSIZE)) {
            PUT(HDRP(oldptr), PACK(asize, 1));
            PUT(FTRP(oldptr), PACK(asize, 1));
            void *next_bp = NEXT_BLKP(oldptr);
            PUT(HDRP(next_bp), PACK(old_size - asize, 0));
            PUT(FTRP(next_bp), PACK(old_size - asize, 0));
            coalesce(next_bp);
        } */
        return oldptr;
    }

    // if next block is free and enough to enlarge, return the same pointer
    if (!next_alloc && (copySize + next_size >= asize)) {
        delete_block(NEXT_BLKP(oldptr));
        PUT(FTRP(NEXT_BLKP(oldptr)), PACK(old_size + next_size, 1));
        PUT(HDRP(oldptr), PACK(old_size + next_size, 1));
        return oldptr;
    }

    newptr = mm_malloc(size);
    if (newptr == NULL)
      return NULL;
    if (size < copySize)
      copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}

/*--------------------------helper functions--------------------------*/
/*
 * extend_heap - Extend heap with free block and return its block pointer
 */
static void *extend_heap(size_t words)
{
    char *bp;
    size_t size;

    /* Allocate an even number of words to maintain alignment */
    size = (words % 2) ? (words+1) * WSIZE : words * WSIZE;
    if ((long)(bp = mem_sbrk(size)) == -1)
        return NULL;

    /* Initialize free block header/footer and the epilogue header */
    PUT(HDRP(bp), PACK(size, 0));         /* Free block header */
    PUT(FTRP(bp), PACK(size, 0));         /* Free block footer */
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* New epilogue header */

    /* Coalesce if the previous block was free */
    return coalesce(bp);
}

/*
 * coalesce - Boundary tag coalescing. Return ptr to coalesced block
 */
static void *coalesce(void *bp)
{
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if (prev_alloc && next_alloc) {            /* Case 1 */
        insert_block(bp);
        return bp;
    }

    else if (prev_alloc && !next_alloc) {      /* Case 2 */
        delete_block(NEXT_BLKP(bp));
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
        insert_block(bp);
    }

    else if (!prev_alloc && next_alloc) {      /* Case 3 */
        delete_block(PREV_BLKP(bp));
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
        insert_block(bp);
    }

    else {                                     /* Case 4 */
        delete_block(PREV_BLKP(bp));
        delete_block(NEXT_BLKP(bp));
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) +
            GET_SIZE(FTRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
        insert_block(bp);
    }
    return bp;
}

/*
 * find_fit - Find a fit for a block with asize bytes
 */
static void *find_fit(size_t asize)
{
    /* First-fit search */
    void *bp;
    // void *bp_good;
    // size_t min = (size_t) -1;
    // int preview = 0;

    for (int i = GET_INDEX(asize); i < 12; i++) {
        for (bp = *(char **)GET_SEG_PTR(i); bp != NULL; bp = GET_NEXT(bp)) {
            size_t curr_size = GET_SIZE(HDRP(bp));
            if (asize <= curr_size) { // remove GET_ALLOC check part
                // if (asize == curr_size) {
                //     return bp;
                // }
                // if (curr_size - asize < min) {
                //     min = curr_size - asize;
                //     bp_good = bp;
                // }
                // preview++;
                // if (preview > 1) {
                //     if (bp_good != NULL) {
                //         return bp_good;
                //     }
                //     break;
                // }
                return bp;
            }
        }
        // if (bp_good != NULL) {
        //     return bp_good;
        // }
    }
    return NULL; /* No fit */
}

/*
 * place - Place block of asize bytes at start of free block bp
 * and split if remainder would be at least minimum block size
 */
static void place(void *bp, size_t asize)
{
    size_t csize = GET_SIZE(HDRP(bp));
    delete_block(bp);

    if ((csize - asize) >= (3*DSIZE)) {
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize-asize, 0));
        PUT(FTRP(bp), PACK(csize-asize, 0));
        insert_block(bp);
    }
    else {
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
    }
}
/* Insert new node in free_heap_listp */
static void insert_block(void *bp) 
{
    char **root = (char **)GET_SEG_PTR(GET_INDEX(GET_SIZE(HDRP(bp))));
    PUT_PTR(NXTP(bp), *root);
    PUT_PTR(PRVP(bp), NULL);
    if (*root) {  
        PUT_PTR(PRVP(*root), bp);
    }

    *root = bp;
}
/* Delete new node in free_heap_listp */
static void delete_block(void *bp) 
{
    char **root = (char **)GET_SEG_PTR(GET_INDEX(GET_SIZE(HDRP(bp))));
    void *prev; 
    void *next = GET_NEXT(bp);
    if (prev = GET_PREV(bp)) {
        PUT_PTR(NXTP(prev), next);
    }
    else {
        *root = next;
    }

    if (next) {
        PUT_PTR(PRVP(next), prev);
    }
}