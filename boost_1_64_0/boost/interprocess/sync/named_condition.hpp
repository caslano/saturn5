//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NAMED_CONDITION_HPP
#define BOOST_INTERPROCESS_NAMED_CONDITION_HPP

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
#include <boost/interprocess/detail/interprocess_tester.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/detail/locks.hpp>
#if !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/named_condition.hpp>
   #define BOOST_INTERPROCESS_USE_WINDOWS
#else
   #include <boost/interprocess/sync/shm/named_condition.hpp>
#endif

//!\file
//!Describes a named condition class for inter-process synchronization

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
namespace ipcdetail{ class interprocess_tester; }
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//! A global condition variable that can be created by name.
//! This condition variable is designed to work with named_mutex and
//! can't be placed in shared memory or memory mapped files.
class named_condition
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   named_condition();
   named_condition(const named_condition &);
   named_condition &operator=(const named_condition &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:
   //!Creates a global condition with a name.
   //!If the condition can't be created throws interprocess_exception
   named_condition(create_only_t create_only, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global condition with a name.
   //!If the condition is created, this call is equivalent to
   //!named_condition(create_only_t, ... )
   //!If the condition is already created, this call is equivalent
   //!named_condition(open_only_t, ... )
   //!Does not throw
   named_condition(open_or_create_t open_or_create, const char *name, const permissions &perm = permissions());

   //!Opens a global condition with a name if that condition is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   named_condition(open_only_t open_only, const char *name);

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~named_condition();

   //!If there is a thread waiting on *this, change that
   //!thread's state to ready. Otherwise there is no effect.*/
   void notify_one();

   //!Change the state of all threads waiting on *this to ready.
   //!If there are no waiting threads, notify_all() has no effect.
   void notify_all();

   //!Releases the lock on the named_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), and then reacquires the lock.
   template <typename L>
   void wait(L& lock);

   //!The same as:
   //!while (!pred()) wait(lock)
   template <typename L, typename Pr>
   void wait(L& lock, Pr pred);

   //!Releases the lock on the named_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), or until time abs_time is reached,
   //!and then reacquires the lock.
   //!Returns: false if time abs_time is reached, otherwise true.
   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time);

   //!The same as:   while (!pred()) {
   //!                  if (!timed_wait(lock, abs_time)) return pred();
   //!               } return true;
   template <typename L, typename Pr>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time, Pr pred);

   //!Erases a named condition from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   #if defined(BOOST_INTERPROCESS_USE_WINDOWS)
   typedef ipcdetail::windows_named_condition   condition_type;
   #else
   typedef ipcdetail::shm_named_condition       condition_type;
   #endif
   condition_type m_cond;

   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction()
   {  ipcdetail::interprocess_tester::dont_close_on_destruction(m_cond); }
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_condition::~named_condition()
{}

inline named_condition::named_condition(create_only_t, const char *name, const permissions &perm)
   :  m_cond(create_only_t(), name, perm)
{}

inline named_condition::named_condition(open_or_create_t, const char *name, const permissions &perm)
   :  m_cond(open_or_create_t(), name, perm)
{}

inline named_condition::named_condition(open_only_t, const char *name)
   :  m_cond(open_only_t(), name)
{}

inline void named_condition::notify_one()
{  m_cond.notify_one();  }

inline void named_condition::notify_all()
{  m_cond.notify_all();  }

template <typename L>
inline void named_condition::wait(L& lock)
{
   ipcdetail::internal_mutex_lock<L> internal_lock(lock);
   m_cond.wait(internal_lock);
}

template <typename L, typename Pr>
inline void named_condition::wait(L& lock, Pr pred)
{
   ipcdetail::internal_mutex_lock<L> internal_lock(lock);
   m_cond.wait(internal_lock, pred);
}

template <typename L>
inline bool named_condition::timed_wait
   (L& lock, const boost::posix_time::ptime &abs_time)
{
   ipcdetail::internal_mutex_lock<L> internal_lock(lock);
   return m_cond.timed_wait(internal_lock, abs_time);
}

template <typename L, typename Pr>
inline bool named_condition::timed_wait
   (L& lock, const boost::posix_time::ptime &abs_time, Pr pred)
{
   ipcdetail::internal_mutex_lock<L> internal_lock(lock);
   return m_cond.timed_wait(internal_lock, abs_time, pred);
}

inline bool named_condition::remove(const char *name)
{
   return condition_type::remove(name);
}

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_NAMED_CONDITION_HPP

/* named_condition.hpp
RijL0bdfkvORoeQvXW+rn6v565vuXy/7JlnOK+A+w9I3EQ/wJ8SzFToRFyj9ibJdhXLNS/f2Te5Xm/dN3Zhno5fH4f6IOicXOid/+g/Zz/50b/9UqanW12i/g3IdUvZLzhD7Je+cXrT5ZG7z6j7Jdzw9zjrGC5GZ9sAC4Jtir1kJ9UklgxaHvq4Nv2rdxlxfhpfCHafVy/HkKa0H9AX0xqx1oGIs9Q0rPk7aBFL1OcxrndtyvKcp3tcQY4mxZvNimXg2hdfgPX4gOqMfeZnCnB6h0hXak8I7ovc06Qo9TeH1MNVNF2Y3UhfzLPIzW1+OtvQ9bbIWpY8z5vAXkN+PIMMtSj3FScBs8r8H/V8XY+zNomdv6e3gt4P+gOY7/5fvDm8S3zuI+QJtmna5It7XjH5C4/mXuZ/oQf7/osv3AJRFqZzTfEKymqkv0I4Zc5OnKexrjT7qC+LpGsHvfCzvwnnmvUFPUDy1qB3rLeUk2lim0Oc4AO/JNE9ub9WBzDxjBnhtJy1xRsdgafxL/7pLU9hP0QBjzatKuebFfDsGeN9hKscr3wuYrw58qzz6hPMtc37meQ88q2n9ae1EyxoV82gZxjrWCMnjm6beXp6YyltVNp2G476DZqxfEZ4CruH3gZ+CKhLk2sPP4kNb10Ld5/eA4Gv9Kr2q8XFqm1DrFXYBOooKt8Gra37U9MkD58ACydjxY6dJuxwdAtsggf+W2wToIO2K+NrvUdgESAFvnDKt0j7FPYFtAbB/ncfJgPYpwNty+xT3KOxTID6lfYp8hQ0A0RGkqvPK9inslU3qBvs2AFI3tNwGQIcQ7MM4B6ttk2VsCM82WUYY9dCfbbLIIWrbZFkbwrdNlrUhNNtkWRtabpciVNtkTUPUtslyN4Rnmyw3hPqYG0Z9DMU2Wf5QS17pjEy+kVe5beZs2CZzDrPG9wPE51LGJ+v/wSD2Plxh1H+Era7/mda0/gy8bkVam9f/zUHS6zbV/9dt1H93GPUfabHU/9cD1X9Fvt8SawzKfGP0sZnnKlP9PxLMPlIY4w/SYan/R/zYJnvvEoW9LvivUeWV2rq9+lgTQluvCaOtH7Rhf8Zrayh3uDWvP4H/WiOvcgtZuO2d2xAWKa1xviT2HSrj9G3zLwaRcX0Ybf5FP22+SZHeH4O3QZle3/p/MvCYR2HIb0aB639DGPUf6bDUCcSnnH81jrDm9xWxb1KdX24D9sqnMYQ20BhGG3jRRhv4FHjqf9i+wpfjxPPCyh9lP9X3pmxHyu6vnjz/q7+22lcIZl/hCMmte+QjV7/S4WTaxNuXTCh/feaB/w27C510+3YXFrOdg3/ieqnperXpuoJtG2SCbuRriI/WNitYH/Fi03Wx6XoJh/MZ7otM1ytM18tN1zeb4l1lui43paHYlIZlfD0J5OLrPJE2vha6LG/g6+3SNgOfd1fr4B9o1q1a7l8H/wATXwaHFxskvNwA8eaZ+JoCxDvNxOeS8QYMrypAvJkmvvoA8Q41y0XGGyg8FK7/8Eaa+BoCpG+cmS9A+saY5SfTFzC8uBX+451k4msMEO+V5nrA4cUGCM8FymW+TQpd6k9hABb4NLCNaEfA7sDngOmsE34o8CDwGtYJX8g64UtZB3wZ64S/g++N8qhgmwYB6ylI8gWsV1mSL2A9yJd8AcvDLfkClkcN86UEyUe95AuYj0bJF7g+r2S+gPkASb4A9YD3xtPZAGs9KES5ifvFwAzgDcDhwCXAScAi4AzWFZwPLAaWAJcBL9Q9/sYCbwReCSzx6rzXeY8w73UW8Q4E7eBx4++su/kr4EXAr4E0XYT/CQI4fgfbOohiGyltRPx8vwHYlm2kRANfZ50=
*/