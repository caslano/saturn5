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
    BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
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