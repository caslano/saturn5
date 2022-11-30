// Copyright (C) 2000, 2001 Stephen Cleary
// Copyright (C) 2010 Paul A. Bristow added Doxygen comments.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POOL_ALLOC_HPP
#define BOOST_POOL_ALLOC_HPP

/*!
  \file
  \brief C++ Standard Library compatible pool-based allocators.
  \details  This header provides two template types - 
  \ref pool_allocator and \ref fast_pool_allocator -
  that can be used for fast and efficient memory allocation
  in conjunction with the C++ Standard Library containers.

  These types both satisfy the Standard Allocator requirements [20.1.5]
  and the additional requirements in [20.1.5/4],
  so they can be used with either Standard or user-supplied containers.

  In addition, the fast_pool_allocator also provides an additional allocation
  and an additional deallocation function:

<table>
<tr><th>Expression</th><th>Return Type</th><th>Semantic Equivalence<th></tr>
<tr><td><tt>PoolAlloc::allocate()</tt></td><td><tt>T *</tt></td><td><tt>PoolAlloc::allocate(1)</tt></tr>
<tr><td><tt>PoolAlloc::deallocate(p)</tt></td><td>void</tt></td><td><tt>PoolAlloc::deallocate(p, 1)</tt></tr>
</table>

The typedef user_allocator publishes the value of the UserAllocator template parameter.

<b>Notes</b>

If the allocation functions run out of memory, they will throw <tt>std::bad_alloc</tt>.

The underlying Pool type used by the allocators is accessible through the Singleton Pool Interface.
The identifying tag used for pool_allocator is pool_allocator_tag,
and the tag used for fast_pool_allocator is fast_pool_allocator_tag.
All template parameters of the allocators (including implementation-specific ones)
determine the type of the underlying Pool,
with the exception of the first parameter T, whose size is used instead.

Since the size of T is used to determine the type of the underlying Pool,
each allocator for different types of the same size will share the same underlying pool.
The tag class prevents pools from being shared between pool_allocator and fast_pool_allocator.
For example, on a system where
<tt>sizeof(int) == sizeof(void *)</tt>, <tt>pool_allocator<int></tt> and <tt>pool_allocator<void *></tt>
will both allocate/deallocate from/to the same pool.

If there is only one thread running before main() starts and after main() ends,
then both allocators are completely thread-safe.

<b>Compiler and STL Notes</b>

A number of common STL libraries contain bugs in their using of allocators.
Specifically, they pass null pointers to the deallocate function,
which is explicitly forbidden by the Standard [20.1.5 Table 32].
PoolAlloc will work around these libraries if it detects them;
currently, workarounds are in place for:
Borland C++ (Builder and command-line compiler)
with default (RogueWave) library, ver. 5 and earlier,
STLport (with any compiler), ver. 4.0 and earlier.
*/

// std::numeric_limits
#include <boost/limits.hpp>
// new, std::bad_alloc
#include <new>

#include <boost/throw_exception.hpp>
#include <boost/pool/poolfwd.hpp>

// boost::singleton_pool
#include <boost/pool/singleton_pool.hpp>

#include <boost/detail/workaround.hpp>

// C++11 features detection
#include <boost/config.hpp>

// std::forward
#ifdef BOOST_HAS_VARIADIC_TMPL
#include <utility>
#endif

#ifdef BOOST_POOL_INSTRUMENT
#include <iostream>
#include <iomanip>
#endif

// The following code will be put into Boost.Config in a later revision
#if defined(_RWSTD_VER) || defined(__SGI_STL_PORT) || \
    BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x582))
 #define BOOST_NO_PROPER_STL_DEALLOCATE
#endif

namespace boost {

#ifdef BOOST_POOL_INSTRUMENT

template <bool b>
struct debug_info
{
   static unsigned allocated;
};

template <bool b>
unsigned debug_info<b>::allocated = 0;

#endif

 //! Simple tag type used by pool_allocator as an argument to the
 //! underlying singleton_pool.
 struct pool_allocator_tag
{
};

/*!  \brief A C++ Standard Library conforming allocator, based on an underlying pool.

  Template parameters for pool_allocator are defined as follows:

  <b>T</b> Type of object to allocate/deallocate.

  <b>UserAllocator</B>. Defines the method that the underlying Pool will use to allocate memory from the system. See 
  <a href="boost_pool/pool/pooling.html#boost_pool.pool.pooling.user_allocator">User Allocators</a> for details.

  <b>Mutex</b> Allows the user to determine the type of synchronization to be used on the underlying singleton_pool. 

  <b>NextSize</b> The value of this parameter is passed to the underlying singleton_pool when it is created.

  <b>MaxSize</b> Limit on the maximum size used.

  \attention
  The underlying singleton_pool used by the this allocator
  constructs a pool instance that
  <b>is never freed</b>.  This means that memory allocated
  by the allocator can be still used after main() has
  completed, but may mean that some memory checking programs
  will complain about leaks.
 
  
  */
template <typename T,
    typename UserAllocator,
    typename Mutex,
    unsigned NextSize,
    unsigned MaxSize >
class pool_allocator
{
  public:
    typedef T value_type;  //!< value_type of template parameter T.
    typedef UserAllocator user_allocator;  //!< allocator that defines the method that the underlying Pool will use to allocate memory from the system.
    typedef Mutex mutex; //!< typedef mutex publishes the value of the template parameter Mutex.
    BOOST_STATIC_CONSTANT(unsigned, next_size = NextSize); //!< next_size publishes the values of the template parameter NextSize.

    typedef value_type * pointer; //!<
    typedef const value_type * const_pointer;
    typedef value_type & reference;
    typedef const value_type & const_reference;
    typedef typename pool<UserAllocator>::size_type size_type;
    typedef typename pool<UserAllocator>::difference_type difference_type;

    //! \brief Nested class rebind allows for transformation from
    //! pool_allocator<T> to pool_allocator<U>.
    //!
    //! Nested class rebind allows for transformation from
    //! pool_allocator<T> to pool_allocator<U> via the member
    //! typedef other.
    template <typename U>
    struct rebind
    { //
      typedef pool_allocator<U, UserAllocator, Mutex, NextSize, MaxSize> other;
    };

  public:
    pool_allocator()
    { /*! Results in default construction of the underlying singleton_pool IFF an
       instance of this allocator is constructed during global initialization (
         required to ensure construction of singleton_pool IFF an
         instance of this allocator is constructed during global
         initialization. See ticket #2359 for a complete explanation at
         http://svn.boost.org/trac/boost/ticket/2359) .
       */
      singleton_pool<pool_allocator_tag, sizeof(T), UserAllocator, Mutex,
                     NextSize, MaxSize>::is_from(0);
    }

    // default copy constructor.

    // default assignment operator.

    // not explicit, mimicking std::allocator [20.4.1]
    template <typename U>
    pool_allocator(const pool_allocator<U, UserAllocator, Mutex, NextSize, MaxSize> &)
    { /*! Results in the default construction of the underlying singleton_pool, this
         is required to ensure construction of singleton_pool IFF an
         instance of this allocator is constructed during global
         initialization. See ticket #2359 for a complete explanation
         at http://svn.boost.org/trac/boost/ticket/2359 .
       */
      singleton_pool<pool_allocator_tag, sizeof(T), UserAllocator, Mutex,
                     NextSize, MaxSize>::is_from(0);
    }

    // default destructor

    static pointer address(reference r)
    { return &r; }
    static const_pointer address(const_reference s)
    { return &s; }
    static size_type max_size()
    { return (std::numeric_limits<size_type>::max)(); }

#if defined(BOOST_HAS_VARIADIC_TMPL) && defined(BOOST_HAS_RVALUE_REFS)
    template <typename U, typename... Args>
    static void construct(U* ptr, Args&&... args)
    { new (ptr) U(std::forward<Args>(args)...); }
#else
    static void construct(const pointer ptr, const value_type & t)
    { new (ptr) T(t); }
#endif

    static void destroy(const pointer ptr)
    {
      ptr->~T();
      (void) ptr; // avoid unused variable warning.
    }

    bool operator==(const pool_allocator &) const
    { return true; }
    bool operator!=(const pool_allocator &) const
    { return false; }

    static pointer allocate(const size_type n)
    {
#ifdef BOOST_POOL_INSTRUMENT
       debug_info<true>::allocated += n * sizeof(T);
       std::cout << "Allocating " << n << " * " << sizeof(T) << " bytes...\n"
          "Total allocated is now " << debug_info<true>::allocated << std::endl;
#endif
      const pointer ret = static_cast<pointer>(
          singleton_pool<pool_allocator_tag, sizeof(T), UserAllocator, Mutex,
              NextSize, MaxSize>::ordered_malloc(n) );
      if ((ret == 0) && n)
        boost::throw_exception(std::bad_alloc());
      return ret;
    }
    static pointer allocate(const size_type n, const void * const)
    { //! allocate n bytes
    //! \param n bytes to allocate.
    //! \param unused.
      return allocate(n);
    }
    static void deallocate(const pointer ptr, const size_type n)
    {  //! Deallocate n bytes from ptr
       //! \param ptr location to deallocate from.
       //! \param n number of bytes to deallocate.
#ifdef BOOST_POOL_INSTRUMENT
       debug_info<true>::allocated -= n * sizeof(T);
       std::cout << "Deallocating " << n << " * " << sizeof(T) << " bytes...\n"
          "Total allocated is now " << debug_info<true>::allocated << std::endl;
#endif
#ifdef BOOST_NO_PROPER_STL_DEALLOCATE
      if (ptr == 0 || n == 0)
        return;
#endif
      singleton_pool<pool_allocator_tag, sizeof(T), UserAllocator, Mutex,
          NextSize, MaxSize>::ordered_free(ptr, n);
    }
};

/*! \brief Specialization of pool_allocator<void>.

Specialization of pool_allocator for type void: required by the standard to make this a conforming allocator type.
*/
template<
    typename UserAllocator,
    typename Mutex,
    unsigned NextSize,
    unsigned MaxSize>
class pool_allocator<void, UserAllocator, Mutex, NextSize, MaxSize>
{
public:
    typedef void*       pointer;
    typedef const void* const_pointer;
    typedef void        value_type;
    //! \brief Nested class rebind allows for transformation from
    //! pool_allocator<T> to pool_allocator<U>.
    //!
    //! Nested class rebind allows for transformation from
    //! pool_allocator<T> to pool_allocator<U> via the member
    //! typedef other.
    template <class U> 
    struct rebind
    {
       typedef pool_allocator<U, UserAllocator, Mutex, NextSize, MaxSize> other;
    };
};

//! Simple tag type used by fast_pool_allocator as a template parameter to the underlying singleton_pool.
struct fast_pool_allocator_tag
{
};

 /*! \brief A C++ Standard Library conforming allocator geared towards allocating single chunks.

  While class template <tt>pool_allocator</tt> is a more general-purpose solution geared towards
  efficiently servicing requests for any number of contiguous chunks,
  <tt>fast_pool_allocator</tt> is also a general-purpose solution,
  but is geared towards efficiently servicing requests for one chunk at a time;
  it will work for contiguous chunks, but not as well as <tt>pool_allocator</tt>.

  If you are seriously concerned about performance,
  use <tt>fast_pool_allocator</tt> when dealing with containers such as <tt>std::list</tt>,
  and use <tt>pool_allocator</tt> when dealing with containers such as <tt>std::vector</tt>.

  The template parameters are defined as follows:

  <b>T</b> Type of object to allocate/deallocate.

  <b>UserAllocator</b>. Defines the method that the underlying Pool will use to allocate memory from the system. 
  See <a href="boost_pool/pool/pooling.html#boost_pool.pool.pooling.user_allocator">User Allocators</a> for details.

  <b>Mutex</b> Allows the user to determine the type of synchronization to be used on the underlying <tt>singleton_pool</tt>.

  <b>NextSize</b> The value of this parameter is passed to the underlying Pool when it is created.

  <b>MaxSize</b> Limit on the maximum size used.

   \attention
  The underlying singleton_pool used by the this allocator
  constructs a pool instance that
  <b>is never freed</b>.  This means that memory allocated
  by the allocator can be still used after main() has
  completed, but may mean that some memory checking programs
  will complain about leaks.
 
 */

template <typename T,
    typename UserAllocator,
    typename Mutex,
    unsigned NextSize,
    unsigned MaxSize >
class fast_pool_allocator
{
  public:
    typedef T value_type;
    typedef UserAllocator user_allocator;
    typedef Mutex mutex;
    BOOST_STATIC_CONSTANT(unsigned, next_size = NextSize);

    typedef value_type * pointer;
    typedef const value_type * const_pointer;
    typedef value_type & reference;
    typedef const value_type & const_reference;
    typedef typename pool<UserAllocator>::size_type size_type;
    typedef typename pool<UserAllocator>::difference_type difference_type;

    //! \brief Nested class rebind allows for transformation from
    //! fast_pool_allocator<T> to fast_pool_allocator<U>.
    //!
    //! Nested class rebind allows for transformation from
    //! fast_pool_allocator<T> to fast_pool_allocator<U> via the member
    //! typedef other.
    template <typename U>
    struct rebind
    {
      typedef fast_pool_allocator<U, UserAllocator, Mutex, NextSize, MaxSize> other;
    };

  public:
    fast_pool_allocator()
    {
      //! Ensures construction of the underlying singleton_pool IFF an
      //! instance of this allocator is constructed during global
      //! initialization. See ticket #2359 for a complete explanation
      //! at http://svn.boost.org/trac/boost/ticket/2359 .
      singleton_pool<fast_pool_allocator_tag, sizeof(T),
                     UserAllocator, Mutex, NextSize, MaxSize>::is_from(0);
    }

    // Default copy constructor used.

    // Default assignment operator used.

    // Not explicit, mimicking std::allocator [20.4.1]
    template <typename U>
    fast_pool_allocator(
        const fast_pool_allocator<U, UserAllocator, Mutex, NextSize, MaxSize> &)
    {
      //! Ensures construction of the underlying singleton_pool IFF an
      //! instance of this allocator is constructed during global
      //! initialization. See ticket #2359 for a complete explanation
      //! at http://svn.boost.org/trac/boost/ticket/2359 .
      singleton_pool<fast_pool_allocator_tag, sizeof(T),
                     UserAllocator, Mutex, NextSize, MaxSize>::is_from(0);
    }

    // Default destructor used.

    static pointer address(reference r)
    {
      return &r;
    }
    static const_pointer address(const_reference s)
    { return &s; }
    static size_type max_size()
    { return (std::numeric_limits<size_type>::max)(); }

#if defined(BOOST_HAS_VARIADIC_TMPL) && defined(BOOST_HAS_RVALUE_REFS)
    template <typename U, typename... Args>
    void construct(U* ptr, Args&&... args)
    { new (ptr) U(std::forward<Args>(args)...); }
#else
    void construct(const pointer ptr, const value_type & t)
    { new (ptr) T(t); }
#endif

    void destroy(const pointer ptr)
    { //! Destroy ptr using destructor.
      ptr->~T();
      (void) ptr; // Avoid unused variable warning.
    }

    bool operator==(const fast_pool_allocator &) const
    { return true; }
    bool operator!=(const fast_pool_allocator &) const
    { return false; }

    static pointer allocate(const size_type n)
    {
      const pointer ret = (n == 1) ?
          static_cast<pointer>(
              (singleton_pool<fast_pool_allocator_tag, sizeof(T),
                  UserAllocator, Mutex, NextSize, MaxSize>::malloc)() ) :
          static_cast<pointer>(
              singleton_pool<fast_pool_allocator_tag, sizeof(T),
                  UserAllocator, Mutex, NextSize, MaxSize>::ordered_malloc(n) );
      if (ret == 0)
        boost::throw_exception(std::bad_alloc());
      return ret;
    }
    static pointer allocate(const size_type n, const void * const)
    { //! Allocate memory .
      return allocate(n);
    }
    static pointer allocate()
    { //! Allocate memory.
      const pointer ret = static_cast<pointer>(
          (singleton_pool<fast_pool_allocator_tag, sizeof(T),
              UserAllocator, Mutex, NextSize, MaxSize>::malloc)() );
      if (ret == 0)
        boost::throw_exception(std::bad_alloc());
      return ret;
    }
    static void deallocate(const pointer ptr, const size_type n)
    { //! Deallocate memory.

#ifdef BOOST_NO_PROPER_STL_DEALLOCATE
      if (ptr == 0 || n == 0)
        return;
#endif
      if (n == 1)
        (singleton_pool<fast_pool_allocator_tag, sizeof(T),
            UserAllocator, Mutex, NextSize, MaxSize>::free)(ptr);
      else
        (singleton_pool<fast_pool_allocator_tag, sizeof(T),
            UserAllocator, Mutex, NextSize, MaxSize>::free)(ptr, n);
    }
    static void deallocate(const pointer ptr)
    { //! deallocate/free
      (singleton_pool<fast_pool_allocator_tag, sizeof(T),
          UserAllocator, Mutex, NextSize, MaxSize>::free)(ptr);
    }
};

/*!  \brief Specialization of fast_pool_allocator<void>.

Specialization of fast_pool_allocator<void> required to make the allocator standard-conforming.
*/
template<
    typename UserAllocator,
    typename Mutex,
    unsigned NextSize,
    unsigned MaxSize >
class fast_pool_allocator<void, UserAllocator, Mutex, NextSize, MaxSize>
{
public:
    typedef void*       pointer;
    typedef const void* const_pointer;
    typedef void        value_type;

    //! \brief Nested class rebind allows for transformation from
    //! fast_pool_allocator<T> to fast_pool_allocator<U>.
    //!
    //! Nested class rebind allows for transformation from
    //! fast_pool_allocator<T> to fast_pool_allocator<U> via the member
    //! typedef other.
    template <class U> struct rebind
    {
        typedef fast_pool_allocator<U, UserAllocator, Mutex, NextSize, MaxSize> other;
    };
};

} // namespace boost

#endif

/* pool_alloc.hpp
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
*/