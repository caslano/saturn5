//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Peter Dimov 2008.
// (C) Copyright Ion Gaztanaga 2013-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//Parts of this file come from boost/smart_ptr/detail/yield_k.hpp
//Many thanks to Peter Dimov.

#ifndef BOOST_INTERPROCESS_SYNC_WAIT_HPP_INCLUDED
#define BOOST_INTERPROCESS_SYNC_WAIT_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/os_thread_functions.hpp>

//#define BOOST_INTERPROCESS_SPIN_WAIT_DEBUG
#ifdef BOOST_INTERPROCESS_SPIN_WAIT_DEBUG
#include <iostream>
#endif

// BOOST_INTERPROCESS_SMT_PAUSE

#if defined(_MSC_VER) && ( defined(_M_IX86) || defined(_M_X64) )

extern "C" void _mm_pause();
#pragma intrinsic( _mm_pause )

#define BOOST_INTERPROCESS_SMT_PAUSE _mm_pause();

#elif defined(__GNUC__) && ( defined(__i386__) || defined(__x86_64__) ) && !defined(_CRAYC)

#define BOOST_INTERPROCESS_SMT_PAUSE __asm__ __volatile__( "rep; nop" : : : "memory" );

#endif

namespace boost{
namespace interprocess{
namespace ipcdetail {

template<int Dummy = 0>
class num_core_holder
{
   public:
   static unsigned int get()
   {
      if(!num_cores){
         return ipcdetail::get_num_cores();
      }
      else{
         return num_cores;
      }
   }

   private:
   static unsigned int num_cores;
};

template<int Dummy>
unsigned int num_core_holder<Dummy>::num_cores = ipcdetail::get_num_cores();

}  //namespace ipcdetail {

class spin_wait
{
   public:

   static const unsigned int nop_pause_limit = 32u;
   spin_wait()
      : m_count_start(), m_ul_yield_only_counts(), m_k()
   {}

   #ifdef BOOST_INTERPROCESS_SPIN_WAIT_DEBUG
   ~spin_wait()
   {
      if(m_k){
         std::cout << "final m_k: " << m_k
                   << " system tick(us): " << ipcdetail::get_system_tick_us() << std::endl;
      }
   }
   #endif

   unsigned int count() const
   {  return m_k;  }

   void yield()
   {
      //Lazy initialization of limits
      if( !m_k){
         this->init_limits();
      }
      //Nop tries
      if( m_k < (nop_pause_limit >> 2) ){

      }
      //Pause tries if the processor supports it
      #if defined(BOOST_INTERPROCESS_SMT_PAUSE)
      else if( m_k < nop_pause_limit ){
         BOOST_INTERPROCESS_SMT_PAUSE
      }
      #endif
      //Yield/Sleep strategy
      else{
         //Lazy initialization of tick information
         if(m_k == nop_pause_limit){
            this->init_tick_info();
         }
         else if( this->yield_or_sleep() ){
            ipcdetail::thread_yield();
         }
         else{
            ipcdetail::thread_sleep_tick();
         }
      }
      ++m_k;
   }

   void reset()
   {
      m_k = 0u;
   }

   private:

   void init_limits()
   {
      unsigned int num_cores = ipcdetail::num_core_holder<0>::get();
      m_k = num_cores > 1u ? 0u : nop_pause_limit;
   }

   void init_tick_info()
   {
      m_ul_yield_only_counts = ipcdetail::get_system_tick_in_highres_counts();
      m_count_start = ipcdetail::get_current_system_highres_count();
   }

   //Returns true if yield must be called, false is sleep must be called
   bool yield_or_sleep()
   {
      if(!m_ul_yield_only_counts){  //If yield-only limit was reached then yield one in every two tries
         return (m_k & 1u) != 0;
      }
      else{ //Try to see if we've reched yield-only time limit
         const ipcdetail::OS_highres_count_t now = ipcdetail::get_current_system_highres_count();
         const ipcdetail::OS_highres_count_t elapsed = ipcdetail::system_highres_count_subtract(now, m_count_start);
         if(!ipcdetail::system_highres_count_less_ul(elapsed, m_ul_yield_only_counts)){
            #ifdef BOOST_INTERPROCESS_SPIN_WAIT_DEBUG
            std::cout << "elapsed!\n"
                      << "  m_ul_yield_only_counts: " << m_ul_yield_only_counts
                     << " system tick(us): " << ipcdetail::get_system_tick_us() << '\n'
                      << "  m_k: " << m_k << " elapsed counts: ";
                     ipcdetail::ostream_highres_count(std::cout, elapsed) << std::endl;
            #endif
            //Yield-only time reached, now it's time to sleep
            m_ul_yield_only_counts = 0ul;
            return false;
         }
      }
      return true;   //Otherwise yield
   }

   ipcdetail::OS_highres_count_t m_count_start;
   unsigned long m_ul_yield_only_counts;
   unsigned int  m_k;
};

} // namespace interprocess
} // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // #ifndef BOOST_INTERPROCESS_SYNC_WAIT_HPP_INCLUDED

/* wait.hpp
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
*/