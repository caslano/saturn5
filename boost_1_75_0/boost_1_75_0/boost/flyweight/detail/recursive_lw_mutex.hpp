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
5KFMdQaFV/Va8fMeEmpOid7d14Bdv89Ei7L4mzCqIagmwcpkz7fJHHHJ23RW83263cCvq9/Hx+dgqi3+d/njlz5MM0wRufopIgf0FZgaiuRN9nqYK9hw2NmunWlFPJ4vIAX1Np7VGCrhjbcoR0MmfbswklesxrV5B8qnDvIBm5D/23owp7x4Ne15Tn4Ls5lAl9FvUeY38usgetyfLja6FPCX379H121w9Q/jGTbyp6v49b0P8KN33tPZxCiGo079s2GU4Pj3klX1LxefHGZqn2J9eDFbUil8SfXsAlpSlUFFYc3JtLuPMlG7m2xF7S7+DEmQMn/GQlpSlSlWabGANvV3uyudm0DB/gkdbNYDpKRLGuSNhLPeBQmkPpNBaDMpaXzplJpAsDQVlpqXYGtLDXSbINQ61Lpx0B+MJztcGc+sDF8JcOHt8LaAPrdUX8wzwz7i0/oKBLPsbm1n8k+4ngTEyzzh41qpj4tSUeQuiqf+v5SLGDlQ/3HFq9WrwuoJLWFcPIWzzuWmrslKSQU8H8LrUQoxvmPcvdllstnVkzV6UiatY0v9MR+lIVl1Gll1giyctTJZJhCETg0gTBFnMGolHkuBAN2fUGafTTilOHUu/7DD5iazts/ET1ZsWqzpCk1xPJ1ifXQxjyXTUg5ex2MV68cyaB34zX9l2O/0+zJjgf9fLxao2ZZqGXKI3Y1uHrR/6f92XIapyFdk
*/