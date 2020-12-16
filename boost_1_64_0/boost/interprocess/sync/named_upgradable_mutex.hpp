//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_named_upgradable_mutex_HPP
#define BOOST_INTERPROCESS_named_upgradable_mutex_HPP

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

   //!Opens or creates a global upgradable mutex with a name.
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

   //!Precondition: The thread must have sharable ownership of the mutex.
   //!Effects: The thread atomically releases sharable ownership and tries to acquire
   //!   upgradable ownership. This operation will fail if there are threads with sharable
   //!   or upgradable ownership, but it will maintain sharable ownership.
   //!Returns: If acquires upgradable ownership, returns true. Otherwise returns false.
   //!Throws: An exception derived from interprocess_exception on error.
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

#endif   //BOOST_INTERPROCESS_named_upgradable_mutex_HPP

/* named_upgradable_mutex.hpp
X3UgnOe3MDrrEh8h6t8cc/9Nkc/g9yBEOJxf5gt1SObe2DR8V+7BSb9SppSULS7riKTj+sNrb5YvdlFM3XL7al8nMy853QlynWyXdc48XR6h3murzKrfXltlVsPvtS1qpN5rq86q315bdVbwe23VWT/vXptR1yMb8ztl3msbCxwp2vQcY6+tfnW9fE7w+23ltrpNzPXZf3qRaJ7EPdLLlH0jh6GUR/0afYvQ92jhtv0y473Uv4nmM+1WhEBusL1HbvdpUXDlNos/2WYFI7Pmss4C3ke7l/z00sV7+gLUpxPI4F3Ik6tJYzlO8Xv6JKbpHGXsm6W79EZC/HVY2W2uqHDlvhn7yYwy9s0mK/fNjPhL8W2XoItZkSbnB74yssvgJwdpfDvGV75nWB1vX/bNNd6+1N1v2N90c79hlrXcYzvwC+yxqffAAu29hb43doz2xi6f0mfLmIcT0i48+tO6GUfnZv/8e2MNtQd2X4pwb3rAtXpBu3cHfvnntEfiF49eFGjvreH2Jn/Le29plr23Sp333uRv6ieq6U69aLPyt7l3xntdIKNvck+M6OTe2RwvXYSCrrOFLpPDa1pHeB6mS6yDrpzpEmqhyzDmKMAeivvbqaCjb8AEfh/QmfcUU4lOxkdzAPZfqQfeS6wOgq7SHEOoTlG6msNss7w7aMzvDJKAg/heZgbvIU4FpvNe42Tea5zLe43XA4cDb+U9xhd4T/EI04u6kQn8kcMRiRgLjOU9xDTgZL4vPIX3DgXdi2He+4h7v/buB64e7GywPcHfut7/3+q+YF36/g+/8r+5P9gQ+v7tuv5P7xWe6l5hQ+8TVqJvOgRzEiZ5CPTtwyyCWQuzA+bAkFPbOzz9d/rv9N/pv9N/p/9O/53+O/13+u/03//X3y92/p9Tkp/bAPr/k/j8f30XcZY9eMrknMKFeeapv2Z+P8TfR+dOLCYayG4DiXl/oHVX43teYWn+gvy84qGLivLnG2RaW6bLttGV+NwxuCdWY/lxtC9Mf9/z/t93MO80x57kcDrX8UnMYo/3/Ort5nRGmxXgLIf96hbaeVnq82ym5XOYUc29mrAT+Xwzib4d19aKkxyYN33ocky5xy2J7nOSXfcszD9h5LlOsXn28tRwX/3RkSPoLMbUX3ZvrNdcEeNngnhvYJypifzGM2/4LIPdiAe+OmWc9vsdk0GbOcLGe3Gzg/I0onnA83H4O/V7HSO86fZJ3wGn+l5H2TBb+nA1o+64jDsdWlfbnQ6p/zDMfqejUNyxsPMEtzlCv8thyM1cHeX9MB15FJ4mAz2Ip5zjUTSynMKiwvzL8rxnmsMS6IySPmkW3VnNRgr/UUgLywGk8IY6C7RH9Z6OMO0xR5aW7gxjGfgcH1KxxhEny5Ld5RmwRUcfnxs+IL4jJJXe9BOjKA3meea/ifYlR5TjD6Y88JmjvbL+E437+6izi3MuyfIULCnJKirkPA0hXZX3kv8BTpGWiHjvuwNNk3qAt9L3/s4DjnA8cw/XLG8CRJiUDlHH51C6+qIedaT6W8Oy/izxk/sxdjfDyC8k96N+9HA3w15IfG+jR2jxuqA9DlpuLyIMU7/MzZSGDlosv0nQyF+VoxX4L+lzzHcR0fT9fsejult7Xt9K4cSZ/EskP03JT7EpY7CE4ojW22jvs5uurSc3B9L2seaf56ZcF1pRmHM1vzya7yf4uzWdZpn/QOG3Nvu2bqOlvPcBCHxcI68eL1d0P80m751pPKDZIWgiJ5g097M+9bZMs90IxzndFR7ucka4nCuOen+pdS+zvxfh7wE6115mP3tmmhqDJsoTkCYukuOPXHlBoHykg+ZBQeNe2c2gaR7rSzM7kuM=
*/