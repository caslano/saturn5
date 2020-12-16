//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_PTHREAD_HELPERS_HPP
#define BOOST_INTERPROCESS_PTHREAD_HELPERS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <pthread.h>
#include <errno.h>
#include <boost/interprocess/exceptions.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail{

   #if defined BOOST_INTERPROCESS_POSIX_PROCESS_SHARED

   //!Makes pthread_mutexattr_t cleanup easy when using exceptions
   struct mutexattr_wrapper
   {
      //!Constructor
      mutexattr_wrapper(bool recursive = false)
      {
         if(pthread_mutexattr_init(&m_attr)!=0 ||
            pthread_mutexattr_setpshared(&m_attr, PTHREAD_PROCESS_SHARED)!= 0 ||
             (recursive &&
              pthread_mutexattr_settype(&m_attr, PTHREAD_MUTEX_RECURSIVE)!= 0 ))
            throw interprocess_exception("pthread_mutexattr_xxxx failed");
      }

      //!Destructor
     ~mutexattr_wrapper()  {  pthread_mutexattr_destroy(&m_attr);  }

      //!This allows using mutexattr_wrapper as pthread_mutexattr_t
      operator pthread_mutexattr_t&()  {  return m_attr;  }

      pthread_mutexattr_t m_attr;
   };

   //!Makes pthread_condattr_t cleanup easy when using exceptions
   struct condattr_wrapper
   {
      //!Constructor
      condattr_wrapper()
      {
         if(pthread_condattr_init(&m_attr)!=0 ||
            pthread_condattr_setpshared(&m_attr, PTHREAD_PROCESS_SHARED)!= 0)
            throw interprocess_exception("pthread_condattr_xxxx failed");
      }

      //!Destructor
     ~condattr_wrapper() { pthread_condattr_destroy(&m_attr); }

      //!This allows using condattr_wrapper as pthread_condattr_t
      operator pthread_condattr_t&(){  return m_attr;  }

      pthread_condattr_t m_attr;
   };

   //!Makes initialized pthread_mutex_t cleanup easy when using exceptions
   class mutex_initializer
   {
    public:
      //!Constructor. Takes interprocess_mutex attributes to initialize the interprocess_mutex
      mutex_initializer(pthread_mutex_t &mut, pthread_mutexattr_t &mut_attr)
      : mp_mut(&mut)
      {
         if(pthread_mutex_init(mp_mut, &mut_attr) != 0)
            throw interprocess_exception("pthread_mutex_init failed");
      }

     ~mutex_initializer() {  if(mp_mut) pthread_mutex_destroy(mp_mut);  }

      void release() {mp_mut = 0; }

    private:
      pthread_mutex_t *mp_mut;
   };

   //!Makes initialized pthread_cond_t cleanup easy when using exceptions
   class condition_initializer
   {
    public:
      condition_initializer(pthread_cond_t &cond, pthread_condattr_t &cond_attr)
      : mp_cond(&cond)
      {
         if(pthread_cond_init(mp_cond, &cond_attr)!= 0)
            throw interprocess_exception("pthread_cond_init failed");
      }

     ~condition_initializer()   {  if(mp_cond) pthread_cond_destroy(mp_cond);  }

      void release()       { mp_cond = 0; }

    private:
      pthread_cond_t *mp_cond;
   };

   #endif   //   #if defined BOOST_INTERPROCESS_POSIX_PROCESS_SHARED

   #if defined(BOOST_INTERPROCESS_POSIX_BARRIERS) && defined(BOOST_INTERPROCESS_POSIX_PROCESS_SHARED)

   //!Makes pthread_barrierattr_t cleanup easy when using exceptions
   struct barrierattr_wrapper
   {
      //!Constructor
      barrierattr_wrapper()
      {
         if(pthread_barrierattr_init(&m_attr)!=0 ||
            pthread_barrierattr_setpshared(&m_attr, PTHREAD_PROCESS_SHARED)!= 0)
            throw interprocess_exception("pthread_barrierattr_xxx failed");
      }

      //!Destructor
     ~barrierattr_wrapper()  {  pthread_barrierattr_destroy(&m_attr);  }

      //!This allows using mutexattr_wrapper as pthread_barrierattr_t
      operator pthread_barrierattr_t&()  {  return m_attr;  }

      pthread_barrierattr_t m_attr;
   };

   //!Makes initialized pthread_barrier_t cleanup easy when using exceptions
   class barrier_initializer
   {
    public:
      //!Constructor. Takes barrier attributes to initialize the barrier
      barrier_initializer(pthread_barrier_t &mut,
                          pthread_barrierattr_t &mut_attr,
                          int count)
      : mp_barrier(&mut)
      {
         if(pthread_barrier_init(mp_barrier, &mut_attr, count) != 0)
            throw interprocess_exception("pthread_barrier_init failed");
      }

     ~barrier_initializer() {  if(mp_barrier) pthread_barrier_destroy(mp_barrier);  }

      void release() {mp_barrier = 0; }

    private:
      pthread_barrier_t *mp_barrier;
   };

   #endif   //#if defined(BOOST_INTERPROCESS_POSIX_BARRIERS) && defined(BOOST_INTERPROCESS_POSIX_PROCESS_SHARED)

}//namespace ipcdetail

}//namespace interprocess

}//namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif //ifdef BOOST_INTERPROCESS_PTHREAD_HELPERS_HPP

/* pthread_helpers.hpp
TlIc5t0p15j5xiG5A/eB5zX3H/+SadHBmBOcF251e38HM+0fF+81dAIW9dnbcZSnTySxTkRLnr6G8nCirYy3PntNB5EW9K4+C5QWlR04LerNWRsoP7tR1/7uHX9ri+t3I4yHYnCxbBvYRWpi/lJeh1j/lzSDln53eA06wbxx0sZOLilU9Fu5PaHoV7mt/Sryq3P9571+aYOSvOYPY3zN2+r7mtvG+povjpNm65hWSmf7uSyNGyMfxpvnsvjuf+I1dI0aB1xDB7fBn8uyMj74c1lWxtf9XJZGjet+LkvvLvY0aiLaavY04j013jRKriaNttQijbbUIo22nEYaJZ9GGk04355GKWLO3p5GvEae9xdWc75PVS3SqKoWaVR1Gmn0/Wmc77Ooqz2N0pBGMQn2NKIU4vHjZoHzEdwGn0YxCcGnUUxC3dOoWR3ykTEuNKy718PbeZ3aYlzfib6qN41QIJbmF5SJbq/o5trWUcixNpJfoI3Ev3PVc+PwU7lGwmw/d6f7BWixZtrTU+0eQZJtyT50fzLmGsPsaczu1eNGUpfqSJIZhr11blV/VvrB63B2xppX0PsubesfFGsd3Iq1DjG2cQy/dTw97OdZNRdlQoJxnpWtbqlxz3FVQvDnWVUl1P08K4ShuvOsZP3Z0x7HluKbTrTHkeuGGvehxiQGH8eYxLrHcV1scHF0XWCPY6YYU1fEkcv2mveg1SKO2acRx2VBvsc9ijiegzjm2uPIZXPNewlyaxHH3NOII8KgjqNf2brkIl6n78AzmQ649aARTHEszbPqHqByaX5czTq+yT3H0+nisR9LGTaN7r8Obc6zlOPnVvfFMZxOlrL8DrrfzzFFd2r362cpy1L2Q5alqG/G0jis7HMcOCxknMpyFO5tc6OGvujr6d5VjvkYN/qLHslzhLx2TZN6oF8luaYOB1K9D8Z/ShBWY+xkCd27H2NdUdA9eo3us++A0+kBkunhKNJ1pFRTWl+xH/lyWy9jPaju1sPQ20Rn+l53RIiyr8lu9vfifluzLLJPZPv43kbfMUU5Z9kd5miYX4rxXuvqV3dJmVOxgsHMR7q99fwRxNVizmFzLPpNz9B70tL7X96uncZ2D0i7cw27hdIu27Cbadqd29mwK5J2nQy74dKuo2HXT9p1MOw6SLv2muV8DHwXSt3OyP/cb5P1ZnEMf4+2epPzqN9ZB0f7ehPsGK5IXL/hao2yyGOURaW28nYqRGzfT6zx/ZC7T7V31etg4a//+LsMl/J7tZRr/0gy9rXKef3pdL9K+17d7oF75TpW9XeZqFizwN/LDLr3s7aP/XrGuhafv8nHSWad9gqtMeBvkezehfkV+saWolzshDT/xlhzHY6VRO9XM5bEbkb1Neac7Osb6SwW/o60OPo2rIR9zd8Ktc8U+Sec5xtk/pF5De/DZz9fjN9aVuu80KhLeL28OFMeXAS2FX3/BmY+y/fmMlveMsusd0n2Jr0exiO7qedc4V/w65Yhq5rLUeUjyKrmnWR5/CHdL9bD4OpV1I/t9VhFHpP+yDxWYq7Fm9CQ1reYa/G6NuL1dj46GaQ+BtXay9/J/37mXNoC8jPf7ifdZzNi2AJ5KFyWxdSml2UymzkfxQc5V2nLUzWseZbzV5yf/Oa/Ym16DHzbHEc5j53NAUrG9XmS2ONAeczbccDezMnFtI7flkcU+Qlug1u3z3GV8fLTXTLkct4TpXv74jeAP4n9dd6wFeN0EFvjXbUWG0YtLYnesd4abYR2uksVbvZXvU8qFjxE98/nPUOGfD3TD7ZT7JGSa7ScFI5k5J4o8sdtuukivx0/f7Ib89kQmmY++xTdn6z7tIc4/zanZ1ykt0Q=
*/