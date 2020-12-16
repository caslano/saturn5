//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NAMED_RECURSIVE_MUTEX_HPP
#define BOOST_INTERPROCESS_NAMED_RECURSIVE_MUTEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/permissions.hpp>
#if !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/named_recursive_mutex.hpp>
   #define BOOST_INTERPROCESS_USE_WINDOWS
#else
   #include <boost/interprocess/sync/shm/named_recursive_mutex.hpp>
#endif

//!\file
//!Describes a named named_recursive_mutex class for inter-process synchronization

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
namespace ipcdetail{ class interprocess_tester; }
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!A recursive mutex with a global name, so it can be found from different
//!processes. This mutex can't be placed in shared memory, and
//!each process should have it's own named_recursive_mutex.
class named_recursive_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   named_recursive_mutex();
   named_recursive_mutex(const named_recursive_mutex &);
   named_recursive_mutex &operator=(const named_recursive_mutex &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   //!Creates a global recursive_mutex with a name.
   //!If the recursive_mutex can't be created throws interprocess_exception
   named_recursive_mutex(create_only_t create_only, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global recursive_mutex with a name.
   //!If the recursive_mutex is created, this call is equivalent to
   //!named_recursive_mutex(create_only_t, ... )
   //!If the recursive_mutex is already created, this call is equivalent
   //!named_recursive_mutex(open_only_t, ... )
   //!Does not throw
   named_recursive_mutex(open_or_create_t open_or_create, const char *name, const permissions &perm = permissions());

   //!Opens a global recursive_mutex with a name if that recursive_mutex is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   named_recursive_mutex(open_only_t open_only, const char *name);

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~named_recursive_mutex();

   //!Unlocks a previously locked
   //!named_recursive_mutex.
   void unlock();

   //!Locks named_recursive_mutex, sleeps when named_recursive_mutex is already locked.
   //!Throws interprocess_exception if a severe error is found.
   void lock();

   //!Tries to lock the named_recursive_mutex, returns false when named_recursive_mutex
   //!is already locked, returns true when success.
   //!Throws interprocess_exception if a severe error is found.
   bool try_lock();

   //!Tries to lock the named_recursive_mutex until time abs_time,
   //!Returns false when timeout expires, returns true when locks.
   //!Throws interprocess_exception if a severe error is found
   bool timed_lock(const boost::posix_time::ptime &abs_time);

   //!Erases a named recursive mutex
   //!from the system
   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction();

   #if defined(BOOST_INTERPROCESS_USE_WINDOWS)
      typedef ipcdetail::windows_named_recursive_mutex   impl_t;
      #undef BOOST_INTERPROCESS_USE_WINDOWS
   #else
      typedef ipcdetail::shm_named_recursive_mutex impl_t;
   #endif
   impl_t m_mut;

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_recursive_mutex::~named_recursive_mutex()
{}

inline void named_recursive_mutex::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_mut);  }

inline named_recursive_mutex::named_recursive_mutex(create_only_t, const char *name, const permissions &perm)
   :  m_mut  (create_only, name, perm)
{}

inline named_recursive_mutex::named_recursive_mutex(open_or_create_t, const char *name, const permissions &perm)
   :  m_mut  (open_or_create, name, perm)
{}

inline named_recursive_mutex::named_recursive_mutex(open_only_t, const char *name)
   :  m_mut   (open_only, name)
{}

inline void named_recursive_mutex::lock()
{  m_mut.lock();  }

inline void named_recursive_mutex::unlock()
{  m_mut.unlock();  }

inline bool named_recursive_mutex::try_lock()
{  return m_mut.try_lock();  }

inline bool named_recursive_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
{  return m_mut.timed_lock(abs_time);  }

inline bool named_recursive_mutex::remove(const char *name)
{  return impl_t::remove(name); }

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_NAMED_RECURSIVE_MUTEX_HPP

/* named_recursive_mutex.hpp
knkXKtsWaIPfrwWt/UyHaeMstHG+tDyuLSjIWVhCtC0ttOJ3dT3Kh+sp7+UwX+R8gN0p/wH34eMUZ3ItzfGH0u2rh/Usez1vizKvsZW5nCOqyvxE4PrNYem2+YaqvGvqwT+u35Yx2bevm5Fs7+vaiT3mfEteeezgri5gX9c6P2Bfx+HpLCtS+EWYFl7F5Qfs5+C3/vkXccaLOLmP60Jh4mze7ONY9kwbu5yRbaDJ9p7Hyo7NPs/gNROpjlbxAGGENq9genNc3BDEeol5wGsgpKWWeYU136vb2vN9O+LLVOab5xJB5jszxHxnzgteDmqmH482NjCPlPIarbrS2rOMAxgnzCSYSLSfDG/7ycVNk9K8LMxxmVcn4nk/1iL3N5NoB6t4x+HINRv4jMBUfJO0UiYs7rBYZKNPpu8D5XqB5M5IWfFz8lkXBMXFsoYpNrlG9BBNEtuxmiF7tKnXeCv83YQyuBnmFt5HvSmEvVTwxyYjR6QlnvNt5f2RjlxXde+7SycwEbyvZN4XCb7L/RLao5DyfKUM1ieI/k3IxzgXbkOQDg4DIa9CbLI82F25nlOWCeiV+y+Kusy06v0XxXjN9La1HXSHWvb6Pyaa57FmivPbp5flvulCQdPClD9bQ376UrjJYUa4uRh45bltLMnmNL4Vzbfu+z9F/j/T8tAiGptheAzecvhPg9vRmE/NIp6VsfzVzTCiQmwCZgiMJbvtjNalkMkqwmVdDOa+EcpcymSV7Vy59nQp9pPc9v0k8+w2md2ZN6aeRa+7h8aZv/E48wIYI+xpF3rt3RK99vnS7lO3q7to9NfIodH3CGBL0GgXWep2CHtU8KfYs5B7AFML6CwGtWSsqh6zf3W978L1KJxovtfb4v9k0pDQDloEdcgLcEE2xGjtFfxW1HuErWwjyjoPWvX+CPdxi+j7HtK0qZi3sn/1nmUXrr89iOY1vQNKZBO49wUwVsd7JpgymK0wvmdjko/LyK9bnIaabfBacrsJa/RwU0b7EuL3dWh1pbZ2afhbSzTtkW6n2SdolnqYyHzfQeFHgO8XaTejRf0HNm7LyB59I1nSR9Ffzj7b0EtWts5fDjzTCCEaLH+5bKdNRjPTbDNpVrj9aQbC3pTW8XKvdw2Q5TDTntIG3v9dwG6mexB6oBpqn0m2dV4n+I7z1D7/RLzF2Ru3194FXvs5bF/gZy8v8G3vd7P9QAvf9j0uxZCtwjpWYXogjHIqr7KFeYV5xfnzs3JKCnvY6rqifcNf8HuSRMttINYcZwLrvLaGPYpSj/1DS3+/k76fjbAdtY8ZvP9/K8p5M8wW4+5NEPvDlnKptaxFfuJlfpR9tb9szYxu6jl/mXfuS52sdbof7Ly3LMR5b5nfXHZNA89lrfpZPN3V832PLc801Q8qv54Q8+sJYZ7v8ePNbQ3Mm7rksrc+Ry0Pu2Zx/eRh1yw+ddmggeRhx6Wq5WFrhfWXh60VhiYPWys8dXnAocrD1nqo5WG7C+snD9tdGLx8UHfhqcsHDUYetiEj96Qir8vhP9nMq9i6EYdbwydMGT1xgixn2zpUvd9vKefZsXWXc3I9yhlpsZUz4gxcziyLv4jl2xXCNMfYmerNu3jAsShv/kVZGNmhNkjMzvi+QaLZx0j9ZuQnHzLMdLW8ejNf8E+58ZjjXjp9m4/bCg5bXl2BxrFE3/nFdAoDMpQSNLIXs/1fbF8l7T799ziWz1/B/L+deVDtxwOeSHD+7fPlZ4h+o3a9Wucph2ddYyJEv/PD74mmH0JIMfn6Dbn1wMz1bCXvXqDv5bhF5gx6vufPu+N+vGtZ5GvvXeTLyxHS7lOfRrGs9zN1xAVsBUwQc7Ei5qXBRbE=
*/