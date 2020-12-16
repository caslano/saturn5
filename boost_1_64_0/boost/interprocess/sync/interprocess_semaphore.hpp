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
1La3PI9IQxD9D2yLTKHH/2phy0PmUTEmBn83TQ0hn6lh5FMPUlcHcT9a39nj+UHxHPRdgaKNbuZ8ltCKuUsL4Yys8Mvn8Xn8cckwuL+MIp67MIZOV5exaVxaGmfIydBhkUbuy1Xjn4xfnksunl9YbNh1SgF2I55VqjER/tW6M5JE2shtp+X9MZbzNYzcp9PajAsJPYOHB+hdLYLe1db4eVdLYf4eKI/99K7WX3F+VfbXL4NnEvrpyaBn4TbFxjuZv7OnKWYdGFxW5vnQ0jiuO8wbJ89fs1x950kVXT2R/hoUA/oV16mmDUadWjzfZb8+kT+f+YwL/mVd+ILcf6KsR/Crrkdcnp+R+wn1PGpD4HrUCfg18RxV1CPpvzvKrK2G8qKykjTZuA++vhbs3DCXHeQSerkN9Z6dP88T4T2c/u2gWeK7k6fPc5Wgos+ZD3Uonirvt21uJ/6R6vPz3Kf5rsvKM/FTyH29NgTcivKE/8BlkgDcRDypRnqup/sLFWXsm55E6uyLxel14j0t9Nhwe+M2RlgHepn74iS1/hk5P/IpB1lecp2U7YYqyga8lAaRrmRKl2/f3dSN9bPz2uQ80HWiP99hKi+aYqrLqhPw/B1+7RVyOHK+qtN8VbadNuR+vbr/3uG3nFTlwPxqfUXtyC1PE3oB+qKO5iHfV1Kfqjv1NrTkPdqfXoAE9lMBPznUr15sXQPDvYPL+B/geTmEua+1bNmODsmKyzZIu3s71RPwE1yOj4OuETaRTOVobC+3lKUcU28n/j3aZoSu1OtjKs948l/i91uG21R+w+KJl79GyzH0h8QzSlWe8B+8na4nnosUfaf0L9dTFywuKS0z+omt5P4A3v90j21rLr/cBFF+TGehLOPpGcnJKEshj2QpjwB9q3xfzWfjG8/qHlsZzwBHdsbzu6iMSws9Pesc6lrnsN1XYx3KJbp1411vN/lZpidrnfRpeoyqrBGufT0lZt40wcvr3V04voXk/qg+EG/InyAEp36vssw5HPn9C3JbKuZaXD+Xk/tOfSFSWI+T6it0p7ZDjzTW0Gfe3fz9eIHhPwW4mPw/oi+HZP+Kt98teoS2B2RZc+d0l1J4V/H3AF2rJv/jEHuy93sefhSFUa96kJ+HtEvxl9YHDH/l+gTtj1q+rpvezefLd3PO41DyPwZjfrQlX6IvOp6K8knj72/tK8da+iLm6Z3G3/SiKi+XuoB8eXK8PO0q+/njcYFnquDpULlYfk/w5dkBnmm09r9Erg8046kDzwDShZJv4emJ+2iNvgvQ+sF04CleS8jjtYRxNuan4ptB/V2Wbwa8tok2EERPSho9Q92lsC6Jp/qG6w9SfMfNwz09kSbCMQbYEThKfFe4h9ui7G2pnhSlUBsUz4y+7xXifVfZ9hCOXCuStnqVbY95FXX4CtJdt4/cz/iOi1zXfkpudd7+HL+56DhkXf6E3O/G2lh7oy7/hp49qsXj6R4tkvzOo3dA11yah3Hbia8WfBVoPd342xylrXSJqV94nML6i+ZEOPPA+QugSPfnSPez5PYRjdnzeyCvPfmblT5SDNiR7m2k0kf9nZr99O3J363aT7N+p2aePPCkU710f+l0dLTUTR7baW1rBvJwFdfD6CD18I5qaz0U9SCZ64HvOheVr09/7+ql1g/WVB2efrCm6rOnH+xyTuui3ta0loJX26lIq1TNx/UiYHoRhpwH3J8YXDeftrPluvmQFotuPsTpVzdf3kVqvWhxO8PTixa3075etLid34xetMPWvNJ+tVQjr3IZS6qmbLluSlcfa3wH0GlkKOOT9f/RwLoA4b/l9R9hq+t/ujWtC8V7ryKtzet/7yB1IctU//c=
*/