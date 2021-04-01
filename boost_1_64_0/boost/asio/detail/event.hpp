//
// detail/event.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_EVENT_HPP
#define BOOST_ASIO_DETAIL_EVENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
# include <boost/asio/detail/null_event.hpp>
#elif defined(BOOST_ASIO_WINDOWS)
# include <boost/asio/detail/win_event.hpp>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_event.hpp>
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
# include <boost/asio/detail/std_event.hpp>
#else
# error Only Windows, POSIX and std::condition_variable are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS)
typedef null_event event;
#elif defined(BOOST_ASIO_WINDOWS)
typedef win_event event;
#elif defined(BOOST_ASIO_HAS_PTHREADS)
typedef posix_event event;
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
typedef std_event event;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_EVENT_HPP

/* event.hpp
Ufdmt2ocKwQBkt/dNk6tZ4HG8PkYkatAlcslU6MgSarBvznPXZnGwmH0TRLX9k4cxDE+GllCNRzf8eQS3m0yYosKaXpm2jSxa3Ogu3+xiWip0NwGtav2Wqp6aoN0hpQ19IXeEsD1UMzJ1Hb2Gf3rVAwdvR3cSh6TUKHy9XTvh7L58Y4byIrx2g7CrhhfoTZ8STe5zDjwDNyG3UwFihcnV6y1OhqQG2AON0I1FaI+LmIDn/Fki37WKNzu8PAoWhP5qVM5LSMmtIyg6vgdPJZe88NakZnqs017sBdUtn9N8hUU9tuLPIRrctsgfWTSw63CtAPlbTSmOiC5JLLKgoKc6r5FxRWC9n6X/VO7CMMEoB6LmVQSmDbOZsX38RqpCMDyoukFQqmVpMKjDeEaZenFAPdDJDTU+Vh7mwdcxGPsefPqBAviOQvkSSgdKEazmWTh8M4jD7W3l8y4KBEcrBX4y7/yjGxhFs6ZdCIWhCxVFhfKoN7LenM3C1SUrD4YN6umSU3YhaGoCfY5bbOqhfn/xEkg7UZAY0L+qj6A8s2FbWnDpFRm76MpOxZN9Q==
*/