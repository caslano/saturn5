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