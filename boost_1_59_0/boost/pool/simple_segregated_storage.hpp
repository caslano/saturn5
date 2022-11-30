// Copyright (C) 2000, 2001 Stephen Cleary
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_SIMPLE_SEGREGATED_STORAGE_HPP
#define BOOST_SIMPLE_SEGREGATED_STORAGE_HPP

/*!
  \file
  \brief Simple Segregated Storage.
  \details A simple segregated storage implementation:
  simple segregated storage is the basic idea behind the Boost Pool library.
  Simple segregated storage is the simplest, and probably the fastest,
  memory allocation/deallocation algorithm.
  It begins by partitioning a memory block into fixed-size chunks.
  Where the block comes from is not important until implementation time.
  A Pool is some object that uses Simple Segregated Storage in this fashion.
*/

// std::greater
#include <functional>

#include <boost/pool/poolfwd.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4127)  // Conditional expression is constant
#endif

#ifdef BOOST_POOL_VALIDATE
#  define BOOST_POOL_VALIDATE_INTERNALS validate();
#else
#  define BOOST_POOL_VALIDATE_INTERNALS
#endif

namespace boost {

/*! 

\brief Simple Segregated Storage is the simplest, and probably the fastest,
memory allocation/deallocation algorithm.  It is responsible for
partitioning a memory block into fixed-size chunks: where the block comes from 
is determined by the client of the class.

\details Template class simple_segregated_storage controls access to a free list of memory chunks. 
Please note that this is a very simple class, with preconditions on almost all its functions. It is intended to 
be the fastest and smallest possible quick memory allocator - e.g., something to use in embedded systems. 
This class delegates many difficult preconditions to the user (i.e., alignment issues).

An object of type simple_segregated_storage<SizeType>  is empty  if its free list is empty. 
If it is not empty, then it is ordered  if its free list is ordered. A free list is ordered if repeated calls 
to <tt>malloc()</tt> will result in a constantly-increasing sequence of values, as determined by <tt>std::less<void *></tt>. 
A member function is <i>order-preserving</i> if the free list maintains its order orientation (that is, an 
ordered free list is still ordered after the member function call).

*/
template <typename SizeType>
class simple_segregated_storage
{
  public:
    typedef SizeType size_type;

  private:
    simple_segregated_storage(const simple_segregated_storage &);
    void operator=(const simple_segregated_storage &);

    static void * try_malloc_n(void * & start, size_type n,
        size_type partition_size);

  protected:
    void * first; /*!< This data member is the free list.
      It points to the first chunk in the free list,
      or is equal to 0 if the free list is empty.
    */

    void * find_prev(void * ptr);

    // for the sake of code readability :)
    static void * & nextof(void * const ptr)
    { //! The return value is just *ptr cast to the appropriate type. ptr must not be 0. (For the sake of code readability :)
    //! As an example, let us assume that we want to truncate the free list after the first chunk.
    //! That is, we want to set *first to 0; this will result in a free list with only one entry.
    //! The normal way to do this is to first cast first to a pointer to a pointer to void,
    //! and then dereference and assign (*static_cast<void **>(first) = 0;).
    //! This can be done more easily through the use of this convenience function (nextof(first) = 0;).
    //! \returns dereferenced pointer.
      return *(static_cast<void **>(ptr));
    }

  public:
    // Post: empty()
    simple_segregated_storage()
    :first(0)
    { //! Construct empty storage area.
      //! \post empty()
    }

    static void * segregate(void * block,
        size_type nsz, size_type npartition_sz,
        void * end = 0);

    // Same preconditions as 'segregate'
    // Post: !empty()
    void add_block(void * const block,
        const size_type nsz, const size_type npartition_sz)
    { //! Add block
      //! Segregate this block and merge its free list into the
      //!  free list referred to by "first".
      //! \pre Same as segregate.
      //!  \post !empty()
      BOOST_POOL_VALIDATE_INTERNALS
      first = segregate(block, nsz, npartition_sz, first);
      BOOST_POOL_VALIDATE_INTERNALS
    }

    // Same preconditions as 'segregate'
    // Post: !empty()
    void add_ordered_block(void * const block,
        const size_type nsz, const size_type npartition_sz)
    { //! add block (ordered into list)
      //! This (slower) version of add_block segregates the
      //!  block and merges its free list into our free list
      //!  in the proper order.
       BOOST_POOL_VALIDATE_INTERNALS
      // Find where "block" would go in the free list
      void * const loc = find_prev(block);

      // Place either at beginning or in middle/end
      if (loc == 0)
        add_block(block, nsz, npartition_sz);
      else
        nextof(loc) = segregate(block, nsz, npartition_sz, nextof(loc));
      BOOST_POOL_VALIDATE_INTERNALS
    }

    // default destructor.

    bool empty() const
    { //! \returns true only if simple_segregated_storage is empty.
      return (first == 0);
    }

    void * malloc BOOST_PREVENT_MACRO_SUBSTITUTION()
    { //! Create a chunk.
      //!  \pre !empty()
      //! Increment the "first" pointer to point to the next chunk.
       BOOST_POOL_VALIDATE_INTERNALS
      void * const ret = first;

      // Increment the "first" pointer to point to the next chunk.
      first = nextof(first);
      BOOST_POOL_VALIDATE_INTERNALS
      return ret;
    }

    void free BOOST_PREVENT_MACRO_SUBSTITUTION(void * const chunk)
    { //! Free a chunk.
      //! \pre chunk was previously returned from a malloc() referring to the same free list.
      //! \post !empty()
       BOOST_POOL_VALIDATE_INTERNALS
      nextof(chunk) = first;
      first = chunk;
      BOOST_POOL_VALIDATE_INTERNALS
    }

    void ordered_free(void * const chunk)
    { //! This (slower) implementation of 'free' places the memory
      //!  back in the list in its proper order.
      //! \pre chunk was previously returned from a malloc() referring to the same free list
      //! \post !empty().

      // Find where "chunk" goes in the free list
       BOOST_POOL_VALIDATE_INTERNALS
      void * const loc = find_prev(chunk);

      // Place either at beginning or in middle/end.
      if (loc == 0)
        (free)(chunk);
      else
      {
        nextof(chunk) = nextof(loc);
        nextof(loc) = chunk;
      }
      BOOST_POOL_VALIDATE_INTERNALS
    }

   void * malloc_n(size_type n, size_type partition_size);
    
    //! \pre chunks was previously allocated from *this with the same
    //!   values for n and partition_size.
    //! \post !empty()
    //! \note If you're allocating/deallocating n a lot, you should
    //!  be using an ordered pool.
    void free_n(void * const chunks, const size_type n,
        const size_type partition_size)
    { 
       BOOST_POOL_VALIDATE_INTERNALS
      if(n != 0)
        add_block(chunks, n * partition_size, partition_size);
       BOOST_POOL_VALIDATE_INTERNALS
    }

    // pre: chunks was previously allocated from *this with the same
    //   values for n and partition_size.
    // post: !empty()
    void ordered_free_n(void * const chunks, const size_type n,
        const size_type partition_size)
    { //! Free n chunks from order list.
      //! \pre chunks was previously allocated from *this with the same
      //!   values for n and partition_size.

      //! \pre n should not be zero (n == 0 has no effect).
       BOOST_POOL_VALIDATE_INTERNALS
      if(n != 0)
        add_ordered_block(chunks, n * partition_size, partition_size);
       BOOST_POOL_VALIDATE_INTERNALS
    }
#ifdef BOOST_POOL_VALIDATE
    void validate()
    {
       int index = 0;
       void* old = 0;
       void* ptr = first;
       while(ptr)
       {
          void* pt = nextof(ptr); // trigger possible segfault *before* we update variables
          ++index;
          old = ptr;
          ptr = nextof(ptr);
       }
    }
#endif
};

//! Traverses the free list referred to by "first",
//!  and returns the iterator previous to where
//!  "ptr" would go if it was in the free list.
//!  Returns 0 if "ptr" would go at the beginning
//!  of the free list (i.e., before "first").

//! \note Note that this function finds the location previous to where ptr would go
//! if it was in the free list.
//! It does not find the entry in the free list before ptr
//! (unless ptr is already in the free list).
//! Specifically, find_prev(0) will return 0,
//! not the last entry in the free list.
//! \returns location previous to where ptr would go if it was in the free list.
template <typename SizeType>
void * simple_segregated_storage<SizeType>::find_prev(void * const ptr)
{ 
  // Handle border case.
  if (first == 0 || std::greater<void *>()(first, ptr))
    return 0;

  void * iter = first;
  while (true)
  {
    // if we're about to hit the end, or if we've found where "ptr" goes.
    if (nextof(iter) == 0 || std::greater<void *>()(nextof(iter), ptr))
      return iter;

    iter = nextof(iter);
  }
}

//! Segregate block into chunks.
//! \pre npartition_sz >= sizeof(void *)
//! \pre    npartition_sz = sizeof(void *) * i, for some integer i
//! \pre    nsz >= npartition_sz
//! \pre Block is properly aligned for an array of object of
//!        size npartition_sz and array of void *.
//! The requirements above guarantee that any pointer to a chunk
//! (which is a pointer to an element in an array of npartition_sz)
//! may be cast to void **.
template <typename SizeType>
void * simple_segregated_storage<SizeType>::segregate(
    void * const block,
    const size_type sz,
    const size_type partition_sz,
    void * const end)
{
  // Get pointer to last valid chunk, preventing overflow on size calculations
  //  The division followed by the multiplication just makes sure that
  //    old == block + partition_sz * i, for some integer i, even if the
  //    block size (sz) is not a multiple of the partition size.
  char * old = static_cast<char *>(block)
      + ((sz - partition_sz) / partition_sz) * partition_sz;

  // Set it to point to the end
  nextof(old) = end;

  // Handle border case where sz == partition_sz (i.e., we're handling an array
  //  of 1 element)
  if (old == block)
    return block;

  // Iterate backwards, building a singly-linked list of pointers
  for (char * iter = old - partition_sz; iter != block;
      old = iter, iter -= partition_sz)
    nextof(iter) = old;

  // Point the first pointer, too
  nextof(block) = old;

  return block;
}

//! \pre (n > 0), (start != 0), (nextof(start) != 0)
//! \post (start != 0)
//! The function attempts to find n contiguous chunks
//!  of size partition_size in the free list, starting at start.
//! If it succeds, it returns the last chunk in that contiguous
//!  sequence, so that the sequence is known by [start, {retval}]
//! If it fails, it does do either because it's at the end of the
//!  free list or hits a non-contiguous chunk.  In either case,
//!  it will return 0, and set start to the last considered
//!  chunk.  You are at the end of the free list if
//!  nextof(start) == 0.  Otherwise, start points to the last
//!  chunk in the contiguous sequence, and nextof(start) points
//!  to the first chunk in the next contiguous sequence (assuming
//!  an ordered free list).
template <typename SizeType>
void * simple_segregated_storage<SizeType>::try_malloc_n(
    void * & start, size_type n, const size_type partition_size)
{
  void * iter = nextof(start);
  while (--n != 0)
  {
    void * next = nextof(iter);
    if (next != static_cast<char *>(iter) + partition_size)
    {
      // next == 0 (end-of-list) or non-contiguous chunk found
      start = iter;
      return 0;
    }
    iter = next;
  }
  return iter;
}

//! Attempts to find a contiguous sequence of n partition_sz-sized chunks. If found, removes them 
//! all from the free list and returns a pointer to the first. If not found, returns 0. It is strongly 
//! recommended (but not required) that the free list be ordered, as this algorithm will fail to find 
//! a contiguous sequence unless it is contiguous in the free list as well. Order-preserving. 
//! O(N) with respect to the size of the free list.
template <typename SizeType>
void * simple_segregated_storage<SizeType>::malloc_n(const size_type n,
    const size_type partition_size)
{
   BOOST_POOL_VALIDATE_INTERNALS
  if(n == 0)
    return 0;
  void * start = &first;
  void * iter;
  do
  {
    if (nextof(start) == 0)
      return 0;
    iter = try_malloc_n(start, n, partition_size);
  } while (iter == 0);
  void * const ret = nextof(start);
  nextof(start) = nextof(iter);
  BOOST_POOL_VALIDATE_INTERNALS
  return ret;
}

} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif

/* simple_segregated_storage.hpp
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
*/