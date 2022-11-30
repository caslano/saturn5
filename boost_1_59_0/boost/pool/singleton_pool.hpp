// Copyright (C) 2000, 2001 Stephen Cleary
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_SINGLETON_POOL_HPP
#define BOOST_SINGLETON_POOL_HPP

/*!
  \file
  \brief The <tt>singleton_pool</tt> class allows other pool interfaces
  for types of the same size to share the same underlying pool.

  \details Header singleton_pool.hpp provides a template class <tt>singleton_pool</tt>,
  which provides access to a pool as a singleton object.
  
*/

#include <boost/pool/poolfwd.hpp>

// boost::pool
#include <boost/pool/pool.hpp>
// boost::details::pool::guard
#include <boost/pool/detail/guard.hpp>

#include <boost/type_traits/aligned_storage.hpp>

namespace boost {

 /*! 
 The singleton_pool class allows other pool interfaces
 for types of the same size to share the same pool.  Template
 parameters are as follows:

 <b>Tag</b> User-specified type to uniquely identify this pool: allows different unbounded sets of singleton pools to exist.

 <b>RequestedSize</b> The size of each chunk returned by member function <tt>malloc()</tt>.

 <B>UserAllocator</b> User allocator, default = default_user_allocator_new_delete.

 <b>Mutex</B> This class is the type of mutex to use to protect simultaneous access to the underlying Pool. 
 Can be any Boost.Thread Mutex type or <tt>boost::details::pool::null_mutex</tt>.
 It is exposed so that users may declare some singleton pools normally (i.e., with synchronization), but 
 some singleton pools without synchronization (by specifying <tt>boost::details::pool::null_mutex</tt>) for efficiency reasons.
 The member typedef <tt>mutex</tt> exposes the value of this template parameter.  The default for this
 parameter is boost::details::pool::default_mutex which is a synonym for either <tt>boost::details::pool::null_mutex</tt>
 (when threading support is turned off in the compiler (so BOOST_HAS_THREADS is not set), or threading support
 has ben explicitly disabled with BOOST_DISABLE_THREADS (Boost-wide disabling of threads) or BOOST_POOL_NO_MT (this library only))
 or for <tt>boost::mutex</tt> (when threading support is enabled in the compiler).

 <B>NextSize</b> The value of this parameter is passed to the underlying Pool when it is created and
 specifies the number of chunks to allocate in the first allocation request (defaults to 32).
 The member typedef <tt>static const value next_size</tt> exposes the value of this template parameter.

 <b>MaxSize</B>The value of this parameter is passed to the underlying Pool when it is created and
 specifies the maximum number of chunks to allocate in any single allocation request (defaults to 0).

  <b>Notes:</b>

  The underlying pool <i>p</i> referenced by the static functions
  in singleton_pool is actually declared in a way that is:

  1 Thread-safe if there is only one thread running before main() begins and after main() ends
  -- all of the static functions of singleton_pool synchronize their access to p.

  2 Guaranteed to be constructed before it is used --
  thus, the simple static object in the synopsis above would actually be an incorrect implementation.
  The actual implementation to guarantee this is considerably more complicated.

  3 Note too that a different underlying pool p exists
  for each different set of template parameters,
  including implementation-specific ones.

  4 The underlying pool is constructed "as if" by:

  pool<UserAllocator> p(RequestedSize, NextSize, MaxSize);

  \attention
  The underlying pool constructed by the singleton 
  <b>is never freed</b>.  This means that memory allocated
  by a singleton_pool can be still used after main() has
  completed, but may mean that some memory checking programs
  will complain about leaks from singleton_pool.
 
  */

 template <typename Tag,
    unsigned RequestedSize,
    typename UserAllocator,
    typename Mutex,
    unsigned NextSize,
    unsigned MaxSize >
class singleton_pool
{
  public:
    typedef Tag tag; /*!< The Tag template parameter uniquely
                     identifies this pool and allows
      different unbounded sets of singleton pools to exist.
      For example, the pool allocators use two tag classes to ensure that the
      two different allocator types never share the same underlying singleton pool.
      Tag is never actually used by singleton_pool.
    */
    typedef Mutex mutex; //!< The type of mutex used to synchonise access to this pool (default <tt>details::pool::default_mutex</tt>).
    typedef UserAllocator user_allocator; //!< The user-allocator used by this pool, default = <tt>default_user_allocator_new_delete</tt>.
    typedef typename pool<UserAllocator>::size_type size_type; //!< size_type of user allocator.
    typedef typename pool<UserAllocator>::difference_type difference_type; //!< difference_type of user allocator.

    BOOST_STATIC_CONSTANT(unsigned, requested_size = RequestedSize); //!< The size of each chunk allocated by this pool.
    BOOST_STATIC_CONSTANT(unsigned, next_size = NextSize); //!< The number of chunks to allocate on the first allocation.

private:
    singleton_pool();

#ifndef BOOST_DOXYGEN
    struct pool_type: public Mutex, public pool<UserAllocator>
    {
      pool_type() : pool<UserAllocator>(RequestedSize, NextSize, MaxSize) {}
    }; //  struct pool_type: Mutex

#else
    //
    // This is invoked when we build with Doxygen only:
    //
public:
    static pool<UserAllocator> p; //!< For exposition only!
#endif


  public:
    static void * malloc BOOST_PREVENT_MACRO_SUBSTITUTION()
    { //! Equivalent to SingletonPool::p.malloc(); synchronized.
      pool_type & p = get_pool();
      details::pool::guard<Mutex> g(p);
      return (p.malloc)();
    }
    static void * ordered_malloc()
    {  //! Equivalent to SingletonPool::p.ordered_malloc(); synchronized.
      pool_type & p = get_pool();
      details::pool::guard<Mutex> g(p);
      return p.ordered_malloc();
    }
    static void * ordered_malloc(const size_type n)
    { //! Equivalent to SingletonPool::p.ordered_malloc(n); synchronized.
      pool_type & p = get_pool();
      details::pool::guard<Mutex> g(p);
      return p.ordered_malloc(n);
    }
    static bool is_from(void * const ptr)
    { //! Equivalent to SingletonPool::p.is_from(chunk); synchronized.
      //! \returns true if chunk is from SingletonPool::is_from(chunk)
      pool_type & p = get_pool();
      details::pool::guard<Mutex> g(p);
      return p.is_from(ptr);
    }
    static void free BOOST_PREVENT_MACRO_SUBSTITUTION(void * const ptr)
    { //! Equivalent to SingletonPool::p.free(chunk); synchronized.
      pool_type & p = get_pool();
      details::pool::guard<Mutex> g(p);
      (p.free)(ptr);
    }
    static void ordered_free(void * const ptr)
    { //! Equivalent to SingletonPool::p.ordered_free(chunk); synchronized.
      pool_type & p = get_pool();
      details::pool::guard<Mutex> g(p);
      p.ordered_free(ptr);
    }
    static void free BOOST_PREVENT_MACRO_SUBSTITUTION(void * const ptr, const size_type n)
    { //! Equivalent to SingletonPool::p.free(chunk, n); synchronized.
      pool_type & p = get_pool();
      details::pool::guard<Mutex> g(p);
      (p.free)(ptr, n);
    }
    static void ordered_free(void * const ptr, const size_type n)
    { //! Equivalent to SingletonPool::p.ordered_free(chunk, n); synchronized.
      pool_type & p = get_pool();
      details::pool::guard<Mutex> g(p);
      p.ordered_free(ptr, n);
    }
    static bool release_memory()
    { //! Equivalent to SingletonPool::p.release_memory(); synchronized.
      pool_type & p = get_pool();
      details::pool::guard<Mutex> g(p);
      return p.release_memory();
    }
    static bool purge_memory()
    { //! Equivalent to SingletonPool::p.purge_memory(); synchronized.
      pool_type & p = get_pool();
      details::pool::guard<Mutex> g(p);
      return p.purge_memory();
    }

private:
   typedef boost::aligned_storage<sizeof(pool_type), boost::alignment_of<pool_type>::value> storage_type;
   static storage_type storage;

   static pool_type& get_pool()
   {
      static bool f = false;
      if(!f)
      {
         // This code *must* be called before main() starts, 
         // and when only one thread is executing.
         f = true;
         new (&storage) pool_type;
      }

      // The following line does nothing else than force the instantiation
      //  of singleton<T>::create_object, whose constructor is
      //  called before main() begins.
      create_object.do_nothing();

      return *static_cast<pool_type*>(static_cast<void*>(&storage));
   }

   struct object_creator
   {
      object_creator()
      {  // This constructor does nothing more than ensure that instance()
         //  is called before main() begins, thus creating the static
         //  T object before multithreading race issues can come up.
         singleton_pool<Tag, RequestedSize, UserAllocator, Mutex, NextSize, MaxSize>::get_pool();
      }
      inline void do_nothing() const
      {
      }
   };
   static object_creator create_object;
}; // struct singleton_pool

template <typename Tag,
    unsigned RequestedSize,
    typename UserAllocator,
    typename Mutex,
    unsigned NextSize,
    unsigned MaxSize >
typename singleton_pool<Tag, RequestedSize, UserAllocator, Mutex, NextSize, MaxSize>::storage_type singleton_pool<Tag, RequestedSize, UserAllocator, Mutex, NextSize, MaxSize>::storage;

template <typename Tag,
    unsigned RequestedSize,
    typename UserAllocator,
    typename Mutex,
    unsigned NextSize,
    unsigned MaxSize >
typename singleton_pool<Tag, RequestedSize, UserAllocator, Mutex, NextSize, MaxSize>::object_creator singleton_pool<Tag, RequestedSize, UserAllocator, Mutex, NextSize, MaxSize>::create_object;

} // namespace boost

#endif

/* singleton_pool.hpp
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
*/