// Copyright (C) 2000, 2001 Stephen Cleary
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POOL_HPP
#define BOOST_POOL_HPP

#include <boost/config.hpp>  // for workarounds

// std::less, std::less_equal, std::greater
#include <functional>
// new[], delete[], std::nothrow
#include <new>
// std::size_t, std::ptrdiff_t
#include <cstddef>
// std::malloc, std::free
#include <cstdlib>
// std::invalid_argument
#include <exception>
// std::max
#include <algorithm>

#include <boost/pool/poolfwd.hpp>

// boost::integer::static_lcm
#include <boost/integer/common_factor_ct.hpp>
// boost::simple_segregated_storage
#include <boost/pool/simple_segregated_storage.hpp>
// boost::alignment_of
#include <boost/type_traits/alignment_of.hpp>
// BOOST_ASSERT
#include <boost/assert.hpp>

#ifdef BOOST_POOL_INSTRUMENT
#include <iostream>
#include<iomanip>
#endif
#ifdef BOOST_POOL_VALGRIND
#include <set>
#include <valgrind/memcheck.h>
#endif

#ifdef BOOST_NO_STDC_NAMESPACE
 namespace std { using ::malloc; using ::free; }
#endif

// There are a few places in this file where the expression "this->m" is used.
// This expression is used to force instantiation-time name lookup, which I am
//   informed is required for strict Standard compliance.  It's only necessary
//   if "m" is a member of a base class that is dependent on a template
//   parameter.
// Thanks to Jens Maurer for pointing this out!

/*!
  \file
  \brief Provides class \ref pool: a fast memory allocator that guarantees proper alignment of all allocated chunks,
  and which extends and generalizes the framework provided by the simple segregated storage solution.
  Also provides two UserAllocator classes which can be used in conjuction with \ref pool.
*/

/*!
  \mainpage Boost.Pool Memory Allocation Scheme

  \section intro_sec Introduction

   Pool allocation is a memory allocation scheme that is very fast, but limited in its usage.

   This Doxygen-style documentation is complementary to the
   full Quickbook-generated html and pdf documentation at www.boost.org.

  This page generated from file pool.hpp.

*/

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4127)  // Conditional expression is constant
#endif

 namespace boost
{

//! \brief Allocator used as the default template parameter for 
//! a <a href="boost_pool/pool/pooling.html#boost_pool.pool.pooling.user_allocator">UserAllocator</a>
//! template parameter.  Uses new and delete.
struct default_user_allocator_new_delete
{
  typedef std::size_t size_type; //!< An unsigned integral type that can represent the size of the largest object to be allocated.
  typedef std::ptrdiff_t difference_type; //!< A signed integral type that can represent the difference of any two pointers.

  static char * malloc BOOST_PREVENT_MACRO_SUBSTITUTION(const size_type bytes)
  { //! Attempts to allocate n bytes from the system. Returns 0 if out-of-memory
    return new (std::nothrow) char[bytes];
  }
  static void free BOOST_PREVENT_MACRO_SUBSTITUTION(char * const block)
  { //! Attempts to de-allocate block.
    //! \pre Block must have been previously returned from a call to UserAllocator::malloc.
    delete [] block;
  }
};

//! \brief <a href="boost_pool/pool/pooling.html#boost_pool.pool.pooling.user_allocator">UserAllocator</a>
//! used as template parameter for \ref pool and \ref object_pool.
//! Uses malloc and free internally.
struct default_user_allocator_malloc_free
{
  typedef std::size_t size_type; //!< An unsigned integral type that can represent the size of the largest object to be allocated.
  typedef std::ptrdiff_t difference_type; //!< A signed integral type that can represent the difference of any two pointers.

  static char * malloc BOOST_PREVENT_MACRO_SUBSTITUTION(const size_type bytes)
  { return static_cast<char *>((std::malloc)(bytes)); }
  static void free BOOST_PREVENT_MACRO_SUBSTITUTION(char * const block)
  { (std::free)(block); }
};

namespace details
{  //! Implemention only.

template <typename SizeType>
class PODptr
{ //! PODptr is a class that pretends to be a "pointer" to different class types
  //!  that don't really exist.  It provides member functions to access the "data"
  //!  of the "object" it points to.  Since these "class" types are of variable
  //!  size, and contains some information at the *end* of its memory
  //!  (for alignment reasons),
  //! PODptr must contain the size of this "class" as well as the pointer to this "object".

  /*! \details A PODptr holds the location and size of a memory block allocated from the system. 
  Each memory block is split logically into three sections:

  <b>Chunk area</b>. This section may be different sizes. PODptr does not care what the size of the chunks is, 
  but it does care (and keep track of) the total size of the chunk area.

  <b>Next pointer</b>. This section is always the same size for a given SizeType. It holds a pointer 
  to the location of the next memory block in the memory block list, or 0 if there is no such block.

  <b>Next size</b>. This section is always the same size for a given SizeType. It holds the size of the 
  next memory block in the memory block list.

The PODptr class just provides cleaner ways of dealing with raw memory blocks.

A PODptr object is either valid or invalid. An invalid PODptr is analogous to a null pointer.
The default constructor for PODptr will result in an invalid object.
Calling the member function invalidate will result in that object becoming invalid.
The member function valid can be used to test for validity.
*/
  public:
    typedef SizeType size_type;

  private:
    char * ptr;
    size_type sz;

    char * ptr_next_size() const
    {
      return (ptr + sz - sizeof(size_type));
    }
    char * ptr_next_ptr() const
    {
      return (ptr_next_size() -
          integer::static_lcm<sizeof(size_type), sizeof(void *)>::value);
    }

  public:
    PODptr(char * const nptr, const size_type nsize)
    :ptr(nptr), sz(nsize)
    {
      //! A PODptr may be created to point to a memory block by passing
      //! the address and size of that memory block into the constructor.
      //! A PODptr constructed in this way is valid.
    }
    PODptr()
    :  ptr(0), sz(0)
    { //! default constructor for PODptr will result in an invalid object.
    }

    bool valid() const
    { //! A PODptr object is either valid or invalid.
      //! An invalid PODptr is analogous to a null pointer.
      //! \returns true if PODptr is valid, false if invalid.
      return (begin() != 0);
    }
    void invalidate()
    { //! Make object invalid.
      begin() = 0;
    }
    char * & begin()
    { //! Each PODptr keeps the address and size of its memory block.
      //! \returns The address of its memory block.
      return ptr;
  }
    char * begin() const
    { //! Each PODptr keeps the address and size of its memory block.
      //! \return The address of its memory block.
      return ptr;
    }
    char * end() const
    { //! \returns begin() plus element_size (a 'past the end' value).
      return ptr_next_ptr();
    }
    size_type total_size() const
    { //! Each PODptr keeps the address and size of its memory block.
      //! The address may be read or written by the member functions begin.
      //! The size of the memory block may only be read,
      //! \returns size of the memory block.
      return sz;
    }
    size_type element_size() const
    { //! \returns size of element pointer area.
      return static_cast<size_type>(sz - sizeof(size_type) -
          integer::static_lcm<sizeof(size_type), sizeof(void *)>::value);
    }

    size_type & next_size() const
    { //!
      //! \returns next_size.
      return *(static_cast<size_type *>(static_cast<void*>((ptr_next_size()))));
    }
    char * & next_ptr() const
    {  //! \returns pointer to next pointer area.
      return *(static_cast<char **>(static_cast<void*>(ptr_next_ptr())));
    }

    PODptr next() const
    { //! \returns next PODptr.
      return PODptr<size_type>(next_ptr(), next_size());
    }
    void next(const PODptr & arg) const
    { //! Sets next PODptr.
      next_ptr() = arg.begin();
      next_size() = arg.total_size();
    }
}; // class PODptr
} // namespace details

#ifndef BOOST_POOL_VALGRIND
/*!
  \brief A fast memory allocator that guarantees proper alignment of all allocated chunks.

  \details Whenever an object of type pool needs memory from the system,
  it will request it from its UserAllocator template parameter.
  The amount requested is determined using a doubling algorithm;
  that is, each time more system memory is allocated,
  the amount of system memory requested is doubled.

  Users may control the doubling algorithm by using the following extensions:

  Users may pass an additional constructor parameter to pool.
  This parameter is of type size_type,
  and is the number of chunks to request from the system
  the first time that object needs to allocate system memory.
  The default is 32. This parameter may not be 0.

  Users may also pass an optional third parameter to pool's
  constructor.  This parameter is of type size_type,
  and sets a maximum size for allocated chunks.  When this
  parameter takes the default value of 0, then there is no upper
  limit on chunk size.

  Finally, if the doubling algorithm results in no memory
  being allocated, the pool will backtrack just once, halving
  the chunk size and trying again.

  <b>UserAllocator type</b> - the method that the Pool will use to allocate memory from the system.

  There are essentially two ways to use class pool: the client can call \ref malloc() and \ref free() to allocate
  and free single chunks of memory, this is the most efficient way to use a pool, but does not allow for
  the efficient allocation of arrays of chunks.  Alternatively, the client may call \ref ordered_malloc() and \ref
  ordered_free(), in which case the free list is maintained in an ordered state, and efficient allocation of arrays
  of chunks are possible.  However, this latter option can suffer from poor performance when large numbers of
  allocations are performed.

*/
template <typename UserAllocator>
class pool: protected simple_segregated_storage < typename UserAllocator::size_type >
{
  public:
    typedef UserAllocator user_allocator; //!< User allocator.
    typedef typename UserAllocator::size_type size_type;  //!< An unsigned integral type that can represent the size of the largest object to be allocated.
    typedef typename UserAllocator::difference_type difference_type;  //!< A signed integral type that can represent the difference of any two pointers.

  private:
    BOOST_STATIC_CONSTANT(size_type, min_alloc_size =
        (::boost::integer::static_lcm<sizeof(void *), sizeof(size_type)>::value) );
    BOOST_STATIC_CONSTANT(size_type, min_align =
        (::boost::integer::static_lcm< ::boost::alignment_of<void *>::value, ::boost::alignment_of<size_type>::value>::value) );

    //! \returns 0 if out-of-memory.
    //! Called if malloc/ordered_malloc needs to resize the free list.
    void * malloc_need_resize(); //! Called if malloc needs to resize the free list.
    void * ordered_malloc_need_resize();  //! Called if ordered_malloc needs to resize the free list.

  protected:
    details::PODptr<size_type> list; //!< List structure holding ordered blocks.

    simple_segregated_storage<size_type> & store()
    { //! \returns pointer to store.
      return *this;
    }
    const simple_segregated_storage<size_type> & store() const
    { //! \returns pointer to store.
      return *this;
    }
    const size_type requested_size;
    size_type next_size;
    size_type start_size;
    size_type max_size;

    //! finds which POD in the list 'chunk' was allocated from.
    details::PODptr<size_type> find_POD(void * const chunk) const;

    // is_from() tests a chunk to determine if it belongs in a block.
    static bool is_from(void * const chunk, char * const i,
        const size_type sizeof_i)
    { //! \param chunk chunk to check if is from this pool.
      //! \param i memory chunk at i with element sizeof_i.
      //! \param sizeof_i element size (size of the chunk area of that block, not the total size of that block).
      //! \returns true if chunk was allocated or may be returned.
      //! as the result of a future allocation.
      //!
      //! Returns false if chunk was allocated from some other pool,
      //! or may be returned as the result of a future allocation from some other pool.
      //! Otherwise, the return value is meaningless.
      //!
      //! Note that this function may not be used to reliably test random pointer values.

      // We use std::less_equal and std::less to test 'chunk'
      //  against the array bounds because standard operators
      //  may return unspecified results.
      // This is to ensure portability.  The operators < <= > >= are only
      //  defined for pointers to objects that are 1) in the same array, or
      //  2) subobjects of the same object [5.9/2].
      // The functor objects guarantee a total order for any pointer [20.3.3/8]
      std::less_equal<void *> lt_eq;
      std::less<void *> lt;
      return (lt_eq(i, chunk) && lt(chunk, i + sizeof_i));
    }

    size_type alloc_size() const
    { //!  Calculated size of the memory chunks that will be allocated by this Pool.
      //! \returns allocated size.
      // For alignment reasons, this used to be defined to be lcm(requested_size, sizeof(void *), sizeof(size_type)),
      // but is now more parsimonious: just rounding up to the minimum required alignment of our housekeeping data
      // when required.  This works provided all alignments are powers of two.
      size_type s = (std::max)(requested_size, min_alloc_size);
      size_type rem = s % min_align;
      if(rem)
         s += min_align - rem;
      BOOST_ASSERT(s >= min_alloc_size);
      BOOST_ASSERT(s % min_align == 0);
      return s;
    }

    static void * & nextof(void * const ptr)
    { //! \returns Pointer dereferenced.
      //! (Provided and used for the sake of code readability :)
      return *(static_cast<void **>(ptr));
    }

  public:
    // pre: npartition_size != 0 && nnext_size != 0
    explicit pool(const size_type nrequested_size,
        const size_type nnext_size = 32,
        const size_type nmax_size = 0)
    :
        list(0, 0), requested_size(nrequested_size), next_size(nnext_size), start_size(nnext_size),max_size(nmax_size)
    { //!   Constructs a new empty Pool that can be used to allocate chunks of size RequestedSize.
      //! \param nrequested_size  Requested chunk size
      //! \param  nnext_size parameter is of type size_type,
      //!   is the number of chunks to request from the system
      //!   the first time that object needs to allocate system memory.
      //!   The default is 32. This parameter may not be 0.
      //! \param nmax_size is the maximum number of chunks to allocate in one block.
    }

    ~pool()
    { //!   Destructs the Pool, freeing its list of memory blocks.
      purge_memory();
    }

    // Releases memory blocks that don't have chunks allocated
    // pre: lists are ordered
    //  Returns true if memory was actually deallocated
    bool release_memory();

    // Releases *all* memory blocks, even if chunks are still allocated
    //  Returns true if memory was actually deallocated
    bool purge_memory();

    size_type get_next_size() const
    { //! Number of chunks to request from the system the next time that object needs to allocate system memory. This value should never be 0.
      //! \returns next_size;
      return next_size;
    }
    void set_next_size(const size_type nnext_size)
    { //! Set number of chunks to request from the system the next time that object needs to allocate system memory. This value should never be set to 0.
      //! \returns nnext_size.
      next_size = start_size = nnext_size;
    }
    size_type get_max_size() const
    { //! \returns max_size.
      return max_size;
    }
    void set_max_size(const size_type nmax_size)
    { //! Set max_size.
      max_size = nmax_size;
    }
    size_type get_requested_size() const
    { //!   \returns the requested size passed into the constructor.
      //! (This value will not change during the lifetime of a Pool object).
      return requested_size;
    }

    // Both malloc and ordered_malloc do a quick inlined check first for any
    //  free chunks.  Only if we need to get another memory block do we call
    //  the non-inlined *_need_resize() functions.
    // Returns 0 if out-of-memory
    void * malloc BOOST_PREVENT_MACRO_SUBSTITUTION()
    { //! Allocates a chunk of memory. Searches in the list of memory blocks
      //! for a block that has a free chunk, and returns that free chunk if found.
      //! Otherwise, creates a new memory block, adds its free list to pool's free list,
      //! \returns a free chunk from that block.
      //! If a new memory block cannot be allocated, returns 0. Amortized O(1).
      // Look for a non-empty storage
      if (!store().empty())
        return (store().malloc)();
      return malloc_need_resize();
    }

    void * ordered_malloc()
    { //! Same as malloc, only merges the free lists, to preserve order. Amortized O(1).
      //! \returns a free chunk from that block.
      //! If a new memory block cannot be allocated, returns 0. Amortized O(1).
      // Look for a non-empty storage
      if (!store().empty())
        return (store().malloc)();
      return ordered_malloc_need_resize();
    }

    // Returns 0 if out-of-memory
    // Allocate a contiguous section of n chunks
    void * ordered_malloc(size_type n);
      //! Same as malloc, only allocates enough contiguous chunks to cover n * requested_size bytes. Amortized O(n).
      //! \returns a free chunk from that block.
      //! If a new memory block cannot be allocated, returns 0. Amortized O(1).

    // pre: 'chunk' must have been previously
    //        returned by *this.malloc().
    void free BOOST_PREVENT_MACRO_SUBSTITUTION(void * const chunk)
    { //!   Deallocates a chunk of memory. Note that chunk may not be 0. O(1).
      //!
      //! Chunk must have been previously returned by t.malloc() or t.ordered_malloc().
      //! Assumes that chunk actually refers to a block of chunks
      //! spanning n * partition_sz bytes.
      //! deallocates each chunk in that block.
      //! Note that chunk may not be 0. O(n).
      (store().free)(chunk);
    }

    // pre: 'chunk' must have been previously
    //        returned by *this.malloc().
    void ordered_free(void * const chunk)
    { //! Same as above, but is order-preserving.
      //!
      //! Note that chunk may not be 0. O(N) with respect to the size of the free list.
      //! chunk must have been previously returned by t.malloc() or t.ordered_malloc().
      store().ordered_free(chunk);
    }

    // pre: 'chunk' must have been previously
    //        returned by *this.malloc(n).
    void free BOOST_PREVENT_MACRO_SUBSTITUTION(void * const chunks, const size_type n)
    { //! Assumes that chunk actually refers to a block of chunks.
      //!
      //! chunk must have been previously returned by t.ordered_malloc(n)
      //! spanning n * partition_sz bytes.
      //! Deallocates each chunk in that block.
      //! Note that chunk may not be 0. O(n).
      const size_type partition_size = alloc_size();
      const size_type total_req_size = n * requested_size;
      const size_type num_chunks = total_req_size / partition_size +
          ((total_req_size % partition_size) ? true : false);

      store().free_n(chunks, num_chunks, partition_size);
    }

    // pre: 'chunk' must have been previously
    //        returned by *this.malloc(n).
    void ordered_free(void * const chunks, const size_type n)
    { //! Assumes that chunk actually refers to a block of chunks spanning n * partition_sz bytes;
      //! deallocates each chunk in that block.
      //!
      //! Note that chunk may not be 0. Order-preserving. O(N + n) where N is the size of the free list.
      //! chunk must have been previously returned by t.malloc() or t.ordered_malloc().

      const size_type partition_size = alloc_size();
      const size_type total_req_size = n * requested_size;
      const size_type num_chunks = total_req_size / partition_size +
          ((total_req_size % partition_size) ? true : false);

      store().ordered_free_n(chunks, num_chunks, partition_size);
    }

    // is_from() tests a chunk to determine if it was allocated from *this
    bool is_from(void * const chunk) const
    { //! \returns Returns true if chunk was allocated from u or
      //! may be returned as the result of a future allocation from u.
      //! Returns false if chunk was allocated from some other pool or
      //! may be returned as the result of a future allocation from some other pool.
      //! Otherwise, the return value is meaningless.
      //! Note that this function may not be used to reliably test random pointer values.
      return (find_POD(chunk).valid());
    }
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
template <typename UserAllocator>
typename pool<UserAllocator>::size_type const pool<UserAllocator>::min_alloc_size;
template <typename UserAllocator>
typename pool<UserAllocator>::size_type const pool<UserAllocator>::min_align;
#endif

template <typename UserAllocator>
bool pool<UserAllocator>::release_memory()
{ //! pool must be ordered. Frees every memory block that doesn't have any allocated chunks.
  //! \returns true if at least one memory block was freed.

  // ret is the return value: it will be set to true when we actually call
  //  UserAllocator::free(..)
  bool ret = false;

  // This is a current & previous iterator pair over the memory block list
  details::PODptr<size_type> ptr = list;
  details::PODptr<size_type> prev;

  // This is a current & previous iterator pair over the free memory chunk list
  //  Note that "prev_free" in this case does NOT point to the previous memory
  //  chunk in the free list, but rather the last free memory chunk before the
  //  current block.
  void * free_p = this->first;
  void * prev_free_p = 0;

  const size_type partition_size = alloc_size();

  // Search through all the all the allocated memory blocks
  while (ptr.valid())
  {
    // At this point:
    //  ptr points to a valid memory block
    //  free_p points to either:
    //    0 if there are no more free chunks
    //    the first free chunk in this or some next memory block
    //  prev_free_p points to either:
    //    the last free chunk in some previous memory block
    //    0 if there is no such free chunk
    //  prev is either:
    //    the PODptr whose next() is ptr
    //    !valid() if there is no such PODptr

    // If there are no more free memory chunks, then every remaining
    //  block is allocated out to its fullest capacity, and we can't
    //  release any more memory
    if (free_p == 0)
      break;

    // We have to check all the chunks.  If they are *all* free (i.e., present
    //  in the free list), then we can free the block.
    bool all_chunks_free = true;

    // Iterate 'i' through all chunks in the memory block
    // if free starts in the memory block, be careful to keep it there
    void * saved_free = free_p;
    for (char * i = ptr.begin(); i != ptr.end(); i += partition_size)
    {
      // If this chunk is not free
      if (i != free_p)
      {
        // We won't be able to free this block
        all_chunks_free = false;

        // free_p might have travelled outside ptr
        free_p = saved_free;
        // Abort searching the chunks; we won't be able to free this
        //  block because a chunk is not free.
        break;
      }

      // We do not increment prev_free_p because we are in the same block
      free_p = nextof(free_p);
    }

    // post: if the memory block has any chunks, free_p points to one of them
    // otherwise, our assertions above are still valid

    const details::PODptr<size_type> next = ptr.next();

    if (!all_chunks_free)
    {
      if (is_from(free_p, ptr.begin(), ptr.element_size()))
      {
        std::less<void *> lt;
        void * const end = ptr.end();
        do
        {
          prev_free_p = free_p;
          free_p = nextof(free_p);
        } while (free_p && lt(free_p, end));
      }
      // This invariant is now restored:
      //     free_p points to the first free chunk in some next memory block, or
      //       0 if there is no such chunk.
      //     prev_free_p points to the last free chunk in this memory block.

      // We are just about to advance ptr.  Maintain the invariant:
      // prev is the PODptr whose next() is ptr, or !valid()
      // if there is no such PODptr
      prev = ptr;
    }
    else
    {
      // All chunks from this block are free

      // Remove block from list
      if (prev.valid())
        prev.next(next);
      else
        list = next;

      // Remove all entries in the free list from this block
      if (prev_free_p != 0)
        nextof(prev_free_p) = free_p;
      else
        this->first = free_p;

      // And release memory
      (UserAllocator::free)(ptr.begin());
      ret = true;
    }

    // Increment ptr
    ptr = next;
  }

  next_size = start_size;
  return ret;
}

template <typename UserAllocator>
bool pool<UserAllocator>::purge_memory()
{ //! pool must be ordered.
  //! Frees every memory block.
  //!
  //! This function invalidates any pointers previously returned
  //! by allocation functions of t.
  //! \returns true if at least one memory block was freed.

  details::PODptr<size_type> iter = list;

  if (!iter.valid())
    return false;

  do
  {
    // hold "next" pointer
    const details::PODptr<size_type> next = iter.next();

    // delete the storage
    (UserAllocator::free)(iter.begin());

    // increment iter
    iter = next;
  } while (iter.valid());

  list.invalidate();
  this->first = 0;
  next_size = start_size;

  return true;
}

template <typename UserAllocator>
void * pool<UserAllocator>::malloc_need_resize()
{ //! No memory in any of our storages; make a new storage,
  //!  Allocates chunk in newly malloc aftert resize.
  //! \returns pointer to chunk.
  size_type partition_size = alloc_size();
  size_type POD_size = static_cast<size_type>(next_size * partition_size +
      integer::static_lcm<sizeof(size_type), sizeof(void *)>::value + sizeof(size_type));
  char * ptr = (UserAllocator::malloc)(POD_size);
  if (ptr == 0)
  {
     if(next_size > 4)
     {
        next_size >>= 1;
        partition_size = alloc_size();
        POD_size = static_cast<size_type>(next_size * partition_size +
            integer::static_lcm<sizeof(size_type), sizeof(void *)>::value + sizeof(size_type));
        ptr = (UserAllocator::malloc)(POD_size);
     }
     if(ptr == 0)
        return 0;
  }
  const details::PODptr<size_type> node(ptr, POD_size);

  BOOST_USING_STD_MIN();
  if(!max_size)
    next_size <<= 1;
  else if( next_size*partition_size/requested_size < max_size)
    next_size = min BOOST_PREVENT_MACRO_SUBSTITUTION(next_size << 1, max_size*requested_size/ partition_size);

  //  initialize it,
  store().add_block(node.begin(), node.element_size(), partition_size);

  //  insert it into the list,
  node.next(list);
  list = node;

  //  and return a chunk from it.
  return (store().malloc)();
}

template <typename UserAllocator>
void * pool<UserAllocator>::ordered_malloc_need_resize()
{ //! No memory in any of our storages; make a new storage,
  //! \returns pointer to new chunk.
  size_type partition_size = alloc_size();
  size_type POD_size = static_cast<size_type>(next_size * partition_size +
      integer::static_lcm<sizeof(size_type), sizeof(void *)>::value + sizeof(size_type));
  char * ptr = (UserAllocator::malloc)(POD_size);
  if (ptr == 0)
  {
     if(next_size > 4)
     {
       next_size >>= 1;
       partition_size = alloc_size();
       POD_size = static_cast<size_type>(next_size * partition_size +
                    integer::static_lcm<sizeof(size_type), sizeof(void *)>::value + sizeof(size_type));
       ptr = (UserAllocator::malloc)(POD_size);
     }
     if(ptr == 0)
       return 0;
  }
  const details::PODptr<size_type> node(ptr, POD_size);

  BOOST_USING_STD_MIN();
  if(!max_size)
    next_size <<= 1;
  else if( next_size*partition_size/requested_size < max_size)
    next_size = min BOOST_PREVENT_MACRO_SUBSTITUTION(next_size << 1, max_size*requested_size/ partition_size);

  //  initialize it,
  //  (we can use "add_block" here because we know that
  //  the free list is empty, so we don't have to use
  //  the slower ordered version)
  store().add_ordered_block(node.begin(), node.element_size(), partition_size);

  //  insert it into the list,
  //   handle border case
  if (!list.valid() || std::greater<void *>()(list.begin(), node.begin()))
  {
    node.next(list);
    list = node;
  }
  else
  {
    details::PODptr<size_type> prev = list;

    while (true)
    {
      // if we're about to hit the end or
      //  if we've found where "node" goes
      if (prev.next_ptr() == 0
          || std::greater<void *>()(prev.next_ptr(), node.begin()))
        break;

      prev = prev.next();
    }

    node.next(prev.next());
    prev.next(node);
  }
  //  and return a chunk from it.
  return (store().malloc)();
}

template <typename UserAllocator>
void * pool<UserAllocator>::ordered_malloc(const size_type n)
{ //! Gets address of a chunk n, allocating new memory if not already available.
  //! \returns Address of chunk n if allocated ok.
  //! \returns 0 if not enough memory for n chunks.

  const size_type partition_size = alloc_size();
  const size_type total_req_size = n * requested_size;
  const size_type num_chunks = total_req_size / partition_size +
      ((total_req_size % partition_size) ? true : false);

  void * ret = store().malloc_n(num_chunks, partition_size);

#ifdef BOOST_POOL_INSTRUMENT
  std::cout << "Allocating " << n << " chunks from pool of size " << partition_size << std::endl;
#endif
  if ((ret != 0) || (n == 0))
    return ret;

#ifdef BOOST_POOL_INSTRUMENT
  std::cout << "Cache miss, allocating another chunk...\n";
#endif

  // Not enough memory in our storages; make a new storage,
  BOOST_USING_STD_MAX();
  next_size = max BOOST_PREVENT_MACRO_SUBSTITUTION(next_size, num_chunks);
  size_type POD_size = static_cast<size_type>(next_size * partition_size +
      integer::static_lcm<sizeof(size_type), sizeof(void *)>::value + sizeof(size_type));
  char * ptr = (UserAllocator::malloc)(POD_size);
  if (ptr == 0)
  {
     if(num_chunks < next_size)
     {
        // Try again with just enough memory to do the job, or at least whatever we
        // allocated last time:
        next_size >>= 1;
        next_size = max BOOST_PREVENT_MACRO_SUBSTITUTION(next_size, num_chunks);
        POD_size = static_cast<size_type>(next_size * partition_size +
            integer::static_lcm<sizeof(size_type), sizeof(void *)>::value + sizeof(size_type));
        ptr = (UserAllocator::malloc)(POD_size);
     }
     if(ptr == 0)
       return 0;
  }
  const details::PODptr<size_type> node(ptr, POD_size);

  // Split up block so we can use what wasn't requested.
  if (next_size > num_chunks)
    store().add_ordered_block(node.begin() + num_chunks * partition_size,
        node.element_size() - num_chunks * partition_size, partition_size);

  BOOST_USING_STD_MIN();
  if(!max_size)
    next_size <<= 1;
  else if( next_size*partition_size/requested_size < max_size)
    next_size = min BOOST_PREVENT_MACRO_SUBSTITUTION(next_size << 1, max_size*requested_size/ partition_size);

  //  insert it into the list,
  //   handle border case.
  if (!list.valid() || std::greater<void *>()(list.begin(), node.begin()))
  {
    node.next(list);
    list = node;
  }
  else
  {
    details::PODptr<size_type> prev = list;

    while (true)
    {
      // if we're about to hit the end, or if we've found where "node" goes.
      if (prev.next_ptr() == 0
          || std::greater<void *>()(prev.next_ptr(), node.begin()))
        break;

      prev = prev.next();
    }

    node.next(prev.next());
    prev.next(node);
  }

  //  and return it.
  return node.begin();
}

template <typename UserAllocator>
details::PODptr<typename pool<UserAllocator>::size_type>
pool<UserAllocator>::find_POD(void * const chunk) const
{ //! find which PODptr storage memory that this chunk is from.
  //! \returns the PODptr that holds this chunk.
  // Iterate down list to find which storage this chunk is from.
  details::PODptr<size_type> iter = list;
  while (iter.valid())
  {
    if (is_from(chunk, iter.begin(), iter.element_size()))
      return iter;
    iter = iter.next();
  }

  return iter;
}

#else // BOOST_POOL_VALGRIND

template<typename UserAllocator> 
class pool 
{
public:
  // types
  typedef UserAllocator                  user_allocator;   // User allocator. 
  typedef typename UserAllocator::size_type       size_type;        // An unsigned integral type that can represent the size of the largest object to be allocated. 
  typedef typename UserAllocator::difference_type difference_type;  // A signed integral type that can represent the difference of any two pointers. 

  // construct/copy/destruct
  explicit pool(const size_type s, const size_type = 32, const size_type m = 0) : chunk_size(s), max_alloc_size(m) {}
  ~pool()
  {
     purge_memory();
  }

  bool release_memory()
  {
     bool ret = free_list.empty() ? false : true;
     for(std::set<void*>::iterator pos = free_list.begin(); pos != free_list.end(); ++pos)
     {
        (user_allocator::free)(static_cast<char*>(*pos));
     }
     free_list.clear();
     return ret;
  }
  bool purge_memory()
  {
     bool ret = free_list.empty() && used_list.empty() ? false : true;
     for(std::set<void*>::iterator pos = free_list.begin(); pos != free_list.end(); ++pos)
     {
        (user_allocator::free)(static_cast<char*>(*pos));
     }
     free_list.clear();
     for(std::set<void*>::iterator pos = used_list.begin(); pos != used_list.end(); ++pos)
     {
        (user_allocator::free)(static_cast<char*>(*pos));
     }
     used_list.clear();
     return ret;
  }
  size_type get_next_size() const
  {
     return 1;
  }
  void set_next_size(const size_type){}
  size_type get_max_size() const
  {
     return max_alloc_size;
  }
  void set_max_size(const size_type s)
  {
     max_alloc_size = s;
  }
  size_type get_requested_size() const
  {
     return chunk_size;
  }
  void * malloc BOOST_PREVENT_MACRO_SUBSTITUTION()
  {
     void* ret;
     if(free_list.empty())
     {
        ret = (user_allocator::malloc)(chunk_size);
        VALGRIND_MAKE_MEM_UNDEFINED(ret, chunk_size);
     }
     else
     {
        ret = *free_list.begin();
        free_list.erase(free_list.begin());
        VALGRIND_MAKE_MEM_UNDEFINED(ret, chunk_size);
     }
     used_list.insert(ret);
     return ret;
  }
  void * ordered_malloc()
  {
     return (this->malloc)();
  }
  void * ordered_malloc(size_type n)
  {
     if(max_alloc_size && (n > max_alloc_size))
        return 0;
     void* ret = (user_allocator::malloc)(chunk_size * n);
     used_list.insert(ret);
     return ret;
  }
  void free BOOST_PREVENT_MACRO_SUBSTITUTION(void *const chunk)
  {
     BOOST_ASSERT(used_list.count(chunk) == 1);
     BOOST_ASSERT(free_list.count(chunk) == 0);
     used_list.erase(chunk);
     free_list.insert(chunk);
     VALGRIND_MAKE_MEM_NOACCESS(chunk, chunk_size);
  }
  void ordered_free(void *const chunk)
  {
     return (this->free)(chunk);
  }
  void free BOOST_PREVENT_MACRO_SUBSTITUTION(void *const chunk, const size_type)
  {
     BOOST_ASSERT(used_list.count(chunk) == 1);
     BOOST_ASSERT(free_list.count(chunk) == 0);
     used_list.erase(chunk);
     (user_allocator::free)(static_cast<char*>(chunk));
  }
  void ordered_free(void *const chunk, const size_type n)
  {
     (this->free)(chunk, n);
  }
  bool is_from(void *const chunk) const
  {
     return used_list.count(chunk) || free_list.count(chunk);
  }

protected:
   size_type chunk_size, max_alloc_size;
   std::set<void*> free_list, used_list;
};

#endif

} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // #ifdef BOOST_POOL_HPP


/* pool.hpp
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
*/