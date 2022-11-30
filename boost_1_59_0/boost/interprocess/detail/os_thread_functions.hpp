//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//Thread launching functions are adapted from boost/detail/lightweight_thread.hpp
//
//  boost/detail/lightweight_thread.hpp
//
//  Copyright (c) 2002 Peter Dimov and Multi Media Ltd.
//  Copyright (c) 2008 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_INTERPROCESS_DETAIL_OS_THREAD_FUNCTIONS_HPP
#define BOOST_INTERPROCESS_DETAIL_OS_THREAD_FUNCTIONS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/streams/bufferstream.hpp>
#include <cstddef>
#include <ostream>

#if defined(BOOST_INTERPROCESS_WINDOWS)
#  include <boost/interprocess/detail/win32_api.hpp>
#  include <boost/winapi/thread.hpp>
#else
#  include <pthread.h>
#  include <unistd.h>
#  include <sched.h>
#  include <time.h>
#  ifdef BOOST_INTERPROCESS_BSD_DERIVATIVE
      //Some *BSD systems (OpenBSD & NetBSD) need sys/param.h before sys/sysctl.h, whereas
      //others (FreeBSD & Darwin) need sys/types.h
#     include <sys/types.h>
#     include <sys/param.h>
#     include <sys/sysctl.h>
#  endif
#if defined(__VXWORKS__) 
#include <vxCpuLib.h>
#endif 
//According to the article "C/C++ tip: How to measure elapsed real time for benchmarking"
//Check MacOs first as macOS 10.12 SDK defines both CLOCK_MONOTONIC and
//CLOCK_MONOTONIC_RAW and no clock_gettime.
#  if (defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__))
#     include <mach/mach_time.h>  // mach_absolute_time, mach_timebase_info_data_t
#     define BOOST_INTERPROCESS_MATCH_ABSOLUTE_TIME
#  elif defined(CLOCK_MONOTONIC_PRECISE)   //BSD
#     define BOOST_INTERPROCESS_CLOCK_MONOTONIC CLOCK_MONOTONIC_PRECISE
#  elif defined(CLOCK_MONOTONIC_RAW)     //Linux
#     define BOOST_INTERPROCESS_CLOCK_MONOTONIC CLOCK_MONOTONIC_RAW
#  elif defined(CLOCK_HIGHRES)           //Solaris
#     define BOOST_INTERPROCESS_CLOCK_MONOTONIC CLOCK_HIGHRES
#  elif defined(CLOCK_MONOTONIC)         //POSIX (AIX, BSD, Linux, Solaris)
#     define BOOST_INTERPROCESS_CLOCK_MONOTONIC CLOCK_MONOTONIC
#  else
#     error "No high resolution steady clock in your system, please provide a patch"
#  endif
#endif

namespace boost {
namespace interprocess {
namespace ipcdetail{

#if defined (BOOST_INTERPROCESS_WINDOWS)

typedef unsigned long OS_process_id_t;
typedef unsigned long OS_thread_id_t;
struct OS_thread_t
{
   OS_thread_t()
      : m_handle()
   {}

   
   void* handle() const
   {  return m_handle;  }

   void* m_handle;
};

typedef OS_thread_id_t OS_systemwide_thread_id_t;

//process
inline OS_process_id_t get_current_process_id()
{  return winapi::get_current_process_id();  }

inline OS_process_id_t get_invalid_process_id()
{  return OS_process_id_t(0);  }

//thread
inline OS_thread_id_t get_current_thread_id()
{  return winapi::get_current_thread_id();  }

inline OS_thread_id_t get_invalid_thread_id()
{  return OS_thread_id_t(0xffffffff);  }

inline bool equal_thread_id(OS_thread_id_t id1, OS_thread_id_t id2)
{  return id1 == id2;  }

//return the system tick in ns
inline unsigned long get_system_tick_ns()
{
   unsigned long curres, ignore1, ignore2;
   winapi::query_timer_resolution(&ignore1, &ignore2, &curres);
   //Windows API returns the value in hundreds of ns
   return (curres - 1ul)*100ul;
}

//return the system tick in us
inline unsigned long get_system_tick_us()
{
   unsigned long curres, ignore1, ignore2;
   winapi::query_timer_resolution(&ignore1, &ignore2, &curres);
   //Windows API returns the value in hundreds of ns
   return (curres - 1ul)/10ul + 1ul;
}

typedef unsigned __int64 OS_highres_count_t;

inline unsigned long get_system_tick_in_highres_counts()
{
   __int64 freq;
   unsigned long curres, ignore1, ignore2;
   winapi::query_timer_resolution(&ignore1, &ignore2, &curres);
   //Frequency in counts per second
   if(!winapi::query_performance_frequency(&freq)){
      //Tick resolution in ms
      return (curres-1ul)/10000ul + 1ul;
   }
   else{
      //In femtoseconds
      __int64 count_fs    = (1000000000000000LL - 1LL)/freq + 1LL;
      __int64 tick_counts = (static_cast<__int64>(curres)*100000000LL - 1LL)/count_fs + 1LL;
      return static_cast<unsigned long>(tick_counts);
   }
}

inline OS_highres_count_t get_current_system_highres_count()
{
   __int64 count;
   if(!winapi::query_performance_counter(&count)){
      count = winapi::get_tick_count();
   }
   return (OS_highres_count_t)count;
}

inline void zero_highres_count(OS_highres_count_t &count)
{  count = 0;  }

inline bool is_highres_count_zero(const OS_highres_count_t &count)
{  return count == 0;  }

template <class Ostream>
inline Ostream &ostream_highres_count(Ostream &ostream, const OS_highres_count_t &count)
{
   ostream << count;
   return ostream;
}

inline OS_highres_count_t system_highres_count_subtract(const OS_highres_count_t &l, const OS_highres_count_t &r)
{  return l - r;  }

inline bool system_highres_count_less(const OS_highres_count_t &l, const OS_highres_count_t &r)
{  return l < r;  }

inline bool system_highres_count_less_ul(const OS_highres_count_t &l, unsigned long r)
{  return l < static_cast<OS_highres_count_t>(r);  }

inline void thread_sleep_tick()
{  winapi::sleep_tick();   }

inline void thread_yield()
{  winapi::sched_yield();  }

inline void thread_sleep(unsigned int ms)
{  winapi::sleep(ms);  }

//systemwide thread
inline OS_systemwide_thread_id_t get_current_systemwide_thread_id()
{
   return get_current_thread_id();
}

inline void systemwide_thread_id_copy
   (const volatile OS_systemwide_thread_id_t &from, volatile OS_systemwide_thread_id_t &to)
{
   to = from;
}

inline bool equal_systemwide_thread_id(const OS_systemwide_thread_id_t &id1, const OS_systemwide_thread_id_t &id2)
{
   return equal_thread_id(id1, id2);
}

inline OS_systemwide_thread_id_t get_invalid_systemwide_thread_id()
{
   return get_invalid_thread_id();
}

inline long double get_current_process_creation_time()
{
   winapi::interprocess_filetime CreationTime, ExitTime, KernelTime, UserTime;

   winapi::get_process_times
      ( winapi::get_current_process(), &CreationTime, &ExitTime, &KernelTime, &UserTime);

   typedef long double ldouble_t;
   const ldouble_t resolution = (100.0l/1000000000.0l);
   return CreationTime.dwHighDateTime*(ldouble_t(1u<<31u)*2.0l*resolution) +
              CreationTime.dwLowDateTime*resolution;
}

inline unsigned int get_num_cores()
{
   winapi::interprocess_system_info sysinfo;
   winapi::get_system_info( &sysinfo );
   //in Windows dw is long which is equal in bits to int
   return static_cast<unsigned>(sysinfo.dwNumberOfProcessors);
}

#else    //#if defined (BOOST_INTERPROCESS_WINDOWS)

typedef pthread_t OS_thread_t;
typedef pthread_t OS_thread_id_t;
typedef pid_t     OS_process_id_t;

struct OS_systemwide_thread_id_t
{
   OS_systemwide_thread_id_t()
      :  pid(), tid()
   {}

   OS_systemwide_thread_id_t(pid_t p, pthread_t t)
      :  pid(p), tid(t)
   {}

   OS_systemwide_thread_id_t(const OS_systemwide_thread_id_t &x)
      :  pid(x.pid), tid(x.tid)
   {}

   OS_systemwide_thread_id_t(const volatile OS_systemwide_thread_id_t &x)
      :  pid(x.pid), tid(x.tid)
   {}

   OS_systemwide_thread_id_t & operator=(const OS_systemwide_thread_id_t &x)
   {  pid = x.pid;   tid = x.tid;   return *this;   }

   OS_systemwide_thread_id_t & operator=(const volatile OS_systemwide_thread_id_t &x)
   {  pid = x.pid;   tid = x.tid;   return *this;  }

   void operator=(const OS_systemwide_thread_id_t &x) volatile
   {  pid = x.pid;   tid = x.tid;   }

   pid_t       pid;
   pthread_t   tid;
};

inline void systemwide_thread_id_copy
   (const volatile OS_systemwide_thread_id_t &from, volatile OS_systemwide_thread_id_t &to)
{
   to.pid = from.pid;
   to.tid = from.tid;
}

//process
inline OS_process_id_t get_current_process_id()
{  return ::getpid();  }

inline OS_process_id_t get_invalid_process_id()
{  return pid_t(0);  }

//thread
inline OS_thread_id_t get_current_thread_id()
{  return ::pthread_self();  }

inline OS_thread_id_t get_invalid_thread_id()
{
   static pthread_t invalid_id;
   return invalid_id;
}

inline bool equal_thread_id(OS_thread_id_t id1, OS_thread_id_t id2)
{  return 0 != pthread_equal(id1, id2);  }

inline void thread_yield()
{  ::sched_yield();  }

#ifndef BOOST_INTERPROCESS_MATCH_ABSOLUTE_TIME
typedef struct timespec OS_highres_count_t;
#else
typedef unsigned long long OS_highres_count_t;
#endif

inline unsigned long get_system_tick_ns()
{
   #ifdef _SC_CLK_TCK
   long ticks_per_second =::sysconf(_SC_CLK_TCK); // ticks per sec
   if(ticks_per_second <= 0){   //Try a typical value on error
      ticks_per_second = 100;
   }
   return 999999999ul/static_cast<unsigned long>(ticks_per_second)+1ul;
   #else
      #error "Can't obtain system tick value for your system, please provide a patch"
   #endif
}

inline unsigned long get_system_tick_in_highres_counts()
{
   #ifndef BOOST_INTERPROCESS_MATCH_ABSOLUTE_TIME
   return get_system_tick_ns();
   #else
   mach_timebase_info_data_t info;
   mach_timebase_info(&info);
            //ns
   return static_cast<unsigned long>
   (
      static_cast<double>(get_system_tick_ns())
         / (static_cast<double>(info.numer) / info.denom)
   );
   #endif
}

//return system ticks in us
inline unsigned long get_system_tick_us()
{
   return (get_system_tick_ns()-1)/1000ul + 1ul;
}

inline OS_highres_count_t get_current_system_highres_count()
{
   #if defined(BOOST_INTERPROCESS_CLOCK_MONOTONIC)
      struct timespec count;
      ::clock_gettime(BOOST_INTERPROCESS_CLOCK_MONOTONIC, &count);
      return count;
   #elif defined(BOOST_INTERPROCESS_MATCH_ABSOLUTE_TIME)
      return ::mach_absolute_time();
   #endif
}

#ifndef BOOST_INTERPROCESS_MATCH_ABSOLUTE_TIME

inline void zero_highres_count(OS_highres_count_t &count)
{  count.tv_sec = 0; count.tv_nsec = 0;  }

inline bool is_highres_count_zero(const OS_highres_count_t &count)
{  return count.tv_sec == 0 && count.tv_nsec == 0;  }

template <class Ostream>
inline Ostream &ostream_highres_count(Ostream &ostream, const OS_highres_count_t &count)
{
   ostream << count.tv_sec << "s:" << count.tv_nsec << "ns";
   return ostream;
}

inline OS_highres_count_t system_highres_count_subtract(const OS_highres_count_t &l, const OS_highres_count_t &r)
{
   OS_highres_count_t res;

   if (l.tv_nsec < r.tv_nsec){
      res.tv_nsec = 1000000000 + l.tv_nsec - r.tv_nsec;
      res.tv_sec  = l.tv_sec - 1 - r.tv_sec;
   }
   else{
      res.tv_nsec = l.tv_nsec - r.tv_nsec;
      res.tv_sec  = l.tv_sec - r.tv_sec;
   }

   return res;
}

inline bool system_highres_count_less(const OS_highres_count_t &l, const OS_highres_count_t &r)
{  return l.tv_sec < r.tv_sec || (l.tv_sec == r.tv_sec && l.tv_nsec < r.tv_nsec);  }

inline bool system_highres_count_less_ul(const OS_highres_count_t &l, unsigned long r)
{  return !l.tv_sec && (static_cast<unsigned long>(l.tv_nsec) < r);  }

#else

inline void zero_highres_count(OS_highres_count_t &count)
{  count = 0;  }

inline bool is_highres_count_zero(const OS_highres_count_t &count)
{  return count == 0;  }

template <class Ostream>
inline Ostream &ostream_highres_count(Ostream &ostream, const OS_highres_count_t &count)
{
   ostream << count ;
   return ostream;
}

inline OS_highres_count_t system_highres_count_subtract(const OS_highres_count_t &l, const OS_highres_count_t &r)
{  return l - r;  }

inline bool system_highres_count_less(const OS_highres_count_t &l, const OS_highres_count_t &r)
{  return l < r;  }

inline bool system_highres_count_less_ul(const OS_highres_count_t &l, unsigned long r)
{  return l < static_cast<OS_highres_count_t>(r);  }

#endif

inline void thread_sleep_tick()
{
   struct timespec rqt;
   //Sleep for the half of the tick time
   rqt.tv_sec  = 0;
   rqt.tv_nsec = (long)get_system_tick_ns()/2;
   ::nanosleep(&rqt, 0);
}

inline void thread_sleep(unsigned int ms)
{
   struct timespec rqt;
   rqt.tv_sec = ms/1000u;
   rqt.tv_nsec = (ms%1000u)*1000000u;
   ::nanosleep(&rqt, 0);
}

//systemwide thread
inline OS_systemwide_thread_id_t get_current_systemwide_thread_id()
{
   return OS_systemwide_thread_id_t(::getpid(), ::pthread_self());
}

inline bool equal_systemwide_thread_id(const OS_systemwide_thread_id_t &id1, const OS_systemwide_thread_id_t &id2)
{
   return (0 != pthread_equal(id1.tid, id2.tid)) && (id1.pid == id2.pid);
}

inline OS_systemwide_thread_id_t get_invalid_systemwide_thread_id()
{
   return OS_systemwide_thread_id_t(get_invalid_process_id(), get_invalid_thread_id());
}

inline long double get_current_process_creation_time()
{ return 0.0L; }

inline unsigned int get_num_cores()
{
   #ifdef _SC_NPROCESSORS_ONLN
      long cores = ::sysconf(_SC_NPROCESSORS_ONLN);
      // sysconf returns -1 if the name is invalid, the option does not exist or
      // does not have a definite limit.
      // if sysconf returns some other negative number, we have no idea
      // what is going on. Default to something safe.
      if(cores <= 0){
         return 1;
      }
      //Check for overflow (unlikely)
      else if(static_cast<unsigned long>(cores) >=
              static_cast<unsigned long>(static_cast<unsigned int>(-1))){
         return static_cast<unsigned int>(-1);
      }
      else{
         return static_cast<unsigned int>(cores);
      }
   #elif defined(BOOST_INTERPROCESS_BSD_DERIVATIVE) && defined(HW_NCPU)
      int request[2] = { CTL_HW, HW_NCPU };
      int num_cores;
      std::size_t result_len = sizeof(num_cores);
      if ( (::sysctl (request, 2, &num_cores, &result_len, 0, 0) < 0) || (num_cores <= 0) ){
         //Return a safe value
         return 1;
      }
      else{
         return static_cast<unsigned int>(num_cores);
      }
   #elif defined(__VXWORKS__)
      cpuset_t set =  ::vxCpuEnabledGet();
    #ifdef __DCC__
      int i;
      for( i = 0; set; ++i)
          {
               set &= set -1;
          }
      return(i);
    #else  
      return (__builtin_popcount(set) );
    #endif  
   #endif
}

inline int thread_create(OS_thread_t * thread, void *(*start_routine)(void*), void* arg)
{  return pthread_create(thread, 0, start_routine, arg); }

inline void thread_join(OS_thread_t thread)
{  (void)pthread_join(thread, 0);  }

#endif   //#if defined (BOOST_INTERPROCESS_WINDOWS)

typedef char pid_str_t[sizeof(OS_process_id_t)*3+1];

inline void get_pid_str(pid_str_t &pid_str, OS_process_id_t pid)
{
   bufferstream bstream(pid_str, sizeof(pid_str));
   bstream << pid << std::ends;
}

inline void get_pid_str(pid_str_t &pid_str)
{  get_pid_str(pid_str, get_current_process_id());  }

#if defined(BOOST_INTERPROCESS_WINDOWS)

inline int thread_create( OS_thread_t * thread, boost::ipwinapiext::LPTHREAD_START_ROUTINE_ start_routine, void* arg )
{
   void* h = boost::ipwinapiext::CreateThread(0, 0, start_routine, arg, 0, 0);

   if( h != 0 ){
      thread->m_handle = h;
      return 0;
   }
   else{
      return 1;
   }
}

inline void thread_join( OS_thread_t thread)
{
   winapi::wait_for_single_object( thread.handle(), winapi::infinite_time );
   winapi::close_handle( thread.handle() );
}

#endif

class abstract_thread
{
   public:
   virtual ~abstract_thread() {}
   virtual void run() = 0;
};

template<class T>
class os_thread_func_ptr_deleter
{
   public:
   explicit os_thread_func_ptr_deleter(T* p)
      : m_p(p)
   {}

   T *release()
   {  T *p = m_p; m_p = 0; return p;  }

   T *get() const
   {  return m_p;  }

   T *operator ->() const
   {  return m_p;  }

   ~os_thread_func_ptr_deleter()
   {  delete m_p; }

   private:
   T *m_p;
};

#if defined(BOOST_INTERPROCESS_WINDOWS)

inline boost::winapi::DWORD_ __stdcall launch_thread_routine(boost::winapi::LPVOID_ pv)
{
   os_thread_func_ptr_deleter<abstract_thread> pt( static_cast<abstract_thread *>( pv ) );
   pt->run();
   return 0;
}

#else

extern "C" void * launch_thread_routine( void * pv );

inline void * launch_thread_routine( void * pv )
{
   os_thread_func_ptr_deleter<abstract_thread> pt( static_cast<abstract_thread *>( pv ) );
   pt->run();
   return 0;
}

#endif

template<class F>
class launch_thread_impl
   : public abstract_thread
{
   public:
   explicit launch_thread_impl( F f )
      : f_( f )
   {}

   virtual void run() BOOST_OVERRIDE
   {  f_();  }

   private:
   F f_;
};

template<class F>
inline int thread_launch( OS_thread_t & pt, F f )
{
   os_thread_func_ptr_deleter<abstract_thread> p( new launch_thread_impl<F>( f ) );

   int r = thread_create(&pt, launch_thread_routine, p.get());
   if( r == 0 ){
      p.release();
   }

   return r;
}

}  //namespace ipcdetail{
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_OS_THREAD_FUNCTIONS_HPP

/* os_thread_functions.hpp
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
*/