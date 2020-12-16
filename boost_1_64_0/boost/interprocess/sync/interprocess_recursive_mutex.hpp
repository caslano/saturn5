//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
//
// Parts of the pthread code come from Boost Threads code:
//
//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2001-2003
// William E. Kempf
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation.  William E. Kempf makes no representations
// about the suitability of this software for any purpose.
// It is provided "as is" without express or implied warranty.
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_RECURSIVE_MUTEX_HPP
#define BOOST_INTERPROCESS_RECURSIVE_MUTEX_HPP

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/assert.hpp>

#if !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && \
   (defined(BOOST_INTERPROCESS_POSIX_PROCESS_SHARED) && defined (BOOST_INTERPROCESS_POSIX_RECURSIVE_MUTEXES))
   #include <boost/interprocess/sync/posix/recursive_mutex.hpp>
   #define BOOST_INTERPROCESS_USE_POSIX
//Experimental...
#elif !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/recursive_mutex.hpp>
   #define BOOST_INTERPROCESS_USE_WINDOWS
#elif !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   #include <boost/interprocess/sync/spin/recursive_mutex.hpp>
   #define BOOST_INTERPROCESS_USE_GENERIC_EMULATION
#endif

#if defined (BOOST_INTERPROCESS_USE_GENERIC_EMULATION)
namespace boost {
namespace interprocess {
namespace ipcdetail{
namespace robust_emulation_helpers {

template<class T>
class mutex_traits;

}}}}

#endif

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!\file
//!Describes interprocess_recursive_mutex and shared_recursive_try_mutex classes

namespace boost {
namespace interprocess {

//!Wraps a interprocess_mutex that can be placed in shared memory and can be
//!shared between processes. Allows several locking calls by the same
//!process. Allows timed lock tries
class interprocess_recursive_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   interprocess_recursive_mutex(const interprocess_recursive_mutex &);
   interprocess_recursive_mutex &operator=(const interprocess_recursive_mutex &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:
   //!Constructor.
   //!Throws interprocess_exception on error.
   interprocess_recursive_mutex();

   //!Destructor. If any process uses the mutex after the destructor is called
   //!the result is undefined. Does not throw.
  ~interprocess_recursive_mutex();

   //!Effects: The calling thread tries to obtain ownership of the mutex, and
   //!   if another thread has ownership of the mutex, it waits until it can
   //!   obtain the ownership. If a thread takes ownership of the mutex the
   //!   mutex must be unlocked by the same mutex. The mutex must be unlocked
   //!   the same number of times it is locked.
   //!Throws: interprocess_exception on error.
   void lock();

   //!Tries to lock the interprocess_mutex, returns false when interprocess_mutex
   //!is already locked, returns true when success. The mutex must be unlocked
   //!the same number of times it is locked.
   //!Throws: interprocess_exception if a severe error is found
   bool try_lock();

   //!Tries to lock the interprocess_mutex, if interprocess_mutex can't be locked before
   //!abs_time time, returns false. The mutex must be unlocked
   //!   the same number of times it is locked.
   //!Throws: interprocess_exception if a severe error is found
   bool timed_lock(const boost::posix_time::ptime &abs_time);

   //!Effects: The calling thread releases the exclusive ownership of the mutex.
   //!   If the mutex supports recursive locking, the mutex must be unlocked the
   //!   same number of times it is locked.
   //!Throws: interprocess_exception on error.
   void unlock();
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:

   #if defined (BOOST_INTERPROCESS_USE_GENERIC_EMULATION)
      #undef BOOST_INTERPROCESS_USE_GENERIC_EMULATION
      void take_ownership(){ mutex.take_ownership(); }
      friend class ipcdetail::robust_emulation_helpers::mutex_traits<interprocess_recursive_mutex>;
      ipcdetail::spin_recursive_mutex mutex;
   #elif defined(BOOST_INTERPROCESS_USE_POSIX)
      #undef BOOST_INTERPROCESS_USE_POSIX
      ipcdetail::posix_recursive_mutex mutex;
   #elif defined(BOOST_INTERPROCESS_USE_WINDOWS)
      #undef BOOST_INTERPROCESS_USE_WINDOWS
      ipcdetail::windows_recursive_mutex mutex;
   #else
      #error "Unknown platform for interprocess_mutex"
   #endif
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

}  //namespace interprocess {
}  //namespace boost {

namespace boost {
namespace interprocess {

inline interprocess_recursive_mutex::interprocess_recursive_mutex(){}

inline interprocess_recursive_mutex::~interprocess_recursive_mutex(){}

inline void interprocess_recursive_mutex::lock()
{
   #ifdef BOOST_INTERPROCESS_ENABLE_TIMEOUT_WHEN_LOCKING
      boost::posix_time::ptime wait_time
         = microsec_clock::universal_time()
         + boost::posix_time::milliseconds(BOOST_INTERPROCESS_TIMEOUT_WHEN_LOCKING_DURATION_MS);
      if (!mutex.timed_lock(wait_time)){
         throw interprocess_exception(timeout_when_locking_error, "Interprocess mutex timeout when locking. Possible deadlock: owner died without unlocking?");
      }
   #else
      mutex.lock();
   #endif
}

inline bool interprocess_recursive_mutex::try_lock()
{ return mutex.try_lock(); }

inline bool interprocess_recursive_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
{ return mutex.timed_lock(abs_time); }

inline void interprocess_recursive_mutex::unlock()
{ mutex.unlock(); }

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_RECURSIVE_MUTEX_HPP

/* interprocess_recursive_mutex.hpp
n8prTj34vh9wMNs0HQScwDZ7q5Gv+s8xz0502NL3jvdQ7P9whPTe3/rO37J3/m/rff+/7V3/bL3n29X5Hp3kCPqO3/p+H977fY+k1nf11l/rr/XX+mv9fYvv/3hVn38W3v978v7/rEyxh330tJw5Y7Kn583JnZI9OU9q5teI7wKxB5T4sqdPnwE7diZetgZA6wlp4Dt6ieDzrCXMWVBUsLDUYwOgN9yyhgs3k19SelhQXqFJewMzVTxsTqAbeHoJ3baSR6aB7QiMMtkR6BthPafQR+z13kLrFs0yTRs2aa2hd6B93ltafkYB4Vp0au/1c0ahYbMqjSiYEM4n5GX612Uf57CeT0gX5ayWDTb7hn42wRvXMwp7Av0QV5UnrmaFLcvBmeS/HKrCKAeEaymHvpHqcshQpjG0cth/if9yqFbYFOgP2dQq4w2pHCZabAq0sZbDg6KuWeKS53VqAuh1awitDCaay6BGYdNhfxs/53U2N0tfqOd0hvvXzZoUZZX/AHGWqblMQjufM7H5+ZxTvNf9Ed7vsU8Q+ru4rc3jgYbmOfNdQnM2pctoB3hmsumZTP4e1Prg752ge9W6hRG+XBvt7bG9iqBV66i+vNsgd5RoScFCyJH3e/Yn91VaHHJWAVLt6xxDPIUoWQeFcyvlvrjQvNZ6NfEkauKMRSfIPx+yuQKVEqcraJNkP39nLJh/PfhHJ9AeSdP+SN99jWPgPhb0JSIcp9Bv7FTq4ua+gWQt9zQKuSWz3MxlWhVtbU/DRd3xlKkcLBXtSg90Dm5ry9uVrjgH52ynbldZW3zS2eL2dSrT/zm4Ve2s7etScQ6uyifusNuZd694NBdssu6RZRJwhDgH54lPzJ7E0YxlS9HO5pUtXoZybrYXWtb3BeTnDa0vcrMKpCorhKveI83tdAq579BSVd8upH9lW5pKbr/WttNZJjzDXcY2PANHLPfNmrDdUFxGflJwl0V+HPo+SEXuhZ5XvECTaVpGPC8hRcl8JsobbjzupS5xoNFmV5CfcygMcdVA90u0GG0G6coXC72pMfheQPrwI5X68LswX26Md190V2e7KGfkd5zt2ijbO/OXxXj3RA+V7b0ZTzV4Joi4YytN7YZ5+JtONtwngq5MCL7PWeiSh0zYPjH3D4r9zdHW/c1yTtHBeiZznJj3bDPOZDabZ3n6hjH+z2PCr/3zmFXb7J/HrNrW8vOYY1pwHtM7/ubEWmWULeY/UkZSPnwOc3wA+dSGIJ/aEORTG4Z8xrdAPt465Opolc+V+NNglQ/PET0yuiyAjBpCkFFDCDJqCENGl7VARpd759BxVhlNFuOwlBGPM9a6lBNATk0hyKkpBDk1hSGnnBbIqT+PjT14ojJI7gHXLhRy8syvMemZM2+u8G+ch8L6REkBjZJK+WyWeb7iHK/9IpV8fHn/7pElolDLR/Ly2WKc+SkoWUi8cSbeOMlrzJM179yNv/3/jdz7YoxqZ8h7nA07WPxNn89pGXIw5I78so0kKXeRr2TOl3gW5z2Xy+mX8xSpa/823ve+ETRazIvupLJYKCabpXKiIm79zlOSyc86LVvMPtTvAQhXyslFMhXBIgyeE3Ql95u1UZi3LwBZy9A3jK2UftisKdWMuUcxuffCfSSf9yaeYorJdJ6qD/HF0a6PFJ7rDKdn12lpkNIEkJhT9Ib/MsSTDk9Oxw3OWJzPbH6OqQvu2+D+FO7/wOeYcuDvw/jgY3ygMd1F5UYp9+mP65Os+gOmdsbzO736AyxjetA1pfo77esOqL+z5boDeqfY049eo9DhP13YEZF5NPWjwdcJGkPIX2MY+auxqeN+vUKH/wwxaGy35o/H1KDrUdp2+3k=
*/