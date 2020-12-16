//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_FILE_LOCK_HPP
#define BOOST_INTERPROCESS_FILE_LOCK_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/detail/os_thread_functions.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/detail/common_algorithms.hpp>
#include <boost/interprocess/sync/detail/locks.hpp>
#include <boost/move/utility_core.hpp>

//!\file
//!Describes a class that wraps file locking capabilities.

namespace boost {
namespace interprocess {


//!A file lock, is a mutual exclusion utility similar to a mutex using a
//!file. A file lock has sharable and exclusive locking capabilities and
//!can be used with scoped_lock and sharable_lock classes.
//!A file lock can't guarantee synchronization between threads of the same
//!process so just use file locks to synchronize threads from different processes.
class file_lock
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   BOOST_MOVABLE_BUT_NOT_COPYABLE(file_lock)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructs an empty file mapping.
   //!Does not throw
   file_lock()
      :  m_file_hnd(file_handle_t(ipcdetail::invalid_file()))
   {}

   //!Opens a file lock. Throws interprocess_exception if the file does not
   //!exist or there are no operating system resources.
   file_lock(const char *name);

   //!Moves the ownership of "moved"'s file mapping object to *this.
   //!After the call, "moved" does not represent any file mapping object.
   //!Does not throw
   file_lock(BOOST_RV_REF(file_lock) moved)
      :  m_file_hnd(file_handle_t(ipcdetail::invalid_file()))
   {  this->swap(moved);   }

   //!Moves the ownership of "moved"'s file mapping to *this.
   //!After the call, "moved" does not represent any file mapping.
   //!Does not throw
   file_lock &operator=(BOOST_RV_REF(file_lock) moved)
   {
      file_lock tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Closes a file lock. Does not throw.
   ~file_lock();

   //!Swaps two file_locks.
   //!Does not throw.
   void swap(file_lock &other)
   {
      file_handle_t tmp = m_file_hnd;
      m_file_hnd = other.m_file_hnd;
      other.m_file_hnd = tmp;
   }

   //Exclusive locking

   //!Effects: The calling thread tries to obtain exclusive ownership of the mutex,
   //!   and if another thread has exclusive, or sharable ownership of
   //!   the mutex, it waits until it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   void lock();

   //!Effects: The calling thread tries to acquire exclusive ownership of the mutex
   //!   without waiting. If no other thread has exclusive, or sharable
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
   //!   and if another thread has exclusive ownership of the mutex, waits until
   //!   it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   void lock_sharable();

   //!Effects: The calling thread tries to acquire sharable ownership of the mutex
   //!   without waiting. If no other thread has exclusive ownership of the
   //!   mutex this succeeds.
   //!Returns: If it can acquire sharable ownership immediately returns true. If it
   //!   has to wait, returns false.
   //!Throws: interprocess_exception on error.
   bool try_lock_sharable();

   //!Effects: The calling thread tries to acquire sharable ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive ownership of
   //!   the mutex or abs_time is reached.
   //!Returns: If acquires sharable ownership, returns true. Otherwise returns false.
   //!Throws: interprocess_exception on error.
   bool timed_lock_sharable(const boost::posix_time::ptime &abs_time);

   //!Precondition: The thread must have sharable ownership of the mutex.
   //!Effects: The calling thread releases the sharable ownership of the mutex.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock_sharable();
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   file_handle_t m_file_hnd;

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

inline file_lock::file_lock(const char *name)
{
   m_file_hnd = ipcdetail::open_existing_file(name, read_write);

   if(m_file_hnd == ipcdetail::invalid_file()){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}

inline file_lock::~file_lock()
{
   if(m_file_hnd != ipcdetail::invalid_file()){
      ipcdetail::close_file(m_file_hnd);
      m_file_hnd = ipcdetail::invalid_file();
   }
}

inline void file_lock::lock()
{
   if(!ipcdetail::acquire_file_lock(m_file_hnd)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}

inline bool file_lock::try_lock()
{
   bool result;
   if(!ipcdetail::try_acquire_file_lock(m_file_hnd, result)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
   return result;
}

inline bool file_lock::timed_lock(const boost::posix_time::ptime &abs_time)
{  return ipcdetail::try_based_timed_lock(*this, abs_time);   }

inline void file_lock::unlock()
{
   if(!ipcdetail::release_file_lock(m_file_hnd)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}

inline void file_lock::lock_sharable()
{
   if(!ipcdetail::acquire_file_lock_sharable(m_file_hnd)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}

inline bool file_lock::try_lock_sharable()
{
   bool result;
   if(!ipcdetail::try_acquire_file_lock_sharable(m_file_hnd, result)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
   return result;
}

inline bool file_lock::timed_lock_sharable(const boost::posix_time::ptime &abs_time)
{
   ipcdetail::lock_to_sharable<file_lock> lsh(*this);
   return ipcdetail::try_based_timed_lock(lsh, abs_time);
}

inline void file_lock::unlock_sharable()
{
   if(!ipcdetail::release_file_lock_sharable(m_file_hnd)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_FILE_LOCK_HPP

/* file_lock.hpp
oMd9FB53A9u7LVW0KautIBWvEIeUh76Zx2sFn5hOlv0lG2W32uGR8tA3K8bwxawQn8aRiLRfE3Lf/nKWqcoZ+l1D4bmOPyC6yjXV6vbAtLKcXhvllO8lcx1/QH5Kyzx+x1nL2YJyFslyqtu+jfG7qB1lLepEWZGHEGVl+e3ubFOOZVFuAb4u2u5uLuv1AcsqzyYx2i9GNhqgMz6Zwl/j8NuZGk/+YsdsId3mWKSfKzGrnmzaqtv+buaV5KmYmVEa9UhjGj1f4vDrMWaT/1roHj+BtdfLVTw1x0l5x7kBnO9axDmDnl/t8Ot7DSV/f9V4g7gsZy1gcJA24l+k5xdZyprA/QGaFOVVS+UZGMVEX8R+P/0Yox0NqIDLczrWE/021OVFlP865P8yulfgMOt5sg1delbicDh6aDPhfDxg2/DVUo90NNddjMMNGawkque3SbcJc2KRA26ve/kcBU8klR1PZFlepThylWXhNEEu9eqW7Tadu8D0qZqw3zEH/XEgGD6JdEuHumK7u7p5X3Y5EwLYbkziMPkIMzyRbHMslvpPZpoVoBkkaKLW92urO57GNFtcbAckoswVFWmxL6nH1QS6z5M+6wwLzQXwi/bXLwm8SfSdOdQf1wPY1RrscJSp9VunIxjinUTnjaRqDtItJz6xbrk860Zlf4PHBO5DZvsbovopPNWpqOtUWdcmHbfW7hZ5fpqzeRpYnr/tK6CTejH+cao+wZruQyiPN2i6UjemPpQuQUPHdWPqpX6AiVf1PRS6PMJ2YLA8S4VAHveC5htxSX3AW1NC6wPWNHRcHxB5segDIs2A+oBb3QrdD5S/Lmj5oR9ks+y+eBw8ngbVDwJtx/WDdin0P5CeUh9wc6K1zA0I3xiszLQNbq+dNjbY13lpbOi4zku9DZ0Xv47POUWZr0L45garvcPOjAWTOL2GJLUtyJaGztmCbOnEGDA3gH5cXbI1r1WgPanIq6XvJ4XQ3Tb0/R3Jofv+yc70/SRr3xdpyr5vrqPNKWobmK0NnbOB2dqO9t/aifZvxwam3ufT2Y4M643sB/4a99wP+m3MtW8OrSg34rIv6wNata05nt/NpufXO97TohTzWnP4n1H7XUozAbIXZ5rzeXBfnlFSR+H+hnA/1edx9z9E5zspbdcXEn2l4x0txjAnLl2KpqTbl1tDNHMchzQX38MMlu6dQF0c4jNTeG5Ks29p0/gxohtGc+NW5NsXrtwh59NLV11jOL9uFT2/wLFZu0Oft26h/A/X30ea4RvkNOLsT2F2O5KYJ3KOLOP9QNAgzknS/j6XoRh5+YH2K+1LdBZGDQp8DmkMpLOMumlt56OZTJPd02/L7mKXIxrG0V0O709dsRHKuTCHWYAwg+gsR498BzJNb6bxguYCSvtyhT09c3z1Pf228Yqs82GmOQKawSK+xPXb2s6/h8Efx+dNxoBmFu6/nijnwfe4zXPilBC26R55yP48uH126Kjt0zl+2x7UbUbrMmstXSiz1l7ZNLWsWSDZt/bLoE0nGbS/7Yv74brf7Z27+YmhjWP3j7yn62TQPmlZM7Wdt0Cyb+2X9ftflWV7n3TPpH25EiDbl9OvhxuuB8lrGruOIN6HxX15TePKceA4uEmJ8v7nDdeDDfS6vsgeaefreBu9jXFG/ROmi1bQjTHQeZguIUR8NZZ01XbDtN2B051otJsi0w0aXwvT9Q6Rv1ZJFzC+Cf51YWA60+l6TGxXRuAuYBJwN+st1hv1fzh8Woj8FEm6gPlp1dfMaL0RdGZ7dTmgywLmsd2UmcAZbE+lkO2pLAbOAZYBC9mOTgGwgv0rgUVsV2cu28uZB2xmPZ/DwIXAFuBlwBPAy4E=
*/