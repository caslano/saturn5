
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_CONVERT_H
#define BOOST_FIBERS_DETAIL_CONVERT_H

#include <chrono>
#include <memory>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

inline
std::chrono::steady_clock::time_point convert(
        std::chrono::steady_clock::time_point const& timeout_time) noexcept {
    return timeout_time;
}

template< typename Clock, typename Duration >
std::chrono::steady_clock::time_point convert(
        std::chrono::time_point< Clock, Duration > const& timeout_time) {
    return std::chrono::steady_clock::now() + ( timeout_time - Clock::now() );
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_CONVERT_H

/* convert.hpp
9xZZ3fOO5Bppg606N8GwHd8yOfSAIMtuw/TpIXGBWfgXGUybk+Vh536rF9o68Q4lxHlfI2dj/3kxVp2iWaVpc5O996oSPIkwLX6o5pbuZfKogIx/3n+jbkOVwpeTNlZYIcvJqqppUdMFy4jhApqtCcuBut5NP3UKOBnOS1cKtwKsSbZ2ktJZhAYHNDWlp7kecsq0caHbxbEjI6MdsuZYOej7EahDpxozpCgqKAPg6OTZ9Gm7/4LMdtvqarrwzoo8J0fe55jGPzS4T9x0QpsGjPxe3BGYU71kkNn+zMUaVvmwn8py3Di9Cnv4iacj5vMRc7GR6JbiF5tx1OUfWflNF4JtbitcagCqpAlXbvgYbXj82BLR/ulKiKiAZt8lEcOiDqecEPXNlrPcqSHoytwqb57Xkv1zHNx4nDjN7aD4O1eIosou5nlDoH9Krl7GY6v3BjKa7MsbOWybwHmLeGfLF6a5C3DCj9Q/seqbPQNpchVewRAKwiFCbk0W/6MRXIHON91yntrRhiMGJkKKoXNeIcUD85RvkEKtjJDGy7rqyEP8T9mZaKJRFuY5ag==
*/