//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SEMAPHORE_HPP
#define BOOST_INTERPROCESS_SEMAPHORE_HPP

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

#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>

#if !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && \
   (defined(BOOST_INTERPROCESS_POSIX_PROCESS_SHARED) && defined(BOOST_INTERPROCESS_POSIX_UNNAMED_SEMAPHORES))
   #include <boost/interprocess/sync/posix/semaphore.hpp>
   #define BOOST_INTERPROCESS_USE_POSIX
//Experimental...
#elif !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/semaphore.hpp>
   #define BOOST_INTERPROCESS_USE_WINDOWS
#elif !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   #include <boost/interprocess/sync/spin/semaphore.hpp>
   #define BOOST_INTERPROCESS_USE_GENERIC_EMULATION
#endif

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!\file
//!Describes a interprocess_semaphore class for inter-process synchronization

namespace boost {
namespace interprocess {

//!Wraps a interprocess_semaphore that can be placed in shared memory and can be
//!shared between processes. Allows timed lock tries
class interprocess_semaphore
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   interprocess_semaphore(const interprocess_semaphore &);
   interprocess_semaphore &operator=(const interprocess_semaphore &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:
   //!Creates a interprocess_semaphore with the given initial count.
   //!interprocess_exception if there is an error.*/
   interprocess_semaphore(unsigned int initialCount);

   //!Destroys the interprocess_semaphore.
   //!Does not throw
   ~interprocess_semaphore();

   //!Increments the interprocess_semaphore count. If there are processes/threads blocked waiting
   //!for the interprocess_semaphore, then one of these processes will return successfully from
   //!its wait function. If there is an error an interprocess_exception exception is thrown.
   void post();

   //!Decrements the interprocess_semaphore. If the interprocess_semaphore value is not greater than zero,
   //!then the calling process/thread blocks until it can decrement the counter.
   //!If there is an error an interprocess_exception exception is thrown.
   void wait();

   //!Decrements the interprocess_semaphore if the interprocess_semaphore's value is greater than zero
   //!and returns true. If the value is not greater than zero returns false.
   //!If there is an error an interprocess_exception exception is thrown.
   bool try_wait();

   //!Decrements the interprocess_semaphore if the interprocess_semaphore's value is greater
   //!than zero and returns true. Otherwise, waits for the interprocess_semaphore
   //!to the posted or the timeout expires. If the timeout expires, the
   //!function returns false. If the interprocess_semaphore is posted the function
   //!returns true. If there is an error throws sem_exception
   bool timed_wait(const boost::posix_time::ptime &abs_time);

   //!Returns the interprocess_semaphore count
//   int get_count() const;
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   #if defined(BOOST_INTERPROCESS_USE_GENERIC_EMULATION)
      #undef BOOST_INTERPROCESS_USE_GENERIC_EMULATION
      ipcdetail::spin_semaphore m_sem;
   #elif defined(BOOST_INTERPROCESS_USE_WINDOWS)
      #undef BOOST_INTERPROCESS_USE_WINDOWS
      ipcdetail::windows_semaphore m_sem;
   #else
      #undef BOOST_INTERPROCESS_USE_POSIX
      ipcdetail::posix_semaphore m_sem;
   #endif   //#if defined(BOOST_INTERPROCESS_USE_GENERIC_EMULATION)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

}  //namespace interprocess {
}  //namespace boost {

namespace boost {
namespace interprocess {

inline interprocess_semaphore::interprocess_semaphore(unsigned int initialCount)
   : m_sem(initialCount)
{}

inline interprocess_semaphore::~interprocess_semaphore(){}

inline void interprocess_semaphore::wait()
{
   #ifdef BOOST_INTERPROCESS_ENABLE_TIMEOUT_WHEN_LOCKING
      boost::posix_time::ptime wait_time
         = microsec_clock::universal_time()
         + boost::posix_time::milliseconds(BOOST_INTERPROCESS_TIMEOUT_WHEN_LOCKING_DURATION_MS);
      if (!m_sem.timed_wait(wait_time))
      {
         throw interprocess_exception(timeout_when_waiting_error, "Interprocess semaphore timeout when waiting. Possible deadlock: owner died without posting?");
      }
   #else
      m_sem.wait();
   #endif
}
inline bool interprocess_semaphore::try_wait()
{ return m_sem.try_wait(); }

inline bool interprocess_semaphore::timed_wait(const boost::posix_time::ptime &abs_time)
{ return m_sem.timed_wait(abs_time); }

inline void interprocess_semaphore::post()
{ m_sem.post(); }

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_SEMAPHORE_HPP

/* interprocess_semaphore.hpp
PkkisPZXBYjkx8NqkljiqTW611vXGt1L44uvPXZVpdq7XSTx+dOtJq/nRu+HsF1re9QlpKBySxuGUgReBsFA10gmwm8ERzqLVaXkhg2Dey5lZCT6WzhTW2uHYMau3AYNO6wmkxDKoszllnn1TGn1jEC/pn7Pkrm6KQLbXloE9e5UtkXGrSxMmZk8j/UBb6/sMj/VtT97See9w4KVWuYV62nVdtcInXI/9LKlMRHU2HjNM5n2Fbt19LvoBplWFNj4alVV4WWeWVNr+Pd/aFzeIgR+gGKxbsMyQ7qG6MYsgIaLNvmz8+emd2tCv3hrKoIY0TxtMdw8kgU0E7+QEAtjq3x9Vl/6cYMAL3h1cXrlOWV9472plLiqDdm2+J4kuPBX4TF4dBr42uuf1XI/1z3+Pg1cowd3zHgXXeX7nA8+ZZpkufBjed50QjTnHYKGhl/lvLFSRkuUaF8MXqbxX1eYIxrCutncAb/x2YAtv5/ifY4bEl/3fG9v5qfBtAaCPo/XZ1FKot75goMdDpkl/IVtpSYImXlVv3LpCfNZzt4vXP2aFgf3oyrX9MRTf/NxEc/nO2d8RtrQc//19TGStunArWFR27KcnZ+JRT6Fn2WcKVUglbmGZzHDpuL0U+qCE632l95ckHRM8DJSnfqZ/cMTL+MWnX/FF81rZS/ryt/tID7n4saBbxZOzz6Rcsnsy2afatJsPrHV8N2fSQA2
*/