// Copyright (C) 2000, 2001 Stephen Cleary
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_OBJECT_POOL_HPP
#define BOOST_OBJECT_POOL_HPP
/*!
\file
\brief  Provides a template type boost::object_pool<T, UserAllocator>
that can be used for fast and efficient memory allocation of objects of type T.
It also provides automatic destruction of non-deallocated objects.
*/

#include <boost/pool/poolfwd.hpp>

// boost::pool
#include <boost/pool/pool.hpp>

// The following code will be put into Boost.Config in a later revision
#if defined(BOOST_MSVC) || defined(__KCC)
# define BOOST_NO_TEMPLATE_CV_REF_OVERLOADS
#endif

// The following code might be put into some Boost.Config header in a later revision
#ifdef __BORLANDC__
# pragma option push -w-inl
#endif

// There are a few places in this file where the expression "this->m" is used.
// This expression is used to force instantiation-time name lookup, which I am
//   informed is required for strict Standard compliance.  It's only necessary
//   if "m" is a member of a base class that is dependent on a template
//   parameter.
// Thanks to Jens Maurer for pointing this out!

namespace boost {

/*! \brief A template class
that can be used for fast and efficient memory allocation of objects.
It also provides automatic destruction of non-deallocated objects.

\details

<b>T</b> The type of object to allocate/deallocate.
T must have a non-throwing destructor.

<b>UserAllocator</b>
Defines the allocator that the underlying Pool will use to allocate memory from the system.
See <a href="boost_pool/pool/pooling.html#boost_pool.pool.pooling.user_allocator">User Allocators</a> for details.

Class object_pool is a template class
that can be used for fast and efficient memory allocation of objects.
It also provides automatic destruction of non-deallocated objects.

When the object pool is destroyed, then the destructor for type T
is called for each allocated T that has not yet been deallocated. O(N).

Whenever an object of type ObjectPool needs memory from the system,
it will request it from its UserAllocator template parameter.
The amount requested is determined using a doubling algorithm;
that is, each time more system memory is allocated,
the amount of system memory requested is doubled.
Users may control the doubling algorithm by the parameters passed
to the object_pool's constructor.
*/

template <typename T, typename UserAllocator>
class object_pool: protected pool<UserAllocator>
{ //!
  public:
    typedef T element_type; //!< ElementType
    typedef UserAllocator user_allocator; //!<
    typedef typename pool<UserAllocator>::size_type size_type; //!<   pool<UserAllocator>::size_type
    typedef typename pool<UserAllocator>::difference_type difference_type; //!< pool<UserAllocator>::difference_type

  protected:
    //! \return The underlying boost:: \ref pool storage used by *this.
    pool<UserAllocator> & store()
    { 
      return *this;
    }
    //! \return The underlying boost:: \ref pool storage used by *this.
    const pool<UserAllocator> & store() const
    { 
      return *this;
    }

    // for the sake of code readability :)
    static void * & nextof(void * const ptr)
    { //! \returns The next memory block after ptr (for the sake of code readability :)
      return *(static_cast<void **>(ptr));
    }

  public:
    explicit object_pool(const size_type arg_next_size = 32, const size_type arg_max_size = 0)
    :
    pool<UserAllocator>(sizeof(T), arg_next_size, arg_max_size)
    { //! Constructs a new (empty by default) ObjectPool.
      //! \param next_size Number of chunks to request from the system the next time that object needs to allocate system memory (default 32).
      //! \pre next_size != 0.
      //! \param max_size Maximum number of chunks to ever request from the system - this puts a cap on the doubling algorithm
      //! used by the underlying pool.
    }

    ~object_pool();

    // Returns 0 if out-of-memory.
    element_type * malloc BOOST_PREVENT_MACRO_SUBSTITUTION()
    { //! Allocates memory that can hold one object of type ElementType.
      //!
      //! If out of memory, returns 0. 
      //!
      //! Amortized O(1).
      return static_cast<element_type *>(store().ordered_malloc());
    }
    void free BOOST_PREVENT_MACRO_SUBSTITUTION(element_type * const chunk)
    { //! De-Allocates memory that holds a chunk of type ElementType.
      //!
      //!  Note that p may not be 0.\n
      //!
      //! Note that the destructor for p is not called. O(N).
      store().ordered_free(chunk);
    }
    bool is_from(element_type * const chunk) const
    { /*! \returns true  if chunk was allocated from *this or
      may be returned as the result of a future allocation from *this.

      Returns false if chunk was allocated from some other pool or
      may be returned as the result of a future allocation from some other pool.

      Otherwise, the return value is meaningless.

      \note This function may NOT be used to reliably test random pointer values!
    */
      return store().is_from(chunk);
    }

    element_type * construct()
    { //! \returns A pointer to an object of type T, allocated in memory from the underlying pool
      //! and default constructed.  The returned objected can be freed by a call to \ref destroy.
      //! Otherwise the returned object will be automatically destroyed when *this is destroyed.
      element_type * const ret = (malloc)();
      if (ret == 0)
        return ret;
      try { new (ret) element_type(); }
      catch (...) { (free)(ret); throw; }
      return ret;
    }


#if defined(BOOST_DOXYGEN)
    template <class Arg1, ... class ArgN>
    element_type * construct(Arg1&, ... ArgN&)
    {
       //! \returns A pointer to an object of type T, allocated in memory from the underlying pool
       //! and constructed from arguments Arg1 to ArgN.  The returned objected can be freed by a call to \ref destroy.
       //! Otherwise the returned object will be automatically destroyed when *this is destroyed.
       //!
       //! \note Since the number and type of arguments to this function is totally arbitrary, a simple system has been 
       //! set up to automatically generate template construct functions. This system is based on the macro preprocessor 
       //! m4, which is standard on UNIX systems and also available for Win32 systems.\n\n
       //! detail/pool_construct.m4, when run with m4, will create the file detail/pool_construct.ipp, which only defines 
       //! the construct functions for the proper number of arguments. The number of arguments may be passed into the 
       //! file as an m4 macro, NumberOfArguments; if not provided, it will default to 3.\n\n
       //! For each different number of arguments (1 to NumberOfArguments), a template function is generated. There 
       //! are the same number of template parameters as there are arguments, and each argument's type is a reference 
       //! to that (possibly cv-qualified) template argument. Each possible permutation of the cv-qualifications is also generated.\n\n
       //! Because each permutation is generated for each possible number of arguments, the included file size grows 
       //! exponentially in terms of the number of constructor arguments, not linearly. For the sake of rational 
       //! compile times, only use as many arguments as you need.\n\n
       //! detail/pool_construct.bat and detail/pool_construct.sh are also provided to call m4, defining NumberOfArguments 
       //! to be their command-line parameter. See these files for more details.
    }
#else
// Include automatically-generated file for family of template construct() functions.
// Copy .inc renamed .ipp to conform to Doxygen include filename expectations, PAB 12 Jan 11.
// But still get Doxygen warning:
// I:/boost-sandbox/guild/pool/boost/pool/object_pool.hpp:82:
// Warning: include file boost/pool/detail/pool_construct.ipp
// not found, perhaps you forgot to add its directory to INCLUDE_PATH?
// But the file IS found and referenced OK, but cannot view code.
// This seems because not at the head of the file
// But if moved this up, Doxygen is happy, but of course it won't compile,
// because the many constructors *must* go here.

#ifndef BOOST_NO_TEMPLATE_CV_REF_OVERLOADS
#   include <boost/pool/detail/pool_construct.ipp>
#else
#   include <boost/pool/detail/pool_construct_simple.ipp>
#endif
#endif
    void destroy(element_type * const chunk)
    { //! Destroys an object allocated with \ref construct. 
      //!
      //! Equivalent to:
      //!
      //! p->~ElementType(); this->free(p);
      //!
      //! \pre p must have been previously allocated from *this via a call to \ref construct.
      chunk->~T();
      (free)(chunk);
    }

    size_type get_next_size() const
    { //! \returns The number of chunks that will be allocated next time we run out of memory.
      return store().get_next_size();
    }
    void set_next_size(const size_type x)
    { //! Set a new number of chunks to allocate the next time we run out of memory.
      //! \param x wanted next_size (must not be zero).
      store().set_next_size(x);
    }
};

template <typename T, typename UserAllocator>
object_pool<T, UserAllocator>::~object_pool()
{
#ifndef BOOST_POOL_VALGRIND
  // handle trivial case of invalid list.
  if (!this->list.valid())
    return;

  details::PODptr<size_type> iter = this->list;
  details::PODptr<size_type> next = iter;

  // Start 'freed_iter' at beginning of free list
  void * freed_iter = this->first;

  const size_type partition_size = this->alloc_size();

  do
  {
    // increment next
    next = next.next();

    // delete all contained objects that aren't freed.

    // Iterate 'i' through all chunks in the memory block.
    for (char * i = iter.begin(); i != iter.end(); i += partition_size)
    {
      // If this chunk is free,
      if (i == freed_iter)
      {
        // Increment freed_iter to point to next in free list.
        freed_iter = nextof(freed_iter);

        // Continue searching chunks in the memory block.
        continue;
      }

      // This chunk is not free (allocated), so call its destructor,
      static_cast<T *>(static_cast<void *>(i))->~T();
      // and continue searching chunks in the memory block.
    }

    // free storage.
    (UserAllocator::free)(iter.begin());

    // increment iter.
    iter = next;
  } while (iter.valid());

  // Make the block list empty so that the inherited destructor doesn't try to
  // free it again.
  this->list.invalidate();
#else
   // destruct all used elements:
   for(std::set<void*>::iterator pos = this->used_list.begin(); pos != this->used_list.end(); ++pos)
   {
      static_cast<T*>(*pos)->~T();
   }
   // base class will actually free the memory...
#endif
}

} // namespace boost

// The following code might be put into some Boost.Config header in a later revision
#ifdef __BORLANDC__
# pragma option pop
#endif

#endif

/* object_pool.hpp
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
*/