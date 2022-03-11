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
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <cstddef>
#include <ostream>

#if defined(BOOST_INTERPROCESS_WINDOWS)
#  include <boost/interprocess/detail/win32_api.hpp>
#  include <process.h>
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
   return count;
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
   winapi::system_info sysinfo;
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
   rqt.tv_nsec = get_system_tick_ns()/2;
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

inline int thread_create( OS_thread_t * thread, unsigned (__stdcall * start_routine) (void*), void* arg )
{
   void* h = (void*)_beginthreadex( 0, 0, start_routine, arg, 0, 0 );

   if( h != 0 ){
      thread->m_handle = h;
      return 0;
   }
   else{
      return 1;
   }

   thread->m_handle = (void*)_beginthreadex( 0, 0, start_routine, arg, 0, 0 );
   return thread->m_handle != 0;
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

inline unsigned __stdcall launch_thread_routine( void * pv )
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

   void run()
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