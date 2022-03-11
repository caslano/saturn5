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