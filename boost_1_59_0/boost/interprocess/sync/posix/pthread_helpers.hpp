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
              pthread_mutexattr_settype(&m_attr, PTHREAD_MUTEX_RECURSIVE) != 0 )
              #ifdef BOOST_INTERPROCESS_POSIX_ROBUST_MUTEXES
              || pthread_mutexattr_setrobust(&m_attr, PTHREAD_MUTEX_ROBUST) != 0
              #endif
              )
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
                          unsigned int count)
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
YfgRTd8QXnbTpgTH6kntUKKc2uiauxfe6ajQADAHLCADluhX/ScSrWlJIRYCF3YIy5hmT41WiwSZEEUrfPurm+FrP2oaoGibwabnufILulvIL0k/eq6nEAHly1QWMyJHFQzaQW1GKnozPur42NVZI9SUQNnc3QiahohYKFGIDsIxCgD1KrGzWickFSZXz5UQQAoTDdAminPvLIKAuIUmxObL3H4/hSYHKDkygaxXkgES4n3WtvFmezWUh+RLsfz0xzFSo1W/FJ7rnExM8w6XJtEANVUHbVGubEzGOJTt/ZVNkmqmmot9TPdW9IMDRzow+hlvoiSWrRrtJ2mIACFHTU9OHHXnPb29ut6eDKO03aOoBiTFvfPro+Z9RsdPnCp3/o233n7ruPbNYyweruFTCQzrJXJG+KLqnJyuuz/7yPAEAAmAmgRjCgPsKqUA8QNPHoh09aw84L+bgtPs59EU6XlLm0ngyobvyWwknj4AAOCcglkQAgZEt39tRaKXMybiceF5GyqTt+fLmukrzXY990ZQTIandU8pUCuL8M95a6NB2MPS82SV5yEsj4/DEnJ1X4jhkoHh6yUgkRZHvxukZaqSlK23P40ysMlV+jE0QflZHm1bCyNmoOwik9WczZgDp29CVKgq/wTsjlVlgm9Au1pHu93c6Is2j+9D3aQ+VEX9Ko8ul3LViXVwd8aKp/5G/niN3TBOjFAohAN46gM1tiiwmxOKO6MLUI1fht/9Tl5iUNmw2laF/Xg4mhiPygJvKMHPcskFfWY249hBwJsQ7tZOE6lh9eZeYBAjbyPzOsg1tNzRh2tinXfyzRzj2mbNwfSgRvEVYNEZmRpdb5El1ybXyHGwq7ENjiRysU3iXVmdj0Z7Zve/D0Ee8VSFI7+7IN84Q/ibi4WGV526q5il0tsX2ObPfZfkMmZ9YG015DZhpn65Z97t3Eb8oNXhh1iy/tmaAYbFWSPkn6o98Llx6h0BcEqpUULLuq7ymttnnjUaBvzKMgPC9vveAkd0GjUrPRb6BbPB0jeY8fp/QcySen/elfCoP2Rks65PWC5u7EC5gJu1t9vKBeMO5qyOEvvc0Zopm5UyTeAUG+d1eGWVESgFRuuMQHP8hJGYEHNFcqSXf/yhXf4uPfVJvgLHJOTn7W2GFX1H+6Yr8nyT9bSp9siGXY9Eh9CHwa1MGi0VaDA/JaH/bFFSCQ8Phr52ibdXxe6SUpduB6jZrXkUKedC1/7gnq0EtlSXzxq4DyKdPrRPQNpCCiWmdzkiGWRgQsbMbUgCvw9eTO0RsI0RBdigTKNK1kkn4m3vAumY/KZv162XyXOMfpGfRVpJoBGczNr6xw9YZd0lkMEzbBD9TKsp4VqFCkCbyojlCOaf+75Bja3htlxSVXsru98R/JBDZg52YqE4DwXvK/bUd6M+guLHgjHQvkNKAf6xucG0tmkdCwhrvg3AGpwjSUINtql5UscKudrv/76wjFtjsCK0vqSAaKVx4At9XlIdjKDmqRqqRqpOKBzJyz66a31l/efe1985OHiYyYPh4UZpx12rVIOpCOivg/127MVKtBxP5zD0zBgPNBgDHWx2lvGk4QgUX3fZzrIkEHGLWC/8t2S3SIp7teSIJB5PajF89tyhURPdFLUXrI+38dGsBgAQnubZqlvmAoNkv/uVivvBhCOYG9VmykdT+Y6Qhr76Jp9nUD7bRg6f930SSvbh1pbXS1bNOtRIuyOX9EkjFYuvsCx5fUJXw0S4Mr88TCC3jkYF1GXYrdQJM1ClmRWjFaMg2YBGEDKSh2dkcvIxi6Cctt7R7Bs5fyRq+EnKYtDFLDqiajlNbs/IVX3LxbTEmbtUIBnHDwDugnxaYL0thn85AZ9OQNZTxj0V1IxSXK3aGyhTG2GuCJI61H133qy1dmQdztiCwI5MqqCMsami2QVKORzWI2fZm9ERUV4lzLo0jUkcITUTwXVrDP2N9bMfD3hM6EJzOr4D4wtxZkTkeJgLMEGlknOrb6Xv8STBJUrs0gZ/IskTFU2jME5dZ6AXmqJfExBpWbRsI8TOw/DEZVnGNUJs+bbH6vlgXfgCrogmDZyUvRiQk9qSLuPCUrbzbt+bt6M7T5k/oRA+6sjigjSNVFWd0web9HG5VoV2NZMb7w7S4z//7OkuaMoc1pKFRmJVPAli0Sg57XzEKJhD3xXZV/mJX109u6JaZUcxRsFdAKkZrO1kmbNU3DBkU6jzA58CCy9+bgXiHFKxHd4sDcoRYf+JY85i9Tw6s5xwt4LBQjXfShYnTFwM0PNhwIeFnmjyFk8u1bpE+gdxA3Qd36uWka+iAksZ+AaSQu6X8mZaX8kMnnpkjs4hacSvZZPN9ts2SmOC1g1+Q4UzE2no3fRog+Ny9gNq+vzcsSBHntKtEorkFb6kVTS+CBk1BBDt9l7y8B0KUL5FYY2cN+w3jZuQeBLKcNFfjqrbsdWY4fZGC7ruC+VFJ8uTWqm1mjUAaTHcYgBmhFE6f26xALoHZ6+vWRXnuyPLOUUq/ABaUZVd76JzvOdfHDugvBJtUt8Ydwnf42bGTpDMhdS1lXaTuD38ygQGjTNCAOxP6cnPMGCl/m0+aeu+kWApvleBIfO95DbS7ehtHgKTgX1wxPTK0YjVVBOe3utXKQ5N98pQMZ/7IV7O1aMEpyX6ptT9g4o3VXjXATpMT/woiMzEUN67UXmcsoCHJ0XSCYVdK0jxsG+5oRg4w4ao1ASDWd2XeyPJpnjxL38C46eqZKuw7yrcZ4LFeb2i7UrBNJKXcUdcZ5pNKC6k4kRi2Sf9fSq5LrXKYCUOB9vHYMnKOZ2/cFqLQPBJchYHESz2zNRhp5bD+SYphDpsKGdO7hgUsceR4t0yzDGyQBXztr/2wf+RRhluGKrmtHNNIjIAKqW+gwx2vmMNTRVgNWESxQT+khdh6MGPhouzM071+OE0Ib6pq20huuZ3cOC/XiFlUBOETQVlCElVKDcoXRpFVCVVYF0PM9Lwd/8WlOfhwqGOGopSptsIWqfzcgJhOFKP7eTxR+LQpuhcKuuaA4ouwopQaHFizSYkTpizNCkx18ZMTPuUfUxrOYm0QbR58oQwkoBGheuFk0spqgGsqkJEwMDCEEZdwZoig7OFAHv0vTXQcKVdkvsyc7QlEWRI3Hmenj0DUbScSgKqJA3Vfpi7X7VFJeH1MLcd5IVHxQT9fZRJmcw722RlkyJLRrkVe8XQkBaGUD5ZWm3vLUjMBDqX3XjT1oKsDtPNvUUrCtda3MzT605EurtFuzUtF+mEnRMZFelNlj2dUWLeaYPQ0PcwBokASyuFAW1qejaAR6CRb3a1kL6GBy2/G/trVj8NBftydJEGk0YRcXPNFUYttrlO/qNZbxneTCBDCHHhgT1CKqGhUkLBxnavs07w9Vf9xEWXpqbC7GHZsVvuynC4iKd0B4ijFMLmlASRFK3Kxb8vgmOCJgEXZIOEhEcdtUOuKVLUKDpkUtxI1lfUNwrIw4wWtQNAYW7/RNQcEnBxwfYxqbuSypTHW/ECYlV7ucrGbljGQ9PaKt9Cip2SuApK0hSQWHa6pSEpBeeCwWyDn4vrzO1BCxiGVZYdxs0t7xQ7P2SVJejOZag4gGVmPkI31EmNIFAPfZkZtv2zRUhSSt81OVX9yJFoWcZY3I4GzdHHoc/WD9d39aWudRqhYCwpha1asLjiwrokSSKJWhZn0PrMUYvSxusHQePy94eHjBjGDEdgqW89HIAkQM0Ns4RCKzV5AIDeTusAbOTYNodix953kPAFt51curbBAlj5PwOMdwHIk9/iq/8pN0Gxlun2/3fijsDwf+oCUBkdiwc1iRiNqeiSwwkHaikhxYDRjvhVCOVqWrBdSijMJ8zM/uWgNG1uJb9phXCW+9Hk+OVgMh8Q1I5UaDWKWsBdrfSsWiaZgdtokMx82iDjqcBpW0ws1AbGJB92hzEBPgfwQFCVPPcjlsBGVyK7GxvdRjfA23CUGYrJraxKj54PNdCRDcDY0ha66PmC5ZFBp5ftEAIVSRYoqFESih4pWszZsaMULe4nsYFplDPDUmkYRu5xrhL6jicUwVn/d3qzzdI3P96fEqjdWRTa7kd76vOYVAsxm1SHEO2sqTpsPJLZWJUw5Z7VcQ1QWNGKzCdEK1x2JVkYQzBnY48F40BWkYM7KUU2yB4TiTKyjlFYlU3BH1alKZHxHazpIN0dMBZgAUACNKBPsFhZc43HxvduuxmNi6BcdV/0l8ni9xZHrYBc2uwxYakqpMjiDw5w+Z+c/fYIbhyR7eCJOKuJJroNdYDSyEMfjsypYmLN6TQaT6DZBk85W5ncY4H+dORYdPygeiWeCoUFFFN2XXAW+T0b9mwybeVja1VVkSUvcVZ3kcZhsao5Wrtr2NNOkitwaP8YRy/2JUfKIGxxKqxJTCMYACrgWkbJWv1NOXVMMxKBXqQT9SqjybLlhF7olcdutXNmCoQAy6LKFN0w9Byr5WGa0HoEMRiDeI8GK6oFKg8dY045xwJfUesJZNVA4qI2PY6U5jp0EApU13nodQVlLpxxeR2FTen1uoJiP4ZflOrAboue3GEbvuNEPY9yrMAC2SqT1oxUChLqSsEb8ySrEhtW2JIWiWYVlLVYGAQD0ZswbZJSxnCVwQ4WQMEAaPUeQLv9f0HJ+f8IJeZK7xHSoFBIOPvi0aTonu5USMoIHLNFjZAwZVBluL4uIsRFolVqfNs+hBFVjJkxGONqnKh9DTWeHWUxZwQ9pRCjh1cfTenDEBnK0P6cr5bDt0sNoo0TnNcFIslXHsbbfU8sXb+Wfecbj6qTrFwiMcRoRA96GYtF3lNVoRJMSI94UpLamCfYWUAyRJQjNbUPCYVZD1T0JWYyl0AealU84ddYrUQJ5iQsxMpo4371qrr0eMrntMi54ACR8xOj2F726uqnD9EOQR0qH/tRNpQYLBsq7GfJUEKMIiNhUwrSR5FiV6GGylR4EnHZ2Tnt7hKyEU4t84NP8iHnuoweyk5//sM2/4seTVpjVk1VEt5TaS5ZwZb7LDiCbpbkBsZTOUEFAHACsD77XUiT/jpA+3/Eqs0qBTMmCCEgpY1+rWNH0+lJJZkeCp/nmgQVedNEIsB7JzUVcbQoBHGLwJoeB9KV/W1VMSzt4DR6HZOGA/tMBsC/WvJMSf4Ck1eDd28Yaw4lcg6+aqnqLd/WdszcWZpyVa7OpCfVtJhmnuVnXbtWd/UQlUmMaCdHWtiM/Vo6yJlx8Kw4VG0WGuCE1Jfjy3qDVUUy7OYxK4MDedSPZ1MJk5F2EvFJAEVSp4vMdXqQBYgjjgWMAmwYOuvnv9w+erZqSf6tIR+NznPgpmiPJZXrq+IYOja8zq7oVV99T/F7V54e9H3vw7LFOxsSpqqxFFQSrecUm8oR1JmlAnT0Gryxy4gCXCAfdBQZ1lMCiK94L3bjEEdjkiygKmE6gIFec+/+uhtXYObE5f0PeoT/QY/3v9ADrINGA8BD+D+2RY2WwRoWC2FUMCKgl3N1qqIUkU5SojKAtVZfa5JEE4eiiyemA43S27nPFboNtrK4nHAvVe8hL1w2cTwHRCKtVoxtjKubJke3O6O7m7O201RhDs9cyfDpDnzghNMNveGcfX5Mp68sN2/VVeBz3bpel6qMgYaP5Jxo3L2l+mhswW0ZLxkzjPqwUEvRBPYCnVt9VgxSJoYZm5Qm0bHAGmmDqK4mLKcHTmlHExTQSnJZRnPEKEaLkKUCU7DqwqON2eTowepV5nV22hYdphI6OIOPGZI7yoKcAweyUoN6oR1WGQ5B7A5AbOQGGdHSsjFBERJ2GObGsaDPbTagHnNbwB/StWNebM6rgD2oVqOB3sj58TgZWBAVQBFCAGEANkpJxFpfLi5nfV698mw8PzV3ALBqSfzX4t7dpEpwg4IMC0YolsV0VkVlGqxURIUBGLf3Jey8yugVoZ3XX6IOo/lapiLLb7G0qwKzz49jtHAotpB2a6rX64k7h8hP8q0qSmRKFRwkkE1rD2PS7orzmf3rj5ijwzov8aXmJ2ZTlTa29QgqNA9U5gRWDmOlsSoai9VrhIcP0b4pE62wCM+gc9CfUJMQRbu9mwtc5dQCjQwz6o3nEVFBYQOKiStbzYo+hDWAUngo0D6VGRHIOduuAfpKRSQtZ2nYdri7uizlmp6Y6a5OxtHTXR9GGNGEMqBFvfeXXyAC52dFORqHYJ4Vgshp2ghwqkpd35zjtnb/t4yFxk0auYBCeKDqBRjt54+tLxHT6PMslg8KoKJbB5wB5rGDZEChHAtHDoaIqVUVswyMN0C8/v7K9pAndEXiJP2a11zPdRzpvuo09HbtbYYrMV7+PbHveTlOdF7Gj1RFceoxpxYB3LefjYJjCUreKrBVcQAAuA7BLCgFA2Lbv63LSHD/OJBbMTLSBB9FwFDAw/QTpmBOfFs+TULn7LAJGcgcxjrMEY0L3F6N+PXyBcm+5+ZAYWrmfpnKMVSqjpQeqfirNZRyUuIGDI4sMhMfFR35xJPAXhc6w8FwL/tpaD8SvA3OYYhki4eTPvayjVNskMVAqTW1g1ivh1b6NpgTBsDPtOVx3jc6BNiEYNEAiSWbw6rIXWYodNUwgvtQibur8nS7kQ1hDubg3BjjCPtxgqoQ1wl+P68f4hGsvjgCcLYVWDfabE5SD2XY7JHy70T9tjE9OIhJlOD716ZeDAgFAqFAhR/yCqLbAwSY3OOU8ooUl9vNZdTyqqEGju3nizOCxxOr2GhuywDnD+f3YL94LjRXXrXC4IkIeC4rXVfqEsCQhG0rH3HO0f2gq4dAn6lBjs8qDqffe4nInfoZEWqTbfj0S4iDxg5dgx/Ua1ehM1288zL6eUs/pLibd6KxlMWrP+reo5NY/OLeGrBLGcoFxD0JbFdVbHKvx1tjNKwgVU696/R0gkKm4JUN//LHf4GYmI/456ndJaLtyekCqhEI+I3tVWSvZAK6EIkyVb6S5nzfMO0fUapDjYSD8aDbChtXco3BwFx1L/oyhqkl8Ku5V6i46O3FFwEXskGPn5Zw2j/r8CYGTnInxdjTH5dPKk5ct8L3/CE3swwoPmAMOYJg/97p590MWhUoyWqF+zOiciVnaswfoYJfy+AJ8X50I+2CwmUf+/Q2913VhW1euje9sCsIHE0ieYXAO9Px4vlB52iNGKaUbwbh6iNhNhdMbgDrHgp8W2yiNy8DmT7adQCt192Z6Np20z3SdczP1dd1V4VsK+U/VeGsmuNuZauv4VszwEYM+7oGanJ2v/KPvzEp8CPmu59v59/WnuIyEoUhvnPwnw58X3BWyhEJOmg0Nzq/LzzJ6vnl9wkYaOEdO8FZ+PrEiBTrlI9+i3fz5LEUmXdV7/yeO7njpJ+ABHVUq6J8uRNGf7jCMVYUc4lu4S1bJBtUv7wN3zTHw4Ui4+yyDg3PNUcrSZWvh0ULzr9oTiG/2IL5Yngc+lqG7bHWIvoDGLOetvv1TZzNqimCBdhOzM+jEBzNg4OxixKdG4ufKK5KzFj9voGPHSFdRlj4dgKZBJdlQwmmNtEwvxW58xxLfaPvse6bk6sHLfGhOVlt5ZsVr5Q04ID51bmukpQ7z0UmyLVXjhVt7mTsqd9dZuhlGRe+a1O2
*/