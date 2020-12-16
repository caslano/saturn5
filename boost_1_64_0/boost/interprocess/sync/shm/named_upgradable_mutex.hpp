//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NAMED_UPGRADABLE_MUTEX_HPP
#define BOOST_INTERPROCESS_NAMED_UPGRADABLE_MUTEX_HPP

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
#include <boost/interprocess/sync/interprocess_upgradable_mutex.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/shm/named_creation_functor.hpp>
#include <boost/interprocess/permissions.hpp>

//!\file
//!Describes a named upgradable mutex class for inter-process synchronization

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
namespace ipcdetail{ class interprocess_tester; }
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

class named_condition;

//!A upgradable mutex with a global name, so it can be found from different
//!processes. This mutex can't be placed in shared memory, and
//!each process should have it's own named upgradable mutex.
class named_upgradable_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   named_upgradable_mutex();
   named_upgradable_mutex(const named_upgradable_mutex &);
   named_upgradable_mutex &operator=(const named_upgradable_mutex &);
   friend class named_condition;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   //!Creates a global upgradable mutex with a name.
   //!If the upgradable mutex can't be created throws interprocess_exception
   named_upgradable_mutex(create_only_t create_only, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global upgradable mutex with a name, and an initial count.
   //!If the upgradable mutex is created, this call is equivalent to
   //!named_upgradable_mutex(create_only_t, ...)
   //!If the upgradable mutex is already created, this call is equivalent to
   //!named_upgradable_mutex(open_only_t, ... ).
   named_upgradable_mutex(open_or_create_t open_or_create, const char *name, const permissions &perm = permissions());

   //!Opens a global upgradable mutex with a name if that upgradable mutex
   //!is previously.
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   named_upgradable_mutex(open_only_t open_only, const char *name);

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~named_upgradable_mutex();

   //Exclusive locking

   //!Effects: The calling thread tries to obtain exclusive ownership of the mutex,
   //!   and if another thread has exclusive, sharable or upgradable ownership of
   //!   the mutex, it waits until it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   void lock();

   //!Effects: The calling thread tries to acquire exclusive ownership of the mutex
   //!   without waiting. If no other thread has exclusive, sharable or upgradable
   //!   ownership of the mutex this succeeds.
   //!Returns: If it can acquire exclusive ownership immediately returns true.
   //!   If it has to wait, returns false.
   //!Throws: interprocess_exception on error.
   bool try_lock();

   //!Effects: The calling thread tries to acquire exclusive ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive, sharable or
   //!   upgradable ownership of the mutex or abs_time is reached.
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

   //Upgradable locking

   //!Effects: The calling thread tries to obtain upgradable ownership of the mutex,
   //!   and if another thread has exclusive or upgradable ownership of the mutex,
   //!   waits until it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   void lock_upgradable();

   //!Effects: The calling thread tries to acquire upgradable ownership of the mutex
   //!   without waiting. If no other thread has exclusive or upgradable ownership
   //!   of the mutex this succeeds.
   //!Returns: If it can acquire upgradable ownership immediately returns true.
   //!   If it has to wait, returns false.
   //!Throws: interprocess_exception on error.
   bool try_lock_upgradable();

   //!Effects: The calling thread tries to acquire upgradable ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive or upgradable
   //!   ownership of the mutex or abs_time is reached.
   //!Returns: If acquires upgradable ownership, returns true. Otherwise returns false.
   //!Throws: interprocess_exception on error.
   bool timed_lock_upgradable(const boost::posix_time::ptime &abs_time);

   //!Precondition: The thread must have upgradable ownership of the mutex.
   //!Effects: The calling thread releases the upgradable ownership of the mutex.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock_upgradable();

   //Demotions

   //!Precondition: The thread must have exclusive ownership of the mutex.
   //!Effects: The thread atomically releases exclusive ownership and acquires
   //!   upgradable ownership. This operation is non-blocking.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock_and_lock_upgradable();

   //!Precondition: The thread must have exclusive ownership of the mutex.
   //!Effects: The thread atomically releases exclusive ownership and acquires
   //!   sharable ownership. This operation is non-blocking.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock_and_lock_sharable();

   //!Precondition: The thread must have upgradable ownership of the mutex.
   //!Effects: The thread atomically releases upgradable ownership and acquires
   //!   sharable ownership. This operation is non-blocking.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock_upgradable_and_lock_sharable();

   //Promotions

   //!Precondition: The thread must have upgradable ownership of the mutex.
   //!Effects: The thread atomically releases upgradable ownership and acquires
   //!   exclusive ownership. This operation will block until all threads with
   //!   sharable ownership release it.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock_upgradable_and_lock();

   //!Precondition: The thread must have upgradable ownership of the mutex.
   //!Effects: The thread atomically releases upgradable ownership and tries to
   //!   acquire exclusive ownership. This operation will fail if there are threads
   //!   with sharable ownership, but it will maintain upgradable ownership.
   //!Returns: If acquires exclusive ownership, returns true. Otherwise returns false.
   //!Throws: An exception derived from interprocess_exception on error.
   bool try_unlock_upgradable_and_lock();

   //!Precondition: The thread must have upgradable ownership of the mutex.
   //!Effects: The thread atomically releases upgradable ownership and tries to acquire
   //!   exclusive ownership, waiting if necessary until abs_time. This operation will
   //!   fail if there are threads with sharable ownership or timeout reaches, but it
   //!   will maintain upgradable ownership.
   //!Returns: If acquires exclusive ownership, returns true. Otherwise returns false.
   //!Throws: An exception derived from interprocess_exception on error.
   bool timed_unlock_upgradable_and_lock(const boost::posix_time::ptime &abs_time);

   //!Precondition: The thread must have sharable ownership of the mutex.
   //!Effects: The thread atomically releases sharable ownership and tries to acquire
   //!   exclusive ownership. This operation will fail if there are threads with sharable
   //!   or upgradable ownership, but it will maintain sharable ownership.
   //!Returns: If acquires exclusive ownership, returns true. Otherwise returns false.
   //!Throws: An exception derived from interprocess_exception on error.
   bool try_unlock_sharable_and_lock();

   bool try_unlock_sharable_and_lock_upgradable();

   //!Erases a named upgradable mutex from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction();

   interprocess_upgradable_mutex *mutex() const
   {  return static_cast<interprocess_upgradable_mutex*>(m_shmem.get_user_address()); }

   typedef ipcdetail::managed_open_or_create_impl<shared_memory_object, 0, true, false> open_create_impl_t;
   open_create_impl_t m_shmem;
   typedef ipcdetail::named_creation_functor<interprocess_upgradable_mutex> construct_func_t;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_upgradable_mutex::~named_upgradable_mutex()
{}

inline named_upgradable_mutex::named_upgradable_mutex
   (create_only_t, const char *name, const permissions &perm)
   :  m_shmem  (create_only
               ,name
               ,sizeof(interprocess_upgradable_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoCreate)
               ,perm)
{}

inline named_upgradable_mutex::named_upgradable_mutex
   (open_or_create_t, const char *name, const permissions &perm)
   :  m_shmem  (open_or_create
               ,name
               ,sizeof(interprocess_upgradable_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoOpenOrCreate)
               ,perm)
{}

inline named_upgradable_mutex::named_upgradable_mutex
   (open_only_t, const char *name)
   :  m_shmem  (open_only
               ,name
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoOpen))
{}

inline void named_upgradable_mutex::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_shmem);  }

inline void named_upgradable_mutex::lock()
{  this->mutex()->lock();  }

inline void named_upgradable_mutex::unlock()
{  this->mutex()->unlock();  }

inline bool named_upgradable_mutex::try_lock()
{  return this->mutex()->try_lock();  }

inline bool named_upgradable_mutex::timed_lock
   (const boost::posix_time::ptime &abs_time)
{  return this->mutex()->timed_lock(abs_time);  }

inline void named_upgradable_mutex::lock_upgradable()
{  this->mutex()->lock_upgradable();  }

inline void named_upgradable_mutex::unlock_upgradable()
{  this->mutex()->unlock_upgradable();  }

inline bool named_upgradable_mutex::try_lock_upgradable()
{  return this->mutex()->try_lock_upgradable();  }

inline bool named_upgradable_mutex::timed_lock_upgradable
   (const boost::posix_time::ptime &abs_time)
{  return this->mutex()->timed_lock_upgradable(abs_time);   }

inline void named_upgradable_mutex::lock_sharable()
{  this->mutex()->lock_sharable();  }

inline void named_upgradable_mutex::unlock_sharable()
{  this->mutex()->unlock_sharable();  }

inline bool named_upgradable_mutex::try_lock_sharable()
{  return this->mutex()->try_lock_sharable();  }

inline bool named_upgradable_mutex::timed_lock_sharable
   (const boost::posix_time::ptime &abs_time)
{  return this->mutex()->timed_lock_sharable(abs_time);  }

inline void named_upgradable_mutex::unlock_and_lock_upgradable()
{  this->mutex()->unlock_and_lock_upgradable();  }

inline void named_upgradable_mutex::unlock_and_lock_sharable()
{  this->mutex()->unlock_and_lock_sharable();  }

inline void named_upgradable_mutex::unlock_upgradable_and_lock_sharable()
{  this->mutex()->unlock_upgradable_and_lock_sharable();  }

inline void named_upgradable_mutex::unlock_upgradable_and_lock()
{  this->mutex()->unlock_upgradable_and_lock();  }

inline bool named_upgradable_mutex::try_unlock_upgradable_and_lock()
{  return this->mutex()->try_unlock_upgradable_and_lock();  }

inline bool named_upgradable_mutex::timed_unlock_upgradable_and_lock
   (const boost::posix_time::ptime &abs_time)
{  return this->mutex()->timed_unlock_upgradable_and_lock(abs_time);  }

inline bool named_upgradable_mutex::try_unlock_sharable_and_lock()
{  return this->mutex()->try_unlock_sharable_and_lock();  }

inline bool named_upgradable_mutex::try_unlock_sharable_and_lock_upgradable()
{  return this->mutex()->try_unlock_sharable_and_lock_upgradable();  }

inline bool named_upgradable_mutex::remove(const char *name)
{  return shared_memory_object::remove(name); }

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_NAMED_UPGRADABLE_MUTEX_HPP

/* named_upgradable_mutex.hpp
tnTfjcw8gHX2w8HAm2Yd6DjvoXUget4068B7xHto4PT7JOGTI+ZXn4/kIUee6UV8ZvFqESHPyWH5mBZFPkJ8UXb8vd34m6V7sIHb73L7OXWg41yEOQfa30+5/G3N05sZgY8v90DH+fhy21Cvcg+0vx1FU69CfVUwAh9f/oFTw8eXfyD6/jn/QPv75+j4+JKb+CaVj28K0k3nzW8lfMEBdw21fCoRnXtfZS2zKY+EM3zjmPOIrvvOc7u806yw9cRG2vbbIH5l4ncIP5ejgHx4OFrWSDyZxBMn78B2zhJT9Dule57vHSWkMyxFuX2Ss9w+y/Oe3DfCu7yvfml5aFm73yj6zm/nh/zZerZb8rJB3GXO2uKaQKQ1nW1fQ9y7yPbftX9ftxl7X3kn8O3bDyWckXh55DXE5jWjkdfamtfORl77a17zeurWHJvXXkde+2teCxt57fXbuhbS0rWwhaG1sO6xjMNss9z1r5nO+lf3+HzP8eme4wGe4wvceGTsaDpon8vR4xWIzEGHxrp0THB62Bz0JN1jfDKYBk4Bs3QtSx9bHzwTvBgcpXs0TwYvAWeAl4KI7O08GywArwQvA0vAy8EycA54M3g1eAc4H9yga26qwQW6l/W1ulf5UvA7YCn4lKZnl67BqQOLdC/zEvB5Pf9nCadjIuBizW83ib/pl6v5PRfMAfPAEeBo8FzwPHC6nv8w+CHwWt0rfiE4BiwRt7tH3w69Xn+9nnePvhT0bEwF+4FpnnCNGq6HIVyGhsvUNUlZbjj9NiYuQ7jlGm4FmAqWazjbM0fDrdNw3jVYazXcLWAX8Da9/+vBXN2TfBx4JzhN/a/WNUoLwHu0fO4CS9S9GPwIeIu6nbWc+31rJY1rZuuj1Gt09WgTkdfCHotSzzrg6mW2sDY0OUq9nCj1cqPUy49Cr1Cfm/Ks0vvdFZmjeqfpp/AAMAU8Q9v9meAQ8CxtF4P0/g8F88Ah4CR1PxtrnZL1HM3XcvjXcexHTOs3zGs3vOs1Ts1aDV2n4Vmj4V+f4V2bkXmZdz2GeS3Gpst8azB86y+ar70wr7vwrrnYdVfr6yzcNRYtr6+o3+BfVzEYidM1FLp+wl070cZ1E6Y1E+b1Er51ErpGwrc+ovnaiDaui2hpHUSNs/ahY3shtrzewV3j4K5vMK5r8K5pkPUM+WspL6QKqUF2IQeRk0jOTaxXQCqQGqQOOYwk38yeg0jhzZ1rEzp/nb/3fv4fjjKZ/u/4/P/EVMvZT6xWm/N4e32+4ib7O73BO8chttQ2eaudigoidDjDAh4+slteFu5Gxwa6UOIImr/nG9zv+Tdk/JmYV7nz6SVyflDgBr5l/2b1MX/nNxg5Bh2OjdVyPiNg4lvaIOcaHDv+BZL2XN6bYyLazu+TMGXqDoXJEP0LUpVHzsOj9BXRf8zhP64R93GrK36/0DnWs9L9XJRlopcTSAzEWtk6f77BXt9uz43E9QoGkoKJXS0/r1E/1d0V0g2MFl6jqschNorEeaphGjmxR2zzp/vGNdJVJzG0LiBQ9UgwqZs7bhaml4tevR1Xj9uDcMz492hTvTnojUux9apeDo8rG3e88qPakq8cqWdFwVUUmg8tkvGStc74iV3Pems9886bbI3zj8/1yaJMXjbNm8hQJNdQ/uHI43IaPqC8EC2ORaLb/rFI0uEbl+N6xjHuOfH+vB6hXI45edVhyEsnFRRcPGuaTmlJHg63PE9EHO0fKyZu4741BQn+9P5JGqM5ve6uNZb2La3MQ3jWFk2IYt8aa1/7960hLb59aya0sG9NvmFvvqPEkRwp7zJqHN29St4X/Zhx8r72jxkfjmJOL5Tf3ETz/FrOvo7Pr+U=
*/