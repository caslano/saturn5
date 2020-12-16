/* Copyright 2006-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_RECURSIVE_LW_MUTEX_HPP
#define BOOST_FLYWEIGHT_DETAIL_RECURSIVE_LW_MUTEX_HPP

#if defined(_MSC_VER)
#pragma once
#endif

/* Recursive lightweight mutex. Relies entirely on
 * boost::detail::lightweight_mutex, except in Pthreads, where we
 * explicitly use the PTHREAD_MUTEX_RECURSIVE attribute
 * (lightweight_mutex uses the default mutex type instead).
 */

#include <boost/config.hpp>

#if !defined(BOOST_HAS_PTHREADS)
#include <boost/detail/lightweight_mutex.hpp>
namespace boost{

namespace flyweights{

namespace detail{

typedef boost::detail::lightweight_mutex recursive_lightweight_mutex;

} /* namespace flyweights::detail */

} /* namespace flyweights */

} /* namespace boost */
#else
/* code shamelessly ripped from <boost/detail/lwm_pthreads.hpp> */

#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <pthread.h>

namespace boost{

namespace flyweights{

namespace detail{

struct recursive_lightweight_mutex:noncopyable
{
  recursive_lightweight_mutex()
  {
    pthread_mutexattr_t attr;
    BOOST_VERIFY(pthread_mutexattr_init(&attr)==0);
    BOOST_VERIFY(pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE)==0);
    BOOST_VERIFY(pthread_mutex_init(&m_,&attr)==0);
    BOOST_VERIFY(pthread_mutexattr_destroy(&attr)==0);
  }

  ~recursive_lightweight_mutex(){pthread_mutex_destroy(&m_);}

  struct scoped_lock;
  friend struct scoped_lock;
  struct scoped_lock:noncopyable
  {
  public:
    scoped_lock(recursive_lightweight_mutex& m):m_(m.m_)
    {
      BOOST_VERIFY(pthread_mutex_lock(&m_)==0);
    }

    ~scoped_lock(){BOOST_VERIFY(pthread_mutex_unlock(&m_)==0);}

  private:
    pthread_mutex_t& m_;
  };

private:
  pthread_mutex_t m_;
};

} /* namespace flyweights::detail */

} /* namespace flyweights */

} /* namespace boost */
#endif

#endif

/* recursive_lw_mutex.hpp
hI5nqk6+Y3AT6kO/G1CfmMtQtxeo3WbUdcT1JHcI+jiGPtBAufhSCNi5DvUfuv8T0N77dwmdp1CPjtCq/qfY5KNiMr+d4ORa00GoNZ1JWlO2csurABMqMqUpOaJAulAUSNQKkx3CoYRTpvsq050acXy+Dgox0GTZo/4e0snEFUjAbcTOxt+QnRwjOzGnhMJyP04ftJx9WvxXcK8S3p9E7TKqPwkyu/35XKxDBkcfwf2MQJb0QvU7LOJQ7lPrcmqIDyh4IXfd0f/XL7GG87i4X+Hdav6PoUnts4Oq/nOHnfkwnYM+f5DrPy+zYT/HxP5AtJwkh2jVYEgq4RN7/liMfnkf3URjOjtaXGihiQP3AWSiWz9eua/ui0M5yn+KA2GbCesQthPcgDMMVTD2Z9pL0n7HFRisr+CpILoq0tXG9+iVrLqnjIuuDLZ8rQERE7YVUhbHqaSUQVICdwSmW9oiUzfPPInt8Lxwu9AecBmz1pdXvN2MoHOz1hbVRAeeu/TCtvnoq1GU2LYN4dep+lWmvyNcbLrE2QYPduRc3aY8394beyURS5OC87TaKzH+Zw0XqWb8wnuCJpC6e7h2gNql+n4cMr672PpJPeLcDuhEU02MLSqP3dCXZG0xpdEx1ON0vIRnTdpHoNugyORl6d7jqTOxwv8p6HFRFqZ2zwjE+q8IBi+VN1/V/tdJH5nrhPJ9Htpq5/ucxkG3+7n9WxUb5xP5zj/lfCLcfLrPoUSKT07CBWdCfbq8yK8uXKU5pSOcrWni/m0XsFYM76l1TzkhRDxk8NSalsQ/MsRHF6i//8bJL1DPSBXItSPYgORlaUpWbEGKeNEvCx+Oh3or8HQPpV3pYper6wecHM846AD/kEvglSdE/x8slpsMCv5Mp5iZ2rPf4KfyIP8g7mAEqyWytEmGEt1ZCQZb2D21rTd1QmxRM8zIpIyh2al5eiwo0TDeFO2m5k4cNVSa235mXCi7IfZ/54k/ca3FFCBDagpx5JLS836jTfaEXvo7bQG9CyhAcBQeUBswTDnb1FdTyHlBVgplPEgW3NXQN4HB5BGzEo2M21EA2uffy/j/XfI/yMB/vuR/A8rgnKQm0xJJaUCJFFE5hRKlHp2vbOWBUa4Kv0VpgYKBhB4/G9aAHdR36wZUW6XPTGwVZlC2GqphjeNf6hB1+e6lJR4/Ut810j45k+wFGGKa3Bvt8xbu8rbbItr3VmmbmkVlYTSq9XaarvbG5TRQeQxkGqzwYiZ26QxDF/75CgvzeH/jHPW3OsJT9LsE0cb7XeyNZbihcaOjfeXxj0fILktIB+V2s3R3qkifScqo6H3H2gGk4B5sjCGNrJqiclgFHr44BNxi8kewttFpD3ZFg2Qsm5K0LtrpHZoAL8BJ0rqE+LpbxGsqvnqHVkpDideTk7SukqfuLr1HowMr/pBvpqTv545fWXsKLZ+VnCbjIM1xi7vdz9DaoWd95ZbKOPYfeU6Fi5FOnyvwqh57vyBBD6EHrd3cwR11ojzhAgl0Fp2GuJEenGeMu4UbnYrUVxCPhVxIrAcTmnHBdzvTWsPSgqicBfH0ga0tkTm0i3k5VnA3hbhT8sqUxN7LYdiLZewFrjDysMih8hBXlIllKgcSiQWSZGP91/5vtIOh31vPs/J7A7Z158f5+Mfly8Q/0T4P/inj64d/Yn3DAg9amJLffBbU6LdZZDT4BTLyLTI8v0LG5RYZw7HNalpkvH8OIGKKWl7sqWv476XdmdD1JkuuN7S0XCFE+WDymxMSHeo5VFOxepK2mFbPZgVVRLJLTRbTUUXIFFeQo0KquMZYRUHyhmZ6ZgdTpod71PopSJeYKtHgxEpp0RA9LFfB+UI=
*/