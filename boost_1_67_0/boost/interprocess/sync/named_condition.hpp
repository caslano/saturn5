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
ywVW22lEOu3L8xegPvQS4h6NMoiNJOrJWRJTPpzU1Xf2d4CKI4BvZIGFPzq5ne1p1jMAzyEkttmiEaoSPkL9LGROEtGR65QtTCwdl/uRKCEarLrkreQbGaPwx0XsqSGuO+/axq/f6xUIEYoDnEKWgVJoHzxgiG2kLmBRCa1uuv2hpJDYLVwphJ3jGSDk/lBWJtH9JhLNnRWJUcWYzEQ6jCjZn/nGDnhx3K0P8LQ9QvgdvdXMvKcZL7AMu/LjXrjiy/Y6IlNHCJs6vAC5Rv6vejyzO3YQWYCfO7zvOoAOm3mhNDpWnpknK9TcV6JHYrUVWLpKY5kPDzmoRo8yL41qVWnruGb/LKxrqIvbTVzd6G2u8V2g+cSBn3b8bY6buR4+t7JwVaF51cIy1nMy68lznjGr25k+sKfJmFfWWOmMGuYqMoRrYuiYPbKjWQF9fjaweexjpobaPzSs5Qjcwt0UW9Rn8fSuY1LQu4pL9jlzRvO6C8vxTmbSL0rU3NCzKt9yrp5ybe5x3Puj7QqEJ/B2pizNKbUtsOxcX5fQX6Zuyi1JvXyRgI7Wg2f0Qm7ynN6nrnKJnOQ/oPw2uq+G8C4r6Q3KdgQP9nV2gJbbdgITqTd4lVi/dm7bvnPypiOi7EJCPtoZl/FsW9LaSxbVs3a4qUqPCOaoWPCaJfHiQrQvteBCD3hVPdZ05KPQfdw24Wfs9J5L8PVfrH5G/tHRfOGMaHp2vozssmXsQBqcm/v4wf4oe3nkNHtddrdtykGhd4ycSPhiwZRtu+L/hEU2yzOqb67UTzZr5dm29OvqvozlZMei3mTSfjR358AXRNWkbQvfTnVuTB/bfeJsDOnETYgpvF62JPW97rD7mJsbcWhNlw5NqWTYVjeHhUXuVEdlV+9SfVqfnMB+1awdTlT++WfdErZZ4XScZ5IHPxM9t/b8IOGb1n2iccXG+3yTlqnp/c310GFymValdJxmB3Qw4+MyO0L5EvCs6DjNV0DjXZ/AV+vmvUsTzm4G9omWr5fek+3PsKg3aLtqdnsRbburXRhnr+rlzg/qY2nHK0E81s/YTvjNx4A263sqqL0Ax9tL5x3/yXdsB+MrpCHeIrBhsnuDq/oJqH0fvsvv7vQihNgT6tKTj1sJ1+L4cu3eo7A6djKG9cl2tA1MwzY8awUAZ76eVBXjWjU38/QX7viSK8/L91H7RNSHhBhLdhM7AQR7XmgHgtainUCeE0Qa3Fxrlu5SNpgrXxdq3ccJwXBwXudvRaBe95dPXwvRaWYE7nMTQeOZqOFCKfkf2+Cs3kuTrwXrrVzzzT1k6YZxwbMNtl0EFhOEHeduGz43FEeVmn4/+31sReiV69sLIaEzgTIh5QeTZ1a48nHmHUcmsN0fEFJ0592FYDm9skb2vu1KPUXidKAhev+XoMg4PzTESo42hvaT57b1wfGzp7eNwe/Qlz9gg+rVPhwNL7XACf7mBAiUkJIksyZSoJqpVMEERfOx0qyGHXVhACKgp1RQRGA+qyKVBUrgFgQUg8kz50sP+Yb8PKJIR3n2zNxZPdsyG2IjcXI7RCfWNl4zpvz3WX7WzFlh+pP9XSR1sGVOVoI4Mk9BheJA8oU3sn3d+mODZSKNEEcM8A4XxyyEDA8WKntJ3WTel/m6lvCnkOJSofqdclzYVU/fnKRvFUBX3ON33g5bqN2SyGju/MhcpFx3MiklBv1m+1zxQcu2vnHWAIt0acYwH4NOfIygrN04MmxUyYViYtgSPso1iNfGccQqyfNFQMZjF4Ex6nr+0QUJEBNh3y2Ws6deyt/d9d1I9gFhhAQcW/iK1NR+RCdr4Ny7kCc8lfpeMngEa3aCZFuKbEgkkKSOVTjq9Q7UOmgTVpOQHknh0syoHZIIFIBkQ9slLYRQUD1qoXIxOO4w3kQZbcvcxcSWa2eSR+ZCQ5oZY4rYTeWalMolnn9FCFyISYcRneS4KLEOCtXoJcEP/pWeVOevFJqg3r9M+YcAVVQ7HDfYqmml76HLU2bGhHa7r13nkgbLHuSCN+Vn90dd3N014odGZp8v4kdKIv3DMD6c7juZA093i02Rwr24pcwwyZExrAtBi5pzlJVY42gvRoNzOJOFM2my2y///X1oPJjXZmNgnZSyzDLRZjjglG1Wqiup2DL/tllB21Fte/BETtwjJVavyNF7Ps4OCXcJlJ4HnL9JMNSHtlXpiNNm88TsCkBMIl+M24ZyMHkTZoUJgsPqPDR2PwFJZMLquD2VJ+SSGimfU13jki2LzjNAWSSMvCsgHc64n5abNefYAZhKaabq9Bmjx8KoNX8Jv+v7MOmq9HK4Lcbzr/M11KmgotTAFbbP4YHbu3MngzD33RKNL7f+G/jyjYXLeRe59I1n2I9r6lUD6tvB0ZfiIbk9/uJOdH0GbmdwcrbvLzDIhistjAB006eg5+H71twp+5p4peXlNs4hMwAawU1irJ3+g0NRpo8WDDoJQh2IUhChkLrJfRXRC6OxyO7ptmvoJqROfgvX+pzF8LGToI7xVbA1AWcnFzMRIIoNeLBL2gq1m+XrhrW6H1On0xLGkutDt8pPTexf4P9pE1FqDa9t2DbsvWKXrZev0L95Ix3ID17aimWfyx1IQgdmb2APjzoGEhPhsyL+vFsobou/5C9pRsvpY+tW4Sj5xIq4ANOq13z4vWn0jlygZiqqx+BXbyg/Bce9zNtI9dV21uFItpqJ79a2/U9aapHumaaNt97hhwUV5CdS09FLbfxIjax0Snf9sYKm6vbIXCtnec+3eJLQxKb302CCKouvzvp+kQlo0QGI+lHUXDR9h4mjqPHW2se4/NQE+fg7hnaDXEehfauhctQEGewnRsdecxRHw9njlkJ+aMuAaNrrBsUwWIyO1DdXIj/nYkqzapITtbUXbTL3mF7RYCImjpbahLi3P/IWuZNPCO3Sjc5bl26AB82gycCtbaO4lrRm7VINcQMnjW7MWta3NdD9n1V56Fj4wd6GUNCbcKoqm6/h2umaRYPRMoxnXIisIrK26XvdXt1ec92ew7Z1P6zT1xLYC7JJB8Y/2XkAfn6iWxA3wXhxRfKWgpOMgas38tKNohVQttJal8/Acrh1W8zLILIJfheuqWjZvK67L+Fb5KJ5Hh57gwFhaG5fL2MHwhYKctnzt8gjP5vjp1z2ksVjAcXvu9SjNd08g9SJIGwHcjURSg2Dtd5w1JVqrGDOLg2ydn623jadLkbbukyRTH3yQyFVoQp/9M/AvODuXvDNQO/AnT2dduHmwUxR7uupbe9b5Vb9YJRFYWrCW7RP/e3ZgB1J2yIW4oScl1S/jit1TTzIHXYRPEXGn9qut/OsqwS998EH2xtSgHBkQ8P819VWAxG06cSKiYS+vGpXZ+AO4bsebxSVHgplDJJDoKD39xznYDhFFRzS2Um9+doL3nX9KEywLaZZVPipSq2+ZQ5bIA4Ojol1kd1gYJQ8RHfHWMyMVXXTS+YFGoaBOFB3UlvZpBNbbB5ilTHh5qWYHHVrQsNSQj37jCRkM7VJvUdxHPFIiY3KVWKIcjylU3TxCpUYOS4/bSytS0lUW7AVqRkp8vxPuaTVd0c3yZfM2fMvE0XnqHGFWhMjTJWNTMY6k3yrwcQwmvR6R/M9UzeXn+vzyM5cxCqEF7G8AtkRVNkdngRUWBsNXofB79m4PuOBuX2AtzgO30am3mIiiIVBa6QCK+jrv0ZKZsjJYyUZsDNF7nV67YsWXHy5eCpLkwmGJ7U2PvMsZkufhtMDvi6bfZjOyj1rHyvfukV+L5x1frte4xX3h7btErEdOX/l3O5c+BebS+vfS9hWHLlyHup/GGq5N7CupLTATzzWb7sZtJdkXBKx+OnthUOyNvZuO2hjWucfnNk1rCtlJ5Lw1r4bc9l8PZtqbo1eo4MDBiZMt6dMrqL6sc/RgcU+PnB4LvPuOaBtr3ZdOWvun5p4UnKfDdi1M7RlUQf31vxstqA/Zw+UytmuGNKnX/GWde1v3l971FtSSsY9feW6lG4+/8m/zMyXj/jU8H38PAl7J6YXldowjDQFJ+2LXVx12bxatmPZWBkMLZi9jST7dsd6EqG9mR708G6nLpMU0ycyn/F7UMTVzB1V0WfC3Kjgi4+vm6+4p0/HSq4UV52S3Spdryx0lFWI+fnqlmA1XnzCopGhHbXRN+jxmbHx8RENt1SyJg20bH1eliBJc5XIzYShb8mnvvFVfpJFZ5RhnaPNrfmgKmbIm1Fv2XV2Dcb6R03qMVeNO+QMl2lfGnVq66ajyaLF+S1MMWDvdOTTbzo+f7wdcudvZTrQXj52gyUKFC6dFbF2ubdaz1zp+WUf52y4cteY4grVnxxeq0oQtoZaoRA2C/c4gSHyIVheMPD6Uq5//IuHCsXxvUM+Nbzv4s6+8bvc+VSI6z6bhRjCzHUBf1PBe/HTmH4veOYDfflMiGLEJSwJYEN78cvH1QB0g//Q61o/CLw8neX/a4i8/y6v+byZ4XJaOEhZS0v2zH+EfKqIoxEC3vFvNszzFTAk4IQB+KrX45PQ7lLQM/HZr/GDfm/j6y1KEDLNtECPP+VlB/P4eejjZtf70X8a9SW3S8h0iZ7T4xXEcQU5bbAK8XhXoGEL+NUb2E//hUVwZu5k2oBkMahm9qXL2cGe9PyKGYHWl3DF1t8rA1II0OwGuDvJqWVlv4x15ICccHcAs38sfgQjtGSI4U669mbtUzMGarLUpWk9g1KX9uUsVwszhMQAmrHi5x6+DzcBr6zDbCbMjw15dkADCjF3tHa5fzOydhlKdUSagA3XOEB+lugKdgETnlYc5gBTzdZgu5KNOx97qr/H/qnyhlWAHv5sAPg6Yan/dP4+gC1TQw6JFjOtXXLc2MU6XqjdF4DFUKs+J5uu/5/cy95tX9e/kOVICJszZW4s6V5lLiJs1hDPxUnBQT0xNUkALi04Ickqu33cRhCLAsTteNt4pvl52nnJVPptYhCugwXTclJYBNXJ4ztMCVzIMyzIBiksd9QwDVJEmiurrgWOOc/21BpLTQtfn1Fd8uKHPu2SBBpNrqIarTna3eu6wQcZEHgYqbvLD+9eAT4gSuQCPYYxk4Dk2Gq7eIFWTwVZm2W7iOSoTB+PBFmbcSlCYc5v/pxgbSNwfwB/YWlAAP8fvxvFg3GEG+WD85W0fhnj1nkA8mfeLCBMMEoT/Ydw+kWOqK85ujiFvcnzKVYBDhHbeOSOxSpVIjTqFrjwGMfBaOJcmXFHFOon3SIg8ZLZkYRBlfvCPIwT+IRBdFU+YcpNPZHOP7izpPsWyymKg+33mumeK2Jl/ogV6aDIGzRPc3J/GIyaTJAr+PgyX83KTYyUtufIRCuVtaPJKCdZ0IcQDlxxxYZO1YENMlEIB7iJ1EKTMPay6piyMUrcjCKOLYP+tmrwxZBmVpgYfQ/mWSURNQtLdpJRwiyy32UWhds4ywb+zjGsCOBRzvHG0qxf3ePWNbORJZBVtJhEy3LP8kSr68otzj2U0sR4yYgo3xxyfSdWTOFuSCCMSA5ej6cbxs8SwXlcqne5ar4OikZulFULnrmbjQ6bDktyt7M9upx01W60IG/eacQbPJR6AHbATS/OFbUe0Dq3rkkOceAvn9apHKgaK9/MwLyWIQPOfzwUin4/MmYCkEJm7kzNhcIZkhjworQ3xjD6ftb9meghOBSCw5mt5/aseTneWur4lBkRTea4uIpVPm7GUzZj45xcFtNpNTNzUHRZJkvqSnDnckJ0eaIzk3aqdkI8SXWN5BuDm9PUxwssXW8fZYbXh0BokiDqD759LGqvHVlZy672LC3tP3RVFs5xnLmTKTBxZ4EmnZPZK5OrD8FyKKSyb8umy1EplqFrrsaEqlw6qz8FmaeoRQ4qKoTiw6I5qmfTzDrW1PGAVXvwPoISlZCj+6s4S9tWBRdF9z46x5TFIlf80/cSr3a26QDGPfV4/4YfXHyS4DDTezabWwBTMX0l+cXJQENH1wUAnyyWNLRf376F7Gy+FIUYE4iD2o3zfb7aiI3ICxXx7n5WH7pPcVbhoitsRsgvXh38KMRkw1TPeGONu86aKe/ZfKEwyriycj9QfvkEV7hlsGvM4/Pj5z4D9iPfZeai4XKXz6p6ouoW5ZcWz7ewts/UbvHF2t++aejiflki1jJ3WN9P27BwVJ8pqKzz3Le6m8HF/spR0wf5PvoI1f2wdAFiAAIYJb6TX7BlFOv/AayzLM8T2+asy98iJCWg6/YueMYZU1XC1lI3ZMO6r5rb4lTLbV0bzLzn5s3F8gS2mIOmD+Ij4YlKU4ZoSXUJ5rtjRbiHeGDXc2N79oLrazAwVBWFrvO59u+DXrfl+viIWHyzvXPkNovOZ/fZJQ2LqLtzP+7cLqKm+SP84rxwh8/jqWRBWO3K6abD96ZkfUneeLnG13mBcL9ny2gyib273ub6XVG76oK/Q1/s430642o1zmuiGNo258l5Z4Om6ajFZ1HXY4PdCnyr++cU0625UroN/8PuRdfMF+PDtsezdX8utYKMN/X9qX4El3p2wQmd3Y73tvILs+Jq/Qr7+k+Xz/k1Kb0tI60P4ocTPt7j9/U/0GPeOHmtWjOppf5YVOWZTbc9WeRnRr3rkpdvgu5NyoowX1Sf5WPg6wh5fHuTz8+pNHbeh6vKltyv5e6L0Zej4w3fynGu9wN/VGK/bb+XjDB+WOivq2w9Jb8NLSQ/Z2PTfsbjjy0ez8+6W3UyHKvvprPVsxTiOL93l2OHY/juhwHOAukF2oJV8s3Hj7y7HwwrCY5FcuK9qRpyMhjbVtK9T2A30svMzeRwn8EJMpyLh7hh8XdNsj/r/NfHHPv0vmtF8gt5H0U3tZRxL/ihX8PYYsdmS2rGcWjvMfIduy91I1lEw2H8rHaffzXxY3s+nzWTaunfup9SfH0PJ8M+R0Jmjuy6uMriO+rd9riHhv/OZo2g+aQ6f7XV5EseTRmJ57KbBIW9pu4keLqvP1wXNFyHn6m+/KkxcFnN+4zt5z1O3oV7CD3nkY7z2YPdyJVrMuq5hxazs1+5bJ3QWXI13ms60k5V6747mQ8pvKffdPt32s/fsuMxV4k5o+esPjsdlV7DGRvkgTEvfQdhIyd6ilFUFQGhKsgFQ13IurcI74M+y4MI+fUHSSiqFhjAuxto3lmCf4Cp/S+8UDNHsG+c6D+c3B8keZ9FL8AvOYmGAYR3uBJP9l2MHIEXgNk0QX6tVKmveSMlAbBJkGehbReGQziAdvxdT4BXdRFCFQge24BG3PtH4EzT0xElwipg3R2BnePAYJ1GJsAbu14rFyYh6o/Z1vzVkS+bfG0Q5VYViZ19jkKCC8ded1ZvucAL3i5ELUCuHUiPNICSNIIe2HlRez+EIr+BE/ndTPiZ0oDuGWFPMPun8BLfA5P8Ddp4V+ASmdol111u8Hn2Xmbsezj/GUoBPSieewbY1TPfXjVgD/wgFfDWGzBr00ts/OOHCD1ID11gnpr+k5pdJ+5DH/RTOeA3sl1EMMq2tBn+b+vLEfhHO6DpQoEPoNscoEfugGsznL5K8qesG/hmTPj70iBcKsEfVXcZ4Gyr3Q7sRwngzS/hs9UPpFtngXaM+/aAG2j7H1uKIOL4aqBuI4KZPpJzcT/S3XdXffbnQnjl+0J5mMG473qBr9MVsH1xP+l838cIBWBmCzDvAVhMe+cu07yX+OAwWyZjrCrWJIU0wgAJI64YWJFMhRbwRaZxj2s+GMwR0ETFfwfSAVImnt2o/1QKqpWDupqKcgH62B0qMvddtB7O1LEuq0jvB4VyTK32ph8ZrPboBr8TZji7A1CMGmQ23gbBhTMVwt+8WKthbvwWW6Hq2F6zFxzY9QlbcGed5oCSLGkffHQfLDWDX+kX6SIsHGNcJYVyWhXssnUNmqUIWuLLTxZIV0/M6cWpFgkVc5gH+ARyGhCY8VTfdNDlWPRKujfRzquAdCKCOW6U94cR+MoHZcOvHhk03byLPZlQ6mPmcmXD/Rz1kTLEigMkUc5fDTUEvLhcQ0A7Sw9wbZA6FTObJBHOGZj/qAWqbOXh0lELVn+zWyb1Omv8lQ1UCNM7ahiNsRUfkDfXk1IR6f1QUiKWM9cbP4ewC7vEv1C3pOlg7OdeH0X+uKqZ69/qoFeEdiN8DkgAom5C6DHhNlawfAkiBlVTmiZaNKp0lZTJErpKDOayiUIZdHgxSbIk5iYCRdXNVPknHMZlFvpF7DItNLnwtzOnKWzy++5daPydubBzSfD39lZKhlMKbBQPqAbfc1Dq/lx8EY5rEx9FhKT7rfTn7MVGLvfqhPuIOvt7ZdLFLLeWWgjI/EbXIfPNhUb2UI7RCnqywdhDO4spCrV33PIoTzEyC8FKMUlDYpIRi+TB6AQs8Vja2eZ9hAtWkthLjNnUtovQoDSgiW2gXl7jrOScSirdCGIviUYTs1QfVgSfoWWXYeSLcXqrQbD7wQft6EMmBo07SKrsIQU8+d+NzLkvyzR0lNZm0F1PAAYs+dOG4Pt7fhDmIlsENNYw2/3r5+cHiA4QAPgXyC/QX2C/wH9B/IL8BfUL+hfML9hfcL/gfyH8QvyF9Av5F8ov1F9ov9B/YfzC/IX1C/sXzi/cX3i/8H8R/CL8RfSL+BfJL9JfZL/If1H8ovxF9Yv6F80v2l90v+h/Mfxi/MX0i/kXyy/WX2y/2H9x/OL8xfWL+xfPL95ffL/4fwn8Evwl9Ev4l8gv0V9iv8R/SfyS/CX1S/qXzC/ZX3K/5H8p/FL8pfRL+ZfKL9Vfar/Uf2n80vyl9Uv7159fOr90f+n90v9l8Mvwl9Ev418mv0x/mf0y/2Xxy/KX1S/rXza/bH/Z/bL/5fDL8ZfTL+dfLr9cf7n9cv/l8cvzl9cv718+v3x/+f/6/9sjR9GIhzJGX4MqajdKXDljlufG7HXLZ6HUgZnwskgatKu4kKLDKe3zmTQxtWkcYXvGP4AdjmKuJIxF/hmi6k6pHE0pe/ZlKnPSUec3TM4jT4J10oHE7Ib2GrdHIh44oZZwNEyfD9CPbn6Kwjiq1U3saEkun8W7mh/MnLyp0sRaqNLkikqU8/K02u40lYN0f9DSKD+esporS9xMyRSye6IxdFEuBpRkjSBfaota4u2Jo3IrsdXJQ16vODlzCvR62l/4ntftOmz0fz5/kuMu6PLcWBjNJ+s=
*/