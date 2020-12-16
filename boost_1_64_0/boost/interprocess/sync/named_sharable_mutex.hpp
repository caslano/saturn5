//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NAMED_SHARABLE_MUTEX_HPP
#define BOOST_INTERPROCESS_NAMED_SHARABLE_MUTEX_HPP

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
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/sync/interprocess_sharable_mutex.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/shm/named_creation_functor.hpp>
#include <boost/interprocess/permissions.hpp>

//!\file
//!Describes a named sharable mutex class for inter-process synchronization

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
namespace ipcdetail{ class interprocess_tester; }
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

class named_condition;

//!A sharable mutex with a global name, so it can be found from different
//!processes. This mutex can't be placed in shared memory, and
//!each process should have it's own named sharable mutex.
class named_sharable_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   named_sharable_mutex();
   named_sharable_mutex(const named_sharable_mutex &);
   named_sharable_mutex &operator=(const named_sharable_mutex &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   //!Creates a global sharable mutex with a name.
   //!If the sharable mutex can't be created throws interprocess_exception
   named_sharable_mutex(create_only_t create_only, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global sharable mutex with a name.
   //!If the sharable mutex is created, this call is equivalent to
   //!named_sharable_mutex(create_only_t, ...)
   //!If the sharable mutex is already created, this call is equivalent to
   //!named_sharable_mutex(open_only_t, ... ).
   named_sharable_mutex(open_or_create_t open_or_create, const char *name, const permissions &perm = permissions());

   //!Opens a global sharable mutex with a name if that sharable mutex
   //!is previously.
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   named_sharable_mutex(open_only_t open_only, const char *name);

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~named_sharable_mutex();

   //Exclusive locking

   //!Effects: The calling thread tries to obtain exclusive ownership of the mutex,
   //!   and if another thread has exclusive or sharable ownership of
   //!   the mutex, it waits until it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   void lock();

   //!Effects: The calling thread tries to acquire exclusive ownership of the mutex
   //!   without waiting. If no other thread has exclusive or sharable
   //!   ownership of the mutex this succeeds.
   //!Returns: If it can acquire exclusive ownership immediately returns true.
   //!   If it has to wait, returns false.
   //!Throws: interprocess_exception on error.
   bool try_lock();

   //!Effects: The calling thread tries to acquire exclusive ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive, or sharable
   //!   ownership of the mutex or abs_time is reached.
   //!Returns: If acquires exclusive ownership, returns true. Otherwise returns false.
   //!Throws: interprocess_exception on error.
   bool timed_lock(const boost::posix_time::ptime &abs_time);

   //!Precondition: The thread must have exclusive ownership of the mutex.
   //!Effects: The calling thread releases the exclusive ownership of the mutex.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock();

   //Sharable locking

   //!Effects: The calling thread tries to obtain sharable ownership of the mutex,
   //!   and if another thread has exclusive ownership of the mutex,
   //!   waits until it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   void lock_sharable();

   //!Effects: The calling thread tries to acquire sharable ownership of the mutex
   //!   without waiting. If no other thread has exclusive ownership
   //!   of the mutex this succeeds.
   //!Returns: If it can acquire sharable ownership immediately returns true. If it
   //!   has to wait, returns false.
   //!Throws: interprocess_exception on error.
   bool try_lock_sharable();

   //!Effects: The calling thread tries to acquire sharable ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive
   //!   ownership of the mutex or abs_time is reached.
   //!Returns: If acquires sharable ownership, returns true. Otherwise returns false.
   //!Throws: interprocess_exception on error.
   bool timed_lock_sharable(const boost::posix_time::ptime &abs_time);

   //!Precondition: The thread must have sharable ownership of the mutex.
   //!Effects: The calling thread releases the sharable ownership of the mutex.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock_sharable();

   //!Erases a named sharable mutex from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction();

   interprocess_sharable_mutex *mutex() const
   {  return static_cast<interprocess_sharable_mutex*>(m_shmem.get_user_address()); }

   typedef ipcdetail::managed_open_or_create_impl<shared_memory_object, 0, true, false> open_create_impl_t;
   open_create_impl_t m_shmem;
   typedef ipcdetail::named_creation_functor<interprocess_sharable_mutex> construct_func_t;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_sharable_mutex::~named_sharable_mutex()
{}

inline named_sharable_mutex::named_sharable_mutex
   (create_only_t, const char *name, const permissions &perm)
   :  m_shmem  (create_only
               ,name
               ,sizeof(interprocess_sharable_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoCreate)
               ,perm)
{}

inline named_sharable_mutex::named_sharable_mutex
   (open_or_create_t, const char *name, const permissions &perm)
   :  m_shmem  (open_or_create
               ,name
               ,sizeof(interprocess_sharable_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoOpenOrCreate)
               ,perm)
{}

inline named_sharable_mutex::named_sharable_mutex
   (open_only_t, const char *name)
   :  m_shmem  (open_only
               ,name
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoOpen))
{}

inline void named_sharable_mutex::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_shmem);  }

inline void named_sharable_mutex::lock()
{  this->mutex()->lock();  }

inline void named_sharable_mutex::unlock()
{  this->mutex()->unlock();  }

inline bool named_sharable_mutex::try_lock()
{  return this->mutex()->try_lock();  }

inline bool named_sharable_mutex::timed_lock
   (const boost::posix_time::ptime &abs_time)
{  return this->mutex()->timed_lock(abs_time);  }

inline void named_sharable_mutex::lock_sharable()
{  this->mutex()->lock_sharable();  }

inline void named_sharable_mutex::unlock_sharable()
{  this->mutex()->unlock_sharable();  }

inline bool named_sharable_mutex::try_lock_sharable()
{  return this->mutex()->try_lock_sharable();  }

inline bool named_sharable_mutex::timed_lock_sharable
   (const boost::posix_time::ptime &abs_time)
{  return this->mutex()->timed_lock_sharable(abs_time);  }

inline bool named_sharable_mutex::remove(const char *name)
{  return shared_memory_object::remove(name); }

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_NAMED_SHARABLE_MUTEX_HPP

/* named_sharable_mutex.hpp
Lsd/jOcnHwOHAv8NHA08zjKrPwNeAKzh/H4O9AC/4HSdAK4Gfs/pOgm8j3UI3A8MQz15iWXqvsc6Br5gHQHfsI6AH1lHQFMdZQNsBXQBL5EyeDHgOJVyeFvD3ZDFm13lUMrbtcra3bFbytutYpm7Qt7uvt2/jszdQ7t/Gbm7AWTu/qzydgekOeuUuXt8d+hydyOrkHYYu/xdu+zdtKrg5e8OqwpOBq+nSsrhXVtlk8VLcnjHpTmDlsW7rcpfHm/osnj3Vtnk8ZqyeMMGmzJ4Tfm7B6qkDN5jVfWXw3uySimL1yaH173n/1MW74A9tcvjXb/bK5M3c4+vXN5Fe0KTzZuNerMaphLmEIzWG/JyYUbBeGDKYXbBHIQ5AdOyD2Rmw8yGKYPZBrMP5ihMJJSKpMJMhfHArIXZDrMP5ihMWDrChhkH44HZDLMX5nD6afm6p/9O//1W/34x+X/z8ktLSoUAwPrJ/2sLGX/9xTnieJL/V5IlRJHQeU1Wac68ArHNSDTngkYjOYAX5V2ataQkZ2GelYpkAeIuhPlmI9fB+uN47TAU5jyEcSCHzivzey71KqMfMnpq1pSpk0dPGOm9//xNrLz/HFD3a46/7n3BDHlX+H363lV5Rsl+5T0Sel8saVwWGj63JNrkViQJCw/25JnfIaI715TrkYnwOiruFEQGeC+OvMp7vzb9/pQnPl/jeyacVuu5sNsZQAf+vPrd+Umd13B3foy0nnSq775kzKvf3ZeMecHffcmY9/PefTHq/7YIUy8UrYmvAw4U9T/Le17fM78e9T8r+HuUTCvru5STQ20lKlt8n6QP0NZAF1eK8qyew7DKxzHl7ESz/w9RmtF6uF9bkfKH+hJde/1hhPhPxBLLbzOSyf0A7hg/bJOvk8B3Ds4mmjS9tXYd9gR6sLvh9zVI5mmNvfebzXN8r/tgXZ7VzyuxyhbaQ9/naq209sIPnT+/R3n8vS7khQgm14TzHeSw3q6oCJde9hKJFVTK8ElgPy0jDBk+mULcj02Oj/GOYBqf0U9nfDSGz+zpd91n9er+o1aZBNx/UNnLs/VfQIdzqGfuoeoiVp/Fh67zeec44b7r9sKU1icvP39rv001s9aeuKXhzujVZ/GBzu4bThe0+ky/4c7if82z9daWs/VLzLN1+ZvOLozxnOcikbrv2UUP3qPsBWwOTOOzht7ANHYfCOwLHOqrt5THSN4jrU0/WRB0R8x+lsYMSqfoRg8y3XmsH28I68UbCuzK+nm7AefwXucIYCafOcwGjgIWA8cA32T7+8CprPdxLOu3E3bESf4TgbMFH4Ai3I7AccB04ATgYOBE4Ej+PhY4DTgHeD5wGXAG67ebCbyO6XaEIT9fY08B5vAgJxjjDEoPmGrfUa3j67et3+vX2Gf85hfQ6/Vr6PSqjz6vUPcPQ9k7/Dl1d/2W9HYdb+5scN1d7dEfjYJZBLM249T26X659T9ev5TUf/3fEWv7JEzQU1LDMS8cMnjK6KFiFYYlyeDRE6ZOwXOi32WVlnrX99tMWf/ybDuW8y0cH0c4qd71jS0gvtdPa4jdoNO1HPW6M8t3fbYgpm5ZrMabVhFuPMK1rsNOcjojLGvOb5pj6JkTIJ35pXXGlwCe/ZCAMZN4VlCE6/vw5iuHpoD3P5qyxyYwg4RczED8Kcy7GCRmvhcGkW9rfOu5uiYyQSuYIbB4vPHlYr1pi1Pj8shIDFweHsv68XhzWlsXqmW++NLG0jwn8Hs9j185/z6m7rdSRjkjvaKczfWOSFc8pwtuHBfcOH4rn5b76TKIhxkm9r+8fMJDfAWfgqi35Za8f0d8KlpSquKTpJWypELIO9Lgk3cRVzzHZX0=
*/