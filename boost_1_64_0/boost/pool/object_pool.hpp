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
ku/nAoe3DOq2EhhHuU8P+NOXTToZMpZeymRURSp6zIGe8u2nIPbIecofh6P+iFPy67Dpcy4eMuc9XJc+zuGHFh5d7Gch7fENxp8VUdrXpac9uAr2zvYvbmJzexLXZVWpMbH9uWOl16Wb2NllWXQ59rZTOqj5geYS5H1jz2tZXrSyh2O+U7r4zx+NzeLwdjJPUFHFSeHooSZmj78zMP4RyGFzXYvwqMLVwX8eae6NvpbdY8f96SyD/YQt+bkDZq2Wj6htoEnQuDrMycq4hevRJFmCgwpXD/+5pOkfjowqSKJadDiZVHpQ+3VxSbl6uP/3V46MEDLKuK2woWEp3rmf4U6Hrw+wNa5bfBNWtidLhBvLu/t1bp+AvR6Lqh8mP/OkIw1ip/4yh7cOYgQM1KKJ/DqoBmAxnILKOJLkqRAham8eU+IxAS91yhTyILyU9xtYmeMjz3L7NKS9QgOw88KLVE4fiLLtkxRbc8/t9/VM75UoT5xgbayLUPQhK9t7I5GuV7c5dSiDqEvCJImG/ntgZgwvVK8vnzllY4cXMt1nHD3iADZbltRxw/WArXoSq854lKieK6N67Hg9O7+pRS7Kph/08N3BZ/dc9r2e7enhr637ln+L8QWJhWWnA+i6JK9n+0+RhxEmhYDkOTL5Jean4wfNftjRpQuiLMXV1DxWutA9jXsyo+To/niJyjlcNUWFpi1GbZbM9WnrZ7qFldsWVdsXWeWU60m2ynMY3vZ6Fi/TZPDyCFWw98nyqTiJ3zIZfRd3XZW738O6V1ahysnl1VdNnYPuvMDOFDJEYvZJMygzvo+yBYcZjfc9ae7UXGDxkFXahHXuzkvED3liwc2D8LwLTvtXYV8VsWp/cTTT5W2ZfH0XWO7FGBNQJFpeHlx8sjDcIVyeyp942pGRyXiFvC4LNQ5893St7X7xAvMzwj0X5WGty+dOtWGZ1vmTyfnvZxwdSpxdI3oOMZhGB+V7VlPCBs+r9x1HDxm3G4UxJpXt9KD3+KgP/J+OnBjxpDLTap9IOcoVL9sCXVLND3izEbva1fXArk1738Ds2bTCSUqudeHOpNXjmwtnaECI+bZvcHVpi6joZCJFN2UPta7HS+/Etl9zdCnhlKqTuIr1Go3i5XA4tYLzKHqz1e5LHP48wF6oQ1hcwnVAUPTiaeaXuNXhbeHzrNoWWwNVtutMMFMbiztj+tfYmGaxiDzlL52ABjym73dvYD7HOqmiLCl17NTq0rCpVOaSXKVNSjfTx0yuiTfye+Uprpy1Pl1Ordq54XimfadvZH2rjrNcjm5TpMlaQDIxjtel6R2cOUcPERQ5BnwRth49pHW9BkEyrdK0HenIkQm5S3iFm6FvWPebsiVkayGAe2nZ7R+3vJH1D5GECH3NPLrgcpe79n2N1SPH+UTbJIUqX51O6EzmOMHDzK9OixwdLjMd0gy7rqwpPDrgHM7tX/92eDOMsTwpZOboYUcDBxC+wKsW1lfUTLrB79I9/E3s7K3JS9H2bHyomYMO1cD20eBN7HuKBqEkZR9sjbMCdlf6bprs49NZvIlv8/SbmF0vIsw+be/XhyQkIblYb3bqlAWwh0VdlQnXhyUNVGrZ8f9lR04cyORCIm3Zd/HMqgGx9Vj7JthhhGURO7ogTgW6jKdKeFQIowhxTrBfN6wuOy6yM7m4DpM2K7260OxfxNa55qJbnyaN5OW5cFtd5KM7Rhnb58RFFitdSeui4/OImwxwYvOZLl9kuTHCvK+6tAw8nmK+/7zI2iHvklhmMA98aeDcPP5ndPm3OjJi6a9JGwRMOeW7+WI2jZ130f2eXZyladmHrHycqjKvdTA5M6PndCoDW78oLKIacag=
*/