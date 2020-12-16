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
oi4qbV3M4YsXcz2imvq6qlrns3EB7zVOlzzbwO8tBc+0IZ1uUG78eWVfOV8LNF4qfBzTtDpjGfoxzf55Cjzqvcolsr+BUYLfEQnG8J3CO8BaY+tZ2U9T5qWGxqr6Rmsdrzo5X20MQbm7o5V7GenSn6NhZ8tyOdaz1o7BczU71lO7Duem6Nb183WdgC4d604U5bvxEhsPxs+jUbzE9uVbVVfX1zQ0bFs1a2btwQ6syPD4uAmUY/fFwzmJsSLGo13HigzXYEVQpwsrMiKKkeEE9hvb/SvSqoOg+853a2LX06Za1wYcwzvS+qrGmbPrdG1FPtt2tx4gtos1OvTtVHl/FDvHE6v+3gi8zue7mjl4whLeLIU3S3i976cHgB4v5783TiP2rRgZx0IPmWKD9S484Qjs98V+Bc5XIpmTSBXoVKRpSOOxb9rtYqTq3MQY0QJ13TZbn5adQm84Lnqz7t2gHxwT/cixLOs5U/RgrynyH8LE+F2zxC+G5lLB0LzTb+fjVkiZctTdM+d8E5q3/KwAQ/NfxNDQ11+eOzN6CfYC1wz77zvt4zKOrwEdCHvZhzwrGmgX/77AwtPwW4WMKTmn+GMjjxprfzHxNBq+IQpfO8vrl6A8Y4l3vZMsPqQ4fLsreIsy8q1IPhVv8RL4TPoyaBj0FeIsXgUdBPoa6FDQ11leCVKE5fVleSmgRSyvkuVVKTiAZvJnkV/FAbxF/reJA2i324f3nN56nWDz4R2lt153V+RuiyP3XpRjitpf5C+MU+4C6x0N3lGRLxv0LPLVUq/11Gsj6AjijTYg3qicOKMJoIcSj3QYaDPoUaBHEy/VAnoM6Fmgc0EvAj0OdAHxU5dx/yrQI0Fv5nGrPZSzMJH9PUz8Q5x2t5i85LuLfP1B55LvduI07gEdCHo/27mY+K6HQGeBLiHu6knQRq41M5drzMwDXQZ6IehjbN8ToFeT/xquQXIn9yk/noG85V9RGRel5BuqGRfP0B7aQEOgz4L2434+94eAPqfoo5LlHajRRwv4UkHPYDlnga4l+zYeZ2vQC0F3IP5pMvFPexP3VEXc077EVe1P/FUd92eDXgTaxH2rP4nPS5Pjqj5kHqQd894I9DeNHa9GfawO2ht0Dc4Pm4GuStxYKXFlm4JuCbot8WW7EE82BXRryr8N8X1jaN/b0r7HEfc0nmvubAj6K/crlbVIXjkecfiR4mFg8ualGsORomuTbFaUKriYctA4a5TEW58EOJm/Zo2Snlif5IYdU/+WNUr+L+uTFC35d6xR0t31STZb0rNrlHQHH9QT65T8U2uU/NfWJxk7D/Mf0lykBUh3I7UhfYeUdwLmOKQJSLVIJyNdgdSK9AbSd0hZJ2J+RBqHFEG68MQAjxRswRZswRZswRZswRZs/7/t7/H/r685QNz/u+f/P5Q+/KWDLV/9XcfsUgHPgZ3FmX8Yzr88GO+zNOfp1G9hCG6P4ZHsxlBiAZ6MOReLB5iurC3wggYP8BrqL22lH6cigIoJeMXbvwF5ffmBx3ynR7mutQXGemACOh50y+gHFzB/sPfaArdrcAGvQ7ZyjV66ig1YNxpnXuOD/wbqisTWZeEDXsqJE4e0tev4AJTr8h3v0Mj2JmRrcchG06B83rbR0g3bQLkuvEhlSG8bC2Pl8+VXnVHksgurvqUht128ZeJnYuvrkm91tI72NLcP4zuDcbzV9mFkPaLvt73HIvL48F9s9eG/2Np1/8W3u+C/GB2Xod5u3byP8ozFLt3I2Iza5LveOkLe5HVkLE5eR8biruvo3S7oyLKf3m5/tQ9RXvFi21+NOko4XosXJ++rVrzYl6+admzrfdXs/l+a4W7bx2hbmas=
*/