//
// detail/atomic_count.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_ATOMIC_COUNT_HPP
#define BOOST_ASIO_DETAIL_ATOMIC_COUNT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
// Nothing to include.
#elif defined(BOOST_ASIO_HAS_STD_ATOMIC)
# include <atomic>
#else // defined(BOOST_ASIO_HAS_STD_ATOMIC)
# include <boost/detail/atomic_count.hpp>
#endif // defined(BOOST_ASIO_HAS_STD_ATOMIC)

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS)
typedef long atomic_count;
inline void increment(atomic_count& a, long b) { a += b; }
#elif defined(BOOST_ASIO_HAS_STD_ATOMIC)
typedef std::atomic<long> atomic_count;
inline void increment(atomic_count& a, long b) { a += b; }
#else // defined(BOOST_ASIO_HAS_STD_ATOMIC)
typedef boost::detail::atomic_count atomic_count;
inline void increment(atomic_count& a, long b) { while (b > 0) ++a, --b; }
#endif // defined(BOOST_ASIO_HAS_STD_ATOMIC)

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_ATOMIC_COUNT_HPP

/* atomic_count.hpp
dnzltIrPIHgyXh1TdTAinH5ahDR6SNFI7X5cC+IEhjIHKKSn5LKo89XeTVhuxQnPhUhMucwzL4v8QFn0v5GnRv5rpIyzD2211sI8pSllKNxBOLpn/xT4UIBdbJmEYJjD/vlRqjaBB8HEIEHC9D+GcJAPSaGMJISM023e7GFlY/k6U7OEzhSy79gWwSQFu8oazms6AMCCQ3Vce7seTppX0RSnuxQa5Rjk7I/ZxcUnMxzxYV++ObQqbIvN/kCL/2JFmdk1wa9C1oZyVaB5qW149Nn8j1ATHEcrOaP/xc2nrmtecZjFUk1OIgIgV5Anh9Uv7nOh6iIik7hKIPpAncA4M+ba2LFvtFOtKZPVyrtndEaWh8l6BZjqCLGIzm4hJ3k32HsP+8YksIJw627r2dZfy5eBFxQ6/uSEjW24FWG8z3oqkgE9Py25YiriK330//LX2PExaBqKvB3Eot4x4gvFo7xs70Iw+1714owbxbs5TrhP5YNqer1otLV0NDtnVpAnjCdM9gLs28ND79wWku75sYD9VaFNYRgnPwmUQlajMAmSklpfzPwFJMKRGw==
*/