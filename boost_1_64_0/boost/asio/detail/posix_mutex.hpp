//
// detail/posix_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_POSIX_MUTEX_HPP
#define BOOST_ASIO_DETAIL_POSIX_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_PTHREADS)

#include <pthread.h>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class posix_event;

class posix_mutex
  : private noncopyable
{
public:
  typedef boost::asio::detail::scoped_lock<posix_mutex> scoped_lock;

  // Constructor.
  BOOST_ASIO_DECL posix_mutex();

  // Destructor.
  ~posix_mutex()
  {
    ::pthread_mutex_destroy(&mutex_); // Ignore EBUSY.
  }

  // Lock the mutex.
  void lock()
  {
    (void)::pthread_mutex_lock(&mutex_); // Ignore EINVAL.
  }

  // Unlock the mutex.
  void unlock()
  {
    (void)::pthread_mutex_unlock(&mutex_); // Ignore EINVAL.
  }

private:
  friend class posix_event;
  ::pthread_mutex_t mutex_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/posix_mutex.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_PTHREADS)

#endif // BOOST_ASIO_DETAIL_POSIX_MUTEX_HPP

/* posix_mutex.hpp
0VzBnN9uK3GuJnId7G3nNrtdFI9L52tqnNg+SiPKzfwOfp4X3usxdscgX21geXYK4vWGulbZ2c+xlyi9XYJcm9LbVeHhefpufk5YvwQlSvOK3YM8XouNFNsVeN1S0dtiXIv2za0Iv2V5b7/4dzz4Ca4L7xHEIQ5xiEMc4hCHOMQhDnGIQxziEId/c5jAikMc4hCHOMQhDnGIQxziEIc4xCEO/4cg1hjsEVgnUIGXh7c2ozUGe0ZytOBpOuD38vNqHenefpyXRFKa+0RxtrONxfy+HXh7pIF57ufnhTGY5/5hfAmZ5gFhzh7e1s5mUrRW4sAgH1grIdJZCHQH/YZOLDaWfj3YrxVL99Yp9C6L3CFBbtuGWtdxaARnrkU6TPKFpbuD6zQPD3F6LdIRIU6vRTpScea6XKrjoyQnF+MyfrTE9QJcxI/x4WV3ZIT0x/pwvZbmOB+u8z3exIWpjJ9g4tQ6ED/Rh3tqLc9JEg8sqpXrb082eVFLo07NacLnO7ZzyuIjadKeU1iH33wSK34YP9WH63KdZuC4tojzOz2I26J910stp0WG8TqmMwI6n4bzPtOn0euyzvLhDfwanrNlG7Zb0Pqys328Xr94ThDvJpvP9eMdbT4vpAtrzvdp2jWfday5gDXiZf7i612JvvC6vgtDGv+6vos68OQmKtfFIY3urGQ09Y9LlK6Q1N2AuEsNTncFsvGyEFdt4Jf3bBqzLg/wWD6uiysCnFyLfGUAN8eGqwKcue/i6gBnrlO+xseF155fq/neZY2qkPleF+bVfoPrQ5ze73GD5NbN5DP+1ZvI3xjgg2vabwrwwXHtZubF8kBcWlqtl9sVSvsWgxPfZRmuOEyT/2+V/HCN3Uj4bQpvjzCB6d3OONU/dBD4hpjbEvuoytjW7lA87JJqRag4/TulrtzjwuaUutzbdZeJjzQQu1thsGPLayF2j8L0evp7GeOxDfKrgRUjyN0X4rZaUo559ytOdOXhzZ0SjbUPSNztKZs2Pmjg8nz9EGO43FQYzzY9HMRFQsw9EuJGVFkeNTkuuLT3MT/XbnCcx324sw2awdwTAc7ca/BkgBPlkvGeCnCi1Uk7nvZx+pzwjImLxDitZ4O44YvnQpz2xfM+rgZTESGgvF7wcfr8+aKJ47mB8Jd8uD6vvuzDPfiqFeX9Sgi3S61tiHvV5HiMlza/5uO2gu/tjWwrudclVx2m0QdX0BL3RoirCRK5N5njNgrWbOfINvkWc1DUpsf18LYPg4ZSpbb6DuP0Iu16SdbnuwbOeWDa7zGOxWft+xIDK3vEpJDxDyTeKo72DOt5zocmDnGk3R8xzi5C7ceI6b2OUvuJgUPKiH2qMTXefobYBtmkvV4CdsHBom25tLmMfvw8xGM2eD79ws+pBeiVCsT26Hz6ZbSmtJmwoow6tOOraN2I7A9fh3gsAtrxTYjDs9XWRVckQPG/VZrhCnz4DKq57cl5w3eSk2vC7dZmsOWlLM+F30ueTG83mw7MdTavD7NtP2ies9Xt/kfFiVFdJkzcT5qDD40UG+KEI9vAz5IjS0VuiFtjMS5OUE20AtMaS+Htmi4h1dPYglunsIb85GLvgM1bl/V+lK6OGr0fb5yOGj3PHNenWSu9Qca/j3G8MK/mBeOHOdVOJwAOv2cqPugHJ/UE7JBg+5GfMJLX+3gmiuT1GDix4HuNLdls0ySMjwwvPSa4t3pS5OR2ZkpnMsTMrdWknRxxf9pTEFaPSntK5OQWasKmIsxzcHs0YVMLLLM6bK7Uc6BpEIPKSaVyWEviM3+Op/bnTBvg+RuGyE0X4vS5b/ogV3O2UXudg1yjWW/VS/UK8zMGefH5QXEhy/6fyeA=
*/