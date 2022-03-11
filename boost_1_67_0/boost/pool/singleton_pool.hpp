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